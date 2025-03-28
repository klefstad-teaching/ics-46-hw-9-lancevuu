#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.numVertices;
    vector<int> distances(n, INF);
    previous.assign(n, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    distances[source] = 0;
    pq.push({0, source});
    while (!pq.empty()) {
        int currentDist = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        if (currentDist > distances[u]) continue;
        for (const Edge& edge : G[u]) {
            int v = edge.dst, weight = edge.weight;
            if (distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                pq.push({distances[v], v});
            }
        }
    }
    return distances;
}  // Dijkstra's algorithm, computing the shortest paths from the source node to all other nodes



vector<int> extract_shortest_path(const vector<int>&, const vector<int>& previous, int destination) {
    vector<int> path;
    for (int node = destination; node != -1; node = previous[node]) {
        path.push_back(node);
    }
    reverse(path.begin(), path.end());
    return path; // finds the shortest path
}

void print_path(const vector<int>& path, int total) {
    if (path.empty()) {
        cout << "\nTotal cost is " << total << "\n";
        return;
    }
    for (size_t i = 0; i < path.size(); ++i)
        cout << path[i] << " ";
    cout << "\nTotal cost is " << total << "\n";
} // prints out the path from Dijkstra's
