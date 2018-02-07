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
    ifstream cin("cyclic.in");
    ofstream cout("cyclic.out");
    cin.clear();
    getline(cin,s);

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

    vector<int> unsuf(suf_mas.size());
    for (int i = 0; i < suf_mas.size(); ++i) {
        unsuf[suf_mas[i]]=i;
    }
    int index = unsuf[0];

    int q = C[C.size()-1][0];
    int i = 0;
    while (q!=C[C.size()-1][suf_mas[i]]) {
        i++;
    }
    cout << i+1;
//    for (int i = 0; i < s.length() - 1; ++i) {
//        int val = 0;
//        int f = suf_mas[i];
//        int ss = suf_mas[i + 1];
//        for (int j = C.size() - 1; j >= 0; --j) {
//            if (C[j][f] == C[j][ss]) {
//                if(val+(1 << j)>s.length()) {
//                    continue;
//                }
//                val += (1 << j);
//                f = (f+(1 << j))%s.length();
//                ss = (ss+(1 << j))%s.length();
//                if(val == s.length()) {
//                    break;
//                }
//            }
//        }
//        lcp.push_back(val);
//    }
//
//    vector<int> ans;
//    int q = 0;
//    ans.push_back(q);
//    for (int i = 0; i < lcp.size(); ++i) {
//        if (lcp[i] != s.size()) {
//            ans.push_back(i + 1);
//        }
//    }
//    for (int i = 0; i < ans.size(); ++i) {
//        cout << ans[i] << " ";
//    }
//    cout << endl;
//    int k;
//    cin >> k;
//    string answer = "";
//    if (k > ans.size()) {
//        cout << "IMPOSSIBLE";
//    } else {
//        int index = suf_mas[ans[k - 1]];
//        for (int i = index; i < s.length(); ++i) {
//            answer += s[i];
//        }
//        for (int i = 0; i < index; ++i) {
//            answer += s[i];
//        }
//        cout << answer;
//    }
    return 0;
}

