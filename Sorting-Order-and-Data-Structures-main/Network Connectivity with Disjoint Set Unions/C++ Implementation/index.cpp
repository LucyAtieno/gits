#include "DisjointSetUnion.h"

int main() {
    DisjointSetUnion dsu;

    // Create sets for computers (nodes)
    std::string computers[] = {"A", "B", "C", "D", "E"};
    for (const auto& comp : computers) {
        dsu.makeSet(comp);
    }

    // Union operations (connectivity)
    dsu.unionSets("A", "B");
    dsu.unionSets("B", "C");
    dsu.unionSets("D", "E");

    // Check connectivity
    std::cout << "\nConnectivity Checks:" << std::endl;
    std::cout << "Are 'A' and 'C' connected? " << (dsu.connected("A", "C") ? "Yes" : "No") << std::endl;
    std::cout << "Are 'A' and 'E' connected? " << (dsu.connected("A", "E") ? "Yes" : "No") << std::endl;

    // Merge clusters
    dsu.unionSets("C", "D");

    // Check connectivity after merging
    std::cout << "\nAfter Merging Clusters:" << std::endl;
    std::cout << "Are 'A' and 'E' connected? " << (dsu.connected("A", "E") ? "Yes" : "No") << std::endl;

    return 0;
}
