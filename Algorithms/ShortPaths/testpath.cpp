#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

vector<pair<long long, long long>> *ptr;
long long *arr, *key;

int main() {
    /*ifstream cin("path.in");
    ofstream cout("path.out");*/
    int n, m;
    cin >> n >> m;
    ptr = new vector<pair<long long, long long>>[n];
    for (int i = 0; i < m; i++) {
        long long l, r, k;
        cin >> l >> r >> k;
        ptr[l - 1].push_back({ r, k });
    }
    arr = new long long[n];
    key = new long long[n];
    for (int i = 0; i < n; i++) {
        arr[i] = 9223372036854775807;
        key[i] = 0;
    }
    arr[0] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (arr[j] != 9223372036854775807) {
                for (int k = 0; k < ptr[j].size(); k++) {
                    if (arr[j] < 0 && ptr[j][k].second < 0 && arr[j] + ptr[j][k].second > 0) {
                        arr[ptr[j][k].first - 1] = -9223372036854775807;
                        continue;
                    }
                    arr[ptr[j][k].first - 1] = min(arr[ptr[j][k].first - 1], arr[j] + ptr[j][k].second);
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (arr[j] != 9223372036854775807) {
                for (int k = 0; k < ptr[j].size(); k++) {
                    if (arr[j] < 0 && ptr[j][k].second < 0 && arr[j] + ptr[j][k].second > 0) {
                        arr[ptr[j][k].first - 1] = -9223372036854775807;
                        continue;
                    }
                    if (arr[ptr[j][k].first - 1] > arr[j] + ptr[j][k].second) {
                        key[ptr[j][k].first - 1] = 1;
                    }
                    arr[ptr[j][k].first - 1] = min(arr[ptr[j][k].first - 1], arr[j] + ptr[j][k].second);
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (key[i] == 1) {
            arr[i] = -9223372036854775807;
        }
    }
    for (int i = 0; i < n; i++) {
        (arr[i] == 9223372036854775807) ? cout << 30000 << " " : (arr[i] == -9223372036854775807) ? cout << "-\n" : cout << arr[i] << " ";
    }
    return 0;
}

