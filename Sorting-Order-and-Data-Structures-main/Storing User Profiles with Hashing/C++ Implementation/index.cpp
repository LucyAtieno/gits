#include <iostream>
#include <vector>
#include <list>
#include <string>

struct Profile {
    int age;
    std::string email;
};

class UserHashTable {
public:
    UserHashTable(size_t size = 100) : table(size) {}

    void addUser(const std::string& username, const Profile& profileData) {
        size_t index = hash(username);
        auto& bucket = table[index];

        // Check if the username already exists and update the profile data
        for (auto& pair : bucket) {
            if (pair.first == username) {
                pair.second = profileData;
                std::cout << "Updated profile for username '" << username << "'.\n";
                return;
            }
        }

        // If not found, add the new user
        bucket.emplace_back(username, profileData);
        std::cout << "Added user '" << username << "' to the hash table.\n";
    }

    Profile* getUser(const std::string& username) {
        size_t index = hash(username);
        auto& bucket = table[index];

        // Search for the username in the bucket
        for (auto& pair : bucket) {
            if (pair.first == username) {
                std::cout << "Found profile for username '" << username << "'.\n";
                return &pair.second;
            }
        }

        // Username not found
        std::cout << "Username '" << username << "' not found in the hash table.\n";
        return nullptr;
    }

private:
    std::vector<std::list<std::pair<std::string, Profile>>> table;

    size_t hash(const std::string& key) const {
        // Simple hash function (djb2 algorithm)
        size_t hash = 5381;
        for (char c : key)
            hash = ((hash << 5) + hash) + c;  // hash * 33 + c
        return hash % table.size();
    }
};

// Example Usage
int main() {
    UserHashTable userTable;

    // Add users
    userTable.addUser("alice", {30, "alice@example.com"});
    userTable.addUser("bob", {25, "bob@example.com"});
    userTable.addUser("charlie", {35, "charlie@example.com"});

    // Retrieve users
    Profile* profile = userTable.getUser("alice");
    if (profile) {
        std::cout << "Profile Data: Age=" << profile->age << ", Email=" << profile->email << "\n";
    }

    profile = userTable.getUser("david");  // Should not be found
    if (profile) {
        std::cout << "Profile Data: Age=" << profile->age << ", Email=" << profile->email << "\n";
    }

    return 0;
}
