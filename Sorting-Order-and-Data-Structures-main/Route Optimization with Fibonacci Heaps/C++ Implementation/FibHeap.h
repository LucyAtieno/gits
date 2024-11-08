// FibHeap.h

#ifndef FIBHEAP_H
#define FIBHEAP_H

#include <iostream>
#include <cmath>
#include <vector>
#include <unordered_map>

template <typename TKey, typename TValue>
class FibHeap;

template <typename TKey, typename TValue>
class Node {
public:
    TKey key;
    TValue data;
    int degree;
    bool mark;
    Node* parent;
    Node* child;
    Node* left;
    Node* right;

    Node(TKey key, TValue data) : key(key), data(data), degree(0), mark(false),
        parent(nullptr), child(nullptr) {
        left = right = this;
    }
};

template <typename TKey, typename TValue>
class FibHeap {
public:
    FibHeap();
    ~FibHeap();

    Node<TKey, TValue>* insert(TKey key, TValue data);
    void decreaseKey(Node<TKey, TValue>* x, TKey k);
    Node<TKey, TValue>* extractMin();

private:
    Node<TKey, TValue>* min;
    int totalNodes;

    void consolidate();
    void link(Node<TKey, TValue>* y, Node<TKey, TValue>* x);
    void cut(Node<TKey, TValue>* x, Node<TKey, TValue>* y);
    void cascadingCut(Node<TKey, TValue>* y);
    void addToRootList(Node<TKey, TValue>* node);
    void removeFromRootList(Node<TKey, TValue>* node);
    void deleteAll(Node<TKey, TValue>* node);
};

#endif // FIBHEAP_H
