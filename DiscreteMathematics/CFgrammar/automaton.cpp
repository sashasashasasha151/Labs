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
    ifstream cin("automaton.in");
    ofstream cout("automaton.out");
    int n;
    char S;
    cin >> n >> S;

    out = new int[27];
    for (int i = 0; i < 27; i++) {
        out[i] = 0;
    }

    out[26] = 1;

    ptr = new vector<vector<int>>[27];

    for (int i = 0; i < 27; i++) {
        ptr[i].resize(26);
    }

    for (int i = 0; i < n; ++i) {
        char s;
        string op, products;
        cin >> s >> op >> products;
        ptr[s - 65][products[0] - 97].push_back((products.length() == 2) ? products[1] : '[');
    }

    int m;
    cin >> m;

    for (int q = 0; q < m; ++q) {
        cin >> str;
        vector<bool> *s = new vector<bool>[str.length() + 1];
        for (int i = 0; i < str.length() + 1; i++) {
            s[i].resize(100);
        }
        for (int i = 0; i < str.length() + 1; i++) {
            for (int j = 0; j < 100; j++) {
                s[i][j] = false;
            }
        }
        s[0][S-65] = true;

        for (int i = 0; i < str.length(); i++) {
            for (int j = 0; j < 27; j++) {
                if (s[i][j]) {
                    for (int k = 0; k < ptr[j][str[i] - 97].size(); k++) {
                        s[i + 1][ptr[j][str[i] - 97][k] - 65] = true;
                    }
                }
            }
        }
        bool kk = true;
        for (int i = 0; i < s[str.length()].size(); i++) {
            if (s[str.length()][i] == true && out[i] == 1) {
                cout << "yes" << "\n";
                kk = false;
                break;
            }
        }

        if (kk) {
            cout << "no" << "\n";
        }
    }

    return 0;
}

