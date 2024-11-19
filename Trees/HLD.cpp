#include <bits/stdc++.h>
using namespace std;


constexpr int N = 1e4 + 5;

struct SegTree {
  vector<int> seg;
  int N, ign;
  SegTree(int n) {
    N = 1;
    while (N <= n) N <<= 1;
    ign = -1e18;  // Update this if needed (e.g., use a large value for min queries)
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
// vector<int>adj[N]; // for update node
vector<pair<int, int>>adj[N];// for update edge
vector<int>in(N), tree(N), par(N), sz(N), lvl(N), tp(N), arr(N);
vector<int>edge_node(N), edge_cost(N);
SegTree seg(N);
int n, q, id = 0;

void dfs0(int cur, int p) {
  sz[cur] = 1;
  par[cur] = p;
  for (auto neigh : adj[cur]) {
    // int chi = neigh; // (node)
    int chi = neigh.first, idx = neigh.second;// (edge)
    if (chi == p) continue;
    lvl[chi] = lvl[cur] + 1;
    par[chi] = cur;
    edge_node[idx] = chi;
    dfs0(chi, cur);
    sz[cur] += sz[chi];
  }
}

void dfs1(int cur, int p, int top, int idx = 0) {// w for edge
  in[cur] = ++id;
  tree[id] = cur;
  tp[cur] = top;
  seg.update(in[cur], edge_cost[idx]);
  int h_w = -1e18;// for edge
  int h_chi = -1, h_sz = -1;
  for (auto neigh : adj[cur]) {
    // int chi = neigh; //(node)
    int chi = neigh.first;
    if (chi != p and sz[chi] > h_sz)
      h_sz = sz[chi], h_chi = chi, h_w = neigh.second;
  }

  if (!~h_chi) return;
  dfs1(h_chi, cur, top, h_w);
  for (auto neigh : adj[cur]) {
    // int chi = neigh; //(node)
    int chi = neigh.first;// (edge)
    if (chi == p || chi == h_chi) continue;
    dfs1(chi, cur, chi, neigh.second);
  }
}

pair<int, int> query(int u, int v) {
  int res = seg.ign;
  while (tp[u] != tp[v]) {
    if (lvl[tp[u]] < lvl[tp[v]]) swap(u, v);
    res = max(res, seg.query(in[tp[u]], in[u]));
    u = par[tp[u]];
  }
  if (lvl[u] > lvl[v]) swap(u, v);
  // (edge)
  if (in[u] + 1 > in[v]) return { res ,u };
  res = max(res, seg.query(in[u] + 1, in[v]));
  // res = (res + seg.query(in[u], in[v]));// (node)
  return { res,u };// u LCA
}

vector<pair<int , int>>getPath( int u , int v ) {
  vector<pair<int , int>>a , b;
  while ( tp [ u ] != tp [ v ] ) {
    if ( lvl [ tp [ u ] ] < lvl [ tp [ v ] ] ) {
      b.push_back( { in [ tp [ v ] ], in [ v ] } );
      v = par [ tp [ v ] ];
      }
    else {
      a.push_back( { in [ tp [ u ] ], in [ u ] } );
      u = par [ tp [ u ] ];
      }
    }
  if ( lvl [ u ] > lvl [ v ] ) a.push_back( { in [ v ], in [ u ] } );
  else b.push_back( { in [ u ], in [ v ] } );
  reverse( a.begin( ) , a.end( ) );
  reverse( b.begin( ) , b.end( ) );
  a.insert(a.end(), b.begin(), b.end());
  return a;
  }

