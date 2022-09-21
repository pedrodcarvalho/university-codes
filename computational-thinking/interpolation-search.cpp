#include <iostream>
#include <vector>

int InterpolationSearch(std::vector<int> L, int size, int key)
{
    int low = 0;
    int mid;
    int high = size - 1;

    while (L.at(high) != L.at(low) && key >= L.at(low) && key <= L.at(high)) {
        mid = low + ((key - L[low]) * (high - low) / (L[high] - L[low]));

        if (L[mid] < key) {
            low = mid + 1;
        }
        else if (L[mid] > key) {
            high = mid - 1;
        }
        else {
            return mid;
        }
    }

    if (key == L[low]) {
        return low;
    }
    else {
        return L.size() + 1;
    }
}

int main()
{
    std::vector<int> L = {1, 3, 12, 34, 42, 56, 89, 102};
    int size, result;
    int key = 42;

    result = InterpolationSearch(L, L.size(), key);

    if (result != L.size() + 1) {
        std::cout << "The key " << key << " is in the index " << result << " of the list" << std::endl;
    }
    else {
        std::cout << "The key is not in the list" << std::endl;
    }

    return 0;
}
