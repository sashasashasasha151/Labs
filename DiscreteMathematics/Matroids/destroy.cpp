#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <queue>
using namespace std;

pair<long long int, long long int> *arr;
vector<pair<long long int, pair<long long int, pair<long long int,long long int>>>> ptr;
vector<pair<long long int,pair<bool,long long int>>> used;

long long int check(long long int k) {
    if (k == arr[k].first)
        return k;
    return arr[k].first = check(arr[k].first);
}

void answer(long long int left, long long int right) {
    left = check(left);
    right = check(right);
    if (left != right) {
        if (arr[left].second < arr[right].second)
            swap(left, right);
        arr[right].first = left;
        if (arr[left].second == arr[right].second)
            arr[left].second++;
    }
}

int main() {
    ifstream cin("destroy.in");
    ofstream cout("destroy.out");
    long long int n, m, max;
    cin >> n >> m >> max;
    arr = new pair<long long int, long long int>[n];
    for (long long int i = 0; i < n; i++) {
        arr[i] = { i, 0 };
    }

    for (long long int i = 0; i < m; i++) {
        long long int start, finish, weight;
        cin >> start >> finish >> weight;
        weight*=-1;
        ptr.push_back({ weight, { start, {finish, i+1 }} });
    }

    sort(ptr.begin(), ptr.end());
    long long int ans = 0;
    for (long long int i = 0; i < m; i++) {
        if (check(ptr[i].second.first - 1) != check(ptr[i].second.second.first - 1)) {
            answer(ptr[i].second.first - 1, ptr[i].second.second.first - 1);
            ans += ptr[i].first;
            used.push_back({ptr[i].first*-1,{true,ptr[i].second.second.second}});
        } else {
            used.push_back({ptr[i].first*-1, {false,ptr[i].second.second.second}});
        }
    }
    sort(used.begin(),used.end());
//    for (int i = 0; i < used.size(); ++i) {
//        cout << "{" << used[i].first << " " << used[i].second.first << " " << used[i].second.second << "}";
//    }
//    cout << endl;
    vector<long long int> answer;
    for (long long int i = 0; i < used.size(); ++i) {
        if(!used[i].second.first) {
            if(max-used[i].first>=0) {
                max-=used[i].first;
                answer.push_back(used[i].second.second);
            } else {
                break;
            }
        }
    }

    sort(answer.begin(),answer.end());
    cout << answer.size() << endl;
    for (long long int i = 0; i < answer.size(); ++i) {
        cout << answer[i] << " ";
    }

    return 0;
}
/*
6 6
1 2
2 3
3 4
4 5
5 6
6 1
*/

