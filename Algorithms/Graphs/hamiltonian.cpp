#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <queue>
using namespace std;

int *arr;
int *sum;
vector<pair<int, pair<int, int>>> ptr;
pair<int, int> *help;
vector<int> cache;


void answer(int k) {
    arr[k - 1] = -1;
    for (int i = help[k - 1].first; i <= help[k - 1].second; i++) {
        if (i == -1) {
            break;
        }
        if (arr[ptr[i].second.first - 1] == -1) {
            answer(ptr[i].second.first);
        }
    }
    cache.push_back(k);
    arr[k - 1] = 1;
    return;
}

void add() {
    for (int j = cache.size() - 1; j >= 0; j--) {
        int that = cache[j];
        for (int i = help[that - 1].first; i <= help[that - 1].second; i++) {
            if (i == -1) {
                break;
            }
            int l = min(sum[ptr[i].second.first - 1], sum[that - 1] + ptr[i].second.second);
            sum[ptr[i].second.first - 1] = min(sum[ptr[i].second.first - 1], sum[that - 1] + ptr[i].second.second);
        }
    }
}

int main() {
    ifstream cin("hamiltonian.in");
    ofstream cout("hamiltonian.out");
    int n, m;
    cin >> n >> m;
    arr = new int[n];
    sum = new int[n];
    for (int i = 0; i < n; i++) {
        arr[i] = 0;
        sum[i] = INT_MAX;
    }

    for (int i = 0; i < m; i++) {
        int start, finish;
        cin >> start >> finish;
        ptr.push_back({ start, { finish, -1 } });
    }

    sort(ptr.begin(), ptr.end());

    help = new pair<int, int>[n];
    for (int i = 0; i < n; i++) {
        help[i].first = -1;
        help[i].second = -1;
    }

    for (int i = 0; i < m; i++) {
        int k = i;
        while (k < m - 1 && ptr[k].first == ptr[k + 1].first) {
            k++;
        }
        help[ptr[i].first - 1] = { i, k };
        i = k;
    }

    for (int i = 0; i < m; i++) {
        arr[ptr[i].second.first - 1] = -1;
    }
    vector<int> p,p1;
    for (int i = 0; i < n; i++) {
        if (help[i].first == -1) {
            p1.push_back(i + 1);
        }
        if (arr[i] == 0) {
            p.push_back(i + 1);
            arr[i] = -1;
        }
    }
    if (p.size() == 0 || p.size() > 1 || p1.size() == 0 || p1.size() > 1) {
        cout << "NO";
        return 0;
    }

    answer(p[0]);

    bool k = false;

    for (int i = 0; i < cache.size(); i++) {
        if (cache[i] == p1[0]) {
            k = true;
            break;
        }
    }

    if (k) {
        sum[p[0] - 1] = 0;
        add();
        if (sum[p1[0] - 1] * -1 == n - 1) {
            cout << "YES";
        }
        else {
            cout << "NO";
        }
    }
    else {
        cout << "NO";
        return 0;
    }
    return 0;
}

