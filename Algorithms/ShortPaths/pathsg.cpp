#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

vector<pair<int, int>> *ptr;
int *arr, *key;

int main() {
    ifstream cin("pathsg.in");
    ofstream cout("pathsg.out");
    int n, m;
    cin >> n >> m;
    ptr = new vector<pair<int, int>>[n];
    for (int i = 0; i < m; i++) {
        int l, r, k;
        cin >> l >> r >> k;
        ptr[l-1].push_back({ r, k });
    }
    arr = new int[n];
    key = new int[n];
    for (int q = 0; q < n; ++q) {
        for (int i = 0; i < n; ++i) {
            arr[i] = key[i] = INT_MAX;
        }
        arr[q] = 0;
        for (int i = 0; i < n; ++i) {
            int Min = INT_MAX;
            int k = 0;
            for (int j = 0; j < n; ++j) {
                if (key[j] != 1 && arr[j] < Min) {
                    Min = arr[j];
                    k = j;
                }
            }
            key[k] = 1;
            for (int j = 0; j < ptr[k].size(); ++j) {
                arr[ptr[k][j].first - 1] = min(arr[ptr[k][j].first - 1], arr[k] + ptr[k][j].second);
            }
        }
        for (int i = 0; i < n; ++i) {
            (arr[i] != INT_MAX) ? cout << arr[i] << " " : cout << -1 << " ";
        }
        cout << "\n";
    }
    return 0;
}
/*
3 3
1 2 5
2 3 2
3 1 8
*/

