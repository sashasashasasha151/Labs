#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

vector<string> ptr[26];
bool out[26], o[26];
int outN[26];

void dfs(int n) {
    outN[n] = 2;
    for (int i = 0; i < ptr[n].size(); ++i) {
        for (int j = 0; j < ptr[n][i].length(); ++j) {
            if (!islower(ptr[n][i][j]) && outN[ptr[n][i][j]-65] != 2) {
                dfs(ptr[n][i][j] - 65);
            }
        }
    }
}

void answer() {
    for (int i = 0; i < 26; ++i) {
        if (out[i] || outN[i] == 0) {
            continue;
        }
        int size = 0;
        for (int j = 0; j < ptr[i].size(); ++j) {
            bool realE = false;
            for (int k = 0; k < ptr[i][j].length(); ++k) {
                if (islower(ptr[i][j][k])) {
                    realE = true;
                    break;
                }
                if (out[ptr[i][j][k] - 65]) {
                    continue;
                }
                else {
                    realE = true;
                    break;
                }
            }
            if (realE) {
                break;
            }
            else {
                size++;
            }
        }
        if (size == ptr[i].size()) {
            out[i] = true;
            answer();
            return;
        }
    }
}

int main() {
    ifstream cin("useless.in");
    ofstream cout("useless.out");
    string a;
    int n;
    char S;
    cin >> n >> S;
    getline(cin, a);

    for (int i = 0; i < 26; i++) {
        o[i] = out[i] = false;
        outN[i] = 0;
    }

    for (int i = 0; i < n; ++i) {
        string products;
        getline(cin, products);
        for (int k = 0; k < products.length(); ++k) {
            if (!islower(products[k]) && products[k] < 91 && products[k] > 64) {
                outN[products[k]-65] = 1;
            }
        }
        ptr[products[0] - 65].push_back((products[products.length() - 1] == '>') ? "" : products.substr(5, products.length() - 5));
    }

    dfs(S - 65);

    for (int i = 0; i < 26; ++i) {
        if (outN[i] == 1) {
            out[i] = true;
            continue;
        }
        if (outN[i] == 2) {
            bool t = true;
            for (int j = 0; j < ptr[i].size(); ++j) {
                if (ptr[i][j].length() != 0) {
                    t = false;
                    break;
                }
            }
            if (t) {
                o[i] = true;
                out[i] = true;
            }
        }
    }

    answer();

    for (int i = 0; i < 26; ++i) {
        if (o[i]) {
            for (int j = 0; j < 26; ++j) {
                if (!out[j] && outN[j] != 0) {
                    for (int k = 0; k < ptr[j].size(); ++k) {
                        if (ptr[j][k].size() < 2) {
                            continue;
                        }
                        for (int q = 0; q < ptr[j][k].length();++q) {
                            if (ptr[j][k][q] - 65 == i) {
                                out[i] = false;
                            }
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < 26; ++i) {
        if (out[i]) {
            cout << static_cast<char>(i + 65) << " ";
        }
    }

    return 0;
}

