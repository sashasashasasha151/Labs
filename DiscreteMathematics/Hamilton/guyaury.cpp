#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <list>
#include <random>
#include <vector>
#include <chrono>

using namespace std;

int **arr;
vector<int> lst;

bool f(int i, int j) {
    if(arr[i][j] == 1) {
        return true;
    } else {
        return false;
    }
}

int main() {
    ifstream cin("guyaury.in");
    ofstream cout("guyaury.out");
    int n;
    cin >> n;
    arr = new int *[n];
    for (int i = 0; i < n; ++i) {
        arr[i] = new int[n];
        arr[i][i] = -1;
    }
    for (int i = 1; i < n; ++i) {
        string s;
        cin >> s;
        for (int j = 0; j < s.length(); ++j) {
            arr[i][j] = s[j] - '0';
            if (arr[i][j] == 0) {
                arr[j][i] = 1;
            } else {
                arr[j][i] = 0;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        lst.push_back(i);
    }
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    shuffle (lst.begin(), lst.end(), std::default_random_engine(seed));
    stable_sort(lst.begin(),lst.end(),f);
    while(arr[lst.back()][lst.front()]!=1) {
        seed = std::chrono::system_clock::now().time_since_epoch().count();

        shuffle (lst.begin(), lst.end(), std::default_random_engine(seed));
        stable_sort(lst.begin(),lst.end(),f);
    }
    for (int i = 0; i < n; ++i) {
        cout << lst[i]+1 << " ";
    }

    return 0;
}

