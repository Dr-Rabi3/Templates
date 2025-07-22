using cd = complex<double>;
const double PI = acos(-1);

void fft(vector<cd> & a, bool invert) {
    int n = a.size();

    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i+j], v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w *= wlen;
            }
        }
    }

    if (invert) {
        for (cd & x : a)
            x /= n;
    }
}

vector<int> multiply(vector<int> const& a, vector<int> const& b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < (int)a.size() + b.size())
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, true);

    vector<int> result(n);
    for (int i = 0; i < n; i++)
        result[i] = round(fa[i].real());
    return result;
}

vector<int> poly_pow(vector<int> poly, int p, int limit = 1e9) {
    vector<int> ans{1};
    while (p > 0) {
        if(p & 1) ans = multiply(ans, poly);
        poly = multiply(poly, poly);
        ans.resize(limit + 1);
        poly.resize(limit + 1);
        p >>= 1;
    }
    return ans;
}


vector<int> string_match(string s, string ptr) {
    int n = s.size();
    int m = ptr.size();
    vector<int> v1(n), v2(m);
    vector<int>ans_tot(n);
    const int sh = m - 1;
    for (int i = 0;i < 26;i++) { // loop in char in S
        vector<int>p1(n), p2(m);
        // make all valid indices for char c with one (some problem allow distance k)
        // for allow distance add partial sum from l = max(0ll, i - k), r = min(n - 1, i + k)
        // than make max value 1
        for (int j = 0; j < n; ++j) {
            p1[j] = (s[j] - 'a') == i;
        }
        for (int j = 0;j < m;++j) {
            p2[-j + sh] = (ptr[j] -'a') == i;
        }
        auto ans = multiply(p1, p2);
        for (int j = 0;j < n;j++) {
            ans_tot[j] += ans[j];
        }
    }
    return  ans_tot;// match in ans_tot[i + sh]
}