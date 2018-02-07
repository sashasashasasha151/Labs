#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>

using namespace std;

pair<int,int> **dp, *p;
vector<vector<pair<int,int>>> G;
int *d;
int deep = 0, n, power;

void dfs(int k) {
    deep++;
    for (int i = 0; i < G[k].size(); ++i) {
        if (G[k][i].first == p[k].first) {
            continue;
        }
        d[G[k][i].first] = deep;
        dfs(G[k][i].first);
    }
    deep--;
}

void pre() {
    for (int i = 0; i < n; ++i) {
        dp[i][0].first = p[i].first;
        dp[i][0].second = p[i].second;
    }

    for (int j = 1; j < power; ++j) {
        for (int i = 0; i < n; ++i) {
            dp[i][j].first = dp[dp[i][j - 1].first][j - 1].first;
            dp[i][j].second = min(dp[i][j - 1].second,dp[dp[i][j - 1].first][j - 1].second);
        }
    }
}

int lca(int l, int r) {
    int mi = INT_MAX;
    if(d[l]<d[r]) {
        swap(l,r);
    }
    for(int i=power-1;i>=0;--i) {
        if(d[dp[l][i].first] >= d[r]) {
            mi = min(mi,dp[l][i].second);
            l = dp[l][i].first;
            continue;
        }
    }
    if(l==r) {
        return mi;
    }
    for(int i=power-1;i>=0;--i) {
        if(dp[l][i].first!=dp[r][i].first) {
            mi = min(mi,dp[l][i].second);
            l = dp[l][i].first;
            mi = min(mi,dp[r][i].second);
            r = dp[r][i].first;
        }
    }
    mi = min(mi,min(p[l].second,p[r].second));
    return mi;
}

int main() {
    ifstream cin("minonpath.in");
    ofstream cout("minonpath.out");

    cin >> n;

    G.resize(n);

    power = (int) (log(n) / log(2)+1);
    dp = new pair<int,int> *[n];
    for (int i = 0; i < n; ++i) {
        dp[i] = new pair<int,int>[power];
    }

    p = new pair<int,int>[n];
    for (int i = 0; i < n; ++i) {
        p[i].first = -1;
        p[i].second = INT_MAX;
    }

    d = new int[n];

    for (int i = 0; i < n - 1; ++i) {
        int u, w;
        cin >> u >> w;
        G[i+1].push_back({u-1,w});
        G[u-1].push_back({i+1,w});
        p[i+1].first = u-1;
        p[i+1].second = w;
    }

    p[0].first = 0;
    d[0] = 0;
    dfs(0);

    pre();

    /*for (int i = 0; i < n; ++i) {
        for (int j = 0; j < power; ++j) {
            cout << dp[i][j].second << " ";
        }
        cout << endl;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < power; ++j) {
            cout << dp[i][j].first << " ";
        }
        cout << endl;
    }
    for (int i = 0; i < n; ++i) {
        cout << d[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < n; ++i) {
        cout << p[i].first << " ";
    }
    cout << endl;
    for (int i = 0; i < n; ++i) {
        cout << p[i].second << " ";
    }
    cout << endl;*/


    int k;
    cin >> k;
    for (int i = 0; i < k; ++i) {
        int l,r;
        cin >> l >> r;
        cout << lca(l-1,r-1) << endl;
    }

    return 0;
}

