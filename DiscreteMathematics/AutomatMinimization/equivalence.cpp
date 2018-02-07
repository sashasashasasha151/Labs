#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

queue<pair<int, int>> arr;
int **first, **second;
bool *f, *s, *ff, *ss;
int n, m, k;

int main() {
    ifstream cin("equivalence.in");
    ofstream cout("equivalence.out");
    cin >> n >> m >> k;
    n++;
    ff = new bool[n];
    f = new bool[n];
    for (int i = 0; i < n; ++i) {
        f[i] = false;
        ff[i] = false;
    }
    for (int i = 0; i < k; ++i) {
        int key;
        cin >> key;
        f[key] = true;
    }
    first = new int *[n];
    for (int i = 0; i < n; ++i) {
        first[i] = new int[27];
        for (int j = 0; j < 27; ++j) {
            first[i][j] = 0;
        }
    }
    for (int i = 0; i < m; ++i) {
        int l, r;
        char s;
        cin >> l >> r >> s;
        first[l][s-96] = r;
    }
    cin >> n >> m >> k;
    n++;
    s = new bool[n];
    ss = new bool[n];
    for (int i = 0; i < n; ++i) {
        s[i] = false;
        ss[i] = false;
    }
    for (int i = 0; i < k; ++i) {
        int key;
        cin >> key;
        s[key] = true;
    }
    second = new int *[n];
    for (int i = 0; i < n; ++i) {
        second[i] = new int[27];
        for (int j = 0; j < 27; ++j) {
            second[i][j] = 0;
        }
    }
    for (int i = 0; i < m; ++i) {
        int l, r;
        char s;
        cin >> l >> r >> s;
        second[l][s - 96] = r;
    }
    ss[1] = true;
    ff[1] = true;
    arr.push({ 1, 1 });
    while (!arr.empty()) {
        int l = arr.front().first;
        int r = arr.front().second;
        if (l == 0 && r == 0) {
            arr.pop();
            continue;
        }
        if (s[r] != f[l]) {
            cout << "NO";
            return 0;
        }
        if (r != 0) {
            ss[r] = true;
        }
        if (l != 0) {
            ff[l] = true;
        }
        for (int j = 0; j < 27; ++j) {
            if (!ss[second[r][j]] || !ff[first[l][j]]) {
                arr.push({ first[l][j], second[r][j] });
            }
        }
        arr.pop();
    }
    cout << "YES";

    return 0;
}
/*
2 4 1
2
1 2 a
1 2 b
2 2 a
2 2 b
3 6 2
2 3
1 2 a
1 3 b
2 2 a
2 2 b
3 3 a
3 3 b
*/

