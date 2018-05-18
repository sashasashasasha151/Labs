#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int n, m;

vector<string> table;
vector<vector<int>> arr1, arr2, help;

pair<int, vector<vector<bool>>> drawing(vector<vector<int>> ptr, int color) {
    vector<vector<bool>> answer;
    vector<vector<int>> help;
    int ans = 0;

    answer.resize(2);
    help.resize(2);

    answer[0].assign(ptr.size(), false);
    answer[1].assign(ptr[0].size(), false);
    help[0].assign(ptr.size(), 0);
    help[1].assign(ptr[0].size(), 0);

    int sum = 0;
    for (int i = 0; i < ptr.size(); ++i) {
        sum = 0;
        for (int j : ptr[i]) {
            if (j == color) {
                sum++;
            }
        }
        help[0][i] = sum;
    }

    for (int i = 0; i < ptr[0].size(); ++i) {
        sum = 0;
        for (auto &j : ptr) {
            if (j[i] == color) {
                sum++;
            }
        }
        help[1][i] = sum;
    }

    int index = 0;
    int ii = 0;
    int max = 0;
    for (int i = 0; i < help[0].size(); ++i) {
        if (help[0][i] > max) {
            ii = 0;
            index = i;
            max = help[0][i];
        }
    }
    for (int i = 0; i < help[1].size(); ++i) {
        if (help[1][i] > max) {
            ii = 1;
            index = i;
            max = help[1][i];
        }
    }

    while (max != 0) {
        ans++;
        answer[ii][index] = true;
        help[ii][index] = 0;
        if (ii == 0) {
            for (int i = 0; i < ptr[0].size(); ++i) {
                if (ptr[index][i] == color) {
                    help[1][i]--;
                }
            }
        } else {
            for (int i = 0; i < ptr.size(); ++i) {
                if (ptr[i][index] == color) {
                    help[0][i]--;
                }
            }
        }

        max = 0;
        for (int i = 0; i < help[0].size(); ++i) {
            if (help[0][i] > max) {
                ii = 0;
                index = i;
                max = help[0][i];
            }
        }
        for (int i = 0; i < help[1].size(); ++i) {
            if (help[1][i] > max) {
                ii = 1;
                index = i;
                max = help[1][i];
            }
        }
    }

    return {ans, answer};
}

int main() {
    cin >> n >> m;
    if (n == 1 && m == 1) {
        cout << 0;
        return 0;
    }
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        table.push_back(s);
    }

    help.resize(n);
    for (int i = 0; i < n; ++i) {
        help[i].assign(m, 0);
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if ((i + j) % 2 == 0) {
                help[i][j] = 1;
            }
            //cout << help[i][j];
        }
        //cout << endl;
    }

    int n1 = 0;
    int n2 = 0;
    int m1 = 0;
    int m2 = 0;
    for (int i = 1; i < m; ++i) {
        if (help[0][i] == 1) {
            n1++;
        } else {
            n2++;
        }
        if (help[n - 1][i] == 1) {
            m1++;
        } else {
            m2++;
        }
    }
    for (int i = 0; i < n; ++i) {
        if (help[i][0] == 1) {
            n1++;
            m1++;
        } else {
            n2++;
            m2++;
        }
    }

    arr1.resize(n1);
    arr2.resize(n2);
    for (auto &i : arr1) {
        i.assign(m1, 2);
    }
    for (auto &i : arr2) {
        i.assign(m2, 2);
    }

    for (int i = 0; i < m; i += 2) {
        int ii = (m + 1) / 2 - i / 2 - 1;
        int jj = i / 2;
        int i1 = 0;
        int j1 = i;
        for (; i1 < n && j1 < m; ++i1, ++j1) {
            if (table[i1][j1] == 'W') {
                arr1[ii][jj++] = 0;
            } else {
                arr1[ii][jj++] = 1;
            }
        }
    }

    for (int i = 2; i < n; i += 2) {
        int ii = (m + 1) / 2 + i / 2 - 1;
        int jj = i / 2;
        int i1 = i;
        int j1 = 0;
        for (; i1 < n && j1 < m; ++i1, ++j1) {
            if (table[i1][j1] == 'W') {
                arr1[ii][jj++] = 0;
            } else {
                arr1[ii][jj++] = 1;
            }
        }
    }

    for (int i = 1; i < m; i += 2) {
        int ii = m / 2 - i / 2 - 1;
        int jj = i / 2;
        int i1 = 0;
        int j1 = i;
        for (; i1 < n && j1 < m; ++i1, ++j1) {
            if (table[i1][j1] == 'W') {
                arr2[ii][jj++] = 0;
            } else {
                arr2[ii][jj++] = 1;
            }
        }
    }

    for (int i = 1; i < n; i += 2) {
        int ii = m / 2 + i / 2;
        int jj = i / 2;
        int i1 = i;
        int j1 = 0;
        for (; i1 < n && j1 < m; ++i1, ++j1) {
            if (table[i1][j1] == 'W') {
                arr2[ii][jj++] = 0;
            } else {
                arr2[ii][jj++] = 1;
            }
        }
    }

//    cout << endl;
//
//    for (auto &i : arr1) {
//        for (int j : i) {
//            cout << j;
//        }
//        cout << endl;
//    }
//    cout << endl;
//
//    for (auto &i : arr2) {
//        for (int j : i) {
//            cout << j;
//        }
//        cout << endl;
//    }

    pair<int, vector<vector<bool>>> f0 = drawing(arr1, 0);
    pair<int, vector<vector<bool>>> f1 = drawing(arr1, 1);
    pair<int, vector<vector<bool>>> s0 = drawing(arr2, 0);
    pair<int, vector<vector<bool>>> s1 = drawing(arr2, 1);

    cout << min(f0.first + s1.first, f1.first + s0.first);

    return 0;
}