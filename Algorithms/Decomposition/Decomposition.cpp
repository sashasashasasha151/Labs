#include <iostream>
#include <vector>
#include <random>
#include <ctime>

using namespace std;

int *ans, *sons, *in;
int t, n;

vector<vector<int>> G;

int make_sons(int k, int d, int max, bool ot) {
    in[k] = d;
    sons[k] = 1;
    bool check = true;
    for (int i = 0; i < G[k].size(); ++i) {
        if (ans[G[k][i]] == -2 && in[G[k][i]] != d) {
            sons[k] += make_sons(G[k][i], d, max,false);

        }
    }
    if ((sons[k] * 2 > max || ot) && t == -1) {
        t = k;
    }
    return sons[k];
}

void make_dec(int k, int par, int d) {
    t = -1;
    int unused = make_sons(k, d, n / (1 << d), true);

    ans[t] = par;

    int tt = t;
    for (int i = 0; i < G[tt].size(); ++i) {
        if (ans[G[tt][i]] == -2) {
            make_dec(G[tt][i], tt, d+1);
        }
    }
}

int main() {
    cin >> n;

    G.resize(n);

    ans = new int[n];
    fill(ans, ans + n, -2);
    sons = new int[n];
    in = new int[n];
    fill(in, in + n, -1);

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        G[u - 1].push_back(v - 1);
        G[v - 1].push_back(u - 1);
    }

    make_dec(0, -1, 0);

    for (int i = 0; i < n; ++i) {
        cout << ans[i] + 1 << " ";
    }

    return 0;
}

