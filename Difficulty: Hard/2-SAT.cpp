#include <bits/stdc++.h>
using namespace std;

/*
  2-SAT Solver using Tarjan's SCC algorithm
  -----------------------------------------
  - Each variable x_i has two nodes:
        i       →  represents x_i
        i + n   →  represents ¬x_i
  - Each clause (a ∨ b) is turned into:
        (¬a → b) and (¬b → a)
  - Run Tarjan's SCC to find strongly connected components.
  - If x_i and ¬x_i are in the same component → UNSAT.
  - Otherwise assign values according to SCC topological order.
*/

struct TwoSAT {
    int n;                              // number of variables
    vector<vector<int>> g;              // implication graph
    vector<int> idx, low, comp, stk;
    vector<bool> onStack;
    int dfsTime = 0, compCount = 0;
    vector<int> assignment;

    TwoSAT(int N = 0) { init(N); }

    void init(int N) {
        n = N;
        g.assign(2 * n, {});
        idx.assign(2 * n, -1);
        low.assign(2 * n, 0);
        comp.assign(2 * n, -1);
        onStack.assign(2 * n, false);
        dfsTime = compCount = 0;
        stk.clear();
    }

    // Add implication u → v
    void addImp(int u, int v) { g[u].push_back(v); }

    // Add clause (a ∨ b)
    // Each literal is represented as ±i (1-based variable index):
    //  i  = x_i
    // -i  = ¬x_i
    void addClause(int a, int b) {
        int A = abs(a) - 1;
        int B = abs(b) - 1;
        int a_true = (a > 0 ? A : A + n);
        int a_false = (a > 0 ? A + n : A);
        int b_true = (b > 0 ? B : B + n);
        int b_false = (b > 0 ? B + n : B);
        // (a ∨ b) ⇒ (¬a → b) and (¬b → a)
        addImp(a_false, b_true);
        addImp(b_false, a_true);
    }

    void tarjanDFS(int v) {
        idx[v] = low[v] = dfsTime++;
        stk.push_back(v);
        onStack[v] = true;

        for (int to : g[v]) {
            if (idx[to] == -1) {
                tarjanDFS(to);
                low[v] = min(low[v], low[to]);
            } else if (onStack[to]) {
                low[v] = min(low[v], idx[to]);
            }
        }

        if (low[v] == idx[v]) {
            while (true) {
                int u = stk.back(); stk.pop_back();
                onStack[u] = false;
                comp[u] = compCount;
                if (u == v) break;
            }
            compCount++;
        }
    }

    bool satisfiable() {
        int N = 2 * n;
        for (int i = 0; i < N; ++i)
            if (idx[i] == -1) tarjanDFS(i);

        assignment.assign(n, 0);
        for (int i = 0; i < n; ++i) {
            if (comp[i] == comp[i + n]) return false; // UNSAT
            assignment[i] = (comp[i] > comp[i + n]);
        }
        return true;
    }

    vector<int> getAssignment() { return assignment; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cout << "Enter number of variables and clauses:\n";
    if (!(cin >> n >> m)) return 0;

    TwoSAT solver(n);
    cout << "Enter clauses (a b) for (a ∨ b):\n";
    cout << "Use positive numbers for x_i, negative for ¬x_i (1-based indices)\n";

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        solver.addClause(a, b);
    }

    if (!solver.satisfiable()) {
        cout << "UNSATISFIABLE\n";
    } else {
        cout << "SATISFIABLE\n";
        auto ans = solver.getAssignment();
        cout << "Assignment:\n";
        for (int i = 0; i < n; ++i)
            cout << "x" << (i + 1) << " = " << (ans[i] ? "TRUE" : "FALSE") << "\n";
    }

    return 0;
}
