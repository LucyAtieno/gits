#include <iostream>
#include <string>

struct BookData {
    std::string title;
    std::string author;
};

struct Node {
    long long isbn;
    BookData bookData;
    Node* left;
    Node* right;

    Node(long long isbn, const BookData& bookData)
        : isbn(isbn), bookData(bookData), left(nullptr), right(nullptr) {}
};

class BookBST {
public:
    BookBST() : root(nullptr) {}

    void insert(long long isbn, const BookData& bookData) {
        std::cout << "Inserting ISBN " << isbn << ": " << bookData.title << "\n";
        root = insertRecursive(root, isbn, bookData);
    }

    BookData* search(long long isbn) {
        std::cout << "Searching for ISBN " << isbn << ".\n";
        Node* result = searchRecursive(root, isbn);
        if (result) {
            std::cout << "Found ISBN " << isbn << ": " << result->bookData.title << "\n";
            return &result->bookData;
        } else {
            std::cout << "ISBN " << isbn << " not found.\n";
            return nullptr;
        }
    }

    void deleteNode(long long isbn) {
        std::cout << "Deleting ISBN " << isbn << ".\n";
        bool deleted;
        root = deleteRecursive(root, isbn, deleted);
        if (deleted) {
            std::cout << "ISBN " << isbn << " deleted.\n";
        } else {
            std::cout << "ISBN " << isbn << " not found.\n";
        }
    }

    void inorderTraversal() {
        std::cout << "Inorder Traversal:\n";
        inorderRecursive(root);
    }

private:
    Node* root;

    Node* insertRecursive(Node* node, long long isbn, const BookData& bookData) {
        if (node == nullptr) {
            return new Node(isbn, bookData);
        } else if (isbn < node->isbn) {
            node->left = insertRecursive(node->left, isbn, bookData);
        } else if (isbn > node->isbn) {
            node->right = insertRecursive(node->right, isbn, bookData);
        } else {
            // ISBN already exists, update the book data
            node->bookData = bookData;
            std::cout << "Updated ISBN " << isbn << " with new book data.\n";
        }
        return node;
    }

    Node* searchRecursive(Node* node, long long isbn) {
        if (node == nullptr || node->isbn == isbn) {
            return node;
        } else if (isbn < node->isbn) {
            return searchRecursive(node->left, isbn);
        } else {
            return searchRecursive(node->right, isbn);
        }
    }

    Node* deleteRecursive(Node* node, long long isbn, bool& deleted) {
        if (node == nullptr) {
            deleted = false;
            return nullptr;
        }

        if (isbn < node->isbn) {
            node->left = deleteRecursive(node->left, isbn, deleted);
        } else if (isbn > node->isbn) {
            node->right = deleteRecursive(node->right, isbn, deleted);
        } else {
            deleted = true;
            if (node->left && node->right) {
                Node* successor = findMin(node->right);
                node->isbn = successor->isbn;
                node->bookData = successor->bookData;
                node->right = deleteRecursive(node->right, successor->isbn, deleted);
            } else {
                Node* temp = node;
                if (node->left) {
                    node = node->left;
                } else {
                    node = node->right;
                }
                delete temp;
            }
        }
        return node;
    }

    Node* findMin(Node* node) {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

    void inorderRecursive(Node* node) {
        if (node != nullptr) {
            inorderRecursive(node->left);
            std::cout << "ISBN " << node->isbn << ": " << node->bookData.title << "\n";
            inorderRecursive(node->right);
        }
    }
};

// Example Usage
int main() {
    BookBST bst;
    // Insert books
    bst.insert(9780131103627LL, {"The C Programming Language", "Kernighan and Ritchie"});
    bst.insert(9780262033848LL, {"Introduction to Algorithms", "Cormen et al."});
    bst.insert(9780131101630LL, {"The UNIX Programming Environment", "Kernighan and Pike"});
    bst.insert(9780201633610LL, {"Design Patterns", "Gamma et al."});

    // Search for a book
    BookData* book = bst.search(9780262033848LL);

    // Delete a book
    bst.deleteNode(9780131101630LL);

    // Inorder traversal
    bst.inorderTraversal();

    return 0;
}
