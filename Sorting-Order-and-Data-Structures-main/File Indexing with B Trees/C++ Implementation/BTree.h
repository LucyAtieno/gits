// BTree.h

#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include <vector>
#include <string>

struct FileEntry {
    std::string fileName;
    std::string location;
};

class BTreeNode {
    int t;  // Minimum degree
    std::vector<FileEntry> keys;  // File entries (keys and locations)
    std::vector<BTreeNode*> children;  // Child pointers
    bool leaf;  // True if node is a leaf

public:
    BTreeNode(int t, bool leaf);

    void insertNonFull(const FileEntry& entry);
    void splitChild(int i, BTreeNode* y);
    FileEntry* search(const std::string& fileName);

    friend class BTree;
};

class BTree {
    BTreeNode* root;
    int t;  // Minimum degree

public:
    BTree(int t);
    ~BTree();

    void insert(const std::string& fileName, const std::string& location);
    FileEntry* search(const std::string& fileName);

private:
    void deleteNode(BTreeNode* node);
};

#endif // BTREE_H
