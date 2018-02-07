#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>

using namespace std;

struct Vertex {
//    Vertex() {
//        fill(arr, arr + 26, -1);
//        fill(auto_vertexes, auto_vertexes + 26, -1);
//    }

    unordered_map<int,int> arr;
    unordered_map<int,int> auto_vertexes;
//    int arr[26];
//    int auto_vertexes[26];
    bool T = false;
    int parent = -1;
    int symbol = -1;
    int s_link = -1;
    int t_link = -1;
    int sum = 0;
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
        if(k==0||aho[k].parent==0) {
            aho[k].s_link=0;
        } else {
            aho[k].s_link = find_algo_V(find_suf(aho[k].parent),aho[k].symbol);
        }
    }
    return aho[k].s_link;
}

int find_algo_V(int k, int c) {
    if (aho[k].auto_vertexes.find(c) == aho[k].auto_vertexes.end()) {
        if(aho[k].arr.find(c)!= aho[k].arr.end()) {
            aho[k].auto_vertexes[c]=aho[k].arr[c];
        } else {
            if(k==0) {
                aho[k].auto_vertexes[c] = 0;
            } else {
                aho[k].auto_vertexes[c] = find_algo_V(find_suf(k),c);
            }
        }
    }
    return aho[k].auto_vertexes[c];
}

int find_t(int k) {
    if (aho[k].t_link == -1) {
        if(aho[find_suf(k)].T) {
            aho[k].t_link = aho[k].s_link;
        } else {
            if(find_suf(k)==0) {
                aho[k].t_link = 0;
            } else {
                aho[k].t_link = find_t(find_suf(k));
            }
        }
    }
    return aho[k].t_link;
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

    int ind = 0;
    for (int i = 0; i < t.length(); ++i) {
        int help = (aho[ind].auto_vertexes.find(t[i] - 'a') == aho[ind].auto_vertexes.end()) ? find_algo_V(ind,t[i] - 'a'): aho[ind].auto_vertexes[t[i] - 'a'];
        if (aho[help].T) {
            aho[help].have_been = true;
            aho[help].sum++;
        }
        int hts = (aho[help].t_link==-1)?find_t(help):aho[help].t_link;
        while (hts != 0 /*&& !aho[hts].have_been*/) {
            aho[hts].have_been = true;
            aho[hts].sum++;
            hts = (aho[hts].t_link==-1)?find_t(hts):aho[hts].t_link;
        }
        ind = help;
    }

    for (int i = 0; i < str_ind.size(); ++i) {
        cout << aho[str_ind[i]].sum << "\n";
    }
//    for (int i = 0; i < str_ind.size(); ++i) {
//        if (aho[str_ind[i]].have_been) {
//            cout << "YES" << endl;
//        } else {
//            cout << "NO" << endl;
//        }
//    }

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

