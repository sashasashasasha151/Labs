#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct Vertex {
    unordered_map<int, int> arr;
    bool T = false;
    int parent = -1;
    int symbol = -1;
    int s_link = -1;
    int t_link = -1;
    int first_ind = -1;
    bool have_been = false;
};

vector<string> str;
vector<Vertex> aho;
int n;
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

vector<Vertex> aho1;
vector<int> str_ind1;

int find1_algo_V(int k, int c);

int find1_suf(int k) {
    if (aho1[k].s_link == -1) {
        if (k == 0 || aho1[k].parent == 0) {
            aho1[k].s_link = 0;
        } else {
            aho1[k].s_link = find1_algo_V(find1_suf(aho1[k].parent), aho1[k].symbol);
        }
    }
    return aho1[k].s_link;
}

int find1_algo_V(int k, int c) {
    if (aho1[k].arr.find(c) == aho1[k].arr.end()) {
        if (aho1[k].arr.find(c) != aho1[k].arr.end()) {
            aho1[k].arr[c] = aho1[k].arr[c];
        } else {
            if (k == 0) {
                aho1[k].arr[c] = 0;
            } else {
                aho1[k].arr[c] = find1_algo_V(find1_suf(k), c);
            }
        }
    }
    return aho1[k].arr[c];
}

int find1_t(int k) {
    if (aho1[k].t_link == -1) {
        if (aho1[find1_suf(k)].T) {
            aho1[k].t_link = aho1[k].s_link;
        } else {
            if (find1_suf(k) == 0) {
                aho1[k].t_link = 0;
            } else {
                aho1[k].t_link = find1_t(find1_suf(k));
            }
        }
    }
    return aho1[k].t_link;
}

int main() {
    ios_base::sync_with_stdio(0);
    ifstream cin("search6.in");
    ofstream cout("search6.out");
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

    int ind = 0;
    for (int i = 0; i < t.length(); ++i) {
        int help = (aho[ind].arr.find(t[i] - 'a') == aho[ind].arr.end()) ? find_algo_V(ind, t[i] - 'a') : aho[ind].arr[
                t[i] - 'a'];
        if (aho[help].T && !aho[help].have_been) {
            aho[help].have_been = true;
            aho[help].first_ind = i;
        }
        int hts = (aho[help].t_link == -1) ? find_t(help) : aho[help].t_link;
        while (hts != 0 && !aho[hts].have_been) {
            aho[hts].have_been = true;
            aho[hts].first_ind = i;
            hts = (aho[hts].t_link == -1) ? find_t(hts) : aho[hts].t_link;
        }
        ind = help;
    }

    str_ind1.resize(n);
    for (int i = 0; i < n; ++i) {
        reverse(str[i].begin(), str[i].end());
    }
    reverse(t.begin(), t.end());

    aho1.push_back(Vertex());

    for (int i = 0; i < n; ++i) {
        int ind1 = 0;
        for (int j = 0; j < str[i].length(); ++j) {
            int f_ind1 = ind1;
            if (aho1[ind1].arr.find(str[i][j] - 'a') == aho1[ind1].arr.end()) {
                aho1.push_back(Vertex());
                aho1[ind1].arr[str[i][j] - 'a'] = aho1.size() - 1;
                ind1 = aho1.size() - 1;
            } else {
                ind1 = aho1[ind1].arr[str[i][j] - 'a'];
            }
            if (j == str[i].length() - 1) {
                aho1[ind1].T = true;
                str_ind1[i] = ind1;
            }
            aho1[ind1].parent = f_ind1;
            aho1[ind1].symbol = str[i][j] - 'a';
        }
    }

    int ind1 = 0;
    for (int i = 0; i < t.length(); ++i) {
        int help = (aho1[ind1].arr.find(t[i] - 'a') == aho1[ind1].arr.end()) ? find1_algo_V(ind1, t[i] - 'a')
                                                                             : aho1[ind1].arr[t[i] - 'a'];
        if (aho1[help].T && !aho1[help].have_been) {
            aho1[help].have_been = true;
            aho1[help].first_ind = i;
        }
        int hts = (aho1[help].t_link == -1) ? find1_t(help) : aho1[help].t_link;
        while (hts != 0 && !aho1[hts].have_been) {
            aho1[hts].have_been = true;
            aho1[hts].first_ind = i;
            hts = (aho1[hts].t_link == -1) ? find1_t(hts) : aho1[hts].t_link;
        }
        ind1 = help;
    }

    for (int i = 0; i < str_ind.size(); ++i) {
        if (aho[str_ind[i]].first_ind == -1) {
            cout << -1 << " ";
        } else {
            cout << aho[str_ind[i]].first_ind - (int) str[i].length() + 1 << " ";
        }
        if (aho1[str_ind1[i]].first_ind == -1) {
            cout << -1 << "\n";
        } else {
            cout << t.length() - aho1[str_ind1[i]].first_ind - 1 << "\n";
        }
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

