#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <fstream>

using namespace std;

int n, m, f, s;
vector<unordered_map<int, int>> G, _G;
vector<int> parents;
vector<bool> used;
vector<int> first;

vector<int> get_path() {
    queue<int> que;
    used.assign(n, false);
    parents.assign(n, -1);

    que.push(s - 1);
    used[s - 1] = true;
    while (que.front() != f - 1 && !que.empty()) {
        for (auto it:_G[que.front()]) {
            if (used[it.first]) {
                continue;
            }
            if (it.second - G[que.front()][it.first] > 0) {
                que.push(it.first);
                parents[it.first] = que.front();
                used[it.first] = true;
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

bool get_spath(int k) {
    first.push_back(k);
    if (k == f - 1) {
        return true;
    }
    for (auto it:G[k]) {
        if (it.second > 0) {
            if(get_spath(it.first)) {
                return true;
            };
        }
    }
    return false;
}


int main() {
    ifstream cin("snails.in");
    ofstream cout("snails.out");
    cin >> n >> m >> s >> f;
    G.resize(n);
    _G.resize(n);

    vector<bool> f_parents;
    f_parents.assign(n, false);

    for (int i = 0; i < m; ++i) {
        int l, r;
        cin >> l >> r;
        G[l - 1][r - 1] = 0;
        G[r - 1][l - 1] = 0;
        _G[l - 1][r - 1] += 1;
        _G[r - 1][l - 1] = 0;
        if (r == f) {
            f_parents[l - 1] = true;
        }
        if (l == f) {
            f_parents[r - 1] = true;
        }
    }

    bool y = false;

    vector<int> path = get_path();
    while (path.size() != 1) {
        int min = 1000000;
        for (int i = 0; i < path.size() - 1; ++i) {
            if (_G[path[i]][path[i + 1]] - G[path[i]][path[i + 1]] < min) {
                min = _G[path[i]][path[i + 1]] - G[path[i]][path[i + 1]];
            }
        }
        for (int i = 0; i < path.size() - 1; ++i) {
            G[path[i]][path[i + 1]] += min;
            G[path[i + 1]][path[i]] -= min;
        }

        int sum = 0;
        for (int i = 0; i < f_parents.size(); ++i) {
            if (f_parents[i]) {
                sum += G[i][f - 1] > 0 ? G[i][f - 1] : 0;
            }
        }
        if (sum > 1) {
            y = true;
            break;
        }

        path = get_path();
    }

    if (!y) {
        cout << "NO";
        return 0;
    }

    get_spath(s-1);
    cout << "YES" << "\n";
    for (int i = 0; i < first.size()-1; ++i) {
        cout << first[i] + 1 << " ";
        G[first[i]][first[i + 1]] -= 1;
    }
    cout << first[first.size()-1]+1;
    cout << "\n";
    first.clear();
    get_spath(s-1);
    for (int i = 0; i < first.size(); ++i) {
        cout << first[i] + 1 << " ";
    }
    return 0;
}

/*
13 15
 1 2 1
 1 3 1
 2 5 1
 3 4 1
 4 5 1
 2 6 1
 6 7 1
 7 8 1
 8 11 1
 5 9 1
 9 11 1
 11 13 1
 9 10 1
 10 12 1
 12 13 1
 */