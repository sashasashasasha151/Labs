#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<bool> easy;

int main() {
    std::ios::sync_with_stdio(false);
    easy.assign(1000000, true);
    easy[0] = false;
    for (int i = 3; i < 1000000; ++i) {
        if (easy[i]) {
            for (int j = i + i + 1; j < 1000000; j += i + 1) {
                easy[j] = false;
            }
        }
    }
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int k;
        cin >> k;
        if (easy[k - 1] && k % 2 != 0 && k % 3 != 0 || k == 2 || k == 3) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    return 0;
}