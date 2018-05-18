#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <map>

using namespace std;

int n, m;
int k, l;
int N;
int s, f;

vector<vector<int>> mapp;
vector<unordered_map<int, int>> G, _G;
vector<int> parents;
vector<bool> used;
vector<pair<int, int>> edges;
vector<bool> f_parents, L;
vector<string> prin;


void add_edge(int l1, int r1, int l2, int r2) {
    int n1f = (l1 - 1) * n + r1 - 1;
    int n1s = N + n1f;
    int n2f = (l2 - 1) * n + r2 - 1;
    int n2s = N + n2f;

    if (n1f == f) {
        f_parents[n2s] = true;
    }
    if (n2f == f) {
        f_parents[n1s] = true;
    }

    _G[n1f][n1s] = (mapp[l1][r1] == 2) ? 1 : 20000;
    _G[n1s][n1f] = 0;

    _G[n2f][n2s] = (mapp[l2][r2] == 2) ? 1 : 20000;
    _G[n2s][n2f] = 0;

    _G[n1s][n2f] = 20000;
    _G[n2f][n1s] = 0;

    _G[n2s][n1f] = 20000;
    _G[n1f][n2s] = 0;

    G[n1f][n1s] = 0;
    G[n1s][n1f] = 0;

    G[n2f][n2s] = 0;
    G[n2s][n2f] = 0;

    G[n1s][n2f] = 0;
    G[n2f][n1s] = 0;

    G[n2s][n1f] = 0;
    G[n1f][n2s] = 0;
}

void dfs(int k) {
    L[k] = true;
    for (auto it:_G[k]) {
        if (it.second - G[k][it.first] > 0 && !L[it.first]) {
            dfs(it.first);
        }
    }
}

vector<int> get_path() {
    queue<int> que;
    used.assign(N * 2, false);
    parents.assign(N * 2, -1);

    que.push(s);
    used[s] = true;
    while (que.front() != f && !que.empty()) {
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
    int k = f;
    while (k != -1) {
        ph.push_back(k);
        k = parents[k];
    }
    //reverse(ph.begin(), ph.end());
    return ph;
}

int main() {
    cin >> m >> n;
    mapp.resize(m + 2);
    for (int i = 0; i < m + 2; ++i) {
        mapp[i].assign(n + 2, 0);
    }
//    cin >> k >> l;
//    for (int i = 0; i < k; ++i) {
//        int x, y;
//        cin >> x >> y;
//        mapp[x][y] = 0;
//    }
//    for (int i = 0; i < l; ++i) {
//        int x, y;
//        cin >> x >> y;
//        mapp[x][y] = 2;
//    }
//    mapp[0].assign(n + 2, 0);
//    mapp[m + 1].assign(n + 2, 0);
//    for (int i = 0; i < m + 2; ++i) {
//        mapp[i][0] = 0;
//        mapp[i][n + 1] = 0;
//    }

    N = n * m;
    G.resize(N * 2);
    _G.resize(N * 2);
    f_parents.assign(N * 2, false);
    L.assign(N * 2, false);

    for (int i = 0; i < m; ++i) {
        string ss;
        cin >> ss;
        prin.push_back(ss);
        for (int j = 0; j < ss.length(); ++j) {
            if (ss[j] == '.') {
                mapp[i + 1][j + 1] = 2;
            }
            if (ss[j] == '-') {
                mapp[i + 1][j + 1] = 1;
            }
            if (ss[j] == 'A') {
                s = N + (i) * n + j;
                mapp[i + 1][j + 1] = 1;
            }
            if (ss[j] == 'B') {
                f = (i) * n + j;
                mapp[i + 1][j + 1] = 1;
            }
        }
    }

//    for (int i = 0; i <= m+1; ++i) {
//        for (int j = 0; j <= n+1; ++j) {
//            cout << mapp[i][j] << " " ;
//        }
//        cout << "\n";
//    }




//    int a, b;
//    cin >> a >> b;
//    s = N + (a - 1) * n + b - 1;
//    cin >> a >> b;
//    f = (a - 1) * n + b - 1;

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (mapp[i][j] == 0) {
                continue;
            }
            if (mapp[i + 1][j] != 0) {
                add_edge(i, j, i + 1, j);
            }
            if (mapp[i][j + 1] != 0) {
                add_edge(i, j, i, j + 1);
            }
        }
    }

    vector<int> path = get_path();
    while (path.size() != 1) {
        int min = 10000000;
        for (int i = path.size() - 1; i > 0; --i) {
            if (_G[path[i]][path[i - 1]] - G[path[i]][path[i - 1]] < min) {
                min = _G[path[i]][path[i - 1]] - G[path[i]][path[i - 1]];
            }
        }
        for (int i = path.size() - 1; i > 0; --i) {
            G[path[i]][path[i - 1]] += min;
            G[path[i - 1]][path[i]] -= min;
        }
        path = get_path();
    }

    int sum = 0;
    for (int i = 0; i < f_parents.size(); ++i) {
        if (f_parents[i]) {
            sum += G[i][f] > 0 ? G[i][f] : 0;
        }
    }

    if (sum >= 15000) {
        cout << -1;
        return 0;
    }

    cout << sum << "\n";

    dfs(s);
    for (int i = 0; i < N; ++i) {
        if (L[i] && !L[i + N] && mapp[i / n + 1][i % n + 1] == 2) {
            prin[i / n][i % n] = '+';
        }
    }
//    for (int i = 0; i < prin.size(); ++i) {
//        cout << prin[i] << "\n";
//    }
}

/*
5 5
3 8
3 2
2 4
3 4
3 1
1 3
2 3
3 3
4 3
5 3
1 4
1 5
2 1
5 5
 */
