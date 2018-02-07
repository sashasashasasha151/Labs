#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

vector<string> ptr[26];
long long ***dp;
bool out[26];

int main() {
    ifstream cin("nfc.in");
    ofstream cout("nfc.out");
    string a;
    int n;
    char S;
    cin >> n >> S;
    getline(cin, a);
    for (int i = 0; i < 26; ++i) {
        out[i] = false;
    }
    for (int i = 0; i < n; ++i) {
        string products;
        getline(cin, products);
        if (products[products.length() - 1] == '>') {
            out[products[0] - 65] = true;
        }
        ptr[products[0] - 65].push_back((products[products.length() - 1] == '>') ? "" : products.substr(5, products.length() - 5));
    }
    cin >> a;
    dp = new long long **[26];
    for (int i = 0; i < 26; ++i) {
        dp[i] = new long long*[a.length()];
        for (int j = 0; j < a.length(); ++j) {
            dp[i][j] = new long long[a.length()];
            for (int k = 0; k < a.length(); ++k) {
                dp[i][j][k] = 0;
            }
        }
    }
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < ptr[i].size(); ++j) {
            if (ptr[i][j].length() == 1) {
                for (int k = 0; k < a.length(); ++k) {
                    if (a[k] == ptr[i][j][0]) {
                        dp[i][k][k] = 1;
                    }
                }
            }
        }
    }
    for (int i = 1; i <= a.length(); ++i) {
        for (int j = 0; j <= a.length() - i; ++j) {
            for (int k = 0; k <= i; ++k) {
                for (int q = 0; q < 26; ++q) {
                    for (int w = 0; w < ptr[q].size(); ++w) {
                        if (ptr[q][w].length() == 2) {
                            if (k == 0) {
                                if (out[ptr[q][w][0] - 65]) {
                                    dp[q][j][j + i - 1] = dp[ptr[q][w][1] - 65][j + k][j + i - 1] % 1000000007;
                                    continue;
                                }
                                continue;
                            }
                            if (k == i) {
                                if (out[ptr[q][w][1] - 65]) {
                                    dp[q][j][j + i - 1] = dp[ptr[q][w][0] - 65][j][j + k - 1] % 1000000007;
                                    continue;
                                }
                                continue;
                            }
                            //cout << dp[ptr[q][w][0] - 65][k - 1][j] << " " << dp[ptr[q][w][1] - 65][i - k][j + k] << endl;
                            dp[q][j][j+i-1] += (dp[ptr[q][w][0] - 65][j][j+k-1] * dp[ptr[q][w][1] - 65][j+k][j + i-1]) % 1000000007;
                            //cout << q << " " << j << " " << j << " " << dp[q][j][j + i - 1] << endl;
                        }
                    }
                }
            }
        }
    }
    cout << dp[S - 65][0][a.length() - 1];
    return 0;
}
/*
6 S
S -> AB
S -> AA
S -> SS
S -> a
A -> a
B -> a
aaa
4 S
S -> AB
A -> a
B -> a
A ->
a
*/

