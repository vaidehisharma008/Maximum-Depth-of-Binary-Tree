#include <bits/stdc++.h>
using namespace std;

struct TwoSAT {
    int n;                       // number of variables
    vector<vector<int>> g, gr;   // graph and reversed graph
    vector<int> comp, order, assignment;
    vector<bool> used;

    TwoSAT(int n) : n(n) {
        g.resize(2 * n);
        gr.resize(2 * n);
        used.assign(2 * n, false);
        comp.assign(2 * n, -1);
        assignment.assign(n, false);
    }

    int varIndex(int x, bool isNeg) {
        // x in [0, n-1], isNeg = false -> x, true -> ¬x
        return 2 * x + (isNeg ? 1 : 0);
    }

    void addImplication(int u, int v) {
        g[u].push_back(v);
        gr[v].push_back(u);
    }

    void addClause(int x, bool xNeg, int y, bool yNeg) {
        // (x ∨ y) == (¬x → y) and (¬y → x)
        addImplication(varIndex(x, !xNeg), varIndex(y, yNeg));
        addImplication(varIndex(y, !yNeg), varIndex(x, xNeg));
    }

    void dfs1(int v) {
        used[v] = true;
        for (int u : g[v]) if (!used[u]) dfs1(u);
        order.push_back(v);
    }

    void dfs2(int v, int cl) {
        comp[v] = cl;
        for (int u : gr[v]) if (comp[u] == -1) dfs2(u, cl);
    }

    bool satisfiable() {
        for (int i = 0; i < 2 * n; i++)
            if (!used[i]) dfs1(i);

        reverse(order.begin(), order.end());
        int j = 0;
        for (int v : order)
            if (comp[v] == -1)
                dfs2(v, j++);

        for (int i = 0; i < n; i++) {
            if (comp[2 * i] == comp[2 * i + 1])
                return false;
            assignment[i] = comp[2 * i] > comp[2 * i + 1];
        }
        return true;
    }

    void printAssignment() {
        for (int i = 0; i < n; i++)
            cout << "x" << i + 1 << " = " << (assignment[i] ? "TRUE" : "FALSE") << "\n";
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m; // n variables, m clauses
    cin >> n >> m;

    TwoSAT solver(n);

    for (int i = 0; i < m; i++) {
        int x, y;
        bool xNeg, yNeg;
        // input: variable_index (1-based), isNeg(0 or 1)
        cin >> x >> xNeg >> y >> yNeg;
        solver.addClause(x - 1, xNeg, y - 1, yNeg);
    }

    if (solver.satisfiable()) {
        cout << "Satisfiable \n";
        solver.printAssignment();
    } else {
        cout << "Unsatisfiable \n";
    }
    return 0;
}

// Complexity ---
//Building graph: O(m)
//Kosaraju’s SCC: O(V + E)
//Total time: O(n + m)
