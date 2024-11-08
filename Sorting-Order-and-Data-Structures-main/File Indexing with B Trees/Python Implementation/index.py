# BTree.py

class BTreeNode:
    def __init__(self, t, leaf=False):
        self.t = t  # Minimum degree (defines the range for the number of keys)
        self.keys = []  # List of keys (file names)
        self.values = []  # Corresponding file locations
        self.children = []  # List of child pointers
        self.leaf = leaf  # True if node is a leaf node

    def insert_non_full(self, key, value):
        """Insert a key into a node that is not full."""
        i = len(self.keys) - 1

        if self.leaf:
            # Insert the new key into the correct position
            self.keys.append(None)
            self.values.append(None)
            while i >= 0 and key < self.keys[i]:
                self.keys[i + 1] = self.keys[i]
                self.values[i + 1] = self.values[i]
                i -= 1
            self.keys[i + 1] = key
            self.values[i + 1] = value
        else:
            # Find the child which is going to have the new key
            while i >= 0 and key < self.keys[i]:
                i -= 1
            i += 1
            # Check if the found child is full
            if len(self.children[i].keys) == 2 * self.t - 1:
                self.split_child(i)
                if key > self.keys[i]:
                    i += 1
            self.children[i].insert_non_full(key, value)

    def split_child(self, i):
        """Split the child y of this node at index i."""
        t = self.t
        y = self.children[i]
        z = BTreeNode(t, y.leaf)

        # Copy the last (t-1) keys and values of y to z
        z.keys = y.keys[t:]
        z.values = y.values[t:]
        y.keys = y.keys[:t - 1]
        y.values = y.values[:t - 1]

        # Copy the last t children of y to z
        if not y.leaf:
            z.children = y.children[t:]
            y.children = y.children[:t]

        # Insert z as a child of this node
        self.children.insert(i + 1, z)
        self.keys.insert(i, y.keys[t - 1])
        self.values.insert(i, y.values[t - 1])

    def search(self, key):
        """Search for a key in the subtree rooted at this node."""
        i = 0
        while i < len(self.keys) and key > self.keys[i]:
            i += 1

        if i < len(self.keys) and key == self.keys[i]:
            return self.values[i]
        elif self.leaf:
            return None
        else:
            return self.children[i].search(key)

class BTree:
    def __init__(self, t):
        self.root = BTreeNode(t, True)
        self.t = t  # Minimum degree

    def insert(self, key, value):
        """Insert a key and value into the B-tree."""
        root = self.root
        if len(root.keys) == 2 * self.t - 1:
            # Root is full, need to split
            s = BTreeNode(self.t, False)
            s.children.insert(0, root)
            s.split_child(0)
            self.root = s
            s.insert_non_full(key, value)
        else:
            root.insert_non_full(key, value)

    def search(self, key):
        """Search for a key starting from the root."""
        return self.root.search(key)

# Example usage
if __name__ == "__main__":
    btree = BTree(t=3)  # t is the minimum degree

    # Insert some file names and locations
    btree.insert("file1.txt", "/home/user/docs/file1.txt")
    btree.insert("file2.txt", "/home/user/docs/file2.txt")
    btree.insert("file3.txt", "/home/user/docs/file3.txt")
    btree.insert("file4.txt", "/home/user/docs/file4.txt")
    btree.insert("file5.txt", "/home/user/docs/file5.txt")

    # Search for a file
    location = btree.search("file3.txt")
    if location:
        print(f"Found 'file3.txt' at {location}")
    else:
        print("File not found")

    # Search for a file that doesn't exist
    location = btree.search("file6.txt")
    if location:
        print(f"Found 'file6.txt' at {location}")
    else:
        print("File not found")
