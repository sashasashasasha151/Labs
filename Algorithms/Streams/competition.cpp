#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

int N;

vector<string> table;
vector<int> c_in, c_out;

int n;
vector<pair<int, int>> edges;

vector<vector<long long int>> G, _G;
vector<long long int> parents;
vector<bool> used;

vector<long long int> get_path() {
    queue<long long int> que;
    used.assign(n, false);
    parents.assign(n, -1);

    que.push(0);
    used[0] = true;
    while (que.front() != n - 1 && !que.empty()) {
        for (int it=0;it<_G[que.front()].size();++it) {
            if(used[it]) {
                continue;
            }
            if(_G[que.front()][it]-G[que.front()][it] > 0) {
                que.push(it);
                parents[it] = que.front();
                used[it] = true;
            }
        }
        que.pop();
    }

    vector<long long int> ph;
    long long int k = n - 1;
    while (k != -1) {
        ph.push_back(k);
        k = parents[k];
    }
    reverse(ph.begin(), ph.end());
    return ph;
}

int main() {
    cin >> N;
    for (int i = 0; i < N; ++i) {
        string s;
        cin >> s;
        table.push_back(s);
    }


    int sum = 0;

    for (int i = 0; i < N; ++i) {
        int k;
        cin >> k;
        sum += k;
        c_in.push_back(k);
        c_out.push_back(0);
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            switch (table[i][j]) {
                case 'W':
                    c_in[i] -= 3;
                    sum -= 3;
                    break;
                case 'w':
                    c_in[i] -= 2;
                    sum -= 2;
                    break;
                case 'l':
                    c_in[i] -= 1;
                    sum -= 1;
                    break;
                default:
                    break;
            }
        }
    }

    for (int i = 1; i < N; ++i) {
        for (int j = 0; j < i; ++j) {
            if (table[i][j] == '.') {
                c_out[i]++;
            }
        }
    }

    n = N + 2;

    G.resize(n);
    _G.resize(n);
    for (int i = 0; i < n; ++i) {
        G[i].assign(n, 0);
        _G[i].assign(n, 0);
    }

    vector<bool> f_parents;
    f_parents.assign(n, false);

    //////////////
    for (int i = 0; i < N; ++i) {
        int l, r, c;
        l = 1;
        r = i + 2;
        c = c_out[i] * 3;
        edges.emplace_back(l - 1, r - 1);
        _G[l - 1][r - 1] += c;
        if (r == n) {
            f_parents[l - 1] = true;
        }
        if (l == n) {
            f_parents[r - 1] = true;
        }
    }

    for (int i = 0; i < N; ++i) {
        int l, r, c;
        l = i + 2;
        r = n;
        c = c_in[i];
        edges.emplace_back(l - 1, r - 1);
        _G[l - 1][r - 1] += c;
        if (r == n) {
            f_parents[l - 1] = true;
        }
        if (l == n) {
            f_parents[r - 1] = true;
        }
    }

    for (int i = 1; i < N; ++i) {
        for (int j = 0; j < i; ++j) {
            if (table[i][j] == '.') {
                int l, r, c;
                l = i + 2;
                r = j + 2;
                c = 3;
                edges.emplace_back(l - 1, r - 1);
                _G[l - 1][r - 1] += c;
                if (r == n) {
                    f_parents[l - 1] = true;
                }
                if (l == n) {
                    f_parents[r - 1] = true;
                }
            }
        }
    }
    //////////////

    vector<long long int> path = get_path();
    while (path.size() != 1) {
        long long int min = 1000000;
        for (long long int i = 0; i < path.size() - 1; ++i) {
            if (_G[path[i]][path[i + 1]] - G[path[i]][path[i + 1]] < min) {
                min = _G[path[i]][path[i + 1]] - G[path[i]][path[i + 1]];
            }
        }
        for (long long int i = 0; i < path.size() - 1; ++i) {
            G[path[i]][path[i + 1]] += min;
            G[path[i + 1]][path[i]] -= min;
        }
        path = get_path();
    }

    for (int i = 1; i < N; ++i) {
        for (int j = 0; j < i; ++j) {
            if (table[i][j] == '.') {
                int l, r;
                l = i + 1;
                r = j + 1;
                // cout << G[l][r] - G[r][l] << " ";
                switch (G[l][r]) {
                    case 0:
                        table[i][j] = 'W';
                        table[j][i] = 'L';
                        break;
                    case 1:
                        table[i][j] = 'w';
                        table[j][i] = 'l';
                        break;
                    case 2:
                        table[i][j] = 'l';
                        table[j][i] = 'w';
                        break;
                    case 3:
                        table[i][j] = 'L';
                        table[j][i] = 'W';
                        break;
                    default:
                        break;
                }
            }
        }
        //cout << endl;
    }

//    for (int i = 0; i < f_parents.size(); ++i) {
//        if (f_parents[i]) {
//            sum -= (G[i][n - 1] > 0) ? (G[i][n - 1] - G[n - 1][i]) : 0;
//        }
//    }
//
//    int aaaaa[10];
//    if(sum!=0) {
//        aaaaa[100000000000000000] = 100000000000000000000;
//    }

    for (int i = 0; i < N; ++i) {
        cout << table[i] << "\n";
    }

    return 0;
}