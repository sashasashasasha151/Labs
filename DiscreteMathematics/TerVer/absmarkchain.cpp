#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    ifstream cin("absmarkchain.in");
    ofstream cout("absmarkchain.out");
    int n, m;
    cin >> n >> m;
    vector<pair<pair<int, int>, double>> ptr;
    for (int i = 0; i < m; i++) {
        int left, right;
        double p;
        cin >> left >> right >> p;
        ptr.push_back({ { left-1, right-1 }, p });
    }
    int *arr = new int[n];
    int *cur = new int[n];
    for (int i = 0; i < n; i++) {
        arr[i] = 0;
    }
    int in = 0;
    int out = n;
    for (int i = 0; i < m; i++) {
        if (ptr[i].first.first == ptr[i].first.second && ptr[i].second == 1) {
            arr[ptr[i].first.first] = 1;
            in++;
            out-- ;
        }
    }
    int cuout = 0, cuin = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == 1) {
            cur[i] = cuin++;
        }
        else {
            cur[i] = cuout++;
        }
    }
    double **need = new double*[n];
    for (int i = 0; i < n; i++) {
        need[i] = new double[n];
    }
    double **none = new double*[n];
    for (int i = 0; i < n; i++) {
        none[i] = new double[n];
    }
    double **one = new double*[n];
    for (int i = 0; i < n; i++) {
        one[i] = new double[n];
    }
    double **help = new double*[n];
    for (int i = 0; i < n; i++) {
        help[i] = new double[n];
    }
    double **answer = new double*[n];
    for (int i = 0; i < n; i++) {
        answer[i] = new double[n];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            need[i][j] = 0;
            none[i][j] = 0;
        }
    }

    for (int i = 0; i < m; i++) {
        if (arr[ptr[i].first.second] == 1) {
            if (arr[ptr[i].first.first] == 0) {
                need[cur[ptr[i].first.first]][cur[ptr[i].first.second]] = ptr[i].second;
            }
        }
        else {
            none[cur[ptr[i].first.first]][cur[ptr[i].first.second]] = ptr[i].second;
        }
    }

    for (int i = 0; i < out; i++) {
        one[i][i] = 1;
        help[i][i] = 1;
    }
    for (int i = 0; i < out; i++) {
        for (int j = 0; j < out; j++) {
            help[i][j] -= none[i][j];
        }
    }

    for (int i = 0; i < out; i++) {
        if (help[i][i] != 1) {
            double key = help[i][i];
            for (int j = 0; j < out; j++) {
                help[i][j] /= key;
                one[i][j] /= key;
            }
        }
        for (int j = 0; j < out; j++) {
            if (i != j) {
                double key = help[j][i];
                for (int k = 0; k < out; k++) {
                    help[j][k] -= (key * help[i][k]);
                    one[j][k] -= (key * one[i][k]);
                }
            }
        }
    }

    for (int i = 0; i < out; i++) {
        for (int j = 0; j < in; j++) {
            answer[i][j] = 0;
            for (int k = 0; k < out; k++) {
                answer[i][j] += (one[i][k] * need[k][j]);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        double ans = 0;
        if (arr[i] == 1) {
            for (int j = 0; j < out; j++) {
                ans += answer[j][cur[i]];
            }
            ans++;
            ans /= n;
        }
        cout << ans << "\n";
    }

    return 0;
}
/*
7 10
1 2 0.5
1 3 0.5
3 2 1
2 1 0.8
2 4 0.2
4 5 1
5 5 1
6 4 0.7
6 7 0.3
7 6 1
*/

