#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <fstream>

using namespace std;

struct Edge {
    long long int g;
    long long int _g;
    long long int l;
    long long int r;
    long long int cost;
    long long int rev;
    long long int new_cost;
};

struct EdgeG {
    long long int l;
    long long int r;
    long long int c;
    long long int cost;
};

long long int n, m;
vector<bool> used;
vector<Edge> edges;
vector<vector<int>> E;
vector<EdgeG> EG;

vector<int> get_path() {
    vector<long long int> arr;
    vector<int> parents;
    vector<bool> usng;
    arr.assign(n, 9223372036854775807);
    parents.assign(n, -1);
    usng.resize(n);
    arr[0] = 0;

    for (int i = 0; i < n; ++i) {
        int v = -1;

        for (int j = 0; j < n; ++j) {
            if (!usng[j] && (v == -1 || arr[j] < arr[v])) {
                v = j;
            }
        }

        if (arr[v] == 9223372036854775807) {
            break;
        }

        usng[v] = true;

        for (int j = 0; j < E[v].size(); ++j) {
            if (edges[E[v][j]]._g - edges[E[v][j]].g < 1) {
                continue;
            }
            int help = edges[E[v][j]].new_cost;
            if (arr[v] + help < arr[edges[E[v][j]].r]) {
                arr[edges[E[v][j]].r] = arr[v] + help;
                parents[edges[E[v][j]].r] = E[v][j];
            }
        }
    }

    for (auto &edge : edges) {
        edge.new_cost = edge.new_cost + arr[edge.l] - arr[edge.r];
    }

    vector<bool> usd;
    used.assign(n, false);
    vector<int> path;
    int v = parents[n - 1];
    if (v == -1) {
        return path;
    }
    for (; edges[v].l != 0; v = parents[edges[v].l]) {
        if (v == -1) {
            path.clear();
            return path;
        }
        if (used[edges[v].l]) {
            path.clear();
            return path;
        }
        path.push_back(v);
        used[edges[v].r] = true;
    }
    path.push_back(v);
    return path;
}

int main() {
    cin >> n;
    cin >> m;

    E.resize(2 * n + 2);

    for (int i = 0; i < n; ++i) {
        long long int cost;
        cin >> cost;
        EG.push_back({i + 2, n + i + 2, 1, 0});
        EG.push_back({n + i + 2, i + 2, 0, cost});
    }

    for (int i = 0; i < m; ++i) {
        long long int l, r, cost;
        cin >> l >> r >> cost;
        l = n + l + 1;
        r = r + 1;
        EG.push_back({l, r, 0, cost});
    }

    n = n * 2 + 2;

    for (EdgeG eg : EG) {
        long long int l, r, c, cost;

        l = eg.l;
        r = eg.r;
        c = 9223372036854775807 - eg.c;
        cost = eg.cost;
        E[l - 1].push_back(edges.size());
        edges.push_back({0, c, l - 1, r - 1, cost, edges.size() + 1, cost});
        E[r - 1].push_back(edges.size());
        edges.push_back({0, 0, r - 1, l - 1, -cost, edges.size() - 1, -cost});

        l = eg.l;
        r = n;
        if (eg.c == 0) {
            continue;
        }
        c = eg.c;
        cost = 0;
        E[l - 1].push_back(edges.size());
        edges.push_back({0, c, l - 1, r - 1, cost, edges.size() + 1, cost});
        E[r - 1].push_back(edges.size());
        edges.push_back({0, 0, r - 1, l - 1, -cost, edges.size() - 1, -cost});

        l = 1;
        r = eg.r;
        c = eg.c;
        cost = 0;
        E[l - 1].push_back(edges.size());
        edges.push_back({0, c, l - 1, r - 1, cost, edges.size() + 1, cost});
        E[r - 1].push_back(edges.size());
        edges.push_back({0, 0, r - 1, l - 1, -cost, edges.size() - 1, -cost});
    }

    vector<long long int> arr;
    arr.assign(n, 9223372036854775807);
    arr[0] = 0;
    for (int j = 0; j < n; ++j) {
        bool ky = false;
        for (int i = 0; i < edges.size(); ++i) {
            if (arr[edges[i].l] != 9223372036854775807) {
                if (edges[i]._g - edges[i].g < 1) {
                    continue;
                }
                if (arr[edges[i].l] < 9223372036854775807) {
                    if (arr[edges[i].r] > arr[edges[i].l] + edges[i].cost) {
                        arr[edges[i].r] = arr[edges[i].l] + edges[i].cost;
                        ky = true;
                    }
                }
            }
        }
        if (!ky) {
            break;
        }
    }

    for (auto &edge : edges) {
        edge.new_cost = edge.cost + arr[edge.l] - arr[edge.r];
    }

    long long int sum = 0;

    vector<int> path = get_path();
    while (path.size() > 0) {
        long long int min = 9223372036854775807;
        for (long long int i = path.size() - 1; i >= 0; --i) {
            long long int yf = edges[path[i]]._g - edges[path[i]].g;
            if (yf < min) {
                min = yf;
            }
        }
        for (long long int i = path.size() - 1; i >= 0; --i) {

            edges[path[i]].g += min;
            sum += min * (edges[path[i]].cost);
            edges[edges[path[i]].rev].g -= min;
        }
        path = get_path();
    }
    cout << sum << "\n";
    return 0;
}