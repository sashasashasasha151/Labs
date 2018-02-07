#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

long long int n, m;
vector<long long int> *G;
vector<long long int> vertex_list;
long long int *height, *first_position;
bool *used;
long long int deep = 0;
long long int **table;
long long int power;
long long int *logs;

long long int fl(long long int len) {
    if (len == 1) {
        return 0;
    } else {
        return fl(len / 2) + 1;
    }
}

void dfs(long long int k) {
    deep++;
    used[k] = true;
    vertex_list.push_back(k);
    for (long long int i = 0; i < G[k].size(); ++i) {
        if (!used[G[k][i]]) {
            height[G[k][i]] = deep;
            dfs(G[k][i]);
            vertex_list.push_back(k);
        }
    }
    deep--;
}

int main() {
    ios_base::sync_with_stdio(0);
    ifstream cin("lca_rmq.in");
    ofstream cout("lca_rmq.out");
    cin >> n >> m;

    G = new vector<long long int>[n];

    height = new long long int[n];
    fill(height, height + n, -1);

    used = new bool[n];
    fill(used, used + n, false);

    first_position = new long long int[n];
    fill(first_position, first_position + n, -1);

    for (long long int i = 0; i < n - 1; ++i) {
        long long int u;
        cin >> u;
        G[u].push_back(i + 1);
    }

    height[0] = 0;
    dfs(0);

    for (long long int i = 0; i < vertex_list.size(); ++i) {
        if (first_position[vertex_list[i]] == -1) {
            first_position[vertex_list[i]] = i;
        }
    }

    power = fl(vertex_list.size()) + 1;
    table = new long long int *[vertex_list.size()];
    for (long long int j = 0; j < vertex_list.size(); ++j) {
        table[j] = new long long int[power];
        fill(table[j], table[j] + power, -1);
    }

    for (long long int j = 0; j < power; ++j) {
        for (long long int i = 0; i < vertex_list.size(); ++i) {
            if (j == 0) {
                table[i][j] = vertex_list[i];
            } else {
                long long int p = (long long int) (i + pow(2, (j - 1)));
                if (p < vertex_list.size() && table[p][j - 1] < n && table[p][j - 1] >= 0) {
                    if (height[table[i][j - 1]] < height[table[p][j - 1]]) {
                        table[i][j] = table[i][j - 1];
                    } else {
                        table[i][j] = table[p][j - 1];
                    }
                }
            }
        }
    }

    logs = new long long int[vertex_list.size() + 1];
    for (long long int i = 1; i <= vertex_list.size(); ++i) {
        long long int t = fl(i);
        logs[i] = fl(i);
    }

    long long int a1, a2;
    cin >> a1 >> a2;
    long long int x, y, z;
    cin >> x >> y >> z;

    long long int sum = 0;
    long long int l = first_position[a1];
    long long int r = first_position[a2];
    if (l > r) {
        swap(l, r);
    }
    long long int length = logs[r - l + 1];
    long long int po = (long long int) (pow(2, length));
    long long int v;
    if (height[table[l][length]] < height[table[r - po + 1][length]]) {
        v = table[l][length];
    } else {
        v = table[r - po + 1][length];
    }
    sum += v;
    for (long long int i = 2; i <= m; ++i) {
        a1 = (x * a1 + y * a2 + z) % n;
        a2 = (x * a2 + y * a1 + z) % n;
        l = first_position[(a1 + v) % n];
        r = first_position[a2];
        if (l > r) {
            swap(l, r);
        }
        length = logs[r - l + 1];
        po = (long long int) (1 << length);
        if (height[table[l][length]] < height[table[r - po + 1][length]]) {
            v = table[l][length];
        } else {
            v = table[r - po + 1][length];
        }
        sum += v;
    }
    cout << sum;
    return 0;
}

