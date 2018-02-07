#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    ifstream cin("problem5.in");
    ofstream cout("problem5.out");

    int V, E, outV, wordLength;

    cin >> V >> E >> outV >> wordLength;

    vector<int> outVArray;

    for (int i = 0; i < outV; i++) {
        int outVV;
        cin >> outVV;
        outVArray.push_back(outVV);
    }

    vector<int> *arrayOfE = new vector<int>[V];

    for (int i = 0; i < E; i++) {
        int l, r;
        char s;
        cin >> l >> r >> s;
        arrayOfE[l - 1].push_back(r);
    }

    vector<long long> *dpArray = new vector<long long>[wordLength];

    for (int i = 0; i < wordLength; i++) {
        dpArray[i].resize(V);
    }

    for (int i = 0; i < wordLength; i++) {
        for (int j = 0; j < V; j++) {
            dpArray[i][j] = 0;
        }
    }

    for (int i = 0; i < arrayOfE[0].size(); i++) {
        dpArray[0][arrayOfE[0][i] - 1] += 1;
    }

    for (int i = 0; i < wordLength - 1; i++) {
        for (int j = 0; j < V; j++) {
            if (dpArray[i][j] != 0) {
                for (int k = 0; k < arrayOfE[j].size(); k++) {
                    dpArray[i + 1][arrayOfE[j][k] - 1] += dpArray[i][j];
                    dpArray[i + 1][arrayOfE[j][k] - 1] %= 1000000007;
                }
            }
        }
    }
    int sum = 0;
    for (int i = 0; i < outV; i++) {
        sum += dpArray[wordLength - 1][outVArray[i] - 1];
        sum %= 1000000007;
    }

    cout << sum % 1000000007;

    return 0;
}
/*
8 10 1 4
8
1 2 e
1 3 r
2 5 t
3 4 t
4 5 y
5 6 t
5 7 t
5 8 t
6 8 t
7 8 t

11 13 1 5
10
1 10 e
1 2 e
2 3 e
3 4 e
4 5 e
5 10 e
1 6 e
6 7 e
7 8 e
8 9 e
9 10 e
10 11 e
11 10 e

3 3 1 5
2
1 2 e
2 3 e
3 2 e

5 7 1 8
5
1 2 r
2 3 r
3 2 r
2 5 r
4 5 r
3 4 r
4 3 r
*/

