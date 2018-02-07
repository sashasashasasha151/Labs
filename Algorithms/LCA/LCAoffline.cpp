#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>

using namespace std;

const int V = 500001;
vector<pair<int, int>> pairs;
vector<pair<int, int>> questions[V];
vector<int> G[V];
int parent[V];
int anc[V];
int rank[500001];
bool visit[V];

int find_set(int k) {
    if (parent[k] == k) {
        return k;
    } else {
        return parent[k] = find_set(parent[k]);
    }
}

void unite(int l, int r, int set) {
    l = find_set(l);
    r = find_set(r);
    if (l != r) {
        parent[r] = l;
        anc[r] = set;
    }
}

void dfs(int k) {
    parent[k] = k;
    anc[k] = k;
    visit[k] = true;
    for (int i = 0; i < G[k].size(); ++i) {
        if (!visit[G[k][i]]) {
            dfs(G[k][i]);
            unite(k, G[k][i], k);
        }
    }
    for (int i = 0; i < questions[k].size(); ++i) {
        if (visit[questions[k][i].first]) {
            questions[k][i].second = anc[find_set(questions[k][i].first)];
        }
    }
}

int main() {
    ifstream cin("lca.in");
    ofstream cout("lca.out");
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        string s;
        int l, r;
        cin >> s >> l >> r;
        if (s == "ADD") {
            G[l].push_back(r);
            G[r].push_back(l);
        } else {
            pairs.push_back({l, r});
            questions[l].push_back({r, -1});
            questions[r].push_back({l, -1});
        }
    }
    dfs(1);

    /*for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < questions[i].size(); ++j) {
            cout << questions[i][j].second << " ";
        }
        cout << endl;
    }*/

    vector<int> a;
    for (int i = pairs.size()-1; i >= 0; --i) {
        if(questions[pairs[i].first].back().second == -1) {
            a.push_back(questions[pairs[i].second].back().second);
            questions[pairs[i].first].pop_back();
            questions[pairs[i].second].pop_back();
        } else {
            a.push_back(questions[pairs[i].first].back().second);
            questions[pairs[i].first].pop_back();
            questions[pairs[i].second].pop_back();
        }
    }
    for (int i = a.size()-1; i >= 0; --i) {
        cout << a[i] << endl;
    }
    return 0;
}

