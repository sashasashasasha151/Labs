#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <cstring>

using namespace std;

vector<long long int> s;
vector<bool> used;
vector<long long int> classes;
vector<long long int> suf_mas;
vector<vector<long long int>> C;
vector<pair<long long int,long long int>> lcp;

int main() {
    ifstream cin("refrain.in");
    ofstream cout("refrain.out");
//    cout << 150000 << " " << 1 << "\n";
//    for (long long long long int i = 0; i < 150000-1; ++i) {
//        cout << 1 << " ";
//    }
//    cout << 1;
    long long int n,m;
    cin >> n >> m;
    for (long long int i = 0; i < n; ++i) {
        long long int q;
        cin >> q;
        s.push_back(q);
    }
    s.push_back(0);
    used.assign(s.size()+1, false);

    long long int *arr = new long long int[s.size() + 'z'+1];
    fill(arr, arr + s.size() + 'z'+1, 0);
    for (long long int i = 0; i < s.size(); ++i) {
        arr[s[i]]++;
    }

    for (long long int i = 1; i < s.size() + 'z'+1; ++i) {
        arr[i] += arr[i - 1];
    }
    suf_mas.resize(s.size());
    for (long long int i = 0; i < s.size(); ++i) {
        suf_mas[--arr[s[i]]] = i;
    }

    classes.resize(s.size());
    long long int ind = 0;
    classes[suf_mas[0]] = 0;

    for (long long int i = 1; i < suf_mas.size(); ++i) {
        if (s[suf_mas[i]] == s[suf_mas[i - 1]]) {
            classes[suf_mas[i]] = ind;
        } else {
            ind++;
            classes[suf_mas[i]] = ind;
        }
    }
    C.push_back(classes);
    long long int suf_l = 1;
    while (suf_l < s.size()) {
        long long int sort[s.size()];
        for (long long int i = 0; i < s.size(); ++i) {
            sort[i] = (suf_mas[i] - suf_l + s.size()) % s.size();
        }
        fill(arr, arr + s.size() + 'z'+1, 0);
        for (long long int i = 0; i < s.size(); ++i) {
            arr[C[C.size() - 1][sort[i]] + 1]++;
        }
        for (long long int i = 1; i < s.size() + 'z'+1; ++i) {
            arr[i] += arr[i - 1];
        }
        for (long long int i = 0; i < s.size(); ++i) {
            suf_mas[arr[C[C.size() - 1][sort[i]]]++] = sort[i];
        }

        vector<long long int> help(s.size());
        help[suf_mas[0]] = 0;
        for (long long int i = 1; i < s.size(); ++i) {
            if (C[C.size() - 1][suf_mas[i]] == C[C.size() - 1][suf_mas[i - 1]] &&
                C[C.size() - 1][(suf_mas[i] + suf_l) % s.size()] ==
                C[C.size() - 1][(suf_mas[i - 1] + suf_l) % s.size()]) {
                help[suf_mas[i]] = help[suf_mas[i - 1]];
            } else {
                help[suf_mas[i]] = help[suf_mas[i - 1]] + 1;
            }
        }
        C.push_back(help);
        suf_l *= 2;
    }

    for (long long int i = 0; i < s.size() - 1; ++i) {
        long long int val = 0;
        long long int f = suf_mas[i];
        long long int s = suf_mas[i + 1];
        for (long long int j = C.size() - 1; j >= 0; --j) {
            if (C[j][f] == C[j][s]) {
                val += (1 << j);
                f += (1 << j);
                s += (1 << j);
            }
        }
        lcp.push_back({val,i});
    }

    vector<vector<long long int>> ans;
    long long int sze = s.size()-1;
    long long int cont = 1;
    long long int index = 0;

    for (long long int i = 1; i < s.size(); ++i) {
        long long int l = 1;
        while(!ans.size()==0 && lcp[i].first <= ans[ans.size()-1][2]) {
            l += ans[ans.size()-1][0];
            if (l * ans[ans.size()-1][2] > sze * cont || (l * ans[ans.size()-1][2] == cont * sze && ans[ans.size()-1][2]<sze)) {
                cont = l;
                sze = ans[ans.size()-1][2];
                index = suf_mas[ans[ans.size()-1][1]];
            }
            ans.pop_back();
        }
        if (ans.size()==0 || lcp[i].first > ans[ans.size()-1][2]) {
            ans.push_back({l, i , lcp[i].first});
        }
    }


    cout << sze*cont<<"\n"<<sze <<"\n";
    for (long long int i = index; i < index+sze; ++i) {
        cout << s[i] << " ";
    }

    return 0;
}

