#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

string str;
vector<vector<int>> *ptr;
vector<int> anses;
int *out;

int main() {
    ios_base::sync_with_stdio(0);
    ifstream cin("problem2.in");
    ofstream cout("problem2.out");
    cin >> str;
    int n, m, k;
    cin >> n >> m >> k;

    out = new int[n];
    for (int i = 0; i < n; i++) {
        out[i] = 0;
    }

    for (int i = 0; i < k; i++) {
        int j;
        cin >> j;
        out[j - 1] = 1;
    }

    ptr = new vector<vector<int>>[n];

    for (int i = 0; i < n; i++) {
        ptr[i].resize(26);
    }

    for (int i = 0; i < m; i++) {
        int l, r;
        char s;
        cin >> l >> r >> s;
        ptr[l - 1][s - 97].push_back(r);
    }

    vector<bool> *s = new vector<bool>[str.length()+1];
    for (int i = 0; i < str.length()+1; i++) {
        s[i].resize(100);
    }
    for (int i = 0; i < str.length()+1; i++) {
        for (int j = 0; j < 100; j++) {
            s[i][j] = false;
        }
    }
    s[0][0]=true;

    for (int i = 0; i < str.length(); i++) {
        for (int j = 0; j < n; j++) {
            if (s[i][j]) {
                for (int k = 0; k < ptr[j][str[i] - 97].size(); k++) {
                    s[i+1][ptr[j][str[i] - 97][k]-1] = true;
                }
            }
        }
    }

    /*for (int i = 0; i < str.length();i++) {
        for (int j = 0; j < s[i].size(); j++) {
            for (int k = 0; k < ptr[s[i][j]-1][str[i] - 97].size(); k++) {
                s[i + 1].push_back(ptr[s[i][j]-1][str[i] - 97][k]);
            }
        }
    }*/

    for (int i = 0; i < s[str.length()].size(); i++) {
        if (s[str.length()][i] == true && out[i]==1) {
            cout << "Accepts";
            return 0;
        }
    }

    cout << "Rejects";

    return 0;
}
/*
abacaba
4 6 1
2
1 2 a
2 1 c
2 3 b
3 2 a
2 4 b
1 4 a
*/

