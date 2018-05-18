#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <fstream>

using namespace std;

struct Edge {
    int g;
    int _g;
    int l;
    int r;
    int cost;
    int rev;
    int new_cost;
};

int n, m;
vector<bool> used;
vector<Edge> edges;
vector<vector<int>> E;

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
    ifstream cin("assignment.in");
    ofstream cout("assignment.out");

    cin >> n;

    E.resize(n * 2 + 2);

    for (int i = 0; i < n; ++i) {
        E[0].push_back(edges.size());
        edges.push_back({0, 1, 0, i + 1, 0, edges.size() + 1, 0});
        E[i + 1].push_back(edges.size());
        edges.push_back({0, 0, i + 1, 0, 0, edges.size() - 1, 0});
        for (int j = 0; j < n; ++j) {
            int cost;
            cin >> cost;
            E[i + 1].push_back(edges.size());
            edges.push_back({0, 1, i + 1, n + j + 1, cost, edges.size() + 1, cost});
            E[n + j + 1].push_back(edges.size());
            edges.push_back({0, 0, n + j + 1, i + 1, -cost, edges.size() - 1, -cost});
        }
        E[n + i + 1].push_back(edges.size());
        edges.push_back({0, 1, n + i + 1, n * 2 + 1, 0, edges.size() + 1, 0});
        E[n * 2 + 1].push_back(edges.size());
        edges.push_back({0, 0, n * 2 + 1, n + i + 1, 0, edges.size() - 1, 0});
    }

    n = 2 * n + 2;

    vector<long long int> arr;
    arr.assign(n, 9223372036854775807);
    arr[0] = 0;
    for (int j = 0; j < n; ++j) {
        bool ky = false;
        for (auto &edge : edges) {
            if (arr[edge.l] != 9223372036854775807) {
                if (edge._g - edge.g < 1) {
                    continue;
                }
                if (arr[edge.l] < 9223372036854775807) {
                    if (arr[edge.r] > arr[edge.l] + edge.cost) {
                        arr[edge.r] = arr[edge.l] + edge.cost;
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
    while (!path.empty()) {
        long long int min = 9223372036854775807;
        for (int i = path.size() - 1; i >= 0; --i) {
            long long int yf = edges[path[i]]._g - edges[path[i]].g;
            if (yf < min) {
                min = yf;
            }
        }
        for (int i = path.size() - 1; i >= 0; --i) {
            edges[path[i]].g += min;
            sum += min * (edges[path[i]].cost);
            edges[edges[path[i]].rev].g -= min;
        }
        path = get_path();
    }
    cout << sum << "\n";
    n = n - 2;
    n /= 2;
    vector<int> answer;
    answer.resize(n);
    for (auto &edge : edges) {
        if (edge.g == 1 && edge.l >= 1 && edge.l <= n) {
            cout << edge.l << " " << edge.r-n << "\n";
        }
    }
    return 0;
}