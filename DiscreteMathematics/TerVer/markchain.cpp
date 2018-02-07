#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
using namespace std;

int main() {
    ifstream cin("markchain.in");
    ofstream cout("markchain.out");
    int n;
    cin >> n;
    double **matrixInput = new double*[n];
    for (int i = 0; i < n; i++) {
        matrixInput[i] = new double[n];
    }

    double **matrixCache = new double*[n];
    for (int i = 0; i < n; i++) {
        matrixCache[i] = new double[n];
    }

    double **matrixInN = new double*[n];
    for (int i = 0; i < n; i++) {
        matrixInN[i] = new double[n];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matrixInN[i][j];
            matrixCache[i][j] = matrixInput[i][j] = matrixInN[i][j];
        }
    }

    for (int k = 1; k < 100; k++){
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                matrixInN[i][j] = 0;
                for (int k = 0; k < n; k++){
                    matrixInN[i][j] += matrixInput[i][k] * matrixInput[k][j];
                }
            }
        }
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++) {
                matrixInput[i][j] = matrixInN[i][j];
            }
        }
    }

    for (int j = 0; j < n; j++) {
        cout << setprecision(4) << matrixInN[0][j] << "  ";
    }
    return 0;
}
/*
4
0.2 0.3 0.4 0.1
0.3 0.4 0.1 0.2
0.4 0.1 0.2 0.3
0.1 0.2 0.3 0.4*/

