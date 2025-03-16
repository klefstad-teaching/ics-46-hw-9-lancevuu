#include "dijkstra.h"

int main() {
    Graph G;
    file_to_graph("src/small.txt", G);
    int source = 0;
    vector<int> previous;
    vector<int> distance = dijkstra_shortest_path(G, source, previous);
    for (int i = 0; i < G.numVertices; ++i) {
        vector<int> path = extract_shortest_path(distance, previous, i);
        int total_cost = distance[i];
        print_path(path, total_cost);
    }
    return 0;
}