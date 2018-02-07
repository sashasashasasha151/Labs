#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

bool f(int i, int j) {
    string ans;
    cout << "1 " << i << " " << j << endl;
    cin >> ans;
    if (ans == "YES") {
        return true;
    } else {
        return false;
    }
}

int main() {
    int n;
    cin >> n;
    int *arr = new int[n];
    for (int i = 0; i < n; ++i) {
        arr[i] = i + 1;
    }
    stable_sort(arr, arr + n, f);
    cout << "0 ";
    for (int j = 0; j < n; ++j) {
        cout << arr[j] << " ";
    }
    cout << endl;
    return 0;
}

