#include <iostream>
#include <vector>

int main() {
    std::vector<int> numbers;
    int size;
    int input;
    int min;
    int i = 0;
    int j = 0;
    int tmp;
    int missingMin;

    std::cout << "How many numbers? ";
    std::cin >> size;

    numbers.resize(size);

    std::cout << "Please enter the numbers ";

    for (int i = 0; i < size; i++) {
        std::cin >> input;
        numbers.at(i) = input;
    }

    min = numbers.at(0);

    while (j < numbers.size() * numbers.size()) {
        if (numbers.at(i) > numbers.at(i + 1)) {
            tmp = numbers.at(i);
            numbers.at(i) = numbers.at(i + 1);
            numbers.at(i + 1) = tmp;
        }

        j++;
        i++;

        if (i == numbers.size() - 1) {
            i = 0;
        }
    }

    for (int i = 0; i < numbers.size() - 1; i++) {
        if (numbers.at(i) - numbers.at(i + 1) != -1) {
            missingMin = numbers.at(i) + 1;
            break;
        }
        else {
            missingMin = numbers.size() + 1;
        }
    }

    std::cout <<  "The smallest missing number is " << missingMin << std::endl;

    return 0;
}
