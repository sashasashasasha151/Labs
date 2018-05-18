#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>

using namespace std;

struct Vertex {
    int l, r, t, b;
    double cx, cy;
};

int n, w, N;
vector<Vertex> V;
vector<pair<int,int>> edges;
vector<vector<pair<int,int>>> E;

int get_path() {
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
            int help = E[v][j].second;
            if (arr[v] + help < arr[E[v][j].first]) {
                arr[E[v][j].first] = arr[v] + help;
            }
        }
    }
    return arr[n - 1];
}

int main() {
    std::ios::sync_with_stdio(false);
    cin >> n >> w;

    E.resize(n + 2);

    for (int i = 0; i < n; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        V.push_back({min(x1, x2), max(x1, x2), max(y1, y2), min(y1, y2)});
        V[i].cx = ((double) (V[i].l + V[i].r)) / 2;
        V[i].cy = ((double) (V[i].t + V[i].b)) / 2;
    }

    int size = 0;
    for (int i = 0; i < n; ++i) {
        E[0].push_back({i + 1, V[i].b});
        E[i + 1].push_back({0, V[i].b});
        E[i + 1].push_back({n + 1, w - V[i].t});
        E[n + 1].push_back({i + 1, w - V[i].t});
    }

    E[0].push_back({n + 1, w});
    E[n + 1].push_back({0, w});

    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            int f, s;
            if (V[i].cx < V[j].cx) {
                f = V[j].l - V[i].r;
            } else {
                f = V[i].l - V[j].r;
            }

            if (V[i].cy < V[j].cy) {
                s = V[j].b - V[i].t;
            } else {
                s = V[i].b - V[j].t;
            }

            f = (max(f, s) < 0 ? 0 : max(f, s));

            E[i + 1].push_back({j + 1, f});
            E[j + 1].push_back({i + 1, f});
        }
    }

    n = n + 2;

    cout << get_path();


    return 0;
}