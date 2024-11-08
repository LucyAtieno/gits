class UserHashTable:
    def __init__(self, size=100):
        self.size = size  # Size of the hash table
        self.table = [[] for _ in range(self.size)]  # Initialize table with empty lists for separate chaining

    def _hash(self, username):
        """Compute a hash value for a given username."""
        return hash(username) % self.size

    def add_user(self, username: str, profile_data: dict):
        """Add a user profile to the hash table."""
        index = self._hash(username)
        bucket = self.table[index]

        # Check if the username already exists and update the profile data
        for i, (uname, _) in enumerate(bucket):
            if uname == username:
                bucket[i] = (username, profile_data)
                print(f"Updated profile for username '{username}'.")
                return

        # If not found, append the new user
        bucket.append((username, profile_data))
        print(f"Added user '{username}' to the hash table.")

    def get_user(self, username: str) -> dict:
        """Retrieve a user profile from the hash table."""
        index = self._hash(username)
        bucket = self.table[index]

        # Search for the username in the bucket
        for uname, profile in bucket:
            if uname == username:
                print(f"Found profile for username '{username}'.")
                return profile

        # Username not found
        print(f"Username '{username}' not found in the hash table.")
        return None

# Example Usage
if __name__ == "__main__":
    user_table = UserHashTable()

    # Add users
    user_table.add_user("alice", {"age": 30, "email": "alice@example.com"})
    user_table.add_user("bob", {"age": 25, "email": "bob@example.com"})
    user_table.add_user("charlie", {"age": 35, "email": "charlie@example.com"})

    # Retrieve users
    profile = user_table.get_user("alice")
    print("Profile Data:", profile)

    profile = user_table.get_user("david")  # Should not be found
    print("Profile Data:", profile)
