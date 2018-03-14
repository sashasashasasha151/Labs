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

vector<bool> L;

void dfs(int k) {
    L[k] = true;
    for (int i = 0; i < _G.size(); ++i) {
        if(_G[k][i]>0 && !L[i]) {
            dfs(i);
        }
    }
}
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
    ifstream cin("cut.in");
    ofstream cout("cut.out");
    cin >> n >> m;
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

    L.assign(n,false);
    dfs(0);
    vector<int> answ;
    for (int i = 0; i < edges.size(); ++i) {
        if((L[edges[i].first.first] && !L[edges[i].first.second]) || (L[edges[i].first.second] && !L[edges[i].first.first])) {
            answ.push_back(i+1);
        }
    }

    cout << answ.size() << " " << sum << "\n";
    for (int i = 0; i < answ.size(); ++i) {
        cout << answ[i] << " ";
    }

    return 0;
}