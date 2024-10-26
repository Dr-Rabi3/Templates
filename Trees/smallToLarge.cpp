#include <bits/stdc++.h>

using namespace std;

constexpr int N = 2e5 + 5;

vector<int>adj[N + 1];
vector<int>in(N), sz(N), tree(N), frq(N), arr(N), lvl(N);
int n, res = 0, cnt = 0, id = 0;

void dfs0(int u, int p = -1) {
  in[u] = ++id;
  tree[id] = u;
  sz[u] = 1;
  for (int v : adj[u]) {
    if (v == p) continue;
    dfs0(v, u);
    sz[u] += sz[v];
  }
}

void add(int node) {}
void rem(int node) {}

void dfs1(int u, int p, bool keep) {
  int bg = -1, mx = -1;
  for (int& v : adj[u]) {
    if (v != p && sz[v] > mx)
      mx = v, bg = v;
  }
  for (int& v : adj[u]) {
    if (v == p or v == bg)continue;
    dfs1(v, u, false);
  }
  if (~bg) {
    dfs1(bg, u, true);
  }
  add(u);
  for (int v : adj[u]) {
    if (v == p or v == bg)continue;
    for (int i = 0; i < sz[v]; ++i) {
      int x = tree[in[v] + i];
      add(x);
    }
  }

  //// get the answers here

  if (!keep) {
    for (int i = 0; i < sz[u]; ++i) {
      int x = tree[in[u] + i];
      rem(x);
    }
  }
}