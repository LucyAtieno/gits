// BTree.cpp

#include "BTree.h"

BTreeNode::BTreeNode(int t, bool leaf) : t(t), leaf(leaf) {}

void BTreeNode::insertNonFull(const FileEntry& entry) {
    int i = keys.size() - 1;

    if (leaf) {
        // Insert the new key into the correct position
        keys.push_back({"", ""});
        while (i >= 0 && entry.fileName < keys[i].fileName) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = entry;
    } else {
        // Find the child that is going to have the new key
        while (i >= 0 && entry.fileName < keys[i].fileName) {
            i--;
        }
        i++;
        // Check if the found child is full
        if (children[i]->keys.size() == 2 * t - 1) {
            splitChild(i, children[i]);
            if (entry.fileName > keys[i].fileName) {
                i++;
            }
        }
        children[i]->insertNonFull(entry);
    }
}

void BTreeNode::splitChild(int i, BTreeNode* y) {
    int t = y->t;
    BTreeNode* z = new BTreeNode(y->t, y->leaf);

    // Copy the last (t-1) keys and values of y to z
    for (int j = 0; j < t - 1; j++) {
        z->keys.push_back(y->keys[j + t]);
    }

    // Copy the last t children of y to z
    if (!y->leaf) {
        for (int j = 0; j < t; j++) {
            z->children.push_back(y->children[j + t]);
        }
    }

    // Reduce the number of keys in y
    y->keys.resize(t - 1);
    if (!y->leaf) {
        y->children.resize(t);
    }

    // Insert z as a child of this node
    children.insert(children.begin() + i + 1, z);
    keys.insert(keys.begin() + i, y->keys[t - 1]);
}

FileEntry* BTreeNode::search(const std::string& fileName) {
    int i = 0;
    while (i < keys.size() && fileName > keys[i].fileName) {
        i++;
    }

    if (i < keys.size() && fileName == keys[i].fileName) {
        return &keys[i];
    } else if (leaf) {
        return nullptr;
    } else {
        return children[i]->search(fileName);
    }
}

BTree::BTree(int t) : t(t), root(new BTreeNode(t, true)) {}

BTree::~BTree() {
    deleteNode(root);
}

void BTree::deleteNode(BTreeNode* node) {
    if (node != nullptr) {
        if (!node->leaf) {
            for (auto child : node->children) {
                deleteNode(child);
            }
        }
        delete node;
    }
}

void BTree::insert(const std::string& fileName, const std::string& location) {
    BTreeNode* r = root;
    if (r->keys.size() == 2 * t - 1) {
        BTreeNode* s = new BTreeNode(t, false);
        s->children.push_back(r);
        s->splitChild(0, r);
        root = s;
        root->insertNonFull({fileName, location});
    } else {
        r->insertNonFull({fileName, location});
    }
}

FileEntry* BTree::search(const std::string& fileName) {
    return root->search(fileName);
}
