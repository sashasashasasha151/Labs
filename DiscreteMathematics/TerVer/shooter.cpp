#include <algorithm>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main() {
    ifstream cin("shooter.in");
    ofstream cout("shooter.out");
    double n, m, k, sum = 0, shooterResult;
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        double shooterP;
        cin >> shooterP;
        if (i == k - 1) {
            shooterResult = pow(1 - shooterP, m);
            sum += shooterResult;
            continue;
        }
        sum += pow(1 - shooterP, m);
    }
    cout << setprecision(13) << shooterResult / sum;
    return 0;
}

