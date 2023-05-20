#define null NULL
#define Size(x) (x?x->siz:0)
#define rnd(l,r) uniform_int_distribution<int>(l,r)(seed)
mt19937 seed (time (null));

struct Treap {
    int siz = 1, prior = rnd (1, 2e9);
    Treap *ls = null, Treap *rs = null;
    Treap() {}
};

void Push (Treap *t) {
    if (!t) {
        return;
    }

}

void Pull (Treap *t) {
    Push (t->ls), Push (t->rs);

}

Treap *Merge (Treap *a, Treap *b) {
    if (!a || !b) {
        return a ? a : b;
    }
    if (a->prior > b->prior) {
        Push (a);
        a->rs = Merge (a->rs, b);
        Pull (a);
        return a;
    } else {
        Push (b);
        b->ls = Merge (a, b->ls);
        Pull (b);
        return b;
    }
}

void Split (Treap *t, Treap *&a, Treap *&b, int k) {
    if (!t) {
        a = b = null;
        return;
    }
    Push (t);
    if (Size (t->ls) >= k) {
        b = t;
        Split (t->ls, a, b->ls, k);
        Pull (b);
    } else {
        a = t;
        Split (t->rs, a->rs, b, k - Size (t->ls) - 1);
        Pull (a);
    }
}
