#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int **first, **second;
bool *f, *s, *bb;
int *ss;
int n, m, k;

bool answer(int q) {
    bb[q] = true;
    int secq = ss[q];
    for (int i = 0; i < 26; ++i) {
        if (first[q][i] == -1 && second[secq][i] == -1) {
            continue;
        }
        if ((first[q][i] == -1 && second[secq][i] != -1) || (first[q][i] != -1 && second[secq][i] == -1)) {
            return false;
        }

        if (ss[first[q][i]] == -1) {
            int w = second[secq][i];
            ss[first[q][i]] = w;
        }
        else {
            if (ss[first[q][i]] != second[secq][i]) {
                return false;
            }
        }
        if (!bb[first[q][i]]) {
            if (answer(first[q][i])) {
                continue;
            }
            else {
                return false;
            }
        }
    }
    return true;
}

int main() {
    ifstream cin("isomorphism.in");
    ofstream cout("isomorphism.out");
    cin >> n >> m >> k;
    f = new bool[n];
    for (int i = 0; i < n; ++i) {
        f[i] = false;
    }
    for (int i = 0; i < k; ++i) {
        int key;
        cin >> key;
        f[key - 1] = true;
    }
    first = new int *[n];
    for (int i = 0; i < n; ++i) {
        first[i] = new int[26];
        for (int j = 0; j < 26; ++j) {
            first[i][j] = -1;
        }
    }
    for (int i = 0; i < m; ++i) {
        int l, r;
        char s;
        cin >> l >> r >> s;
        first[l - 1][s - 97] = r - 1;
    }
    int nS = n, mS = m, kS = k;
    cin >> n >> m >> k;
    s = new bool[n];
    for (int i = 0; i < n; ++i) {
        s[i] = false;
    }
    for (int i = 0; i < k; ++i) {
        int key;
        cin >> key;
        s[key - 1] = true;
    }
    second = new int *[n];
    for (int i = 0; i < n; ++i) {
        second[i] = new int[26];
        for (int j = 0; j < 26; ++j) {
            second[i][j] = -1;
        }
    }
    for (int i = 0; i < m; ++i) {
        int l, r;
        char s;
        cin >> l >> r >> s;
        second[l - 1][s - 97] = r - 1;
    }

    /*for (int j = 0; j < 4; ++j) {
        for (int i = 0; i < n; ++i) {
            cout << first[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
    for (int j = 0; j < 4; ++j) {
        for (int i = 0; i < n; ++i) {
            cout << second[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";*/


    if (n == nS && m == mS && k == kS) {
        ss = new int[n];
        bb = new bool[n];
        for (int i = 0; i < n; ++i) {
            ss[i] = -1;
            bb[i] = false;
        }
        ss[0] = 0;
        if (!answer(0)) {
            cout << "NO";
            return 0;
        }
        for (int i = 0; i < n; ++i) {
            if ((!f[i] && s[ss[i]]) || (f[i] && !s[ss[i]])) {
                cout << "NO";
                return 0;
            }
        }
        cout << "YES";
        return 0;
    }
    else {
        cout << "NO";
        return 0;
    }
}

