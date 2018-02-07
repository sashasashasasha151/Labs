#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    string s,pat,conc="";
    cin >> pat >> s;
    conc +=pat+"!"+s;
    int *pref = new int[conc.length()];
    fill(pref, pref + conc.length(), 0);
    for (int i = 1; i < conc.length(); ++i) {
        int count = pref[i - 1];
        while (count > 0 && conc[i] != conc[count]) {
            count = pref[count - 1];
        }
        if (conc[i] == conc[count]) {
            count++;
        }
        pref[i] = count;
    }
    vector<int> ans;
    for (int i = 0; i < conc.length(); ++i) {
        if(pref[i] == pat.size()) {
            ans.push_back(i);
        }
    }
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); ++i) {
        cout << ans[i]-2*(int)pat.size()+1 << " ";
    }
    return 0;
}

