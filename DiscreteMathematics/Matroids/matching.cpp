#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

vector<vector<int>> G;
vector<int> _G;
vector<int> used;
vector<pair<int,int>> weights;

bool dfs(int k) {
    if(used[k]) {
        return false;
    }
    used[k] = true;
    for (int i = 0; i < G[k].size(); ++i) {
        if(_G[G[k][i]] == -1 || dfs(_G[G[k][i]])) {
            _G[G[k][i]] = k;
            return true;
        }
    }
    return false;
}

int main() {
    ifstream cin("matching.in");
    ofstream cout("matching.out");
    int n;
    cin >> n ;
    G.resize(n);
    for (int i = 0; i < n; ++i) {
        int w;
        cin >> w;
        weights.push_back({w,i});
    }
    sort(weights.begin(),weights.end());

    for (int i = 0; i < n; ++i) {
        int n1;
        cin >> n1;
        for (int j = 0; j < n1; ++j) {
            int k;
            cin >> k;
            G[i].push_back(k-1);
        }
    }

    _G.assign(n,-1);
    for (int i = n-1; i >= 0; --i) {
        used.assign(n,false);
        dfs(weights[i].second);
    }

    vector<int> ans;
    ans.assign(n,-1);
    for (int i = 0; i < _G.size(); ++i) {
        if(_G[i]!=-1) {
            ans[_G[i]] = i;
        }
    }

    for (int i = 0; i < ans.size(); ++i) {
        cout << ans[i]+1 << " ";
    }

    return 0;
}

