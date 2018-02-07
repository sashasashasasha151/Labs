#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

vector<pair<int, long long>> *ptr;
long long *arr;
int *key;

void dfs(int k) {
    key[k] = 1;
    for (int i = 0; i < ptr[k].size(); i++) {
        if (key[ptr[k][i].first - 1] == 0) {
            dfs(ptr[k][i].first - 1);
        }
    }
}

int main() {
    ifstream cin("path.in");
    ofstream cout("path.out");
    int n, m, s;
    cin >> n >> m >> s;
    ptr = new vector<pair<int, long long>>[n];
    for (int i = 0; i < m; i++) {
        long long l, r, k;
        cin >> l >> r >> k;
        ptr[l - 1].push_back({ r, k });
    }
    arr = new long long[n];
    key = new int[n];
    for (int i = 0; i < n; i++) {
        arr[i] = LLONG_MAX;
        key[i] = 0;
    }
    arr[s - 1] = 0;
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n; j++) {
            if (arr[j] != LLONG_MAX) {
                for (int k = 0; k < ptr[j].size(); k++) {
                    if (arr[j] < 0 && ptr[j][k].second < 0 && arr[j] + ptr[j][k].second >= 0) {
                        arr[ptr[j][k].first - 1] = LLONG_MIN;
                        continue;
                    }
                    arr[ptr[j][k].first - 1] = min(arr[ptr[j][k].first - 1], arr[j] + ptr[j][k].second);
                }
            }
        }
    }
    for (int j = 0; j < n; j++) {
        if (arr[j] != LLONG_MAX) {
            for (int k = 0; k < ptr[j].size(); k++) {
                if (arr[j] < 0 && ptr[j][k].second < 0 && arr[j] + ptr[j][k].second >= 0) {
                    dfs(j);
                    continue;
                }
                if (arr[j] + ptr[j][k].second < arr[ptr[j][k].first - 1]) {
                    dfs(j);
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (key[i] == 1) {
            arr[i] = LLONG_MIN;
        }
    }
    for (int i = 0; i < n; i++) {
        if (arr[i] == LLONG_MAX) {
            cout << "*\n";
        }
        else {
            if (arr[i] == LLONG_MIN) {
                cout << "-\n";
            }
            else {
                cout << arr[i] << "\n";
            }
        }
    }
    return 0;
}

