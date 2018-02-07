#include <iostream>
#include <string>

using namespace std;

int main() {
    string s;
    cin >> s;
    int *pref = new int[s.length()];
    fill(pref, pref + s.length(), 0);
    for (int i = 1; i < s.length(); ++i) {
        int count = pref[i - 1];
        while (count > 0 && s[i] != s[count]) {
            count = pref[count - 1];
        }
        if (s[i] == s[count]) {
            count++;
        }
        pref[i] = count;
    }
    for (int i = 0; i < s.length(); ++i) {
        cout << pref[i] << " ";
    }
    return 0;
}

