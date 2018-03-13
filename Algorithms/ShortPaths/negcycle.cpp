#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

vector<int> *ptr;
int *arr;
vector<int> cache;
vector<int> answer;

bool c(int k) {
    int l = k;
    while (cache[l] != k) {
        if (answer.size() == 249) {
            return false;
        }
        if (cache[l] == -1) {
            return false;
        }
        answer.push_back(l);
        l = cache[l];
    }
    answer.push_back(l);
    answer.push_back(cache[l]);
    return true;
}

int main() {
//    ifstream cin("negcycle.in");
//    ofstream cout("negcycle.out");
    int n;
    cin >> n;
    ptr = new vector<int>[n];
    for (int i = 0; i < n; ++i) {
        ptr[i].resize(n);
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int k;
            cin >> k;
            ptr[i][j] = k;
        }
    }
    cache.resize(n);
    arr = new int[n];
    for (int i = 0; i < n; i++) {
        arr[i] = 0;
        cache[i] = -1;
    }
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < ptr[j].size(); k++) {
                if (ptr[j][k] != 1000000000) {
                    if (arr[j] + ptr[j][k] < arr[k]) {
                        arr[k] = arr[j] + ptr[j][k];
                        cache[k] = j;
                    }
                }
            }
        }
    }
    int cy = -1;
    for (int j = 0; j < n; j++) {
        for (int k = 0; k < ptr[j].size(); k++) {
            if (ptr[j][k] != 1000000000 && (arr[j] + ptr[j][k]) < arr[k]) {
                cache[k] = j;
                cy = k;
                arr[k] = arr[j] + ptr[j][k];
                if (c(cy)) {
                    cout << "YES" << "\n";
                    cout << answer.size() << "\n";
                    for (int i = answer.size() - 1; i >= 0; i--) {
                        cout << answer[i] + 1 << " ";
                    }
                    return 0;
                }
                answer.clear();
            }
        }
    }
    if (cy == -1) {
        cout << "NO";
        return 0;
    }
    return 0;
}

/*
3
1000000000 1000000000 -51
100  1000000000 1000000000
1000000000 -50  1000000000
*/

