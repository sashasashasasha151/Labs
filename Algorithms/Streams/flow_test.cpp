#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int v;
int s , f , n;
vector<vector<int>> G, _G;
vector<int> parents;
vector<bool> used;

vector<int> get_path() {
    queue<int> que;
    used.assign(v, false);
    parents.assign(v, -1);

    que.push(s - 1);
    used[s - 1] = true;
    while (que.front() != f - 1 && !que.empty()) {
        for (int i = 0; i < v; ++i) {
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
    int k = f - 1;
    while (k != -1) {
        ph.push_back(k);
        k = parents[k];
    }
    reverse(ph.begin(), ph.end());
    return ph;
}

int main() {

    cin >> v >> n;
    s = 1;
    f = v;
    G.resize(v);
    _G.resize(v);
    for (int i = 0; i < v; ++i) {
        G[i].assign(v, 0);
        _G[i].assign(v, 0);
    }

    vector<bool> f_parents;
    f_parents.assign(v,false);

    for (int i = 0; i < n; ++i) {
        int l, r, c;
        cin >> l >> r >> c;
        G[l - 1][r - 1] = 0;
        G[r - 1][l - 1] = 0;
        _G[l - 1][r - 1] += c;
        _G[r - 1][l - 1] += c;
        if (r == f) {
            f_parents[l-1] = true;
        }
        if(l == f) {
            f_parents[r-1] = true;
        }
    }

    vector<int> path = get_path();
    while (path.size() != 1) {
//        for (int i = 0; i < path.size(); ++i) {
//            cout << path[i] << " ";
//        }
//        cout << endl;
        int min = 1000000;
        for (int i = 0; i < path.size() - 1; ++i) {
            if (_G[path[i]][path[i + 1]] < min && _G[path[i]][path[i + 1]]>0) {
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
        if(f_parents[i]) {
            sum += (G[i][f - 1] > 0) ? (G[i][f - 1] - G[f - 1][i]) : 0;
        }
    }
    cout << sum;

    return 0;
}