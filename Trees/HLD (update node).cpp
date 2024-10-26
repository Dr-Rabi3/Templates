#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2e5 + 5;
struct SegTree {
  vector<int> seg;
  int N, ign;
  SegTree(int n) {
    N = 1;
    while (N <= n) N <<= 1;
    ign = 0;  // Update this if needed (e.g., use a large value for min queries)
    seg.assign(N << 1, ign);
  }

  int mrg(int a, int b) { return max(a, b); }

  void update(int i, int val) {
    seg[i += N - 1] = val;
    while ((i >>= 1) >= 1) {
      seg[i] = mrg(seg[i << 1], seg[i << 1 | 1]);
    }
  }

  int query(int l, int r) {
    int ret = ign, k = 0;
    l += N - 2, r += N - 1;
    while ((l += (1 << k)) <= r) {
      ret = mrg(ret, seg[l >> (k = min(__lg(l & -l), __lg(r - l + 1)))]);
    }
    return ret;
  }
};
vector<int>adj[N];
vector<int>in(N), tree(N), par(N), sz(N), lvl(N), tp(N), arr(N);
SegTree seg(N);
int n, q, id = 0;

void dfs0(int cur, int p) {
  sz[cur] = 1;
  par[cur] = p;
  for (int chi : adj[cur]) {
    if (chi == p) continue;
    lvl[chi] = lvl[cur] + 1;
    par[chi] = cur;
    dfs0(chi, cur);
    sz[cur] += sz[chi];
  }
}

void dfs1(int cur, int p, int top) {
  in[cur] = ++id;
  tree[id] = cur;
  tp[cur] = top;
  seg.update(in[cur], arr[cur]);
  int h_chi = -1, h_sz = -1;
  for (int chi : adj[cur])
    if (chi != p and sz[chi] > h_sz) h_sz = sz[chi], h_chi = chi;

  if (!~h_chi) return;
  dfs1(h_chi, cur, top);
  for (int chi : adj[cur]) {
    if (chi == p || chi == h_chi) continue;
    dfs1(chi, cur, chi);
  }
}

int query(int u, int v) {
  int res = 0;
  while (tp[u] != tp[v]) {
    if (lvl[tp[u]] < lvl[tp[v]]) swap(u, v);
    res = max(res, seg.query(in[tp[u]], in[u]));
    u = par[tp[u]];
  }
  if (lvl[u] > lvl[v]) swap(u, v);
  res = max(res, seg.query(in[u], in[v]));
  return res;
}
