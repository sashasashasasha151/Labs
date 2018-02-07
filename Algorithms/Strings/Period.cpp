#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    string s;
    cin >> s;
    int *Zf = new int[s.length()];
    fill(Zf, Zf + s.length(), 0);

    int l = 0, r = 0;

    for (int i = 1; i < s.length(); ++i) {
        if(i<=r) {
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
    int ans = s.length();
//    for (int i = 0; i < s.length(); ++i) {
//        cout<< Zf[i];
//    }
    for (int i = 1; i < s.length(); ++i) {
        if(Zf[i]+i==s.length() && s.length()%i==0) {
            ans=i;
            break;
        }
    }
    cout << ans;
    return 0;
}

