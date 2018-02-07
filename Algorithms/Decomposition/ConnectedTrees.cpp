#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <random>
#include <map>
#include <string>

using namespace std;

int pr = 1;
int h = 0;
random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> dist(1, 1000000009);

struct Decard {
    int priority;
    int index;
    int value;
    int size = 1;
    int max;
    int add;
    bool che_pravda_dobavit;
    Decard *l;
    Decard *r;
    Decard *parrent;

    Decard(int k) {
        index = k;
        max = pr;
        value = pr++;
        add = 0;
        priority = dist(gen);
        che_pravda_dobavit = false;
        l = nullptr;
        r = nullptr;
        parrent = nullptr;
    }
};

void push(Decard *U) {
    if (U == nullptr) {
        return;
    }
    if (U->che_pravda_dobavit) {
        U->max = U->add;
        U->value = U->add;
        if (U->l != nullptr) {
            U->l->add = U->add;
            U->l->che_pravda_dobavit = true;
        }
        if (U->r != nullptr) {
            U->r->add = U->add;
            U->r->che_pravda_dobavit = true;
        }
        U->che_pravda_dobavit = false;
    } else {
        return;
    }
}

int sizeOf(Decard *U) {
    if (U == nullptr) {
        return 0;
    } else {
        return U->size;
    }
}

int maxx(Decard *U) {
    if (U == nullptr) {
        return -1;
    } else {
        return U->max;
    }
}

void resize(Decard *k) {
    if (k == nullptr) {
        return;
    }
    k->size = sizeOf(k->l) + sizeOf(k->r) + 1;
    k->max = max(k->value, max(maxx(k->l), maxx(k->r)));
}

Decard *merge(Decard *l, Decard *r) {
    push(l);
    push(r);
    if (l == nullptr) {
        return r;
    }
    if (r == nullptr) {
        return l;
    }
    if (l->priority > r->priority) {
        Decard *help_dec = merge(l->r, r);
        resize(help_dec);
        l->r = help_dec;
        if (help_dec != nullptr) {
            help_dec->parrent = l;
        }
        resize(l);
        return l;
    } else {
        Decard *help_dec = merge(l, r->l);
        resize(help_dec);
        r->l = help_dec;
        if (help_dec != nullptr) {
            help_dec->parrent = r;
        }
        resize(r);
        return r;
    }
}

pair<Decard *, Decard *> split(int k, Decard *U) {
    push(U);
    if (U == nullptr) {
        return {nullptr, nullptr};
    }
    int curIn = sizeOf(U->l) + 1;
    if (curIn <= k) {
        pair<Decard *, Decard *> lr = split(k - curIn, U->r);
        resize(lr.first);
        U->r = lr.first;
        if (lr.first != nullptr) {
            lr.first->parrent = U;
        }
        if (lr.second != nullptr) {
            lr.second->parrent = nullptr;
        }
        resize(U);
        resize(lr.second);
        return make_pair(U, lr.second);
    } else {
        pair<Decard *, Decard *> lr = split(k, U->l);
        resize(lr.second);
        U->l = lr.second;
        if (lr.second != nullptr) {
            lr.second->parrent = U;
        }
        if (lr.first != nullptr) {
            lr.first->parrent = nullptr;
        }
        resize(U);
        resize(lr.first);
        return make_pair(lr.first, U);
    }
}

Decard *add(int pos, int k, Decard *U) {
    pair<Decard *, Decard *> lr = split(pos, U);
    Decard *m = new Decard(k);
    return merge(merge(lr.first, m), lr.second);
}

void inorder(Decard *U) {
    if (U == nullptr) {
        return;
    }
    inorder(U->l);
    cout << U->max << " ";
    inorder(U->r);
}

int ans_max(int l, int r, Decard *U) {
    if (r - l + 1 == sizeOf(U)) {
        return U->max;
    }
    pair<Decard *, Decard *> lr1 = split(l, U);
    pair<Decard *, Decard *> lr2 = split(r - l + 1, lr1.second);
    int a = maxx(lr2.first);
    U = merge(merge(lr1.first, lr2.first), lr2.second);
    return a;
}

void pluss(int k, int l, int r, Decard *U) {
    pair<Decard *, Decard *> lr1 = split(l, U);
    pair<Decard *, Decard *> lr2 = split(r - l + 1, lr1.second);
    lr2.first->add = k;
    lr2.first->che_pravda_dobavit = true;
    U = merge(merge(lr1.first, lr2.first), lr2.second);
}

Decard *find_root_in_dec(Decard *U) {
    Decard *aa = U;
    while (aa->parrent != nullptr) {
        aa = aa->parrent;
    }
    return aa;
}

Decard *find_root_in_path(Decard *U) {
    Decard *aa = find_root_in_dec(U);
    while (aa->l != nullptr) {
        aa = aa->l;
    }
    return aa;
}

vector<Decard *> arr;
int *parrents;
int n, m;
map<pair<int,int>, Decard*> mapp;


Decard * expose(Decard * U) {
    Decard * proot = find_root_in_path(U);
    Decard * droot = find_root_in_dec(U);
    pair<Decard*,Decard*> lr = split(sizeOf(U->l)+1,droot);
    droot = lr.first;
    while (parrents[proot->index]!=-1) {
        Decard * droot2 = find_root_in_dec(arr[parrents[proot->index]]);
        Decard * new_root = merge(droot2,droot);
        droot = new_root;
        proot = find_root_in_path(new_root);
    }
    return droot;
}

void link(int l, int r) {
    Decard *new_edge1 = new Decard(0);
    Decard *new_edge2 = new Decard(0);
    mapp.insert({{l,r},new_edge1});
    mapp.insert({{r,l},new_edge2});
    Decard * ll = mapp[{l,l}];
    Decard * rr = mapp[{r,r}];
    Decard * ll_root = find_root_in_dec(ll);
    Decard * rr_root = find_root_in_dec(rr);
    pair<Decard*,Decard*> split_ll = split(sizeOf(ll->l),ll_root);
    pair<Decard*,Decard*> split_rr = split(sizeOf(rr->l),rr_root);
    Decard * s = merge(split_ll.first,merge(new_edge1,merge(split_rr.second,merge(split_rr.first,merge(new_edge2,split_ll.second)))));
}

void cut(int l, int r) {
    Decard *ll = arr[l];
    Decard *rr = arr[r];
    if(parrents[l] == r) {
        Decard * lll = expose(ll);
        parrents[l] = -1;
        pair<Decard *,Decard*> ans = split((sizeOf(lll)-1),lll);
        pluss(h++,0,sizeOf(ans.first)-1,ans.first);
        pluss(h++,0,sizeOf(ans.second)-1,ans.second);
    } else {
        Decard * rrr = expose(rr);
        parrents[r] = -1;
        pair<Decard *,Decard*> ans = split((sizeOf(rrr)-1),rrr);
        pluss(h++,0,sizeOf(ans.first)-1,ans.first);
        pluss(h++,0,sizeOf(ans.second)-1,ans.second);
    }
}

int connected(int l, int r) {
    Decard * ll = mapp[{l,l}];
    Decard * rr = mapp[{r,r}];
    Decard *hhh = sply;
    Decard * ll_root = find_root_in_dec(ll);
    Decard * rr_root = find_root_in_dec(rr);
    if(ll_root->index==rr_root->index) {
        return 1;
    } else {
        return 0;
    }
}

void prin() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << connected(i,j) << " ";
        }
        cout << endl;
    }
}

int main() {
    cin >> n >> m;
    parrents = new int[n];
    fill(parrents, parrents + n, -1);
    for (int i = 0; i < n; ++i) {
        Decard * s = new Decard(i);
        mapp.insert({{i,i},s});
    }
    for (int i = 0; i < m; ++i) {
        string comand;
        int l, r;
        cin >> comand >> l >> r;
        if (comand == "link") {
            link(l - 1, r - 1);
            for (int j = 0; j < n; ++j) {
                cout << parrents[j] << " ";
            }
            cout << endl;
        }
        if (comand == "cut") {
            cut(l - 1, r - 1);
            for (int j = 0; j < n; ++j) {
                cout << parrents[j] << " ";
            }
            cout << endl;
        }
        if (comand == "connected") {
            //cout << connected(l - 1, r - 1) << endl;
            prin();
        }
        prin();
    }
    return 0;
}

/*
 10 1000
 link 10 9
 link 10 8
 link 10 7
 link 9 6
 link 9 5
 link 8 4
 link 4 2
 link 4 3
 link 4 1
 */