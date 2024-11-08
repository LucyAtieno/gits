#include "BTree.h"

int main() {
    BTree btree(3);  // Minimum degree t=3

    // Insert some file names and locations
    btree.insert("file1.txt", "/home/user/docs/file1.txt");
    btree.insert("file2.txt", "/home/user/docs/file2.txt");
    btree.insert("file3.txt", "/home/user/docs/file3.txt");
    btree.insert("file4.txt", "/home/user/docs/file4.txt");
    btree.insert("file5.txt", "/home/user/docs/file5.txt");

    // Search for a file
    FileEntry* entry = btree.search("file3.txt");
    if (entry) {
        std::cout << "Found 'file3.txt' at " << entry->location << std::endl;
    } else {
        std::cout << "File not found" << std::endl;
    }

    // Search for a file that doesn't exist
    entry = btree.search("file6.txt");
    if (entry) {
        std::cout << "Found 'file6.txt' at " << entry->location << std::endl;
    } else {
        std::cout << "File not found" << std::endl;
    }

    return 0;
}
