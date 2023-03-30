#include <stdio.h>

int tree[4 * 400];
int v[400];
void build(int nod, int l, int r) {
    if(l == r) {
        tree[nod] = v[l];
        return;
    }
    int m =  (l + r)/2;
    build(2 * nod, l, m);
    build(2 * nod + 1, m + 1 , r);
    tree[nod] = max(tree[2 * nod], tree[2 * nod + 1]);
}

void update(int nod, int l, int r, int poz, int val) {
    if (l == r) {
        v[poz] = val;
        tree[nod] = val;
        return;
    }

    int m = (l + r)/2;
    if (poz < m) {
        update(2 * nod, l, m, poz, val);
    } else {
        update(2 * nod + 1, m+1, r, poz, val);

    }
}

