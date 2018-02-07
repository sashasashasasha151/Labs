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
    if (a == 0) {
        return;
    }
    arr[k - 1] = 0;
    cache.push_back(k);
    for (int i = help[k - 1].first; i <= help[k - 1].second; i++) {
        if (i == -1) {
            break;
        }
        if (arr[ptr[i].second-1] == -1) {
            answer(ptr[i].second);
        }
        if (arr[ptr[i].second-1] == 0) {
            cache.push_back(ptr[i].second);
            a = 0;
            break;
        }
    }
    arr[k - 1] = 1;
    return;
}

int main() {
    ifstream cin("cycle.in");
    ofstream cout("cycle.out");
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

    for (int i = 0; i < n; i++) {
        if (a==0) {
            break;
        }
        if (arr[i] == -1) {
            answer(i+1);
        }
    }
    if (a == 1) {
        cout << "NO";
    }
    else {
        cout << "YES" << "\n";
        vector<int> answertrue;
        int k = cache.back();
        cache.pop_back();
        while (cache.back() != k) {
            answertrue.push_back(cache.back());
            cache.pop_back();
        }
        answertrue.push_back(k);
        for (int i = answertrue.size() - 1; i >= 0; i--) {
            cout << answertrue[i] << " ";
        }
    }
    return 0;
}
/*
6 6
1 2
2 3
3 4
4 5
5 6
6 1
*/

