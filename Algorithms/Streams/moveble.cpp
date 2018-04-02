#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

vector<vector<double>> arr, weights;
vector<double> _G, used;
vector<double> _GG;
double n;

bool fn(double k) {
    if (used[k]) {
        return false;
    }
    used[k] = true;
    for (int i = 0; i < arr[k].size(); ++i) {
        if (arr[k][i] == 0 && (_G[i] == -1 || fn(_G[i]))) {
            _G[i] = k;
            return true;
        }
    }
    return false;
}

void divide_min() {
    for (int i = 0; i < n; ++i) {
        double min = numeric_limits<double>::max();
        for (int j = 0; j < n; ++j) {
            if (arr[i][j] < min) {
                min = arr[i][j];
            }
        }
        for (int j = 0; j < n; ++j) {
            arr[i][j] -= min;
            arr[i][j] = abs(arr[i][j]);
        }
    }

    for (int i = 0; i < n; ++i) {
        double min = numeric_limits<double>::max();
        for (int j = 0; j < n; ++j) {
            if (arr[j][i] < min) {
                min = arr[j][i];
            }
        }
        for (int j = 0; j < n; ++j) {
            arr[j][i] -= min;
            arr[j][i] = abs(arr[j][i]);
        }
    }
}

void make_kun() {
    _G.assign(n, -1);
    _GG.assign(n, -1);
    for (int i = 0; i < n; ++i) {
        used.assign(n, false);
        fn(i);
    }
    for (int i = 0; i < n; ++i) {
        if (_G[i] != -1) {
            _GG[_G[i]] = i;
        }
    }
}

void strange_f() {
    vector<bool> ii, jj;
    ii.assign(n, false);
    jj.assign(n, false);
    for (int i = 0; i < n; ++i) {
        if (_GG[i] == -1) {
            ii[i] = true;
        }
    }
    for (int i = 0; i < n; ++i) {
        if (ii[i]) {
            for (int j = 0; j < n; ++j) {
                if (arr[i][j] == 0) {
                    jj[j] = true;
                }
            }
        }
    }
    for (int j = 0; j < n; ++j) {
        if (jj[j]) {
            for (int i = 0; i < n; ++i) {
                if (_GG[i] == j) {
                    ii[i] = true;
                }
            }
        }
    }

    double min = numeric_limits<double>::max();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (ii[i] && !jj[j] && arr[i][j] < min) {
                min = arr[i][j];
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (ii[i] && !jj[j]) {
                arr[i][j] -= min;
                arr[i][j] = abs(arr[i][j]);
            }
            if (!ii[i] && jj[j]) {
                arr[i][j] += min;
                arr[i][j] = abs(arr[i][j]);
            }
        }
    }
}

void outt() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << arr[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

int main() {
    cin >> n;
    arr.resize(n);
    weights.resize(n);
    for (int i = 0; i < n; ++i) {
        arr[i].resize(n);
        weights[i].resize(n);
/*        for (int j = 0; j < n; ++j) {
//            cin >> arr[i][j];
//            weights[i][j] = arr[i][j];
*/    }

    vector<pair<pair<double, double>, double>> balls;
    for (int i = 0; i < n; ++i) {
        double l, r, c;
        cin >> l >> r >> c;
        balls.push_back({{l, r}, c});
    }
    for (int i = 0; i < n; ++i) {
        double l, r;
        cin >> l >> r;
        for (int j = 0; j < n; ++j) {
            arr[j][i] = abs(sqrt((l - balls[j].first.first) * (l - balls[j].first.first) +
                                 (r - balls[j].first.second) * (r - balls[j].first.second)) / balls[j].second);
            arr[j][i] = abs(arr[j][i] * arr[j][i] * arr[j][i]);
            weights[j][i] = arr[j][i];
        }
    }

    //outt();
    double old_s = 0;
    while (true) {
        divide_min();
        // outt();
        make_kun();
        double s = 0;
        for (int i = 0; i < n; ++i) {
            //cout << _GG[i] << " ";
            if (_GG[i] != -1) {
                s++;
            }
        }
        //cout << "\n\n";

//        if(old_s == s && n==16){
//            vector<bool> q;
//            q.assign(n,false);
//            for (int i = 0; i < n; ++i) {
//                if(_GG[i] != -1) {
//                    q[i] = true;
//                }
//            }
//            for (int i = 0; i < n; ++i) {
//                if(_GG[i] == -1) {
//                    for (int j = 0; j < n; ++j) {
//                        if(!q[j]) {
//                            _GG[i] = j;
//                            q[j] = true;
//                            break;
//                        }
//                    }
//                }
//            }
//            break;
//        } else {
//            old_s = s;
//        }
        if (s == n) {
            break;
        }

        strange_f();
        //outt();
    }

    double sum = 0;
    for (int i = 0; i < n; ++i) {
        sum = max(sum, weights[i][_GG[i]]);
    }
    cout << cbrt(sum) << "\n";
//    for (int i = 0; i < n; ++i) {
//        cout << _GG[i]+1 << " ";
//    }
    return 0;
}
