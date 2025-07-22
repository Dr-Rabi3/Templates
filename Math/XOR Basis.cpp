ll mul(ll F, ll S) { return F % mod * (S % mod) % mod; }
 
ll binpow(ll b, ll p) {
  b %= mod;
  ll res = 1;
  while (p) {
    if (p & 1) res = mul(res, b);
    p >>= 1, b = mul(b, b);
  }
  return res;
}
 
template<typename T = int, int B = 31>
struct Basis {
  T a[B];
  int sz{}, freev{};
 
  Basis() {
    memset(a, 0, sizeof a);
    sz = freev = 0;
  }
 
  void insert(T x) {
    for (int i = B - 1; i >= 0; i--) {
      if (x >> i & 1) {
        if (a[i]) x ^= a[i];
        else {
          a[i] = x;
          sz++;
          return;
        }
      }
    }
    ++freev;
  }
 
  bool can(T x) {
    for (int i = B - 1; i >= 0; i--) {
      x = min(x, x ^ a[i]);
    }
    return x == 0;
  }
 
  int count_xors(T x) {
    return (can(x) ? binpow(2, freev) % mod : 0);
  }
 
  T max_xor(T ans = 0) {
    for (int i = B - 1; i >= 0; i--) {
      ans = max(ans, ans ^ a[i]);
    }
    return ans;
  }

  // how meny numbers add to achieve for every a, b in array, a ^ b must also in array
  int needAdd(const vector<int> & arr) {
    int n = arr.size();
    for (int i = 0;i < n;++i) {
      if (can(arr[i])) continue;
      insert(arr[i]);
    }
    return (1LL << sz) - n;
  }
};