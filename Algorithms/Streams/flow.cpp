#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <fstream>

using namespace std;

int n, m;
vector<vector<int>> G, _G;
vector<int> parents;
vector<bool> used;
vector<pair<pair<int, int>, int>> edges;

vector<int> get_path() {
    queue<int> que;
    used.assign(n, false);
    parents.assign(n, -1);

    que.push(0);
    used[0] = true;
    while (que.front() != n - 1 && !que.empty()) {
        for (int i = 0; i < n; ++i) {
            if (used[i]) {
                continue;
            }
            if (_G[que.front()][i] > 0) {
                que.push(i);
                parents[i] = que.front();
                used[i] = true;
            }
        }
        que.pop();
    }

    vector<int> ph;
    int k = n - 1;
    while (k != -1) {
        ph.push_back(k);
        k = parents[k];
    }
    reverse(ph.begin(), ph.end());
    return ph;
}

int main() {
//    ifstream cin("flow.in");
//    ofstream cout("flow.out");
    cin >> n;
    cin >> m;
    G.resize(n);
    _G.resize(n);
    for (int i = 0; i < n; ++i) {
        G[i].assign(n, 0);
        _G[i].assign(n, 0);
    }

    vector<bool> f_parents;
    f_parents.assign(n, false);

    for (int i = 0; i < m; ++i) {
        int l, r, c;
        cin >> l >> r >> c;
        edges.push_back({{l - 1, r - 1}, c});
        G[l - 1][r - 1] = 0;
        G[r - 1][l - 1] = 0;
        _G[l - 1][r - 1] += c;
        _G[r - 1][l - 1] += c;
        if (r == n) {
            f_parents[l - 1] = true;
        }
        if (l == n) {
            f_parents[r - 1] = true;
        }
    }

    vector<int> path = get_path();
    while (path.size() != 1) {
        int min = 1000000;
        for (int i = 0; i < path.size() - 1; ++i) {
            if (_G[path[i]][path[i + 1]] < min && _G[path[i]][path[i + 1]] > 0) {
                min = _G[path[i]][path[i + 1]];
            }
        }
        for (int i = 0; i < path.size() - 1; ++i) {
            _G[path[i]][path[i + 1]] -= min;
            G[path[i]][path[i + 1]] += min;
        }
        path = get_path();
    }

    int sum = 0;
    for (int i = 0; i < f_parents.size(); ++i) {
        if (f_parents[i]) {
            sum += (G[i][n - 1] > 0) ? (G[i][n - 1] - G[n - 1][i]) : 0;
        }
    }
    cout << sum << "\n";

    for (int i = 0; i < edges.size(); ++i) {
        int l = edges[i].first.first;
        int r = edges[i].first.second;
        int c = edges[i].second;
        if (G[l][r] == 0 && G[r][l] == 0) {
            cout << 0 << "\n";
            continue;
        }
        if (G[l][r] != 0) {
            cout << min(c, G[l][r]) << "\n";
            G[l][r] -= min(G[l][r], c);
            continue;
        } else {
            cout << -min(c, G[r][l]) << "\n";
            G[r][l] -= min(G[r][l], c);
            continue;
        }
    }

    return 0;
}