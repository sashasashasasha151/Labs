#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>

using namespace std;

vector<vector<int>> G,dp;
vector<int> p, d;
int deep = 0, n, power;

void dfs(int k) {
    deep++;
    for (int i = 0; i < G[k].size(); ++i) {
        if (G[k][i] == p[k]) {
            continue;
        }
        d[G[k][i]] = deep;
        p[G[k][i]]=k;
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

int lca(int l, int r) {
    if (d[l] < d[r]) {
        swap(l, r);
    }
    for (int i = power - 1; i >= 0; --i) {
        if (d[dp[l][i]] >= d[r]) {
            l = dp[l][i];
            continue;
        }
    }
    if (l == r) {
        return l;
    }
    for (int i = power - 1; i >= 0; --i) {
        if (dp[l][i] != dp[r][i]) {
            l = dp[l][i];
            r = dp[r][i];
        }
    }
    return p[r];
}

int main() {
    ifstream cin("dynamic.in");
    ofstream cout("dynamic.out");
    for (;;) {

        cin >> n;

        if (n == 0) {
            return 0;
        }

        G.resize(n);

        power = (int) (log(n) / log(2) + 1);
        dp.resize(n);
        for (int i = 0; i < n; ++i) {
            dp[i].resize(power);
        }

        p.assign(n,-1);
        d.resize(n);

        for (int i = 0; i < n - 1; ++i) {
            int u, v;
            cin >> u >> v;
            G[u - 1].push_back(v - 1);
            G[v - 1].push_back(u - 1);
        }

        p[0] = 0;
        d[0] = 0;
        dfs(0);

        pre();

        int k;
        cin >> k;
        int root = 1;
        for (int i = 0; i < k; ++i) {
            char c;
            cin >> c;
            if (c == '!') {
                cin >> root;
            } else {
                int l, r;
                cin >> l >> r;
                int f, s, t;
                f = lca(root - 1, l - 1);
                s = lca(root - 1, r - 1);
                t = lca(l - 1, r - 1);
                if (f == s) {
                    cout << t + 1 << endl;
                } else {
                    if (f == t) {
                        cout << s + 1 << endl;
                    } else {
                        cout << f + 1 << endl;
                    }
                }
            }
        }
        d.clear();
        p.clear();
        for (int i = 0; i < G.size(); ++i) {
            G[i].clear();
        }
        G.clear();
        for (int i = 0; i < n; ++i) {
            dp[i].clear();
        }
        dp.clear();
    }
}
/*
9
1 2
1 3
2 4
2 5
3 6
3 7
6 8
6 9
10
? 4 5
? 5 6
? 8 7
! 6
? 8 7
? 4 5
? 4 7
? 5 9
! 2
? 4 3
9
1 2
1 3
2 4
2 5
3 6
3 7
6 8
6 9
10
? 4 5
? 5 6
? 8 7
! 6
? 8 7
? 4 5
? 4 7
? 5 9
! 2
? 4 3
0
*/

