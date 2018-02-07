#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <queue>
using namespace std;

void answer(int* arr, queue<int> ans, int current, pair<int, int>* help, vector<pair<int, int>> ptr) {
    if (ans.empty()) {
        return;
    }
    int length = ans.size();
    for (int i = 0; i < length; i++) {
        if (arr[ans.front() - 1] == -1) {
            arr[ans.front() - 1] = current;
            for (int j = help[ans.front() - 1].first; j <= help[ans.front() - 1].second; j++) {
                ans.push(ptr[j].second);
            }
            ans.pop();
        }
        else {
            ans.pop();
        }
    }
    answer(arr, ans, current+1, help, ptr);
}

int main() {
    ifstream cin("pathbge1.in");
    ofstream cout("pathbge1.out");
    int n, m;
    cin >> n >> m;
    int *arr = new int[n];
    for (int i = 0; i < n; i++) {
        arr[i] = -1;
    }

    vector<pair<int, int>> ptr;
    for (int i = 0; i < m; i++) {
        int start, finish;
        cin >> start >> finish;
        ptr.push_back({ start, finish });
        ptr.push_back({ finish, start });
    }
    sort(ptr.begin(), ptr.end());

    pair<int, int> *help = new pair<int, int>[n];
    for (int i = 0; i < n; i++) {
        help[i].first = 0;
        help[i].second = 0;
    }
    for (int i = 0; i < 2*m; i++) {
        int k = i;
        while (k < 2*m-1 && ptr[k].first == ptr[k + 1].first) {
            k++;
        }
        help[ptr[i].first-1] = { i, k };
        i = k;
    }
    queue<int> ans;
    ans.push(1);
    answer(arr, ans, 0, help, ptr);

    for (int i = 0; i < n; i++) {
        if (arr[i] == INT_MAX - 100) {
            cout << 0 << " ";
        }
        else {
            cout << arr[i] << " ";
        }
    }
    return 0;
}

