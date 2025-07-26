#define fs first
#define se second
const int N = 1e5 + 5;
const int mod1 = 1e9 + 7, mod2 = 2e9 + 11, B1 = 31, B2 = 131;
pair<int, int> pw[N];
void pre() {
    pw[0] = {1, 1};
    for (int i = 0;i < N;i++) {
        pw[i + 1] = {
            pw[i].fs * 1LL * B1 % mod1,
            pw[i].se * 1LL * B2 % mod2
        };
    }
}

deque<pair<int, int>> build_prefix( const string & str ) {
    int n = str.size();
    deque<pair<int, int>> h(n);
    for (int i = 0; i < n; ++i) {
        if (i) h[i] = h[i - 1];
        h[i] = {
            h[i].fs * 1LL * B1 % mod1,
            h[i].se * 1LL * B2 % mod2,
        };
        h[i] = {
            (h[i].fs + 0LL + str[i]) % mod1,
            (h[i].se + 0LL + str[i]) % mod2,
        };
    }
    return h;
}
deque<pair<int, int>> build_suffix(const string & str) {
    int n = str.size();
    deque<pair<int, int>> rh(n);
    for (int i = n - 1; i >= 0; --i) {
        if (i + 1 < n) rh[i] = rh[i + 1];
        rh[i] = {
            rh[i].fs * 1LL * B1 % mod1,
            rh[i].se * 1LL * B2 % mod2,
        };
        rh[i] = {
            (rh[i].fs + 0LL + str[i]) % mod1,
            (rh[i].se + 0LL + str[i]) % mod2,
        };
    }
    return rh;
}
pair<int, int> query(int l, int r, const deque<pair<int, int>> & h ) {
    auto res = h[r];
    int sz = r - l + 1;
    --l;
    if (l >= 0) {
        res.fs -= h[l].fs * 1LL * pw[sz].fs % mod1;
        res.se -= h[l].se * 1LL * pw[sz].se % mod2;
        if (res.fs < 0)res.fs += mod1;
        if (res.se < 0)res.se += mod2;
    }
    return res;
}
pair<int, int> rev_query(int l, int r, const deque<pair<int, int>> & rh ) {
    auto res = rh[l];
    int n = rh.size();
    int sz = r - l + 1;
    ++r;
    if (r < n) {
        res.fs -= rh[r].fs * 1LL * pw[sz].fs % mod1;
        res.se -= rh[r].se * 1LL * pw[sz].se % mod2;
        if (res.fs < 0)res.fs += mod1;
        if (res.se < 0)res.se += mod2;
    }
    return res;
}
void push_back( char x, deque<pair<int, int>> & h ){ // if rh use push front
    pair<int, int> h1;
    h1.fs = ( h1.fs * B1 ) % mod1;
    h1.fs = ( h1.fs + x ) % mod1;
    h1.se = ( h1.se * B2 ) % mod2;
    h1.se = ( h1.se + x ) % mod2;
    h.emplace_back( h1 );
}
void push_front( char x , deque<pair<int, int>> & h ){ // if rh use push back
    int len = h.size();
    pair<int, int> h1;
    h1.fs = ( h1.fs + ( x * pw [ len ].fs ) % mod1 ) % mod1;
    h1.se = ( h1.se + ( x * pw [ len ].se ) % mod2 ) % mod2;
    h.emplace_front( h1 );
}
void pop_back( deque<pair<int, int>> & h ){
    assert(!h.empty());
    h.pop_back();
}
// can't create pop front because you do prefix sum, if use segment or not use prefix sum do h1.fs = h1.fs - s.front() * pw1 [ s.size() ]
