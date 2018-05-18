#include <iostream>

using namespace std;

int main() {
    long long int a, b, n, m;
    cin >> a >> b >> n >> m;
    if (n < m) {
        swap(a, b);
        swap(n, m);
    }
    while ((a - b) % m != 0) {
        a += n;
    }
    cout << a;
    return 0;
}