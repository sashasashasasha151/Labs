#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <queue>
using namespace std;


vector<pair<int, int>> ptr;
pair<int, int> *help;
int *arr;
int *ans;
int *pre;
int *in;
int *down;
int key = 0;

void dfs(int n) {
    arr[n] = 0;
    down[n] = in[n] = key++;
    int num = 0;
    for (int i = help[n].first; i <= help[n].second; i++) {
        if (i == -1) {
            break;
        }
        int j = ptr[i].second;
        if (arr[j] == -1) {
            pre[j] = n;
            dfs(j);
            down[n] = min(down[n], down[j]);
            if (down[j] >= in[n] && pre[n] != -1) {
                ans[n] = 1;
            }
            num++;
        }
        else if (arr[j] == 0 && j != pre[n]) {
            down[n] = min(down[n], in[j]);
        }
    }
    arr[n] = 1;
    if (num>=2 && pre[n] == -1) {
        ans[n] = 1;
    }
}

int main() {
    ifstream cin("points.in");
    ofstream cout("points.out");
    int n, m, i;
    cin >> n >> m;
    arr = new int[n];
    ans = new int[n];
    pre = new int[n];
    in = new int[n];
    down = new int[n];
    for (int i = 0; i < n; i++) {
        arr[i] = -1;
        pre[i] = -1;
        ans[i] = 0;
    }
    for (int i = 0; i < m; i++) {
        int start, finish;
        cin >> start >> finish;
        ptr.push_back({ start - 1, finish - 1 });
        ptr.push_back({ finish - 1, start - 1 });
    }
    sort(ptr.begin(), ptr.end());
    help = new pair<int, int>[n];
    for (int i = 0; i < n; i++) {
        help[i].first = -1;
        help[i].second = -1;
    }
    for (int i = 0; i < 2 * m; i++) {
        int k = i;
        while (k < 2 * m - 1 && ptr[k].first == ptr[k + 1].first) {
            k++;
        }
        help[ptr[i].first] = { i, k };
        i = k;
    }

    for (int i = 0; i < n; i++) {
        if (arr[i] == -1) {
            dfs(i);
        }
    }

    vector<int> answer;
    for (int i = 0; i < n; i++) {
        if (ans[i] == 1) {
            answer.push_back(i + 1);
        }
    }
    sort(answer.begin(), answer.end());
    cout << answer.size() << "\n";
    for (int i = 0; i < answer.size(); i++) {
        cout << answer[i] << "\n";
    }
    return 0;
}

