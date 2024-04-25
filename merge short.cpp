#include <iostream>
#include <vector>

std::vector<int> merge(const std::vector<int>& left, const std::vector<int>& right) {
    std::vector<int> result;
    int i = 0, j = 0;

    while (i < left.size() && j < right.size()) {
        if (left[i] < right[j]) {
            result.push_back(left[i++]);
        } else {
            result.push_back(right[j++]);
        }
    }

    while (i < left.size()) {
        result.push_back(left[i++]);
    }

    while (j < right.size()) {
        result.push_back(right[j++]);
    }

    return result;
}


int main() {
    std::vector<int> left = {1, 3, 5};
    std::vector<int> right = {2, 4, 6};

    std::vector<int> merged = merge(left, right);

    std::cout << "Merged Array: ";
    for (int num : merged) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
