#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>

using namespace std;

struct Edge {
    int to_vertex;
    bool heavy;
};

struct Vertex {
    int parent;
    int deep;
    int sons = 1;
    int tree;
    int height;
    int tree_pos;
};

Vertex *vertexs;
int **dp;
vector<vector<Edge>> G;
vector<vector<int>> max_trees, trees;
int deep = 0, n, power;

int dfs(int k) {
    deep++;
    for (int i = 0; i < G[k].size(); ++i) {
        if (G[k][i].to_vertex == vertexs[k].parent) {
            continue;
        }
        vertexs[G[k][i].to_vertex].deep = deep;
        vertexs[G[k][i].to_vertex].parent = k;
        vertexs[k].sons += dfs(G[k][i].to_vertex);
    }
    deep--;
    return vertexs[k].sons;
}

void pre() {
    for (int i = 0; i < n; ++i) {
        dp[i][0] = vertexs[i].parent;
    }

    for (int j = 1; j < power; ++j) {
        for (int i = 0; i < n; ++i) {
            dp[i][j] = dp[dp[i][j - 1]][j - 1];
        }
    }
}

int lca(int l, int r) {
    if (vertexs[l].deep < vertexs[r].deep) {
        swap(l, r);
    }
    for (int i = power - 1; i >= 0; --i) {
        if (vertexs[dp[l][i]].deep >= vertexs[r].deep) {
            l = dp[l][i];
            continue;
        }
    }
    if (l == r) {
        return l;
    }
    for (int i = power - 1; i >= 0; --i) {
        if (dp[l][i] != dp[r][i]) {
            l = dp[l][i];
            r = dp[r][i];
        }
    }
    return vertexs[r].parent;
}

void is_heavy(int k) {
    for (int i = 0; i < G[k].size(); ++i) {
        if (G[k][i].to_vertex == vertexs[k].parent) {
            continue;
        }
        double help = (double )vertexs[k].sons / 2;
        if (vertexs[G[k][i].to_vertex].sons >= help) {
            G[k][i].heavy = true;
        }
        is_heavy(G[k][i].to_vertex);
    }
}

void make_trees(int k, bool w) {
    bool key = false;
    for (int i = 0; i < G[k].size(); ++i) {
        if (G[k][i].to_vertex == vertexs[k].parent) {
            continue;
        }
        if (G[k][i].heavy == w && w) {
            trees[vertexs[k].tree].push_back(G[k][i].to_vertex);
            vertexs[G[k][i].to_vertex].tree = vertexs[k].tree;
            vertexs[G[k][i].to_vertex].tree_pos = trees[vertexs[k].tree].size() - 1;
            make_trees(G[k][i].to_vertex, G[k][i].heavy);
            continue;
        }
        if (G[k][i].heavy == w && !key) {
            trees[vertexs[k].tree].push_back(G[k][i].to_vertex);
            vertexs[G[k][i].to_vertex].tree = vertexs[k].tree;
            vertexs[G[k][i].to_vertex].tree_pos = trees[vertexs[k].tree].size() - 1;
            key = true;
        } else {
            vector<int> vec = {G[k][i].to_vertex};
            vertexs[G[k][i].to_vertex].tree_pos = 0;
            trees.push_back(vec);
            vertexs[G[k][i].to_vertex].tree = trees.size() - 1;
        }
        make_trees(G[k][i].to_vertex, G[k][i].heavy);
    }
}

void build(int cur, int v, int l, int r) {
    if (l == r)
        max_trees[cur][v] = vertexs[trees[cur][l]].height;
    else {
        int m = (l + r) / 2;
        build(cur, v * 2, l, m);
        build(cur, v * 2 + 1, m + 1, r);
        max_trees[cur][v] = max(max_trees[cur][v * 2], max_trees[cur][v * 2 + 1]);
    }
}

int maxi(int cur, int v, int ll, int rr, int l, int r) {
    if (l > r)
        return 0;
    if (l == ll && r == rr)
        return max_trees[cur][v];
    int tm = (ll + rr) / 2;
    return max(maxi(cur, v * 2, ll, tm, l, min(r, tm)), maxi(cur, v * 2 + 1, tm + 1, rr, max(l, tm + 1), r));
}

void update(int cur, int v, int ll, int rr, int pos, int set) {
    if (ll == rr)
        max_trees[cur][v] = set;
    else {
        int tm = (ll + rr) / 2;
        if (pos <= tm)
            update(cur, v * 2, ll, tm, pos, set);
        else
            update(cur, v * 2 + 1, tm + 1, rr, pos, set);
        max_trees[cur][v] = max(max_trees[cur][v * 2], max_trees[cur][v * 2 + 1]);
    }
}

int main() {

    ifstream cin("mail.in");
    ofstream cout("mail.out");

    cin >> n;

    G.resize(n);

    power = (int) (log(n) / log(2) + 1);

    dp = new int *[n];
    for (int i = 0; i < n; ++i) {
        dp[i] = new int[power];
    }

    vertexs = new Vertex[n];

    for (int i = 0; i < n; ++i) {
        cin >> vertexs[i].height;
    }

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        G[u - 1].push_back({v - 1, false});
        G[v - 1].push_back({u - 1, false});
    }

    vertexs[0].parent = 0;
    vertexs[0].deep = 0;
    vertexs[0].tree = 0;
    vertexs[0].tree_pos = 0;
    vector<int> vec = {0};
    trees.push_back(vec);

    int unused = dfs(0);

    pre();

    is_heavy(0);

    make_trees(0, false);

    for (int i = 0; i < trees.size(); ++i) {
        vector<int> vvv;
        vvv.assign(trees[i].size() * 5,-10);
        max_trees.push_back(vvv);
    }

    for (int i = 0; i < max_trees.size(); ++i) {
        build(i, 1, 0, trees[i].size() - 1);
    }

    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        char c;
        int l, r;
        cin >> c >> l >> r;
        l--;
        r--;
        if (c == '!') {
            int cur_tree = vertexs[l].tree;
            update(cur_tree, 1, 0, trees[cur_tree].size() - 1, vertexs[l].tree_pos, r + 1);
        } else {
            int maximum = -10;
            int common_parrent = lca(l, r);
            while (vertexs[l].tree != vertexs[common_parrent].tree) {
                int cur_tree = vertexs[l].tree;
                maximum = max(maximum, maxi(cur_tree, 1, 0, trees[cur_tree].size() - 1, 0, vertexs[l].tree_pos));
                l = vertexs[trees[cur_tree][0]].parent;
            }
            maximum = max(maximum, maxi(vertexs[l].tree, 1, 0, trees[vertexs[l].tree].size() - 1, vertexs[common_parrent].tree_pos, vertexs[l].tree_pos));
            while (vertexs[r].tree != vertexs[common_parrent].tree ) {
                int cur_tree = vertexs[r].tree;
                maximum = max(maximum, maxi(cur_tree, 1, 0, trees[cur_tree].size() - 1, 0, vertexs[r].tree_pos));
                r = vertexs[trees[cur_tree][0]].parent;
            }
            maximum = max(maximum, maxi(vertexs[r].tree, 1, 0, trees[vertexs[r].tree].size() - 1, vertexs[common_parrent].tree_pos, vertexs[r].tree_pos));
            cout << maximum << endl;
        }
    }
    return 0;
}

