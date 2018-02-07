#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

vector<string> *ptr;
bool *out;

void answer() {
    for (int i = 0; i < 26; ++i) {
        if (out[i]) {
            continue;
        }
        for (int j = 0; j < ptr[i].size(); ++j) {
            bool realE = true;
            for (int k = 0; k < ptr[i][j].length(); ++k) {
                if (!out[ptr[i][j][k] - 65]) {
                    realE = false;
                    break;
                }
            }
            if (realE) {
                out[i] = true;
                answer();
            }
        }
    }
}

int main() {
    ifstream cin("epsilon.in");
    ofstream cout("epsilon.out");
    string a;
    int n;
    char S;
    cin >> n >> S;
    getline(cin, a);
    out = new bool[26];
    for (int i = 0; i < 26; i++) {
        out[i] = false;
    }

    ptr = new vector<string>[26];

    for (int i = 0; i < n; ++i) {
        string products;
        getline(cin, products);
        if (products[products.length()-1] == '>') {
            out[products[0] - 65] = true;
            continue;
        }
        bool up = true;
        for (int j = 5; j < products.length(); ++j) {
            if (islower(products[j])) {
                up = false;
                break;
            }
        }
        if (up) {
            ptr[products[0] - 65].push_back(products.substr(5, products.length() - 5));
        }
    }

    answer();

    for (int i = 0; i < 26; ++i) {
        if (out[i]) {
            cout << static_cast<char>(i + 65) << " ";
        }
    }

    return 0;
}

