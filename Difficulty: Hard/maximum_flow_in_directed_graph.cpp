#include <bits/stdc++.h>
using namespace std;

// Define a custom type for flow and capacity values for clarity and safety
using flow_t = long long;

// Time : O(V^2*E) , Space : O(V+E) , V -> vertices, E -> edges
class DinicMaxFlow {
private:
    static constexpr flow_t INF = numeric_limits<flow_t>::max();
    struct Edge {
        int to;
        flow_t capacity;
        flow_t flow;
        int reverse_edge;
    };

    int num_vertices;
    vector<vector<Edge>> adj;
    vector<int> level; // Distance from source for BFS
    vector<int> ptr;   // Next edge to explore in DFS

    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        queue<int> q;
        q.push(s);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (const auto& edge : adj[u]) {
                if (edge.capacity - edge.flow > 0 && level[edge.to] == -1) {
                    level[edge.to] = level[u] + 1;
                    q.push(edge.to);
                }
            }
        }
        return level[t] != -1;
    }

    flow_t dfs(int u, int t, flow_t pushed_flow) {
        if (pushed_flow == 0 || u == t) return pushed_flow;

        for (int& edge_idx = ptr[u]; edge_idx < (int)adj[u].size(); ++edge_idx) {
            Edge& edge = adj[u][edge_idx];
            flow_t residual_cap = edge.capacity - edge.flow;

            if (level[u] + 1 != level[edge.to] || residual_cap == 0) continue;

            flow_t tr = dfs(edge.to, t, min(pushed_flow, residual_cap));

            if (tr == 0) continue;

            // Update flows
            edge.flow += tr;
            adj[edge.to][edge.reverse_edge].flow -= tr;

            return tr;
        }

        return 0;
    }

public:
    DinicMaxFlow(int V) : num_vertices(V), adj(V), level(V), ptr(V) {}

    void add_edge(int u, int v, flow_t capacity) {
        if (capacity <= 0) return; // Skip zero or negative capacity edges

        // Forward edge (u -> v)
        Edge forward_edge = {v, capacity, 0, (int)adj[v].size()};
        // Reverse edge (v -> u) for residual capacity
        Edge reverse_edge = {u, 0, 0, (int)adj[u].size()};

        adj[u].push_back(forward_edge);
        adj[v].push_back(reverse_edge);
    }

    flow_t get_max_flow(int s, int t) {
        flow_t total_flow = 0;

        while (bfs(s, t)) {
            fill(ptr.begin(), ptr.end(), 0);

            while (flow_t pushed = dfs(s, t, INF)) {
                total_flow += pushed;
            }
        }
        return total_flow;
    }
};

void run_test_case(int test_id, int V, int s, int t, const vector<tuple<int, int, int>>& edges) {
    DinicMaxFlow dinic(V);
    
    for (const auto& edge : edges) {
        dinic.add_edge(get<0>(edge), get<1>(edge), get<2>(edge));
    }
    
    flow_t max_flow = dinic.get_max_flow(s, t);
    
    // Result for this test case
    cout << "Test Case " << test_id << " (Source=" << s << ", Sink=" << t << "): Max Flow = " << max_flow << endl;
}


int main() {
    // Test Case 1
    int V1 = 6;
    int s1 = 0; // Source
    int t1 = 5; // Sink
    
    vector<tuple<int, int, int>> edges1 = {
        {0, 1, 10}, {0, 2, 10},
        {1, 3, 4}, {1, 2, 2}, {1, 4, 8},
        {2, 4, 9},
        {3, 5, 6},
        {4, 5, 10}
    };
    run_test_case(1, V1, s1, t1, edges1); // Output: 14

    // Test Case 2
    int V2 = 6;
    int s2 = 0; // Source
    int t2 = 5; // Sink
    vector<tuple<int, int, int>> edges2 = {
        {0, 1, 16}, {0, 2, 13},
        {1, 2, 10}, {1, 3, 12},
        {2, 1, 4}, {2, 4, 14},
        {3, 2, 9}, {3, 5, 20},
        {4, 3, 7}, {4, 5, 4}
    };
    run_test_case(2, V2, s2, t2, edges2); // Output: 23
    
    // Test Case 3
    int V3 = 6;
    int s3 = 0; // Source
    int t3 = 5; // Sink
    vector<tuple<int, int, int>> edges3 = {
        {0, 1, 10}, {0, 2, 5},  
        {1, 3, 4}, {1, 4, 6},
        {2, 3, 8}, {2, 4, 2},
        {3, 5, 7},               
        {4, 5, 8}
    };
    run_test_case(3, V3, s3, t3, edges3); // output: 15

    return 0;
}