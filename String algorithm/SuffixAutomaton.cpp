
struct SuffixAutomaton {
    struct State {
        map<char, int> next;
        int link = -1;
        int len = 0;
        bool is_clone = false;
        int first_pos = 0;
        long long cnt = 0;
        vector<int> inv_link;
    };

    vector<State> st;
    int last = 0;

    SuffixAutomaton(const string &s) {
        st.reserve(s.size() * 2);
        st.emplace_back();
        for (char c: s)
            extend(c);
        build_occurrences();
        build_inv_links();
    }

    void extend(char c) {
        int cur = st.size();
        st.emplace_back();
        st[cur].len = st[last].len + 1;
        st[cur].first_pos = st[cur].len - 1;
        st[cur].cnt = 1;

        int p = last;
        while (p >= 0 && !st[p].next.count(c)) {
            st[p].next[c] = cur;
            p = st[p].link;
        }
        if (p < 0) {
            st[cur].link = 0;
        } else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len) {
                st[cur].link = q;
            } else {
                int clone = st.size();
                st.push_back(st[q]);
                st[clone].len = st[p].len + 1;
                st[clone].is_clone = true;
                st[clone].cnt = 0; // reset clone count

                while (p >= 0 && st[p].next[c] == q) {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }

    bool contains(const string &t) const {
        int v = 0;
        for (char c: t) {
            if (!st[v].next.count(c))
                return false;
            v = st[v].next.at(c);
        }
        return true;
    }

    long long count_distinct_substrings() const {
        long long ans = 0;
        for (int i = 1; i < (int) st.size(); i++)
            ans += st[i].len - st[st[i].link].len;
        return ans;
    }

    long long total_length_distinct_substrings() const {
        long long tot = 0;
        for (int i = 1; i < (int) st.size(); i++) {
            long long mn = st[st[i].link].len + 1;
            long long mx = st[i].len;
            long long cnt = mx - mn + 1;
            tot += cnt * (mn + mx) / 2;
        }
        return tot;
    }

    string kth_substring(long long k) const {
        int n = st.size();
        vector<long long> dp(n, -1);
        function<long long(int)> dfs = [&](int v) {
            if (dp[v] != -1) return dp[v];
            long long cnt = 1;
            for (auto &e: st[v].next)
                cnt += dfs(e.second);
            return dp[v] = cnt;
        };
        dfs(0);

        string ans;
        int v = 0;
        while (k > 0) {
            for (auto &e: st[v].next) {
                long long c = dp[e.second];
                if (c >= k) {
                    ans.push_back(e.first);
                    k--;
                    v = e.second;
                    break;
                }
                k -= c;
            }
        }
        return ans;
    }

    static string minimal_cyclic_shift(const string &s) {
        SuffixAutomaton sa(s + s);
        string ans;
        int v = 0;
        int n = s.size();
        for (int i = 0; i < n; i++) {
            char best = CHAR_MAX;
            for (auto &e: sa.st[v].next)
                best = min(best, e.first);
            ans.push_back(best);
            v = sa.st[v].next[best];
        }
        return ans;
    }

    void build_occurrences() {
        vector<int> order(st.size());
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(), [&](int a, int b) {
            return st[a].len > st[b].len;
        });
        for (int v: order) {
            if (st[v].link >= 0)
                st[st[v].link].cnt += st[v].cnt;
        }
    }

    void build_inv_links() {
        for (int i = 1; i < (int) st.size(); i++)
            st[st[i].link].inv_link.push_back(i);
    }

    long long count_occurrences(const string &t) const {
        int v = 0;
        for (char c: t) {
            if (!st[v].next.count(c))
                return 0;
            v = st[v].next.at(c);
        }
        return st[v].cnt;
    }

    int first_occurrence(const string &t) const {
        int v = 0;
        for (char c: t) {
            if (!st[v].next.count(c))
                return -1;
            v = st[v].next.at(c);
        }
        return st[v].first_pos - (int) t.size() + 1;
    }

    void report_all(int v, int plen, vector<int> &out) const {
        if (!st[v].is_clone)
            out.push_back(st[v].first_pos - plen + 1);
        for (int u: st[v].inv_link)
            report_all(u, plen, out);
    }

    vector<int> all_occurrences(const string &t) const {
        int v = 0;
        for (char c: t) {
            if (!st[v].next.count(c))
                return {};
            v = st[v].next.at(c);
        }
        vector<int> res;
        report_all(v, t.size(), res);
        sort(res.begin(), res.end());
        return res;
    }

    string shortest_absent(int k) const {
        int n = st.size();
        vector<int> dp(n, -1);
        function<int(int)> dfs = [&](int v) {
            if (dp[v] != -1) return dp[v];
            int ans = INT_MAX;
            for (int c = 0; c < k; c++) {
                char ch = char('a' + c);
                if (!st[v].next.count(ch)) {
                    ans = 1;
                    break;
                }
                ans = min(ans, 1 + dfs(st[v].next.at(ch)));
            }
            return dp[v] = ans;
        };
        dfs(0);

        string ans;
        int v = 0;
        while (true) {
            if (dp[v] == 1) {
                for (int c = 0; c < k; c++) {
                    char ch = char('a' + c);
                    if (!st[v].next.count(ch)) {
                        ans.push_back(ch);
                        return ans;
                    }
                }
            }
            for (int c = 0; c < k; c++) {
                char ch = char('a' + c);
                int u = st[v].next.count(ch) ? st[v].next.at(ch) : -1;
                if (u >= 0 && dp[v] == 1 + dp[u]) {
                    ans.push_back(ch);
                    v = u;
                    break;
                }
            }
        }
    }

    static string LCS(const string &A, const string &B) {
        SuffixAutomaton sa(A);
        int v = 0, l = 0, best = 0, bestpos = 0;
        for (int i = 0; i < (int) B.size(); i++) {
            while (v && !sa.st[v].next.count(B[i])) {
                v = sa.st[v].link;
                l = sa.st[v].len;
            }
            if (sa.st[v].next.count(B[i])) {
                v = sa.st[v].next.at(B[i]);
                l++;
            }
            if (l > best) {
                best = l;
                bestpos = i;
            }
        }
        return B.substr(bestpos - best + 1, best);
    }

    static string LCS_multi(const vector<string> &ss) {
        int K = ss.size();
        string T;
        vector<int> origin;
        for (int i = 0; i < K; i++) {
            if (i) {
                char sep = char(128 + i);
                T.push_back(sep);
                origin.push_back(-1);
            }
            for (char c: ss[i]) {
                T.push_back(c);
                origin.push_back(i);
            }
        }
        SuffixAutomaton sa(T);
        int N = sa.st.size();
        vector<int> mask(N, 0);

        int v = 0;
        for (int i = 0; i < (int) T.size(); i++) {
            v = sa.st[v].next[T[i]];
            if (origin[i] >= 0)
                mask[v] |= 1 << origin[i];
        }

        vector<int> order(N);
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(), [&](int a, int b) {
            return sa.st[a].len > sa.st[b].len;
        });
        for (int x: order) {
            if (sa.st[x].link >= 0)
                mask[sa.st[x].link] |= mask[x];
        }

        int full = (1 << K) - 1;
        int bestL = 0, bestS = 0;
        for (int i = 1; i < N; i++) {
            if (mask[i] == full && sa.st[i].len > bestL) {
                bestL = sa.st[i].len;
                bestS = i;
            }
        }
        if (!bestL) return string();
        int endpos = sa.st[bestS].first_pos;
        return T.substr(endpos - bestL + 1, bestL);
    }
};
