class DisjointSet:
    def __init__(self):
        """Initialize an empty disjoint set."""
        self.parent = {}
        self.rank = {}

    def make_set(self, x):
        """Create a new set containing element x."""
        self.parent[x] = x
        self.rank[x] = 0
        print(f"Created set for element '{x}'.")

    def find(self, x):
        """
        Find the representative (root) of the set containing x.
        Implements path compression for optimization.
        """
        if x not in self.parent:
            raise KeyError(f"Element '{x}' is not found in any set.")

        if self.parent[x] != x:
            # Path compression
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]

    def union(self, x, y):
        """
        Merge the sets containing x and y.
        Uses union by rank for optimization.
        """
        x_root = self.find(x)
        y_root = self.find(y)

        if x_root == y_root:
            print(f"Elements '{x}' and '{y}' are already in the same set.")
            return

        # Union by rank
        if self.rank[x_root] < self.rank[y_root]:
            self.parent[x_root] = y_root
            print(f"Element '{x_root}' is now a child of '{y_root}'.")
        else:
            self.parent[y_root] = x_root
            print(f"Element '{y_root}' is now a child of '{x_root}'.")
            if self.rank[x_root] == self.rank[y_root]:
                self.rank[x_root] += 1
                print(f"Incremented rank of '{x_root}' to {self.rank[x_root]}.")

    def connected(self, x, y):
        """Check if elements x and y are in the same set."""
        return self.find(x) == self.find(y)

# Example Usage
if __name__ == "__main__":
    # Initialize the Disjoint Set
    dsu = DisjointSet()

    # Create sets for computers (nodes)
    computers = ['A', 'B', 'C', 'D', 'E']
    for comp in computers:
        dsu.make_set(comp)

    # Union operations (connectivity)
    dsu.union('A', 'B')
    dsu.union('B', 'C')
    dsu.union('D', 'E')

    # Check connectivity
    print("\nConnectivity Checks:")
    print(f"Are 'A' and 'C' connected? {dsu.connected('A', 'C')}")
    print(f"Are 'A' and 'E' connected? {dsu.connected('A', 'E')}")

    # Merge clusters
    dsu.union('C', 'D')

    # Check connectivity after merging
    print("\nAfter Merging Clusters:")
    print(f"Are 'A' and 'E' connected? {dsu.connected('A', 'E')}")
