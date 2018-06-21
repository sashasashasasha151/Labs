#include <iostream>

using namespace std;

long long int bin_mul(long long int l, long long r, long long mod) {
    if (r == 1) {
        return l;
    }
    if (r % 2 == 0) {
        long long int help = bin_mul(l, r / 2, mod);
        return (2 * help) % mod;
    } else {
        return (bin_mul(l, r - 1, mod) + l) % mod;
    }
}

long long int inc(long long int l, long long int r, long long int mod) {
    if (r == 0) {
        return 1;
    }
    if (r % 2 == 0) {
        long long int help = inc(l, r / 2, mod);
        return bin_mul(help, help, mod) % mod;
    } else {
        return (bin_mul(inc(l, r - 1, mod), l, mod)) % mod;
    }
}

int main() {
    long long int n, e, C;
    cin >> n >> e >> C;
    long long int p, q, d;
    for (long long int i = 2; i < n; ++i) {
        if (n % i == 0) {
            p = i;
            q = n / i;
            break;
        }
    }
    long long int E = (q - 1) * (p - 1);
    long long int fac = E;
    long long int sv = E;
    for (long long int i = 2; i*i <= E; ++i) {
        if(E%i==0){
            while (E%i==0){
                E/=i;
            }
            fac-=fac/i;
        }
    }

    if (E > 1) {
        fac -= fac / E;
    }

    d = inc(e,fac-1,sv);

    cout << inc(C, d, n);

    return 0;
}