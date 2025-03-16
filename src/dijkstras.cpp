#include "dijkstras.h"
#include <algorithm>
#include <queue>
#include <iostream>

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.numVertices;
    vector<int> distance(n, INF); // initializes vectors
    vector<bool> visited(n, false);
    priority_queue<Node, vector<Node>, greater<Node>> pq; // pq initialized
    pq.push(Node(source, 0));
    previous.resize(n, -1);
    distance[source] = 0;
    while (!pq.empty()) { // processes each node until pq is empty
        Node currentNode = pq.top();
        pq.pop();
        int u = currentNode.vertex;
        if (visited[u]) continue;
        visited[u] = true;
        for (const Edge& edge : G[u]) {
            int v = edge.dst;
            int weight = edge.weight;
            if (!visited[v] && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                previous[v] = u;
                pq.push(Node(v, distance[v]));
            }
        }
    }
    return distance; //  Dijkstra's algorithm, computing the shortest paths from the source node to all other nodes
}


vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    if (distances[destination] == INF)
        return path;
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
    cout << path[0];
    for (size_t i = 1; i < path.size(); ++i) {
        cout << " " << path[i];
    }
    cout << " \nTotal cost is " << total << "\n";
} // prints out the path from Dijkstra's
