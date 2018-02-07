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
    cin >> s;
    s += s;
    int *Zf = new int[s.length()];
    fill(Zf, Zf + s.length(), 0);

    int l = 0, r = 0;

    for (int i = 1; i < s.length(); ++i) {
        if (i <= r) {
            Zf[i] = min(r - i, Zf[i - l]);
        }
        while (i + Zf[i] < s.length() && s[Zf[i]] == s[Zf[i] + i]) {
            Zf[i]++;
        }
        if (i + Zf[i] > r) {
            l = i;
            r = i + Zf[i];
        }
    }
    int ind = 0;
    //cout << s;
    s+=s;
    for (int i = 1; i < s.length() / 4; ++i) {
        //cout<<Zf[i]<<"\n";
        if(s[Zf[i]]>s[i+Zf[i]]) {
            ind++;
        }
    }
    cout << ind+1;
    return 0;
}

