#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <queue>
using namespace std;

vector<int> *ptr;
vector<int> *unPtr;
int *arr;
int *sumArr;
int a = 1;

void dfs(int k) {
    arr[k - 1] = 1;
    for (int i = 0; i < ptr[k - 1].size(); i++) {
        if (arr[ptr[k - 1][i] - 1] == 0) {
            dfs(ptr[k - 1][i]);
        }
    }
}

void secondDfs(int k) {
    arr[k - 1] = 2;
    for (int i = 0; i < unPtr[k - 1].size(); i++) {
        if (arr[unPtr[k - 1][i] - 1] == 1) {
            secondDfs(unPtr[k - 1][i]);
        }
    }
}

void cycle(int k) {
    if (a == 0) {
        return;
    }
    arr[k - 1] = 3;
    for (int i = 0; i < ptr[k - 1].size(); i++) {
        if (arr[ptr[k - 1][i] - 1] == 2) {
            cycle(ptr[k - 1][i]);
        }
        if (arr[ptr[k - 1][i] - 1] == 3) {
            a = 0;
            break;
        }
    }
    arr[k - 1] = 4;
    return;
}

int anss(int t) {
    if (arr[t - 1] == 5) {
        return sumArr[t - 1];
    }
    int sum = 0;
    for (int i = 0; i < unPtr[t - 1].size(); i++) {
        if (arr[unPtr[t - 1][i] - 1] == 4 || arr[unPtr[t - 1][i] - 1] == 5) {
            sum += anss(unPtr[t - 1][i]);
            sum %= 1000000007;
        }
    }
    arr[t - 1] = 5;
    sumArr[t - 1] = sum;
    return sum;
}

int main() {
    ios_base::sync_with_stdio(0);
    ifstream cin("problem3.in");
    ofstream cout("problem3.out");
    int n, m, k;
    cin >> n >> m >> k;

    vector<int> out;

    for (int i = 0; i < k; i++) {
        int j;
        cin >> j;
        out.push_back(j);
    }

    ptr = new vector<int>[n];
    unPtr = new vector<int>[n];

    for (int i = 0; i < m; i++) {
        int l, r;
        char s;
        cin >> l >> r >> s;
        ptr[l - 1].push_back(r);
        unPtr[r - 1].push_back(l);
    }

    arr = new int[n];
    sumArr = new int[n];

    for (int i = 0; i < n; i++) {
        arr[i] = 0;
        sumArr[i] = 0;
    }

    dfs(1);

    vector<int> outTrue;

    for (int i = 0; i < out.size(); i++) {
        if (arr[out[i] - 1] == 1) {
            outTrue.push_back(out[i]);
        }
    }

    if (outTrue.size() == 0) {
        cout << 0;
        return 0;
    }

    for (int i = 0; i < outTrue.size(); i++) {
        secondDfs(outTrue[i]);
    }

    cycle(1);

    if (a == 0) {
        cout << -1;
        return 0;
    }

    sumArr[0] = 1;
    arr[0] = 5;
    long long kol = 0;

    for (int i = 0; i < outTrue.size(); i++) {
        kol += anss(outTrue[i]);
        kol %= 1000000007;
    }
    cout << kol;

    return 0;
}
/*
5 5 1
3
1 2 r
2 3 r
2 4 r
4 5 r
5 4 r
*/

