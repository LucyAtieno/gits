class Node:
    def __init__(self, isbn, book_data):
        self.isbn = isbn
        self.book_data = book_data
        self.left = None
        self.right = None

class BST:
    def __init__(self):
        self.root = None

    def insert(self, isbn, book_data):
        """Insert a new node with the given ISBN and book data."""
        print(f"Inserting ISBN {isbn}: {book_data}")
        self.root = self._insert_recursive(self.root, isbn, book_data)

    def _insert_recursive(self, node, isbn, book_data):
        if node is None:
            return Node(isbn, book_data)
        elif isbn < node.isbn:
            node.left = self._insert_recursive(node.left, isbn, book_data)
        elif isbn > node.isbn:
            node.right = self._insert_recursive(node.right, isbn, book_data)
        else:
            # ISBN already exists, update the book data
            node.book_data = book_data
            print(f"Updated ISBN {isbn} with new book data.")
        return node

    def search(self, isbn):
        """Search for a node with the given ISBN."""
        print(f"Searching for ISBN {isbn}.")
        return self._search_recursive(self.root, isbn)

    def _search_recursive(self, node, isbn):
        if node is None:
            print(f"ISBN {isbn} not found.")
            return None
        elif isbn == node.isbn:
            print(f"Found ISBN {isbn}: {node.book_data}")
            return node.book_data
        elif isbn < node.isbn:
            return self._search_recursive(node.left, isbn)
        else:
            return self._search_recursive(node.right, isbn)

    def delete(self, isbn):
        """Delete the node with the given ISBN."""
        print(f"Deleting ISBN {isbn}.")
        self.root, deleted = self._delete_recursive(self.root, isbn)
        if deleted:
            print(f"ISBN {isbn} deleted.")
        else:
            print(f"ISBN {isbn} not found.")

    def _delete_recursive(self, node, isbn):
        if node is None:
            return node, False
        deleted = False
        if isbn < node.isbn:
            node.left, deleted = self._delete_recursive(node.left, isbn)
        elif isbn > node.isbn:
            node.right, deleted = self._delete_recursive(node.right, isbn)
        else:
            deleted = True
            if node.left and node.right:
                # Node with two children
                successor = self._find_min(node.right)
                node.isbn, node.book_data = successor.isbn, successor.book_data
                node.right, _ = self._delete_recursive(node.right, successor.isbn)
            elif node.left:
                # Node with only left child
                node = node.left
            elif node.right:
                # Node with only right child
                node = node.right
            else:
                # Node with no children
                node = None
        return node, deleted

    def _find_min(self, node):
        """Find the node with the minimum ISBN."""
        while node.left is not None:
            node = node.left
        return node

    def inorder_traversal(self):
        """Inorder traversal of the BST."""
        print("Inorder Traversal:")
        self._inorder_recursive(self.root)

    def _inorder_recursive(self, node):
        if node:
            self._inorder_recursive(node.left)
            print(f"ISBN {node.isbn}: {node.book_data}")
            self._inorder_recursive(node.right)

# Example Usage
if __name__ == "__main__":
    bst = BST()
    # Insert books
    bst.insert(9780131103627, {"title": "The C Programming Language", "author": "Kernighan and Ritchie"})
    bst.insert(9780262033848, {"title": "Introduction to Algorithms", "author": "Cormen et al."})
    bst.insert(9780131101630, {"title": "The UNIX Programming Environment", "author": "Kernighan and Pike"})
    bst.insert(9780201633610, {"title": "Design Patterns", "author": "Gamma et al."})

    # Search for a book
    book = bst.search(9780262033848)

    # Delete a book
    bst.delete(9780131101630)

    # Inorder traversal
    bst.inorder_traversal()
