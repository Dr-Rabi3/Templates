#define fs first
#define se second
const int N = 1e5 + 5;
const int mod1 = 1e9 + 7, mod2 = 2e9 + 11, B1 = 31, B2 = 131;
pair<int, int> pw[N];
pair<int, int> h[N], rh[N];
int n;
string str;

void build() {
    pw[0] = {1, 1};
    for (int i = 0; i < n; ++i) {
        pw[i + 1] = {
            pw[i].fs * 1LL * B1 % mod1,
            pw[i].se * 1LL * B2 % mod2
        };
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

}

pair<int, int> query(int l, int r) {
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

pair<int, int> rev_query(int l, int r) {
    auto res = rh[l];
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
// BS take size equal from both sides
int BS (int l1, int l2) {
    if (l1 < 0 or l2 >= n)return 0ll;
    int s = 1, e = min(l1 + 1, n - l2), ans{}, md;
    while (s <= e) {
        md = (e + s) >> 1;
        int r1 = l1 - md + 1;
        int r2 = l2 + md - 1;
        if (query(r1, l1) == rev_query(l2, r2)) {
            ans = md, s = md + 1;
        } else {
            e = md - 1;
        }
    }
    return ans;
}

int main() {
    cin >> n >> str;
    for (int i = 0; i < n; ++i) {
        for (int j:{i, i + 1}) {
            if (j >= n) break;
            auto sz = BS(i, j); // max length of substring that contain i as middle index with odd then even length

        }
    }
    return 0;
}
