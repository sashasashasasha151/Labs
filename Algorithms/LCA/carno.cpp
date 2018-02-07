#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;

vector<int *> dp;
vector<vector<int>> G;
vector<int> p, d, name, parent;
int power = 19;
int cur = 1;

int find_set (int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set (parent[v]);
}

void union_sets (int a, int b) {
    a = find_set (a);
    b = find_set (b);
    if (a != b) {
        if (d[a] > d[b])
            swap (a, b);
        parent[b] = a;
    }
}

void pluss(int k) {
    G[k].push_back(cur);
    p.push_back(k);
    d.push_back(d[k] + 1);
    name.push_back(cur);
    parent.push_back(cur);
    dp.push_back(new int[power]);
    dp[cur][0] = k;
    for (int i = 1; i < power; ++i) {
        dp[cur][i] = dp[dp[cur][i - 1]][i - 1];
    }
    cur++;
}

void minuss(int k) {
    union_sets(k,p[k]);
}

int lca(int l, int rr) {
    if (d[l] < d[rr]) {
        swap(l, rr);
    }
    for (int i = power - 1; i >= 0; --i) {
        if (d[dp[l][i]] >= d[rr]) {
            l = dp[l][i];
            continue;
        }
    }
    if (l == rr) {
        return find_set(l);
    }
    for (int i = power - 1; i >= 0; --i) {
        if (dp[l][i] != dp[rr][i]) {
            l = dp[l][i];
            rr = dp[rr][i];
        }
    }

    return find_set(p[rr]);
}

int main() {
    ifstream cin("carno.in");
    ofstream cout("carno.out");
    dp.push_back(new int[power]);
    for (int i = 0; i < power; ++i) {
        dp[0][i] = 0;
    }
    p.push_back(0);
    d.push_back(0);
    name.push_back(0);
    parent.push_back(0);

    G.resize(200001);

    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        char c;
        cin >> c;
        if (c == '?') {
            int l, r;
            cin >> l >> r;
            cout << lca(l - 1, r - 1) + 1 << endl;
        } else {
            int k;
            cin >> k;
            if (c == '+') {
                pluss(k - 1);
            } else {
                minuss(k - 1);
            }
        }
    }
    return 0;
}

