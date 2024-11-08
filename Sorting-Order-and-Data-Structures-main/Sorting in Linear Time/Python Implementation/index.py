from typing import List

def radix_sort(arr: List[int]) -> List[int]:
    if not arr:
        return []

    max_num = max(arr)
    exp = 1  # Exponent representing the digit position
    base = 10  # Base of the numeral system (decimal)

    output = arr.copy()

    while max_num // exp > 0:
        count = [0] * base

        # Counting occurrences
        for number in output:
            index = (number // exp) % base
            count[index] += 1

        # Cumulative count
        for i in range(1, base):
            count[i] += count[i - 1]

        temp = [0] * len(output)

        # Building the output array
        for i in reversed(range(len(output))):
            index = (output[i] // exp) % base
            count[index] -= 1
            temp[count[index]] = output[i]

        output = temp
        exp *= base

    return output
