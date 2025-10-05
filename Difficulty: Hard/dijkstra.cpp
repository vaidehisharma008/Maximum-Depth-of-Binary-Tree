#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

void dijkstra(vector<vector<int>>& graph, int source) {
    int n = graph.size();
    vector<int> dist(n, INF);
    dist[source] = 0;

    // Min-heap: {distance, node}
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0, source});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u]) continue;

        for (int v = 0; v < n; ++v) {
            if (graph[u][v] != 0) {
                int newDist = dist[u] + graph[u][v];
                if (newDist < dist[v]) {
                    dist[v] = newDist;
                    pq.push({newDist, v});
                }
            }
        }
    }

    // Print distances
    cout << "Shortest distances from node " << source << " → [";
    for (int i = 0; i < n; ++i) {
        cout << dist[i];
        if (i != n-1) cout << ", ";
    }
    cout << "]\n";
}

int main() {
    vector<vector<int>> graph = {
        {0, 4, 0, 0, 0, 0, 0, 8, 0},
        {4, 0, 8, 0, 0, 0, 0, 11, 0},
        {0, 8, 0, 7, 0, 4, 0, 0, 2},
        {0, 0, 7, 0, 9, 14, 0, 0, 0},
        {0, 0, 0, 9, 0, 10, 0, 0, 0},
        {0, 0, 4, 14, 10, 0, 2, 0, 0},
        {0, 0, 0, 0, 0, 2, 0, 1, 6},
        {8, 11, 0, 0, 0, 0, 1, 0, 7},
        {0, 0, 2, 0, 0, 0, 6, 7, 0}
    };
    int source = 0;
    dijkstra(graph, source);
    return 0;
}
