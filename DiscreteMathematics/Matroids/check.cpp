#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

vector<vector<bool>> G;
bool arr[2000];
vector<int> as;
vector<int> w;

vector<bool> add(vector<bool> a) {
    int i = 0;
    while(a[i] != false) {
        a[i] = false;
        i++;
    }
    a[i] = true;
    return a;
}

int get(vector<bool> k) {
    int number = 0;
    for (int j = 0; j < k.size(); ++j) {
        if(k[j]) {
            number+=1<<j;
        }
    }
    return number;
}

vector<bool> multiply(vector<bool> a, vector<bool> b) {
    vector<bool> h;
    for (int i = 0; i < a.size(); ++i) {
        h.push_back(a[i] && b[i]);
    }
    return h;
}

vector<int> del(vector<bool> a, vector<bool> b) {
    vector<int> h;
    for (int i = 0; i < a.size(); ++i) {
        if(a[i]==true && b[i]==false) {
            h.push_back(i);
        }
    }
    return h;
}

int main() {
    ifstream cin("check.in");
    ofstream cout("check.out");
    fill(arr,arr+2000,false);
    int n,m;
    cin >> n >> m;
    G.resize(m);

    bool t = true;
    for (int i = 0; i < m; ++i) {
        int n1;
        cin >> n1;
        w.push_back(n1);
        if(n1 == 0) {
            t = false;
        }
        G[i].assign(10, false);
        for (int j = 0; j < n1; ++j) {
            int k;
            cin >> k;
            G[i][k-1] = true;
        }
    }
    if(t) {
        cout << "NO" ;
        return 0;
    }

    for (int i = 0; i < G.size(); ++i) {
        int number = 0;
        for (int j = 0; j < G[i].size(); ++j) {
            if(G[i][j]) {
                number+=(1<<j);
            }
        }
        arr[number] = true;
        as.push_back(number);
    }

    for (int i = 0; i < G.size(); ++i) {
        vector<bool> he = {0,0,0,0,0,0,0,0,0,0};
        if(!arr[get(multiply(he,G[i]))]) {
            cout << "NO";
            return 0;
        }
        for (int j = 0; j < as[i]; ++j) {
            he = add(he);
            if(!arr[get(multiply(he,G[i]))]) {
                cout << "NO";
                return 0;
            }
        }
    }

    for (int i = 0; i < G.size()-1; ++i) {
        for (int j = i+1; j < G.size(); ++j) {
            if(w[i]<w[j]) {
                vector<int> hel = del(G[j],G[i]);
                bool help = true;
                for (int k = 0; k < hel.size(); ++k) {
                    if(arr[as[i]+(1<<hel[k])]) {
                        help = false;
                        break;
                    }
                }
                if(help) {
                    cout << "NO";
                    return 0;
                }
            }
            if(w[i]>w[j]) {
                vector<int> hel = del(G[i],G[j]);
                bool help = true;
                for (int k = 0; k < hel.size(); ++k) {
                    if(arr[as[j]+(1<<hel[k])]) {
                        help = false;
                        break;
                    }
                }
                if(help) {
                    cout << "NO";
                    return 0;
                }
            }
        }
    }
    cout << "YES";
    return 0;
}

