#include "FibHeap.h"

template <typename TKey, typename TValue>
FibHeap<TKey, TValue>::FibHeap() : min(nullptr), totalNodes(0) {}

template <typename TKey, typename TValue>
FibHeap<TKey, TValue>::~FibHeap() {
    if (min != nullptr) {
        deleteAll(min);
    }
}

template <typename TKey, typename TValue>
void FibHeap<TKey, TValue>::deleteAll(Node<TKey, TValue>* node) {
    if (node != nullptr) {
        Node<TKey, TValue>* start = node;
        do {
            Node<TKey, TValue>* temp = node;
            node = node->right;
            if (temp->child != nullptr) {
                deleteAll(temp->child);
            }
            delete temp;
        } while (node != start);
    }
}

template <typename TKey, typename TValue>
Node<TKey, TValue>* FibHeap<TKey, TValue>::insert(TKey key, TValue data) {
    Node<TKey, TValue>* node = new Node<TKey, TValue>(key, data);
    addToRootList(node);
    if (min == nullptr || key < min->key) {
        min = node;
    }
    totalNodes++;
    std::cout << "Inserted node with key " << key << "." << std::endl;
    return node;
}

template <typename TKey, typename TValue>
void FibHeap<TKey, TValue>::decreaseKey(Node<TKey, TValue>* x, TKey k) {
    if (k > x->key) {
        throw std::invalid_argument("New key is greater than current key.");
    }
    x->key = k;
    Node<TKey, TValue>* y = x->parent;
    if (y != nullptr && x->key < y->key) {
        cut(x, y);
        cascadingCut(y);
    }
    if (x->key < min->key) {
        min = x;
    }
    std::cout << "Decreased key of node to " << k << "." << std::endl;
}

template <typename TKey, typename TValue>
void FibHeap<TKey, TValue>::cut(Node<TKey, TValue>* x, Node<TKey, TValue>* y) {
    // Remove x from the child list of y
    if (x->right == x) {
        y->child = nullptr;
    } else {
        x->left->right = x->right;
        x->right->left = x->left;
        if (y->child == x) {
            y->child = x->right;
        }
    }
    y->degree--;
    // Add x to the root list
    addToRootList(x);
    x->parent = nullptr;
    x->mark = false;
    std::cout << "Cut node with key " << x->key << " from its parent with key " << y->key << "." << std::endl;
}

template <typename TKey, typename TValue>
void FibHeap<TKey, TValue>::cascadingCut(Node<TKey, TValue>* y) {
    Node<TKey, TValue>* z = y->parent;
    if (z != nullptr) {
        if (!y->mark) {
            y->mark = true;
            std::cout << "Marked node with key " << y->key << "." << std::endl;
        } else {
            cut(y, z);
            cascadingCut(z);
        }
    }
}

template <typename TKey, typename TValue>
Node<TKey, TValue>* FibHeap<TKey, TValue>::extractMin() {
    Node<TKey, TValue>* z = min;
    if (z != nullptr) {
        if (z->child != nullptr) {
            Node<TKey, TValue>* child = z->child;
            do {
                Node<TKey, TValue>* next = child->right;
                addToRootList(child);
                child->parent = nullptr;
                child = next;
            } while (child != z->child);
        }
        removeFromRootList(z);
        if (z == z->right) {
            min = nullptr;
        } else {
            min = z->right;
            consolidate();
        }
        totalNodes--;
        std::cout << "Extracted min node with key " << z->key << "." << std::endl;
    }
    return z;
}

template <typename TKey, typename TValue>
void FibHeap<TKey, TValue>::consolidate() {
    int max_degree = static_cast<int>(std::log(totalNodes) / std::log(1.61803)) + 1;
    std::vector<Node<TKey, TValue>*> A(max_degree, nullptr);

    // Create a list of root nodes
    std::vector<Node<TKey, TValue>*> rootList;
    Node<TKey, TValue>* x = min;
    if (x != nullptr) {
        do {
            rootList.push_back(x);
            x = x->right;
        } while (x != min);
    }

    for (Node<TKey, TValue>* w : rootList) {
        x = w;
        int d = x->degree;
        while (A[d] != nullptr) {
            Node<TKey, TValue>* y = A[d];
            if (x->key > y->key) {
                std::swap(x, y);
            }
            link(y, x);
            A[d] = nullptr;
            d++;
        }
        A[d] = x;
    }

    min = nullptr;
    for (Node<TKey, TValue>* node : A) {
        if (node != nullptr) {
            if (min == nullptr || node->key < min->key) {
                min = node;
            }
        }
    }
}

template <typename TKey, typename TValue>
void FibHeap<TKey, TValue>::link(Node<TKey, TValue>* y, Node<TKey, TValue>* x) {
    // Remove y from root list
    removeFromRootList(y);
    // Make y a child of x
    y->left = y->right = y;
    y->parent = x;
    if (x->child == nullptr) {
        x->child = y;
    } else {
        // Add y to x's child list
        y->right = x->child;
        y->left = x->child->left;
        x->child->left->right = y;
        x->child->left = y;
    }
    x->degree++;
    y->mark = false;
    std::cout << "Linked node with key " << y->key << " to node with key " << x->key << "." << std::endl;
}

template <typename TKey, typename TValue>
void FibHeap<TKey, TValue>::addToRootList(Node<TKey, TValue>* node) {
    if (min == nullptr) {
        min = node;
        node->left = node->right = node;
    } else {
        node->right = min;
        node->left = min->left;
        min->left->right = node;
        min->left = node;
    }
}

template <typename TKey, typename TValue>
void FibHeap<TKey, TValue>::removeFromRootList(Node<TKey, TValue>* node) {
    if (node->right == node) {
        min = nullptr;
    } else {
        node->left->right = node->right;
        node->right->left = node->left;
        if (min == node) {
            min = node->right;
        }
    }
}

