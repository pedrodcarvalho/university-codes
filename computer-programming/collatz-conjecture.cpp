#include <iostream>

int main()
{
    unsigned int num;
    unsigned int endSequence = 0;

    std::cout << "Enter the first number of the sequence: ";
    std::cin >> num;

    while (endSequence < 3) {
        std::cout << num << " ";

        if (num == 1) {
            endSequence++;
        }

        if (num % 2 == 0) {
            num /= 2;
        }
        else {
            num = (3 * num) + 1;
        }
    }

    std::cout << "..." << std::endl;

    return 0;
}
