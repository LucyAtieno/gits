#include "DisjointSetUnion.h"

void DisjointSetUnion::makeSet(const std::string& x) {
    parent[x] = x;
    rank[x] = 0;
    std::cout << "Created set for element '" << x << "'." << std::endl;
}

std::string DisjointSetUnion::find(const std::string& x) {
    if (parent.find(x) == parent.end()) {
        throw std::invalid_argument("Element '" + x + "' not found in any set.");
    }
    if (parent[x] != x) {
        // Path compression
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void DisjointSetUnion::unionSets(const std::string& x, const std::string& y) {
    std::string xRoot = find(x);
    std::string yRoot = find(y);

    if (xRoot == yRoot) {
        std::cout << "Elements '" << x << "' and '" << y << "' are already in the same set." << std::endl;
        return;
    }

    // Union by rank
    if (rank[xRoot] < rank[yRoot]) {
        parent[xRoot] = yRoot;
        std::cout << "Element '" << xRoot << "' is now a child of '" << yRoot << "'." << std::endl;
    } else {
        parent[yRoot] = xRoot;
        std::cout << "Element '" << yRoot << "' is now a child of '" << xRoot << "'." << std::endl;
        if (rank[xRoot] == rank[yRoot]) {
            rank[xRoot]++;
            std::cout << "Incremented rank of '" << xRoot << "' to " << rank[xRoot] << "." << std::endl;
        }
    }
}

bool DisjointSetUnion::connected(const std::string& x, const std::string& y) {
    return find(x) == find(y);
}
