// Don't forget the build
struct Two2Sat {
   int n, timer = 1;
   vector<vector<int>> adj;
   vector<int> in, low, id, st, id_ans;
   vector<bool> stacked;

   // number of objects not the double
   Two2Sat(int count) {
       n = 2 * count;
       adj.assign(n, {});
   }
   int addVar() {
       adj.push_back({});
       adj.push_back({});
       n += 2;
       return n / 2 - 1;
   }

   void build() {
       in.assign(n, 0);
       low.assign(n, 0);
       id.assign(n, -1);
       stacked.assign(n, 0);
       id_ans.assign(n, -1);

       for (int u = 0; u < n; ++u)
           if (!in[u]) dfs(u);
   }

   int get_neg(int node) {
       return node^1;
   }

   // 0-indexed
   void add_edge(int node_u, int node_v) {
       adj[get_neg(node_u)].push_back(node_v);
       adj[get_neg(node_v)].push_back(node_u);
   }

   void OR(int u, bool neg_u,int v, bool neg_v) { // {01, 10, 11}
       u = (u<<1)^neg_u, v = (v<<1)^neg_v;
       add_edge(u, v);
   }
   void XOR(int u, bool neg_u,int v, bool neg_v) { // {01, 10}
       u = (u<<1)^neg_u, v = (v<<1)^neg_v;
       add_edge(u, v);
       add_edge(get_neg(u), get_neg(v));
   }
   void XNOR(int u, bool neg_u,int v, bool neg_v) { // {00, 11}
       u = (u<<1)^neg_u, v = (v<<1)^neg_v;
       add_edge(get_neg(u), v);
       add_edge(u, get_neg(v));
   }
   void MUST(int u, bool neg_u) { // {1}
       u = (u<<1)^neg_u;
       add_edge(u, u);
   }

   // if u then must v
   void implies(int u, bool neg_u,int v, bool neg_v) {
       u = (u<<1)^neg_u, v = (v<<1)^neg_v;
       add_edge(get_neg(u), v);
   }

   // (1, 1, 1, 1, 1, 0) || (1, 1, 1, 1, 1, 1)
   void allExpectAtMostOne(vector<pair<int, int>> &v){
       OR(v[0].first, v[0].second, addVar(), 1);
       for(int i = 1; i < (int)v.size(); i++){
           int me = addVar();
           OR(v[i].first, v[i].second, me, 1);
           OR(v[i].first, v[i].second, me - 1, 0);
           OR(me - 1,0,  me, 1);
       }
   }
   // (0, 0, 0, 0, 0, 1) || (0, 0, 0, 0, 0, 0)
   void atMostOne(vector<int> &v) {
       OR(v[0], 1, addVar(), 0);
       for (int i = 1;i < v.size();++i) {
           int me = addVar();
           OR(v[i], 1, me, 0);
           OR(v[i], 1, me - 1, 1);
           OR(me - 1, 1, me, 0);
       }
   }

   void dfs(int u) {
       in[u] = low[u] = timer++;
       stacked[u] = 1;
       st.push_back(u);

       for (int& v : adj[u]) {
           if (!in[v]) dfs(v), low[u] = min(low[u], low[v]);
           else if (stacked[v]) low[u] = min(low[u], in[v]);
       }

       if (low[u] == in[u]) {
           int v = -1;
           int fir = -1;
           while (v != u) {
               v = st.back(), st.pop_back(), stacked[v] = 0;
               fir = (fir == -1 ? v : fir);
               id[v] = fir;
               if(~id[get_neg(v)]) id_ans[v] = 0;
               else id_ans[v] = 1;
           }
       }
   }

   // check if can split into two set
   bool can() {
       for (int i = 0; i < n - 1; i += 2) {
           if(id[i] == id[i + 1]) return 0;
       }
       return 1;
   }
   // return one if idx in set
   bool get_val(int idx) { // 0-indexed
       return id_ans[idx * 2];
   }
};
