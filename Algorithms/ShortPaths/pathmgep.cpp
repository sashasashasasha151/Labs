#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

vector<int> *ptr;
long long *arr, *key;

int main() {
    ifstream cin("pathmgep.in");
    ofstream cout("pathmgep.out");
    int n, s, f;
    cin >> n >> s >> f;
    ptr = new vector<int>[n];
    for (int i = 0; i < n; ++i) {
        ptr[i].resize(n);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; ++j) {
            int k;
            cin >> k;
            ptr[i][j] = k;
        }
    }
    arr = new long long[n];
    key = new long long[n];
    for (int i = 0; i < n; ++i) {
        arr[i] = key[i] = 9223372036854775807;
    }
    arr[s - 1] = 0;
    for (int i = 0; i < n; ++i) {
        long long Min = 9223372036854775807;
        int k = 0;
        for (int j = 0; j < n; ++j) {
            if (key[j] != 1 && arr[j] < Min) {
                Min = arr[j];
                k = j;
            }
        }
        key[k] = 1;
        for (int j = 0; j < ptr[k].size(); ++j) {
            if (ptr[k][j] == -1) {
                continue;
            }
            else {
                arr[j] = min(arr[j], arr[k] + ptr[k][j]);
            }
        }
    }
    (arr[f - 1] != 9223372036854775807) ? cout << arr[f - 1] : cout << -1;
    return 0;
}

