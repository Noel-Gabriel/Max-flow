//
//  PushRelabel.h
//
// Source: https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/PushRelabel.h#L15
//
// Used to debug my own push-relabel

#ifndef PushRelabel_h
#define PushRelabel_h

#include <vector>

using namespace std;


using ll = long long;
using vi = vector<int>;

#define rep(i, j, k) for(int i{j}; i < k; ++i)

struct PushRelabel {
    struct Edge {
        int dest, back;
        ll f, c;
    };
    vector<vector<Edge>> g;
    vector<ll> ec;
    vector<Edge*> cur;
    vector<vi> hs; vi H;
    PushRelabel(int n) : g(n), ec(n), cur(n), hs(2*n), H(n) {}

    void addEdge(int s, int t, ll cap, ll rcap=0) {
        if (s == t) return;
        g[s].push_back({t, (int)size(g[t]), 0, cap});
        g[t].push_back({s, (int)size(g[s])-1, 0, rcap});
    }

    void addFlow(Edge& e, ll f) {
        Edge &back = g[e.dest][e.back];
        if (!ec[e.dest] && f) hs[H[e.dest]].push_back(e.dest);
        e.f += f; e.c -= f; ec[e.dest] += f;
        back.f -= f; back.c += f; ec[back.dest] -= f;
    }
    ll calc(int s, int t) {
        int v = size(g); H[s] = v; ec[t] = 1;
       // vi co(2*v); co[0] = v-1;
        rep(i,0,v) cur[i] = g[i].data();
        for (Edge& e : g[s]) addFlow(e, e.c);

        for (int hi = 0;;) {
            while (hs[hi].empty()) {
                if(hi == 0) {
                    return -ec[s];
                }
                --hi;
            }
            int u = hs[hi].back();
            hs[hi].pop_back();
            while (ec[u] > 0)  // discharge u
                if (cur[u] == g[u].data() + size(g[u])) {
                    H[u] = 1e9;
                    for (Edge& e : g[u]) {
                        if (e.c && H[u] > H[e.dest]+1) {
                            H[u] = H[e.dest]+1;
                            cur[u] = &e;
                        }
                    }
                  /*
                    if (++co[H[u]], !--co[hi] && hi < v)
                        rep(i,0,v) if (hi < H[i] && H[i] < v)
                            --co[H[i]], H[i] = v + 1;
               */
                    hi = H[u];
                } else if (cur[u]->c && H[u] == H[cur[u]->dest]+1) {
                    addFlow(*cur[u], min(ec[u], cur[u]->c));
                } else {
                    ++cur[u];
                }
        }
    }
    void printLabels() {
        for(auto l : H) {
            std::cout << l << " ";
        }
        std::cout << "\n";
    }
    bool leftOfMinCut(int a) { return H[a] >= size(g); }
};


#endif /* PushRelabel_h */
