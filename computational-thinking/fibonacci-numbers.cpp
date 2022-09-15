#include <iostream>

int main()
{
    int fibonacciNumbers[10] = {0};

    fibonacciNumbers[1] = 1;

    std::cout << fibonacciNumbers[0] << ", ";
    std::cout << fibonacciNumbers[1] << ", ";

    for (int i = 2; i < 10; i++) {
        fibonacciNumbers[i] = fibonacciNumbers[i - 1] + fibonacciNumbers[i - 2];

        std::cout << fibonacciNumbers[i] << ", ";
    }

    std::cout << "..." << std::endl;

    return 0;
}
