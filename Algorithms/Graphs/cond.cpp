#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <queue>
using namespace std;

int *arr;
vector<pair<int, int>> ptr;
vector<pair<int, int>> ptrT;
int a = 1;
pair<int, int> *help;
pair<int, int> *helpT;
vector<int> cache;
vector<int> strong;


void topsort(int k) {
    arr[k - 1] = 1;
    for (int i = help[k - 1].first; i <= help[k - 1].second; i++) {
        if (i == -1) {
            break;
        }
        if (arr[ptr[i].second - 1] == -1) {
            topsort(ptr[i].second);
        }
    }
    cache.push_back(k);
    return;
}

void answer(int k) {
    arr[k - 1] = 1;
    strong.push_back(k);
    for (int i = helpT[k - 1].first; i <= helpT[k - 1].second; i++) {
        if (i == -1) {
            break;
        }
        if (arr[ptrT[i].second - 1] == -1) {
            answer(ptrT[i].second);
        }
    }
    return;
}

int main() {
    ifstream cin("cond.in");
    ofstream cout("cond.out");
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
        ptrT.push_back({ finish, start });
    }

    sort(ptr.begin(), ptr.end());
    sort(ptrT.begin(), ptrT.end());

    help = new pair<int, int>[n];
    helpT = new pair<int, int>[n];
    for (int i = 0; i < n; i++) {
        help[i] = { -1, -1 };
        helpT[i] = { -1, -1 };
    }

    for (int i = 0; i < m; i++) {
        int k = i;
        while (k < m - 1 && ptr[k].first == ptr[k + 1].first) {
            k++;
        }
        help[ptr[i].first - 1] = { i, k };
        i = k;
    }

    for (int i = 0; i < m; i++) {
        int k = i;
        while (k < m - 1 && ptrT[k].first == ptrT[k + 1].first) {
            k++;
        }
        helpT[ptrT[i].first - 1] = { i, k };
        i = k;
    }

    for (int i = 0; i < n; i++) {
        if (arr[i] == -1) {
            topsort(i + 1);
        }
    }

    for (int i = 0; i < n; i++) {
        arr[i] = -1;
    }

    int ans = 1;
    for (int i = 0; i < n; i++) {
        if (arr[cache[n - 1 - i] - 1] == -1) {
            answer(cache[n - i - 1]);
            for (int i = 0; i < strong.size(); i++) {
                arr[strong[i] - 1] = ans;
            }
            ans++;
            strong.clear();
        }
    }

    vector<pair<int, int>> tiran;
    for (int i = 0; i < m; i++) {
        if (arr[ptr[i].second - 1] != arr[ptr[i].first - 1]) {
            tiran.push_back({ arr[ptr[i].second - 1], arr[ptr[i].first - 1] });
        }
    }
    sort(tiran.begin(), tiran.end());
    int tir = 0;
    if (tiran.size() == 0) {
        cout << ans - 1 << " " << 0;
        return 0;
    }
    if (tiran.size() == 1) {
        cout << ans - 1 << " " << 1;
        return 0;
    }
    for (int i = 0; i < tiran.size(); i++) {
        int k = i;
        while (k < tiran.size() - 1 && tiran[k].first == tiran[k + 1].first && tiran[k].second == tiran[k + 1].second) {
            k++;
        }
        tir++;
        i = k;
    }

    cout << ans - 1 << " " << tir;

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

