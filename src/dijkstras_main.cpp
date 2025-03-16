#include "dijkstras.h"

int main(int argc, char * argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    Graph G;
    file_to_graph(argv[1], G);

    std::vector<int> previous;
    std::vector<int> distance = dijkstra_shortest_path(G, 0, previous);

    for (int i = 0; i < G.numVertices; ++i) {
        std::vector<int> shortestPath = extract_shortest_path(distance, previous, i);
        print_path(shortestPath, distance[i]);
    }
}
