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
    unsigned long long int rev;
    long long int new_cost;
};

int n, m;
vector<bool> used;
vector<Edge> edges;
vector<vector<int>> E;

inline vector<int> get_path() {
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
    ifstream cin("rps2.in");
    ofstream cout("rps2.out");

    n = 3;

    long long int ptr1[3];
    long long int ptr2[3];

    cin >> ptr2[0] >> ptr2[1] >> ptr2[2] >> ptr1[0] >> ptr1[1] >> ptr1[2];

    int k[3] = {0,0,1};
    int nz[3] = {1,0,0};
    int b[3] = {0,1,0};

    E.resize(n * 2 + 2);

    for (int i = 0; i < n; ++i) {
        E[0].push_back(edges.size());
        edges.push_back({0, ptr1[i], 0, i + 1, 0, edges.size() + 1, 0});
        E[i + 1].push_back(edges.size());
        edges.push_back({0, 0, i + 1, 0, 0, edges.size() - 1, 0});
    }

    for (int i = 0; i < n; ++i) {
        E[1].push_back(edges.size());
        edges.push_back({0, 700000000, 1, n + i + 1, k[i], edges.size() + 1, k[i]});
        E[n + i + 1].push_back(edges.size());
        edges.push_back({0, 0, n + i + 1, 1, -k[i], edges.size() - 1, -k[i]});
    }

    for (int i = 0; i < n; ++i) {
        E[2].push_back(edges.size());
        edges.push_back({0, 700000000, 2, n + i + 1, nz[i], edges.size() + 1, nz[i]});
        E[n + i + 1].push_back(edges.size());
        edges.push_back({0, 0, n + i + 1, 2, -nz[i], edges.size() - 1, -nz[i]});
    }

    for (int i = 0; i < n; ++i) {
        E[3].push_back(edges.size());
        edges.push_back({0, 700000000, 3, n + i + 1, b[i], edges.size() + 1, b[i]});
        E[n + i + 1].push_back(edges.size());
        edges.push_back({0, 0, n + i + 1, 3, -b[i], edges.size() - 1, -b[i]});
    }

    for (int i = 0; i < n; ++i) {
        E[n + i + 1].push_back(edges.size());
        edges.push_back({0, ptr2[i], n + i + 1, 7, 0, edges.size() + 1, 0});
        E[7].push_back(edges.size());
        edges.push_back({0, 0, 7, n + i + 1, 0, edges.size() - 1, 0});
    }

    n = 2 * n + 2;

//    vector<long long int> arr;
//    arr.assign(n, 9223372036854775807);
//    arr[0] = 0;
//    for (int j = 0; j < n; ++j) {
//        bool ky = false;
//        for (auto &edge : edges) {
//            if (arr[edge.l] != 9223372036854775807) {
//                if (edge._g - edge.g < 1) {
//                    continue;
//                }
//                if (arr[edge.l] < 9223372036854775807) {
//                    if (arr[edge.r] > arr[edge.l] + edge.cost) {
//                        arr[edge.r] = arr[edge.l] + edge.cost;
//                        ky = true;
//                    }
//                }
//            }
//        }
//        if (!ky) {
//            break;
//        }
//    }
//
//    for (auto &edge : edges) {
//        edge.new_cost = edge.cost + arr[edge.l] - arr[edge.r];
//    }


    long long int sum = 0;

    vector<int> path = get_path();
    while (!path.empty()) {
        long long int min = 9223372036854775807;
        for (int i = path.size() - 1; i >= 0; --i) {
            int yf = edges[path[i]]._g - edges[path[i]].g;
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

    cout << sum ;
    return 0;
}