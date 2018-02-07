#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <deque>

using namespace std;

int **arr;
deque<int> ptr;

int main() {
    ifstream cin("fullham.in");
    ofstream cout("fullham.out");
    int n;
    cin >> n;
    arr = new int *[n];
    for (int i = 0; i < n; ++i) {
        arr[i] = new int[n];
        arr[i][i] = 0;
    }
    for (int i = 1; i < n; ++i) {
        string s;
        cin >> s;
        for (int j = 0; j < s.length(); ++j) {
            arr[i][j] = s[j] - '0';
            arr[j][i] = s[j] - '0';
        }
    }
    for (int i = 0; i < n; ++i) {
        ptr.push_back(i);
    }
    int check = 0;
    for (;;) {
        if (arr[ptr[0]][ptr[1]] != 1) {
            check = 0;
            int j=2;
            while(arr[ptr[0]][ptr[j]] == 0 || arr[ptr[1]][ptr[j + 1]] == 0){
                j++;
            }
            reverse(ptr.begin()+1,ptr.begin()+j+1);
        } else {
            check++;
            if (check == n) {
                break;
            }
        }
        ptr.push_back(ptr[0]);
        ptr.pop_front();
    }
    for (int i = 0; i < n; ++i) {
        cout << ptr[i] + 1 << " ";
    }
    return 0;
}

