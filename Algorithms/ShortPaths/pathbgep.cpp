#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

vector<pair<int, int>> *ptr;
int *arr, *key;
pair<int, int> *t;

void makeTree(int n, int l, int r) {
    if (l == r)
        t[n] = {arr[l], l};
    else {
        int m = (l + r) / 2;
        makeTree(n * 2, l, m);
        makeTree(n * 2 + 1, m + 1, r);
        (t[n * 2].first < t[n * 2 + 1].first) ? t[n] = t[n * 2] : t[n] = t[n * 2 + 1];
    }
}

void reMakeTree(int n, int l, int r, int in, int per) {
    if (l == r)
        t[n] = { per, in };
    else {
        int m = (l + r) / 2;
        if (in <= m)
            reMakeTree(n * 2, l, m, in, per);
        else
            reMakeTree(n * 2 + 1, m + 1, r, in, per);
        (t[n * 2].first < t[n * 2 + 1].first) ? t[n] = t[n * 2] : t[n] = t[n * 2 + 1];
    }
}

int main() {
    ifstream cin("pathbgep.in");
    ofstream cout("pathbgep.out");
    int n, m;
    cin >> n >> m;
    ptr = new vector<pair<int, int>>[n];
    for (int i = 0; i < m; i++) {
        int l, r, k;
        cin >> l >> r >> k;
        ptr[l - 1].push_back({ r, k });
        ptr[r - 1].push_back({ l, k });
    }
    arr = new int[n];
    key = new int[n];
    t = new pair<int, int>[4 * n];
    for (int i = 0; i < n; ++i) {
        arr[i] = key[i] = INT_MAX;
    }
    arr[0] = 0;
    makeTree(1, 0, n - 1);
    for (int i = 0; i < n; ++i) {
        int k = t[1].second;
        key[k] = 1;
        reMakeTree(1, 0, n - 1, k, INT_MAX);
        for (int j = 0; j < ptr[k].size(); ++j) {
            //cout << k + 1 << "to" << ptr[k][j].first << " - " << arr[ptr[k][j].first - 1] << " " << arr[k] << "+" << ptr[k][j].second << "\n";
            int h = min(arr[ptr[k][j].first - 1], arr[k] + ptr[k][j].second);
            arr[ptr[k][j].first - 1] = h;
            if (key[ptr[k][j].first - 1] != 1) {
                reMakeTree(1, 0, n - 1, ptr[k][j].first - 1, h);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        (arr[i] != INT_MAX) ? cout << arr[i] << " " : cout << -1 << " ";
    }
    return 0;
}

