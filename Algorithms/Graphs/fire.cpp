#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <queue>
using namespace std;

int *arr;
vector<pair<int, int>> ptr;
int a = 1;
pair<int, int> *help;
vector<int> cache;


void answer(int k) {
    arr[k - 1] = 1;
    for (int i = help[k - 1].first; i <= help[k - 1].second; i++) {
        if (i == -1) {
            break;
        }
        if (arr[ptr[i].second - 1] == -1) {
            answer(ptr[i].second);
        }
    }
    arr[k - 1] = 1;
    return;
}

int main() {
    /*ifstream cin("fire.in");
    ofstream cout("fire.out");*/
    int n, m;
    cin >> n >> m;
    arr = new int[n];
    for (int i = 0; i < n; i++) {
        arr[i] = -1;
    }

    for (int i = 0; i < m; i++) {
        int start, finish;
        cin >> start >> finish;
        ptr.push_back({ start, finish });
    }

    sort(ptr.begin(), ptr.end());

    help = new pair<int, int>[n];
    for (int i = 0; i < n; i++) {
        help[i].first = -1;
        help[i].second = -1;
    }

    for (int i = 0; i < m; i++) {
        int k = i;
        while (k < m - 1 && ptr[k].first == ptr[k + 1].first) {
            k++;
        }
        help[ptr[i].first - 1] = { i, k };
        i = k;
    }

    int a = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == -1) {
            a++;
            answer(i + 1);
        }
    }
    cout << a;

    return 0;
}

