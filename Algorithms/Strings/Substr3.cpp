#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <cstring>

using namespace std;

vector<string> sss;
string s = "";
vector<int> classes;
vector<int> suf_mas;
vector<vector<int>> C;
int n;
int bar[10] = {60, 61, 62, 63, 64, 65, 66, 67, 68, 69};
vector<int> bars;
vector<int> con;
int number_of = 0;
int *qwer;

int lcp(int l, int r) {
    int val = 0;
    int f = suf_mas[l];
    int ss = suf_mas[r];
    for (int j = C.size() - 1; j >= 0; --j) {
        if (C[j][f] == C[j][ss]) {
            val += (1 << j);
            f += (1 << j)%s.length();
            ss += (1 << j)%s.length();
        }
    }
    return val;
}

int main() {
    ifstream cin("substr3.in");
    ofstream cout("substr3.out");
    cin >> n;
    qwer = new int[n];
    con.assign(n, 0);
    for (int i = 0; i < n; ++i) {
        string str;
        cin >> str;
        sss.push_back(str);
        s += str;
        s += bar[i];
        for (int j = 0; j < str.length(); ++j) {
            bars.push_back(bar[i]);
        }
        bars.push_back(bar[i]);
    }
    if(sss.size()==1) {
        cout << sss[0];
        return 0;
    }
    bool t = true;
    for (int i = 0; i < sss.size()-1; ++i) {
        if(sss[i]!=sss[i+1]) {
            t = false;
        }
    }
    if(t) {
        cout << sss[0];
        return 0;
    }

    int *arr = new int[s.length() + 127];
    fill(arr, arr + s.length() + 127, 0);
    for (int i = 0; i < s.length(); ++i) {
        arr[s[i]]++;
    }

    for (int i = 1; i < s.length() + 127; ++i) {
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
        int * sortt = new int[s.length()];
        for (int i = 0; i < s.length(); ++i) {
            sortt[i] = (suf_mas[i] - suf_l + s.length()) % s.length();
        }
        fill(arr, arr + s.length() + 127, 0);
        for (int i = 0; i < s.length(); ++i) {
            arr[C[C.size() - 1][sortt[i]] + 1]++;
        }
        for (int i = 1; i < s.length() + 127; ++i) {
            arr[i] += arr[i - 1];
        }
        for (int i = 0; i < s.length(); ++i) {
            suf_mas[arr[C[C.size() - 1][sortt[i]]]++] = sortt[i];
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
//    for (int i = 0; i < s.length(); ++i) {
//        cout << s[i];
//    }
//    cout << endl;
//    for (int i = 0; i < s.length(); ++i) {
//        for (int j = suf_mas[i]; j < s.length(); ++j) {
//            cout << s[j];
//        }
//        cout << endl;
//    }
//
//    for (int i = 0; i < n; ++i) {
//        cout << con[i] << " ";
//    }
//    cout << endl;
    int i = 0;
    int l = 0, r = 0;
    int sze = 0;
    int blya = s.length();
    while (l < blya && r < blya) {
        while (number_of < n && r < blya) {
            if (con[bars[suf_mas[r]] - 60] == 0) {
                con[bars[suf_mas[r]] - 60]++;
                number_of++;
            } else {
                con[bars[suf_mas[r]] - 60]++;
            }
            r++;
        }
//        for (int i = 0; i < n; ++i) {
//            cout << con[i] << " ";
//        }
//        cout << endl;
        r--;
//        if (r == s.size()) {
//            break;
//        }
        if (lcp(l, r) > sze) {
            i = l;
            sze = lcp(l, r);
        }

        con[bars[suf_mas[l]] - 60]--;
        if (con[bars[suf_mas[l]] - 60] == 0) {
            number_of--;
        }
        l++;
//        for (int i = 0; i < n; ++i) {
//            cout << con[i] << " ";
//        }
//        cout << endl;
        while (number_of == n && l <= r) {
            if (lcp(l, r) > sze) {
                i = l;
                sze = lcp(l, r);
            }
            con[bars[suf_mas[l]] - 60]--;
            if (con[bars[suf_mas[l]] - 60] == 0) {
                number_of--;
            }
            l++;
        }
        r++;
    }

    string ans = "";
    i = suf_mas[i];
    sze = i+sze;
    for (; i < sze; ++i) {
        ans += s[i];
    }
    cout << ans;
    return 0;
}

