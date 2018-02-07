/*#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>

using namespace std;

int **dp;
vector<vector<int>> G;
int *p, *d;
int deep = 0, n, power, start;

void dfs(int k) {
    deep++;
    for (int i = 0; i < G[k].size(); ++i) {
        if (G[k][i] == p[k]) {
            continue;
        }
        d[G[k][i]] = deep;
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
    if(d[l]<d[r]) {
        swap(l,r);
    }
    for(int i=power-1;i>=0;--i) {
        if(d[dp[l][i]]>=d[r]) {
            l = dp[l][i];
            continue;
        }
    }
    if(l==r) {
        return l;
    }
    for(int i=power-1;i>=0;--i) {
        if(dp[l][i]!=dp[r][i]) {
            l = dp[l][i];
            r = dp[r][i];
        }
    }
    return p[r];
}

int main() {
    ifstream cin("lca.in");
    ofstream cout("lca.out");

    cin >> n;

    G.resize(n);

    power = (int) (log(n) / log(2)+1);
    dp = new int *[n];
    for (int i = 0; i < n; ++i) {
        dp[i] = new int[power];
    }

    p = new int[n];
    fill(p, p + n, -1);

    d = new int[n];

    for (int i = 0; i < n; ++i) {
        int u;
        cin >> u;
        if(u == 0) {
            start = i;
        } else {
            //G[i+1].push_back(u-1);
            G[u - 1].push_back(i);
            p[i + 1] = u - 1;
        }
    }

    p[0] = 0;
    d[0] = 0;
    dfs(0);

    pre();

    int k;
    cin >> k;
    for (int i = 0; i < k; ++i) {
        int l,r;
        cin >> l >> r;
        cout << lca(l-1,r-1)+1 << endl;
    }

    return 0;
}*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>

using namespace std;

int **dp;
vector<vector<int>> G;
int *p, *d;
int deep = 0, n, power, start;

void dfs(int k) {
    deep++;
    for (int i = 0; i < G[k].size(); ++i) {
        if (G[k][i] == p[k]) {
            continue;
        }
        d[G[k][i]] = deep;
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
    ifstream cin("ancestor.in");
    ofstream cout("ancestor.out");

    cin >> n;

    G.resize(n);

    power = (int) (log(n) / log(2) + 1);
    dp = new int *[n];
    for (int i = 0; i < n; ++i) {
        dp[i] = new int[power];
    }

    p = new int[n];
    fill(p, p + n, -1);

    d = new int[n];

    for (int i = 0; i < n; ++i) {
        int u;
        cin >> u;
        if (u == 0) {
            start = i;
            continue;
        }
        G[i].push_back(u - 1);
        G[u - 1].push_back(i);
        p[i] = u - 1;
    }

    p[start] = start;
    d[start] = 0;
    dfs(start);

    pre();

    int k;
    cin >> k;
    for (int i = 0; i < k; ++i) {
        int l, r;
        cin >> l >> r;
        int a = lca(l - 1, r - 1);
        if (a == l - 1) {
            cout << 1 << endl;
        } else {
            cout << 0 << endl;
        }
    }

    return 0;
}

