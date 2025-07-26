
#define ll long long
struct SparseSegTree {
    struct node {
        node *l{}, *r{};
        ll mn{}, mx{}, lz{};
    };
    ll sz;
    node *root{};
    SparseSegTree(int n) : sz(n) {
        root = new node();
    }

    void propagate(node *&rt, ll &l, ll &r) {
        if (rt == nullptr) rt = new node();
        if (rt->lz == 0) return;
        if (l < r) {
            if (rt->l == nullptr) rt->l = new node();
            if (rt->r == nullptr) rt->r = new node();
            rt->l->lz += rt->lz;
            rt->r->lz += rt->lz;
        }
        rt->mn += rt->lz;
        rt->mx += rt->lz;
        rt->lz = 0;
    }

    void merge(node *&l, node *&r, node *&s) {
        s->l = l, s->r = r;
        s->mn = 6e18, s->mx = 0;
        if (l) s->mn = min(s->mn, l->mn), s->mx = max(s->mx, l->mx);
        if (r) s->mn = min(s->mn, r->mn), s->mx = max(s->mx, r->mx);
    }

    // seg.update(l, r, add, seg.root);
    void update(ll &lx, ll &rx, ll &x, node *&rt, ll l = 1, ll r = -1) {
        if (r == -1) r = sz;
        propagate(rt, l, r);
        if (l >= lx && r <= rx) {
            rt->lz = x;
            propagate(rt, l, r);
            return;
        }
        if (l > rx || r < lx) return;
        ll mid = l + r >> 1;
        update(lx, rx, x, rt->l, l, mid);
        update(lx, rx, x, rt->r, mid + 1, r);
        merge(rt->l, rt->r, rt);
    }

    // seg.query(l, r, seg.root);
    pair<ll, ll> query(ll &lx, ll &rx, node *&rt, ll l = 1, ll r = -1) {
        if (r == -1) r = sz;
        propagate(rt, l, r);
        if (l >= lx && r <= rx)
            return {rt->mn, rt->mx};
        if (l > rx || r < lx)
            return {6e18, 0};
        ll mid = l + r >> 1;
        auto ql = query(lx, rx, rt->l, l, mid);
        auto qr = query(lx, rx, rt->r, mid + 1, r);
        return {min(ql.first, qr.first), max(ql.second, qr.second)};
    }
};
