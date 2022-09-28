#include <iostream>
#include <vector>
#include "headers/merge-sort.h"

int main()
{
    std::vector<double> data = {42.0, -7, 1.001e3, -16.5, 2.5, 0.0, -17.8};

    mergeSort(data, 0, data.size() - 1);

    for (int i = 0; i < data.size(); i++) {
        std::cout << data.at(i) << ' ';
    }

    std::cout << std::endl;

    return 0;
}
