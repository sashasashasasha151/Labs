#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int main() {
    ifstream cin("exam.in");
    ofstream cout("exam.out");
    double n, k;
    cin >> k >> n;
    double answer = 0;
    for (int i = 0; i < k; i++) {
        int left, right;
        cin >> left >> right;
        answer += left / n * right / 100;
    }
    cout << answer;
    return 0;
}

