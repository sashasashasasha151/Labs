//#include <iostream>
//#include <vector>
//#include <random>
//#include <ctime>
//#include <cmath>
//
//using namespace std;
//
//struct Vertex {
//    long long int color = 1;
//    long long int length_w=0;
//    long long int length_b=0;
//    long long int amount_b=1;
//    long long int amount_w=0;
//    vector<pair<long long int, long long int>> length_s;
//    long long int position=-1;
//    vector<long long int> cs;
//    long long int own_index;
//};
//
//long long int *ans, *sons, *in, *df3;
//bool *used;
//long long int t, n, m, root, index = 1;
//vector<Vertex> vertexes;
//
//vector<vector<long long int>> G, C;
//
//long long int make_sons(long long int k, long long int d, long long int max, bool ot) {
//    in[k] = d;
//    sons[k] = 1;
//    bool check = true;
//    for (long long int i = 0; i < G[k].size(); ++i) {
//        if (ans[G[k][i]] == -2 && in[G[k][i]] != d) {
//            sons[k] += make_sons(G[k][i], d, max, false);
//
//        }
//    }
//    if ((sons[k] * 2 > max || ot) && t == -1) {
//        t = k;
//    }
//    return sons[k];
//}
//
//void make_dec(long long int k, long long int par, long long int d) {
//    t = -1;
//    long long int unused = make_sons(k, d, n / (1 << d), true);
//
//    ans[t] = par;
//
//    long long int tt = t;
//    for (long long int i = 0; i < G[tt].size(); ++i) {
//        if (ans[G[tt][i]] == -2) {
//            make_dec(G[tt][i], tt, d + 1);
//        }
//    }
//}
//
//pair<long long int,long long int> dfs_pos(long long int k,long long int ind,long long int pos, long long int de) {
//    vertexes[k].position = pos;
//    vertexes[k].cs.push_back(de);
//    vertexes[k].length_b = 0;
//    vertexes[k].amount_b = 1;
//    df3[k] = ind;
//    for (long long int i = 0; i < G[k].size(); ++i) {
//        if (df3[G[k][i]] != ind && used[G[k][i]]) {
//            pair<long long int,long long int> get_pair = dfs_pos(G[k][i],ind,pos,de+1);
//            vertexes[k].amount_b+=get_pair.first;
//            vertexes[k].length_b+=get_pair.second+get_pair.first;
//        }
//    }
//    return {vertexes[k].amount_b,vertexes[k].length_b};
//}
//
//void dfs(long long int k, long long ind) {
//    used[k] = false;
//    vertexes[k].length_b = 0;
//    vertexes[k].amount_b = 1;
//    vertexes[k].own_index = ind;
//    long long int ii = 0;
//    for (long long int i = 0; i < G[k].size(); ++i) {
//        if (used[G[k][i]]) {
//            pair<long long int,long long int> get_pair = dfs_pos(G[k][i],index++,ii++,1);
//            vertexes[k].amount_b+=get_pair.first;
//            vertexes[k].length_b+=get_pair.second+get_pair.first;
//            vertexes[k].length_s.push_back({0,get_pair.second+get_pair.first});
//        }
//    }
//    for (long long int i = 0; i < C[k].size(); ++i) {
//        if (used[C[k][i]]) {
//            dfs(C[k][i],ind+1);
//        }
//    }
//}
//
//long long int find(long long int k) {
//    long long q = k;
//    long long int v = ans[k];
//    long long int summa;
//    if (vertexes[k].color == 1) {
//        long long int sum = vertexes[k].length_b;
//        while (v != -1) {
//            sum += vertexes[v].length_b - vertexes[v].length_s[vertexes[k].position].second +
//                    vertexes[q].cs[vertexes[v].own_index] * (vertexes[v].amount_b - vertexes[k].amount_b);
//            k = v;
//            v = ans[v];
//        }
//        summa = sum;
//    } else {
//        long long int sum = vertexes[k].length_w;
//        while (v != -1) {
//            sum += vertexes[v].length_w - vertexes[v].length_s[vertexes[k].position].first +
//                    vertexes[q].cs[vertexes[v].own_index] * (vertexes[v].amount_w - vertexes[k].amount_w);
//            k = v;
//            v = ans[v];
//        }
//        summa = sum;
//    }
//    return summa;
//}
//
//void change(long long int k) {
//    long long int q = k;
//    long long int v = ans[k];
//    if (vertexes[k].color == 1) {
//        vertexes[k].color = 0;
//        vertexes[k].amount_b--;
//        vertexes[k].amount_w++;
//        while (v != -1) {
//            vertexes[v].amount_b--;
//            vertexes[v].amount_w++;
//            vertexes[v].length_b -= vertexes[q].cs[vertexes[v].own_index];
//            vertexes[v].length_w += vertexes[q].cs[vertexes[v].own_index];
//            vertexes[v].length_s[vertexes[k].position].second -= vertexes[q].cs[vertexes[v].own_index];
//            vertexes[v].length_s[vertexes[k].position].first += vertexes[q].cs[vertexes[v].own_index];
//            k = v;
//            v = ans[v];
//        }
//    } else {
//        vertexes[k].color = 1;
//        vertexes[k].amount_b++;
//        vertexes[k].amount_w--;
//        while (v != -1) {
//            vertexes[v].amount_b++;
//            vertexes[v].amount_w--;
//            vertexes[v].length_b += vertexes[q].cs[vertexes[v].own_index];
//            vertexes[v].length_w -= vertexes[q].cs[vertexes[v].own_index];
//            vertexes[v].length_s[vertexes[k].position].second += vertexes[q].cs[vertexes[v].own_index];
//            vertexes[v].length_s[vertexes[k].position].first -= vertexes[q].cs[vertexes[v].own_index];
//            k = v;
//            v = ans[v];
//        }
//    }
//}
//
//void pr() {
//    for (long long int i = 0; i < n; ++i) {
//        cout << find(i) << " ";
//    }
//}
//
//int main() {
//    cin >> n >> m;
//
//    G.resize(n);
//    C.resize(n);
//    vertexes.resize(n);
//
//    for (long long int i = 0; i < n; ++i) {
//        Vertex v;
//        vertexes[i] = v;
//    }
//
//    ans = new long long int[n];
//    fill(ans, ans + n, -2);
//
//    sons = new long long int[n];
//    in = new long long int[n];
//
//    used = new bool[n];
//    fill(used, used + n, true);
//
//    df3 = new long long int[n];
//    fill(df3, df3 + n, 0);
//
//    for (long long int i = 0; i < n - 1; ++i) {
//        long long int u, v;
//        cin >> u >> v;
//        G[u - 1].push_back(v - 1);
//        G[v - 1].push_back(u - 1);
//    }
//
//    make_dec(0, -1, 0);
//
//    for (long long int i = 0; i < n; ++i) {
//        if (ans[i] == -1) {
//            root = i;
//            break;
//        }
//    }
//
//    for (long long int i = 0; i < n; ++i) {
//        if (ans[i] == -1) {
//            continue;
//        }
//        C[i].push_back(ans[i]);
//        C[ans[i]].push_back(i);
//    }
//
//    vertexes[root].position = -1;
//    used[root] = false;
//    dfs(root,0);
//
//    for (long long int i = 0; i < m; ++i) {
//        long long int l, r;
//        cin >> l >> r;
//        (l==1) ? change(r - 1) : cout << find(r - 1) << endl;
//    }
//    return 0;
//}
//
//
//
//
//
//
//
//
//
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

vector<int> *ptr;
vector<int> *unPtr;
vector<int> out;

int *arr;
int *sumArr;
int a = 1;

void dfs(int k) {
    arr[k - 1] = 1;
    for (int i = 0; i < ptr[k - 1].size(); i++) {
        if (arr[ptr[k - 1][i] - 1] == 0) {
            dfs(ptr[k - 1][i]);
        }
    }
}

void secondDfs(int k) {
    arr[k - 1] = 2;
    for (int i = 0; i < unPtr[k - 1].size(); i++) {
        if (arr[unPtr[k - 1][i] - 1] == 1) {
            secondDfs(unPtr[k - 1][i]);
        }
    }
}

void cycle(int k) {
    if (a == 0) {
        return;
    }
    arr[k - 1] = 3;
    for (int i = 0; i < ptr[k - 1].size(); i++) {
        if (arr[ptr[k - 1][i] - 1] == 2) {
            cycle(ptr[k - 1][i]);
        }
        if (arr[ptr[k - 1][i] - 1] == 3) {
            a = 0;
            break;
        }
    }
    arr[k - 1] = 4;
    return;
}

int anss(int t) {
    if (arr[t - 1] == 5) {
        return sumArr[t - 1];
    }
    int sum = 0;
    for (int i = 0; i < unPtr[t - 1].size(); i++) {
        if (arr[unPtr[t - 1][i] - 1] == 4 || arr[unPtr[t - 1][i] - 1] == 5) {
            sum += anss(unPtr[t - 1][i]);
            sum %= 1000000007;
        }
    }
    arr[t - 1] = 5;
    sumArr[t - 1] = sum;
    return sum;
}

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    for (int i = 0; i < k; i++) {
        int j;
        cin >> j;
        out.push_back(j);
    }

    ptr = new vector<int>[n];
    unPtr = new vector<int>[n];

    for (int i = 0; i < m; i++) {
        int l, r;
        char s;
        cin >> l >> r >> s;
        ptr[l - 1].push_back(r);
        unPtr[r - 1].push_back(l);
    }

    arr = new int[n];
    sumArr = new int[n];

    for (int i = 0; i < n; i++) {
        arr[i] = 0;
        sumArr[i] = 0;
    }

    dfs(1);

    vector<int> outTrue;

    for (int i = 0; i < out.size(); i++) {
        if (arr[out[i] - 1] == 1) {
            outTrue.push_back(out[i]);
        }
    }

    if (outTrue.size() == 0) {
        cout << 0;
        return 0;
    }

    for (int i = 0; i < outTrue.size(); i++) {
        secondDfs(outTrue[i]);
    }

    cycle(1);

    if (a == 0) {
        cout << -1;
        return 0;
    }

    sumArr[0] = 1;
    arr[0] = 5;
    long long kol = 0;

    for (int i = 0; i < outTrue.size(); i++) {
        kol += anss(outTrue[i]);
        kol %= 1000000007;
    }
    cout << kol;

    return 0;
}
/*
5 5 1
3
1 2 r
2 3 r
2 4 r
4 5 r
5 4 r
*/