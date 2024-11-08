#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>

int binarySearch(const std::vector<int>& arr, int target, int& steps) {
    int left = 0, right = arr.size() - 1;
    steps = 0;  // Reset steps counter
    while (left <= right) {
        int mid = left + (right - left) / 2;
        steps++;
        if (arr[mid] == target)
            return mid;  // Target found
        else if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;  // Target not found
}

void analyzeSearchPerformance() {
    std::srand(std::time(nullptr));  // Seed for random number generation
    std::vector<int> sizes = {1000, 10000, 100000, 1000000};  // Different dataset sizes

    for (int n : sizes) {
        std::vector<int> arr(n);
        // Fill the array with sorted integers from 0 to n-1
        for (int i = 0; i < n; ++i) {
            arr[i] = i;
        }

        int steps;
        // Best-case scenario: Target is in the middle
        int target_best = arr[n / 2];
        auto start = std::chrono::high_resolution_clock::now();
        int index = binarySearch(arr, target_best, steps);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::cout << "Best-case for n=" << n << ": Found target at index " << index
                  << " in " << steps << " steps. Time taken: " << elapsed.count() << " seconds.\n";

        // Worst-case scenario: Target is not in the array
        int target_worst = -1;  // Target less than any element in the array
        start = std::chrono::high_resolution_clock::now();
        index = binarySearch(arr, target_worst, steps);
        end = std::chrono::high_resolution_clock::now();
        elapsed = end - start;
        std::cout << "Worst-case for n=" << n << ": Target not found after " << steps
                  << " steps. Time taken: " << elapsed.count() << " seconds.\n";

        // Average-case scenario: Target is a random element
        int target_avg = arr[std::rand() % n];
        start = std::chrono::high_resolution_clock::now();
        index = binarySearch(arr, target_avg, steps);
        end = std::chrono::high_resolution_clock::now();
        elapsed = end - start;
        std::cout << "Average-case for n=" << n << ": Found target at index " << index
                  << " in " << steps << " steps. Time taken: " << elapsed.count() << " seconds.\n";

        std::cout << std::string(60, '-') << std::endl;
    }
}

int main() {
    analyzeSearchPerformance();
    return 0;
}
