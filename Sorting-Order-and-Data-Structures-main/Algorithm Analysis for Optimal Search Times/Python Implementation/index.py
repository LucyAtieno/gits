import time
import random

def binary_search(arr, target):
    """Performs binary search on a sorted array."""
    left, right = 0, len(arr) - 1
    steps = 0  # Count the number of steps to find the target
    while left <= right:
        mid = (left + right) // 2
        steps += 1
        if arr[mid] == target:
            return mid, steps  # Return index and steps taken
        elif arr[mid] < target:
            left = mid + 1
        else:
            right = mid - 1
    return -1, steps  # Target not found

def simulate_search_cases():
    """Simulates best, worst, and average-case scenarios for binary search."""
    sizes = [10**3, 10**4, 10**5, 10**6]  # Different dataset sizes
    for n in sizes:
        arr = list(range(n))  # Sorted array from 0 to n-1

        # Best-case scenario: Target is in the middle
        target_best = arr[len(arr) // 2]
        start_time = time.time()
        index, steps = binary_search(arr, target_best)
        end_time = time.time()
        print(f"Best-case for n={n}: Found target at index {index} in {steps} steps. Time taken: {end_time - start_time:.6f} seconds.")

        # Worst-case scenario: Target is not in the array
        target_worst = -1  # Target less than any element in the array
        start_time = time.time()
        index, steps = binary_search(arr, target_worst)
        end_time = time.time()
        print(f"Worst-case for n={n}: Target not found after {steps} steps. Time taken: {end_time - start_time:.6f} seconds.")

        # Average-case scenario: Target is a random element
        target_avg = random.choice(arr)
        start_time = time.time()
        index, steps = binary_search(arr, target_avg)
        end_time = time.time()
        print(f"Average-case for n={n}: Found target at index {index} in {steps} steps. Time taken: {end_time - start_time:.6f} seconds.")

        print("-" * 60)

if __name__ == "__main__":
    simulate_search_cases()
