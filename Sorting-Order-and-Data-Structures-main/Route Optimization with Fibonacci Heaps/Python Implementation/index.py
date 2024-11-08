class Node:
    def __init__(self, key, data=None):
        self.key = key  # The key value used for priority
        self.data = data  # Additional data (e.g., location information)
        self.parent = None  # Parent node
        self.child = None  # One of the child nodes
        self.left = self  # Left sibling
        self.right = self  # Right sibling
        self.degree = 0  # Number of child nodes
        self.mark = False  # Whether the node has lost a child since the last time it was made the child of another node

class FibHeap:
    def __init__(self):
        self.min = None  # Pointer to the minimum node
        self.total_nodes = 0  # Total number of nodes in the heap

    def insert(self, key, data=None):
        """Insert a new node with the given key and data."""
        node = Node(key, data)
        node.left = node.right = node
        self._merge_with_root_list(node)
        if self.min is None or node.key < self.min.key:
            self.min = node
        self.total_nodes += 1
        print(f"Inserted node with key {key}.")
        return node

    def decrease_key(self, x, k):
        """Decrease the key of node x to new value k."""
        if k > x.key:
            raise ValueError("New key is greater than current key.")
        x.key = k
        y = x.parent
        if y is not None and x.key < y.key:
            self._cut(x, y)
            self._cascading_cut(y)
        if x.key < self.min.key:
            self.min = x
        print(f"Decreased key of node to {k}.")

    def extract_min(self):
        """Remove and return the node with the minimum key."""
        z = self.min
        if z is not None:
            if z.child is not None:
                # Add the children of z to the root list
                children = [x for x in self._iterate(z.child)]
                for x in children:
                    self._merge_with_root_list(x)
                    x.parent = None
            # Remove z from the root list
            self._remove_from_root_list(z)
            if z == z.right:
                self.min = None
            else:
                self.min = z.right
                self._consolidate()
            self.total_nodes -= 1
            print(f"Extracted min node with key {z.key}.")
            return z
        print("Heap is empty.")
        return None

    # Helper methods
    def _merge_with_root_list(self, node):
        """Merge a node with the root list."""
        if self.min is None:
            self.min = node
        else:
            # Insert node into root list
            node.left = self.min.left
            node.right = self.min
            self.min.left.right = node
            self.min.left = node

    def _remove_from_root_list(self, node):
        """Remove a node from the root list."""
        node.left.right = node.right
        node.right.left = node.left

    def _cut(self, x, y):
        """Cut the link between x and its parent y."""
        self._remove_from_child_list(y, x)
        y.degree -= 1
        self._merge_with_root_list(x)
        x.parent = None
        x.mark = False
        print(f"Cut node with key {x.key} from its parent with key {y.key}.")

    def _remove_from_child_list(self, parent, node):
        """Remove a node from the child list of its parent."""
        if parent.child == node:
            if node.right != node:
                parent.child = node.right
            else:
                parent.child = None
        node.left.right = node.right
        node.right.left = node.left

    def _cascading_cut(self, y):
        """Perform a cascading cut on node y."""
        z = y.parent
        if z is not None:
            if not y.mark:
                y.mark = True
                print(f"Marked node with key {y.key}.")
            else:
                self._cut(y, z)
                self._cascading_cut(z)

    def _consolidate(self):
        """Consolidate the heap by combining trees of the same degree."""
        max_degree = self._upper_bound_degree()
        A = [None] * max_degree
        roots = [x for x in self._iterate(self.min)]
        for w in roots:
            x = w
            d = x.degree
            while A[d] is not None:
                y = A[d]
                if x.key > y.key:
                    x, y = y, x
                self._link(y, x)
                A[d] = None
                d += 1
            A[d] = x
        self.min = None
        for node in A:
            if node is not None:
                if self.min is None or node.key < self.min.key:
                    self.min = node

    def _link(self, y, x):
        """Link node y to node x."""
        self._remove_from_root_list(y)
        y.left = y.right = y
        if x.child is None:
            x.child = y
        else:
            # Add y to x's child list
            y.left = x.child.left
            y.right = x.child
            x.child.left.right = y
            x.child.left = y
        y.parent = x
        x.degree += 1
        y.mark = False
        print(f"Linked node with key {y.key} to node with key {x.key}.")

    def _iterate(self, head):
        """Generator to iterate through a circular doubly linked list."""
        node = stop = head
        flag = False
        while True:
            if node == stop and flag:
                break
            elif node == stop:
                flag = True
            yield node
            node = node.right

    def _upper_bound_degree(self):
        """Calculate an upper bound on the degrees in the heap."""
        import math
        return int(math.log(self.total_nodes) * 2) + 1

# Example usage
if __name__ == "__main__":
    # Create a Fibonacci Heap
    fib_heap = FibHeap()

    # Insert nodes (locations with distances)
    nodes = {}
    nodes['A'] = fib_heap.insert(10, 'A')
    nodes['B'] = fib_heap.insert(3, 'B')
    nodes['C'] = fib_heap.insert(15, 'C')
    nodes['D'] = fib_heap.insert(6, 'D')

    # Decrease key of node 'C' from 15 to 2
    fib_heap.decrease_key(nodes['C'], 2)

    # Extract min (should be node 'C')
    min_node = fib_heap.extract_min()
    print(f"Extracted node with key {min_node.key}, data {min_node.data}")

    # Extract min again (should be node 'B')
    min_node = fib_heap.extract_min()
    print(f"Extracted node with key {min_node.key}, data {min_node.data}")
