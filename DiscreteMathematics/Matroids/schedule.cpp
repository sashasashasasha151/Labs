#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <algorithm>

using namespace std;

vector<pair<long long int, long long int>> ptr;
vector<long long int> time;
unordered_map<long long int, long long int> mp;
vector<pair<long long int, long long int>> fake_time;

int main() {
    ifstream cin("schedule.in");
    ofstream cout("schedule.out");
    long long int n;
    cin >> n;

    for (long long int i = 0; i < n; ++i) {
        long long int w, d;
        cin >> d >> w;
        ptr.push_back({w, d});
        time.push_back(d);
    }

    sort(ptr.begin(), ptr.end());
    sort(time.begin(), time.end());

    long long int index = 0;
    mp[time[0]] = index;
    fake_time.push_back({time[0], -1});
    for (long long int i = 1; i < time.size(); ++i) {
        if (time[i] == time[i - 1]) {
            continue;
        } else {
            index++;
            mp[time[i]] = index;
            fake_time.push_back({time[i]-time[i-1], index-1});
        }
    }

//    for (long long int i = 0; i < fake_time.size(); ++i) {
//        cout << fake_time[i].first << " ";
//    }
//    cout << endl;

    long long int ans = 0;
    for (long long int i = ptr.size() - 1; i >= 0; --i) {
        long long int t = mp[ptr[i].second];
        if (fake_time[t].first != 0) {
            fake_time[t].first--;
            continue;
        } else if(fake_time[t].second == -1) {
            ans+=ptr[i].first;
            continue;
        } else if (fake_time[fake_time[t].second].first != 0) {
            fake_time[fake_time[t].second].first--;
        } else {
            fake_time[t].second = fake_time[fake_time[t].second].second;
            i++;
        }
    }
    cout << ans;
    return 0;
}

