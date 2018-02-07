#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

int main() {
    ifstream cin("problem1.in");
    ofstream cout("problem1.out");
    string str;
    cin >> str;
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> out;
    for (int i = 0; i < k; i++) {
        int j;
        cin >> j;
        out.push_back(j);
    }

    vector<pair<int, char>> *ptr = new vector<pair<int, char>>[n];

    for (int i = 0; i < m; i++) {
        int l, r;
        char s;
        cin >> l >> r >> s;
        ptr[l - 1].push_back({ r, s });
    }

    int q = 1;

    for (int i = 0; i < str.length(); i++) {
        bool w = true;
        for (int j = 0; j < ptr[q - 1].size(); j++) {
            if (ptr[q - 1][j].second == str[i]) {
                q = ptr[q - 1][j].first;
                w = false;
                break;
            }
        }
        if (w) {
            cout << "Rejects";
            return 0;
        }
    }
    for (int i = 0; i < out.size(); i++) {
        if (out[i] == q) {
            cout << "Accepts";
            return 0;
        }
    }
    cout << "Rejects";
    return 0;
}
/*
abacaba
2 3 1
2
1 2 a
2 1 b
2 1 c
*/

