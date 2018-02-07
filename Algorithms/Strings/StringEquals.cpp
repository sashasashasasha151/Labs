#include <iostream>
#include <string>

using namespace std;

long long int *p;
long long int *h;

int main() {
    string s;
    cin >> s;
    p = new long long int[s.length()];
    h = new long long int[s.length()];
    p[0] = 1;
    h[0] = s[0] - 'a' + 1;
    for (int i = 1; i < s.length(); ++i) {
        p[i] = p[i - 1] * 31;
        h[i] = (h[i - 1] + (s[i] - 'a' + 1) * p[i]);
    }
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;
        if(r1-l1 != r2-l2) {
            cout <<"No"<<"\n";
            continue;
        }
        if ((h[r1 - 1] - ((l1 == 1) ? 0 : h[l1 - 2])) * p[l2-1]== (h[r2 - 1] - ((l2 == 1) ? 0 : h[l2 - 2])) * p[l1-1]) {
            cout << "Yes" << "\n";
        } else {
            cout << "No" << "\n";
        }
    }
    return 0;
}

