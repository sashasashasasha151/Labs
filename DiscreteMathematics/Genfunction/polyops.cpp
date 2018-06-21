#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    long long int n, m;
    cin >> n >> m;
    n++;
    m++;
    vector<long long int> first, second;
    for (long long int i = 0; i < n; ++i) {
        long long int k;
        cin >> k;
        first.push_back(k);
    }
    for (long long int i = 0; i < m; ++i) {
        long long int k;
        cin >> k;
        second.push_back(k);
    }

    long long int min_elem = (n < m) ? 1 : 2;
    vector<long long int> sum = (min_elem == 1) ? second : first;
    for (long long int i = 0; i < min(n, m); ++i) {
        sum[i] += ((min_elem == 1) ? first[i] : second[i]) % 998244353;
    }

    vector<long long int> mul;
    mul.assign(n + m - 1, 0);

    for (long long int i = 0; i < n; ++i) {
        for (long long int j = 0; j < m; ++j) {
            mul[i + j] += (first[i] * second[j]) % 998244353;
        }
    }

    vector<long long int> _second;
    _second.push_back(1);
    for (int i = 1; i < 1000; ++i) {
        long long int k = 0;
        for (int j = 0; j < min(_second.size(), second.size()); ++j) {
            k = (k - (second[j + 1] * _second[_second.size() - j - 1]) % 998244353) % 998244353;
        }
        _second.push_back(k);
    }

    vector<long long int> div;
    div.assign(1000, 0);

    for (long long int i = 0; i < n; ++i) {
        for (long long int j = 0; j < 1000; ++j) {
            if (i + j < 1000) {
                div[i + j] += (first[i] * _second[j]) % 998244353;
                div[i + j] %= 998244353;
            }
        }
    }

    for (int i = n - m + 1; i < div.size(); ++i) {
        div[i] = 0;
    }

    cout << sum.size() - 1 << "\n";
    for (long long int i : sum) {
        cout << i << " ";
    }
    cout << "\n";

    cout << mul.size() - 1 << "\n";
    for (long long int i : mul) {
        cout << i << " ";
    }
    cout << "\n";

    for (long long int i : div) {
        cout << i << " ";
    }
    return 0;
}
/*
3 1
-42 0 -12 1
-3 1
 */