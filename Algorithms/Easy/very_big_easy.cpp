#include <iostream>
#include <vector>
#include <ctime>

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

long long int gcd(long long int l, long long int r) {
    if (r == 0) {
        return l;
    }
    return gcd(r, l % r);
}

int main() {
    int n = 1;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        long long int k;
        scanf("%lli", &k);
        if (k == 1) {
            cout << "NO\n";
            continue;
        }
        if (k == 2) {
            cout << "YES\n";
            continue;
        }
        srand(time(0));

        long long int s = 0;
        long long int t = k - 1;
        while ((t & 1) == 0) {
            s++;
            t >>= 1;
        }

        bool easy = true;

        for (int j = 0; j < 15; ++j) {
            long long int help = rand() % (k - 2) + 2;

            if (gcd(help, k) != 1) {
                easy = false;
                break;
            }

            long long int x = inc(help, t, k);
            if (x == 1 || x == k - 1) {
                continue;
            }

            bool easy2 = true;

            for (int ii = 0; ii < s; ++ii) {
                x = bin_mul(x, x, k);

                if (x == 1) {
                    easy2 = false;
                    break;
                }
                if (x == k - 1) {
                    break;
                }
                if(ii == s-1) {
                    easy2 = false;
                }
            }
            if (easy2) {
                continue;
            } else {
                easy = false;
                break;
            }
        }
        if (easy) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
}