#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <cstring>

using namespace std;

string s;
vector<int> classes;
vector<int> suf_mas;
vector<vector<int>> C;
vector<int> lcp;

int main() {
    ifstream cin("count.in");
    ofstream cout("count.out");
    cin >> s;
    s += "$";

    int *arr = new int[s.length() + 'z'+1];
    fill(arr, arr + s.length() + 'z'+1, 0);
    for (int i = 0; i < s.length(); ++i) {
        arr[s[i]]++;
    }

    for (int i = 1; i < s.length() + 'z'+1; ++i) {
        arr[i] += arr[i - 1];
    }
    suf_mas.resize(s.length());
    for (int i = 0; i < s.length(); ++i) {
        suf_mas[--arr[s[i]]] = i;
    }

    classes.resize(s.length());
    int ind = 0;
    classes[suf_mas[0]] = 0;

    for (int i = 1; i < suf_mas.size(); ++i) {
        if (s[suf_mas[i]] == s[suf_mas[i - 1]]) {
            classes[suf_mas[i]] = ind;
        } else {
            ind++;
            classes[suf_mas[i]] = ind;
        }
    }
    C.push_back(classes);
    int suf_l = 1;
    while (suf_l < s.length()) {
        int sort[s.length()];
        for (int i = 0; i < s.length(); ++i) {
            sort[i] = (suf_mas[i] - suf_l + s.length()) % s.length();
        }
        fill(arr, arr + s.length() + 'z'+1, 0);
        for (int i = 0; i < s.length(); ++i) {
            arr[C[C.size() - 1][sort[i]] + 1]++;
        }
        for (int i = 1; i < s.length() + 'z'+1; ++i) {
            arr[i] += arr[i - 1];
        }
        for (int i = 0; i < s.length(); ++i) {
            suf_mas[arr[C[C.size() - 1][sort[i]]]++] = sort[i];
        }

        vector<int> help(s.length());
        help[suf_mas[0]] = 0;
        for (int i = 1; i < s.length(); ++i) {
            if (C[C.size() - 1][suf_mas[i]] == C[C.size() - 1][suf_mas[i - 1]] &&
                C[C.size() - 1][(suf_mas[i] + suf_l) % s.length()] ==
                C[C.size() - 1][(suf_mas[i - 1] + suf_l) % s.length()]) {
                help[suf_mas[i]] = help[suf_mas[i - 1]];
            } else {
                help[suf_mas[i]] = help[suf_mas[i - 1]] + 1;
            }
        }
        C.push_back(help);
        suf_l *= 2;
    }

    for (int i = 0; i < s.length() - 1; ++i) {
        int val = 0;
        int f = suf_mas[i];
        int s = suf_mas[i + 1];
        for (int j = C.size() - 1; j >= 0; --j) {
            if (C[j][f] == C[j][s]) {
                val += (1 << j);
                f += (1 << j);
                s += (1 << j);
            }
        }
        lcp.push_back(val);
    }
    long long int sum = 0;
    for (int i = 0; i < s.length() - 2; ++i) {
        sum+=s.length()-1-suf_mas[i+1]-lcp[i+1];
    }
    sum+=s.length()-1-suf_mas[s.length()-1];
    cout << sum;
    return 0;
}

