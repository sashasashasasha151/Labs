#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>

using namespace std;

struct Vertex {
    unordered_map<int, int> arr;
    bool T = false;
    int parent = -1;
    int symbol = -1;
    int s_link = -1;
    int t_link = -1;
    int sum = 0;
    int add = 0;
    bool have_been = false;
};

vector<string> str;
vector<Vertex> aho;
int n;
bool *used;
vector<int> str_ind;

int find_algo_V(int k, int c);

int find_suf(int k) {
    if (aho[k].s_link == -1) {
        if (k == 0 || aho[k].parent == 0) {
            aho[k].s_link = 0;
        } else {
            aho[k].s_link = find_algo_V(find_suf(aho[k].parent), aho[k].symbol);
        }
    }
    return aho[k].s_link;
}

int find_algo_V(int k, int c) {
    if (aho[k].arr.find(c) == aho[k].arr.end()) {
        if (aho[k].arr.find(c) != aho[k].arr.end()) {
            aho[k].arr[c] = aho[k].arr[c];
        } else {
            if (k == 0) {
                aho[k].arr[c] = 0;
            } else {
                aho[k].arr[c] = find_algo_V(find_suf(k), c);
            }
        }
    }
    return aho[k].arr[c];
}

int find_t(int k) {
    if (aho[k].t_link == -1) {
        if (aho[find_suf(k)].T) {
            aho[k].t_link = aho[k].s_link;
        } else {
            if (find_suf(k) == 0) {
                aho[k].t_link = 0;
            } else {
                aho[k].t_link = find_t(find_suf(k));
            }
        }
    }
    return aho[k].t_link;
}

void dfs(int k) {
    int hts = find_t(k);
    while (hts != 0) {
        aho[hts].sum+=aho[k].add;
        hts = find_t(hts);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    ifstream cin("search5.in");
    ofstream cout("search5.out");
    cin >> n;
    str.resize(n);
    str_ind.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> str[i];
    }
    string t;
    cin >> t;

    aho.push_back(Vertex());

    for (int i = 0; i < n; ++i) {
        int ind = 0;
        for (int j = 0; j < str[i].length(); ++j) {
            int f_ind = ind;
            if (aho[ind].arr.find(str[i][j] - 'a') == aho[ind].arr.end()) {
                aho.push_back(Vertex());
                aho[ind].arr[str[i][j] - 'a'] = aho.size() - 1;
                ind = aho.size() - 1;
            } else {
                ind = aho[ind].arr[str[i][j] - 'a'];
            }
            if (j == str[i].length() - 1) {
                aho[ind].T = true;
                str_ind[i] = ind;
            }
            aho[ind].parent = f_ind;
            aho[ind].symbol = str[i][j] - 'a';
        }
    }

    used = new bool[aho.size()];
    fill(used, used + aho.size(), false);

    int ind = 0;
    for (int i = 0; i < t.length(); ++i) {
        int help = find_algo_V(ind, t[i] - 'a');
        aho[help].add++;
        ind = help;
    }

    for (int i = 0; i < aho.size(); ++i) {
        dfs(i);
    }


    for (int i = 0; i < str_ind.size(); ++i) {
        cout << aho[str_ind[i]].sum + aho[str_ind[i]].add << "\n";
    }

    return 0;
}

/*
 5
 abaaba
 aca
 abcca
 cab
 bb
 q
 */
/*
 4
 hers
 his
 she
 er
 q
 */
/*
 4
 abaab
 baa
 aac
 aa
 q
 */

