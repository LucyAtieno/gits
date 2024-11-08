// DisjointSetUnion.h

#ifndef DISJOINT_SET_UNION_H
#define DISJOINT_SET_UNION_H

#include <unordered_map>
#include <string>
#include <iostream>

class DisjointSetUnion {
public:
    void makeSet(const std::string& x);
    std::string find(const std::string& x);
    void unionSets(const std::string& x, const std::string& y);
    bool connected(const std::string& x, const std::string& y);

private:
    std::unordered_map<std::string, std::string> parent;
    std::unordered_map<std::string, int> rank;
};

#endif // DISJOINT_SET_UNION_H
