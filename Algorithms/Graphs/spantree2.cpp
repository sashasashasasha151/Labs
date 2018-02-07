#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <queue>
using namespace std;

pair<int, int> *arr;
vector<pair<int, pair<int, int>>> ptr;

int check(int k) {
    if (k == arr[k].first)
        return k;
    return arr[k].first = check(arr[k].first);
}

void answer(int left, int right) {
    left = check(left);
    right = check(right);
    if (left != right) {
        if (arr[left].second < arr[right].second)
            swap(left, right);
        arr[right].first = left;
        if (arr[left].second == arr[right].second)
            arr[left].second++;
    }
}

int main() {
    ifstream cin("spantree2.in");
    ofstream cout("spantree2.out");
    int n, m;
    cin >> n >> m;
    arr = new pair<int, int>[n];
    for (int i = 0; i < n; i++) {
        arr[i] = { i, 0 };
    }

    for (int i = 0; i < m; i++) {
        int start, finish, weight;
        cin >> start >> finish >> weight;
        ptr.push_back({ weight, { start, finish } });
    }

    sort(ptr.begin(), ptr.end());
    int ans = 0;
    for (int i = 0; i < m; i++) {
        if (check(ptr[i].second.first - 1) != check(ptr[i].second.second - 1)) {
            answer(ptr[i].second.first - 1, ptr[i].second.second - 1);
            ans += ptr[i].first;
        }
    }
    cout << ans;

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

