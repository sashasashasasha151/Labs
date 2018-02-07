#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
using namespace std;

int main() {
    ifstream cin("lottery.in");
    ofstream cout("lottery.out");
    double n, m, E = 0, prev = 0, currentP = 1;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        double p, c;
        cin >> p >> c;
        E += currentP * (p - 1) / p * prev;
        prev = c;
        currentP *= (1 / p);
    }
    E += currentP * prev;
    cout << setprecision(13) << n - E;
    return 0;
}

