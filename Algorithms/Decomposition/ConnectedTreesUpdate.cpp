#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <random>
#include <map>
#include <string>
#include <iterator>

using namespace std;

int pr = 1, n, m;

struct Decard {
    int value;
    int left;
    int right;
    Decard *l;
    Decard *r;
    Decard *parrent;

    Decard(int ll, int rr) {
        left = ll;
        right = rr;
        value = pr++;
        l = nullptr;
        r = nullptr;
        parrent = nullptr;
    }
};

Decard *find_root_in_dec(Decard *U) {
    if (U == nullptr) {
        return nullptr;
    }
    Decard *aa = U;
    while (aa->parrent != nullptr) {
        aa = aa->parrent;
    }
    return aa;
}

Decard *find_max_in_dec(Decard *U) {
    Decard *aa = find_root_in_dec(U);
    if (aa == nullptr) {
        return nullptr;
    }
    while (aa->r != nullptr ) {
        aa = aa->r;
    }
    return aa;
}

void zig(Decard *U) {
    Decard *p = U->parrent;
    Decard *g = p->parrent;

    if (g != nullptr) {
        if (g->l == p) {
            g->l = U;
        } else {
            g->r = U;
        }
    }

    if (p->l == U) {
        p->l = U->r;
        U->r = p;
    } else {
        p->r = U->l;
        U->l = p;
    }
    if (U->l != nullptr) {
        U->l->parrent = U;
    }
    if (U->r != nullptr) {
        U->r->parrent = U;
    }
    if (p->l != nullptr) {
        p->l->parrent = p;
    }
    if (p->r != nullptr) {
        p->r->parrent = p;
    }
    U->parrent = g;

}

Decard *sply(Decard *U) {
    if(U== nullptr) {
        return nullptr;
    }
    if (U->parrent == nullptr) {
        return U;
    }
    Decard *p = U->parrent;
    Decard *g = p->parrent;
    if (g == nullptr) {
        zig(U);
        return U;
    } else {
        if ((g->l == p && p->l == U) || (g->r == p && p->r == U)) {
            zig(p);
            zig(U);
        } else {
            zig(U);
            zig(U);
        }
        return sply(U);
    }
}

Decard *merge(Decard *l, Decard *r) {
    if (l == nullptr) {
        return r;
    }
    if (r == nullptr) {
        return l;
    }
    Decard *aaa = find_max_in_dec(l);
    Decard *aa = sply(aaa);
    aa->r = r;
    r->parrent = aa;
    return aa;
}

pair<Decard *, Decard *> split(Decard *U) {
    if (U == nullptr) {
        return {nullptr, nullptr};
    }
    Decard *ans = sply(U);
    pair<Decard *, Decard *> lr = {ans->l, ans};
    if (lr.first != nullptr) {
        lr.first->parrent = nullptr;
    }
    if (lr.second != nullptr) {
        lr.second->l = nullptr;
    }
    return lr;
}

void inorder(Decard *U) {
    if (U == nullptr) {
        return;
    }
    inorder(U->l);
    cout << U->left << "-" << U->right << " ";
    inorder(U->r);
}

map<pair<int, int>, Decard *> mapp;

void link(int l, int r) {
    Decard *new_edge1 = new Decard(l + 1, r + 1);
    Decard *new_edge2 = new Decard(r + 1, l + 1);
    mapp.insert({{l, r}, new_edge1});
    mapp.insert({{r, l}, new_edge2});
    Decard *ll = mapp[{l, l}];
    Decard *rr = mapp[{r, r}];
    pair<Decard *, Decard *> split_ll = split(ll);
    pair<Decard *, Decard *> split_rr = split(rr);
    Decard *s = merge(split_ll.first, merge(new_edge1, merge(split_rr.second, merge(split_rr.first, merge(new_edge2,
                                                                                                          split_ll.second)))));
}

Decard * delet(Decard *U) {
    Decard *aa = sply(U);
    if (aa->l != nullptr) {
        aa->l->parrent = nullptr;
    }
    if (aa->r != nullptr) {
        aa->r->parrent = nullptr;
    }
    return merge(aa->l, aa->r);
}

bool find_part( Decard* U) {
    Decard *aa = U;
    Decard * son = U;
    while (aa->parrent != nullptr) {
        son = aa;
        aa = aa->parrent;
    }
    if(aa->l==son) {
        return true;
    } else {
        return false;
    }

}

void cut(int l, int r) {
    Decard *del1 = mapp[{l, r}];
    Decard *del2 = mapp[{r, l}];
    Decard * splay1 = sply(del1);
    Decard * splay2 = sply(del2);
    bool le = find_part(del1);

    if(!le) {
        swap(del1,del2);
    }


    pair<Decard *, Decard *> split_ll = split(del1);
    pair<Decard *, Decard *> split_rr = split(del2);
    Decard *lef = split_ll.first;
    Decard *righ = split_rr.second;
    delet(del1);
    righ = delet(del2);
    Decard *aa = merge(sply(lef), sply(righ));

    del1->l= nullptr;
    del1->r= nullptr;
    del1->parrent= nullptr;
    del2->l= nullptr;
    del2->r= nullptr;
    del2->parrent= nullptr;


    auto it1 = mapp.find({l, r});
    mapp.erase(it1);
    auto it2 = mapp.find({r, l});
    mapp.erase(it2);
}

int connected(int l, int r) {
    Decard *ll = mapp[{l, l}];
    Decard *rr = mapp[{r, r}];
    Decard *ll_root = find_root_in_dec(ll);
    Decard *rr_root = find_root_in_dec(rr);
    if (ll_root->value == rr_root->value) {
        return 1;
    } else {
        return 0;
    }
}

//void prin() {
//    for (int i = 0; i < n; ++i) {
//        for (int j = 0; j < n; ++j) {
//            cout << connected(i, j) << " ";
//        }
//        cout << endl;
//    }
//}


int main() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        Decard *s = new Decard(i + 1, i + 1);
        mapp.insert({{i, i}, s});
    }
    for (int i = 0; i < m; ++i) {
        string comand;
        int l, r;
        cin >> comand >> l >> r;
        if (comand == "link") {
            if (l < r) {
                swap(l, r);
            }
            link(l - 1, r - 1);
//            prin();
//            inorder(find_root_in_dec(mapp[{9, 9}]));
//            cout << endl;
        }
        if (comand == "cut") {
            if (l < r) {
                swap(l, r);
            }
            cut(l - 1, r - 1);
//            prin();
//            inorder(find_root_in_dec(mapp[{9, 9}]));
//            cout << endl;
        }
        if (comand == "connected") {
            cout << connected(l - 1, r - 1) << endl;
        }
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

