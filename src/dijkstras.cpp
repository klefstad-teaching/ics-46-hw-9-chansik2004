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

std::vector<int> extract_shortest_path(const std::vector<int> & distances, const std::vector<int> & previous, int destination) {
    std::vector<int> shortestPath;

    if (distances[destination == INF]) {
        return shortestPath;
    }

    for (int curr = destination; curr != -1; curr = previous[curr]) {
        shortestPath.push_back(curr);
    }
    std::reverse(shortestPath.begin(), shortestPath.end());
    return shortestPath;
}

void print_path(const std::vector<int> & v, int total) {
    if (total == INF) {
        std::cout << "No path found\n";
        return;
    }

    if (!v.empty()) {
        for (size_t i = 0; i < v.size(); ++i) {
            std::cout << v[i] << " ";
        }
    }
    std::cout << "\nTotal cost is " << total << "\n";
}
