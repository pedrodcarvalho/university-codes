#include <iostream>

int main()
{
    int num;
    int endSequence;

    std::cout << "Enter the first number of the sequence: ";
    std::cin >> num;
    std::cout << num << " ";

    while (endSequence < 3)
    {
        if (num % 2 == 0)
            num /= 2;
        else
            num = 3 * num + 1;

        std::cout << num << " ";

        if (num == 1)
            endSequence++;
    }

    std::cout << "...";

    return 0;
}
