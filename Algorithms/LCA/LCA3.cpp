#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>

using namespace std;

int **dp;
vector<vector<int>> G;
int *p, *d, *r;
pair<int, int> *roots;
int deep = 0, n, power, max_deep = 0;

void dfs(int k) {
    if (G[k].size() == 0) {
        max_deep = max(max_deep, deep);
    }
    deep++;
    for (int i = 0; i < G[k].size(); ++i) {
        if (G[k][i] == p[k]) {
            continue;
        }
        d[G[k][i]] = deep;
        r[G[k][i]] = r[k];
        dfs(G[k][i]);
    }
    deep--;
}

void pre() {
    for (int i = 0; i < n; ++i) {
        dp[i][0] = p[i];
    }

    for (int j = 1; j < power; ++j) {
        for (int i = 0; i < n; ++i) {
            dp[i][j] = dp[dp[i][j - 1]][j - 1];
        }
    }
}

int lca(int l, int rr) {
    if (r[l] != r[rr]) {
        return -1;
    }
    if (d[l] < d[rr]) {
        swap(l, rr);
    }
    for (int i = power - 1; i >= 0; --i) {
        if (d[dp[l][i]] >= d[rr]) {
            l = dp[l][i];
            continue;
        }
    }
    if (l == rr) {
        return l;
    }
    for (int i = power - 1; i >= 0; --i) {
        if (dp[l][i] != dp[rr][i]) {
            l = dp[l][i];
            rr = dp[rr][i];
        }
    }
    return p[rr];
}

void make_dfs(int k, int g) {
    for (int i = 0; i < G[k].size(); ++i) {
        int p = (int) (log(d[G[k][i]]) / log(2) + 1);
        for (int j = p; j < power; ++j) {
            dp[G[k][i]][j] = dp[dp[G[k][i]][j-1]][j - 1];
        }
        r[G[k][i]] = r[g];
        d[G[k][i]] = d[G[k][i]] + d[g] + 1;
        make_dfs(G[k][i], g);
    }
}

void make(int v, int u) {
    if(r[v]==r[u]){
        return;
    }
    G[v].push_back(u);
    p[u] = v;
    r[u] = r[v];
    d[u] = d[u] + d[v] + 1;
    dp[u][0] = v;
    for (int i = 1; i < power; ++i) {
        dp[u][i] = dp[dp[u][i-1]][i - 1];
    }
    make_dfs(u, v);
}

int main() {
    ifstream cin("lca3.in");
    ofstream cout("lca3.out");

    cin >> n;

    G.resize(n);

    power = (int) (log(n) / log(2) + 1);
    dp = new int *[n];
    for (int i = 0; i < n; ++i) {
        dp[i] = new int[power];
    }

    p = new int[n];
    fill(p, p + n, -1);

    d = new int[n];
    r = new int[n];
    roots = new pair<int, int>[n];
    fill(roots, roots + n, make_pair(-1, -1));

    for (int i = 0; i < n; ++i) {
        int u;
        cin >> u;
        if (u == 0) {
            roots[i].first = 1;
            continue;
        }
        G[u - 1].push_back(i);
        p[i] = u - 1;
    }

    for (int i = 0; i < n; ++i) {
        if (roots[i].first == 1) {
            d[i] = 0;
            p[i] = i;
            r[i] = i;
            deep = 0;
            max_deep = 0;
            dfs(i);
            roots[i].second = max_deep;
        }
    }

    pre();

    /*for (int i = 0; i < n; ++i) {
        for (int j = 0; j < power; ++j) {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }*/
    int k;
    cin >> k;
    int ans = 0;
    for (int i = 0; i < k; ++i) {
        int f, l, r;
        cin >> f >> l >> r;
        l = (l - 1 + ans) % n + 1 - 1;
        r = (r - 1 + ans) % n + 1 - 1;
        if (f == 1) {
            make(r, l);
        } else {
            ans = lca(l, r) + 1;
            cout << ans << endl;
        }
    }

    return 0;
}

