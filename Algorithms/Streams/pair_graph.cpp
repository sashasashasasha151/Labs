#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> G;
vector<int> _G;
vector<int> used;

bool fn(int k) {
    if (used[k]) {
        return false;
    }
    used[k] = true;
    for (int i = 0; i < G[k].size(); ++i) {
        if (_G[G[k][i]] == -1 || fn(_G[G[k][i]])) {
            _G[G[k][i]] = k;
            return true;
        }
    }
    return false;
}

int main() {
    int n, m;
    cin >> n >> m;
    G.resize(n);
    for (int i = 0; i < n; ++i) {
        while (true) {
            int r;
            cin >> r;
            if (r == 0) {
                break;
            }
            G[i].push_back(r - 1);
        }
    }

    _G.assign(m, -1);
    for (int i = 0; i < n; ++i) {
        used.assign(n, false);
        fn(i);
    }

    vector<pair<int, int>> pr;

    for (int i = 0; i < _G.size(); ++i) {
        if (_G[i] != -1) {
            pr.push_back({i, _G[i]});
        }
    }

    cout << pr.size() << endl;

    for (int i = 0; i < pr.size(); ++i) {
        cout << pr[i].second + 1 << " " << pr[i].first + 1 << "\n";
    }

    return 0;
}

