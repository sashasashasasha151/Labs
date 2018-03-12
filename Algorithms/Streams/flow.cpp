#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int s, f, n;
vector<vector<int>> G, _G;
vector<int> parents, f_parents;
vector<bool> used;

vector<int> get_path() {
    queue<int> que;
    used.assign(n, false);
    parents.assign(n, -1);

    que.push(s - 1);
    used[s - 1] = true;
    while (que.front() != f - 1 || !que.empty()) {
        for (int i = 0; i < n; ++i) {
            if (used[i]) {
                continue;
            }
            if (_G[que.front()][i] > 0) {
                que.push(i);
                parents[i] = que.front();
            }
        }
        que.pop();
    }

    vector<int> ph;
    ph.push_back(f - 1);
    int k = f - 1;
    while (k != -1) {
        ph.push_back(k);
        k = parents[k];
    }
    reverse(ph.begin(), ph.end());
    return ph;
}

int main() {
    cin >> s >> f >> n;
    G.resize(n);
    _G.resize(n);
    for (int i = 0; i < n; ++i) {
        G[i].assign(n, -100000);
        _G[i].resize(n, -100000);
    }

    for (int i = 0; i < n; ++i) {
        int l, r, c;
        cin >> l >> r >> c;
        G[l - 1][r - 1] = 0;
        G[r - 1][l - 1] = 0;
        _G[l - 1][r - 1] = c;
        _G[r - 1][l - 1] = c;
        if (r == f) {
            f_parents.push_back(r);
        }
    }

    vector<int> path = get_path();
    while (path.size() != 0) {
        int min = 1000000;
        for (int i = 0; i < path.size() - 1; ++i) {
            if (_G[path[i]][path[i + 1]] < min) {
                min = _G[path[i]][path[i + 1]];
            }
        }
        for (int i = 0; i < path.size() - 1; ++i) {
            _G[path[i]][path[i + 1]] -= min;
            _G[path[i + 1]][path[i]] += min;
            G[path[i]][path[i + 1]] += min;
            G[path[i + 1]][path[i]] -= min;
        }
        path = get_path();
    }

    int sum = 0;
    for (int i = 0; i < f_parents.size(); ++i) {
        sum += G[f_parents[i]][f - 1];
    }
    cout << sum;

    return 0;
}

