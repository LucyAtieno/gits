#include <vector>
#include <algorithm>

std::vector<int> radixSort(std::vector<int>& arr) {
    if (arr.empty()) return {};

    int maxNum = *std::max_element(arr.begin(), arr.end());
    int exp = 1;  // Exponent representing the digit position
    const int base = 10;  // Base of the numeral system (decimal)

    std::vector<int> output = arr;

    while (maxNum / exp > 0) {
        std::vector<int> count(base, 0);

        // Counting occurrences
        for (int number : output) {
            int index = (number / exp) % base;
            count[index]++;
        }

        // Cumulative count
        for (int i = 1; i < base; ++i) {
            count[i] += count[i - 1];
        }

        std::vector<int> temp(output.size());

        // Building the output array
        for (int i = output.size() - 1; i >= 0; --i) {
            int index = (output[i] / exp) % base;
            count[index]--;
            temp[count[index]] = output[i];
        }

        output = temp;
        exp *= base;
    }

    return output;
}
