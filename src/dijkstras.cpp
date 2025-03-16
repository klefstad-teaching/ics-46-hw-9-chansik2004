#include "dijkstras.h"

std::vector<int> dijkstra_shortest_path(const Graph & G, int source, std::vector<int> & previous) {
    int n = G.numVertices;
    std::vector<int> distance(n, INF);
    previous.resize(n, -1);
    std::vector<bool> visited(n, false);

    struct Node {
        int vertex;
        int weight;
        bool operator>(const Node & other) const {
            return weight > other.weight;
        }
    };

    std::priority_queue<Node, std::vector<Node>, std::greater<>> pq;
    pq.push({source, 0});
    distance[source] = 0;

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        int u = current.vertex;

        if (visited[u]) {
            continue;
        }
        visited[u] = true;

        for (const Edge & edge : G[u]) {
            int v = edge.dst;
            int weight = edge.weight;

            if (!visited[v] && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                previous[v] = u;
                pq.push({v, distance[v]});
            }
        }
    }
    return distance;
}
