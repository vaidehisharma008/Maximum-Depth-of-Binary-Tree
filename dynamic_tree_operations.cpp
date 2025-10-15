#include <bits/stdc++.h>
using namespace std;

/*
 Link-Cut Tree supporting:
  - link(u, v)
  - cut(u, v)
  - query(u, v) -> sum of node values along path u..v
  - set u val  -> update value at node u
 Implementation details:
  - splay-based LCT with typical access/splay/makeRoot/findRoot
  - each node stores: ch[2], fa, rev flag, val (self), sum (aggregate)
*/

struct LinkCut {
    int n;
    struct Node {
        int ch[2];
        int fa;
        bool rev;
        long long val;
        long long sum;
        Node(): fa(0), rev(false), val(0), sum(0) { ch[0]=ch[1]=0; }
    };
    vector<Node> t;

    LinkCut(int n=0): n(n), t(n+1) {}

    void init(int N) {
        n = N;
        t.assign(n+1, Node());
    }

    // helper: is x a root of its splay (i.e., not a child of its parent in the preferred-child tree)
    bool isRoot(int x) {
        int f = t[x].fa;
        if (f==0) return true;
        return (t[f].ch[0] != x && t[f].ch[1] != x);
    }

    void pushUp(int x) {
        t[x].sum = t[x].val;
        if (t[x].ch[0]) t[x].sum += t[t[x].ch[0]].sum;
        if (t[x].ch[1]) t[x].sum += t[t[x].ch[1]].sum;
    }

    void pushRev(int x) {
        if (!x) return;
        t[x].rev ^= 1;
        swap(t[x].ch[0], t[x].ch[1]);
    }

    void pushDown(int x) {
        if (t[x].rev) {
            if (t[x].ch[0]) pushRev(t[x].ch[0]);
            if (t[x].ch[1]) pushRev(t[x].ch[1]);
            t[x].rev = false;
        }
    }

    // rotate x around its parent
    void rotate(int x) {
        int p = t[x].fa;
        int g = t[p].fa;
        int is_right = (t[p].ch[1] == x);
        int b = t[x].ch[is_right ^ 1];

        if (!isRoot(p)) {
            if (t[g].ch[0] == p) t[g].ch[0] = x;
            else if (t[g].ch[1] == p) t[g].ch[1] = x;
        }
        t[x].fa = g;

        t[x].ch[is_right ^ 1] = p;
        t[p].fa = x;

        t[p].ch[is_right] = b;
        if (b) t[b].fa = p;

        pushUp(p);
        pushUp(x);
    }

    // splay x to the top of its splay tree (until isRoot(x) == true)
    void splay(int x) {
        if (!x) return;
        // gather ancestors to push down lazy flags
        vector<int> stk;
        int y = x;
        stk.push_back(y);
        while (!isRoot(y)) {
            y = t[y].fa;
            stk.push_back(y);
        }
        for (int i = (int)stk.size()-1; i>=0; --i) pushDown(stk[i]);

        while (!isRoot(x)) {
            int p = t[x].fa;
            int g = t[p].fa;
            if (!isRoot(p)) {
                if ( (t[p].ch[0]==x) ^ (t[g].ch[0]==p) ) rotate(x);
                else rotate(p);
            }
            rotate(x);
        }
        pushUp(x);
    }

    // access: make x the rightmost node of its represented path; returns last accessed node
    int access(int x) {
        int last = 0;
        for (int y = x; y; y = t[y].fa) {
            splay(y);
            t[y].ch[1] = last;
            pushUp(y);
            last = y;
        }
        splay(x);
        return last;
    }

    // make x root of its tree (virtual root)
    void makeRoot(int x) {
        access(x);
        // now x is splayed; toggle rev to reverse its path
        pushRev(x);
    }

    // find root of the tree containing x
    int findRoot(int x) {
        access(x);
        splay(x);
        // go to leftmost node
        while (true) {
            pushDown(x);
            if (t[x].ch[0]) x = t[x].ch[0];
            else break;
        }
        splay(x); // bring root to top
        return x;
    }

    // link u as a child of v (i.e., add edge u-v). returns true if success
    bool link(int u, int v) {
        makeRoot(u);
        // only link if u and v are in different trees (prevent cycles)
        if (findRoot(v) == u) return false;
        t[u].fa = v;
        return true;
    }

    // cut edge u-v if exists. returns true if success
    bool cut(int u, int v) {
        // two attempts (u as root or v as root) to handle either orientation
        makeRoot(u);
        access(v);
        splay(v);
        // after this, if u--v exists and u is direct child of v in the splay tree and u has no right child,
        // then we can remove that connection:
        if (t[v].ch[0] == u && t[u].ch[1] == 0) {
            t[v].ch[0] = 0;
            t[u].fa = 0;
            pushUp(v);
            return true;
        }
        // try the other orientation
        makeRoot(v);
        access(u);
        splay(u);
        if (t[u].ch[0] == v && t[v].ch[1] == 0) {
            t[u].ch[0] = 0;
            t[v].fa = 0;
            pushUp(u);
            return true;
        }
        return false;
    }

    // check if u and v are connected
    bool connected(int u, int v) {
        if (u==0 || v==0) return false;
        return findRoot(u) == findRoot(v);
    }

    // query sum on path u..v
    long long queryPath(int u, int v) {
        makeRoot(u);
        access(v);
        splay(v);
        return t[v].sum;
    }

    // set value at node u
    void setValue(int u, long long val) {
        access(u);
        splay(u);
        t[u].val = val;
        pushUp(u);
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.setf(std::ios::fixed);
    cout<<setprecision(0);

    // read number of nodes first, or detect dynamically
    // We'll allow the first line to optionally be: "n <num>"
    // Otherwise default to 100000 nodes (or we can deduce max node seen)
    string op;
    int maxNode = 0;
    vector<tuple<string,int,long long>> backlog; // store operations until we know n

    // We first read whole input lines into memory to determine max node index (simple & flexible).
    vector<string> lines;
    string line;
    while (std::getline(cin, line)) {
        if (line.size()==0) continue;
        lines.push_back(line);
    }
    if (lines.empty()) return 0;

    // Find maximum node index referenced
    for (auto &L : lines) {
        stringstream ss(L);
        ss >> op;
        if (op=="n") {
            // optional: line "n <num>"
            int N;
            if (ss >> N) {
                maxNode = max(maxNode, N);
            }
            continue;
        }
        if (op=="link" || op=="cut" || op=="query" || op=="set") {
            int a;
            ss >> a;
            maxNode = max(maxNode, a);
            if (op=="link" || op=="cut" || op=="query") {
                int b; ss >> b;
                maxNode = max(maxNode, b);
            } else if (op=="set") {
                long long val; ss >> val;
            }
        }
    }

    if (maxNode <= 0) maxNode = 100000; // fallback
    LinkCut lct(maxNode);

    // initialize nodes' values to 0
    for (int i = 1; i <= maxNode; ++i) {
        lct.t[i].val = 0;
        lct.t[i].sum = 0;
    }

    // Process the lines
    for (auto &L : lines) {
        stringstream ss(L);
        ss >> op;
        if (op=="n") {
            // ignored (we already sized)
            continue;
        } else if (op=="link") {
            int u,v; ss >> u >> v;
            bool ok = lct.link(u,v);
            // output optional status
            // cout << (ok ? "linked\n" : "link_failed\n");
        } else if (op=="cut") {
            int u,v; ss >> u >> v;
            bool ok = lct.cut(u,v);
            // cout << (ok ? "cut\n" : "cut_failed\n");
        } else if (op=="query") {
            int u,v; ss >> u >> v;
            if (!lct.connected(u,v)) {
                cout << "Impossible\n"; // or some sentinel; chosen text: "Impossible"
            } else {
                long long ans = lct.queryPath(u,v);
                cout << ans << "\n";
            }
        } else if (op=="set") {
            int u; long long val; ss >> u >> val;
            lct.setValue(u,val);
        } else {
            // ignore unknown line or comments
        }
    }

    return 0;
}
