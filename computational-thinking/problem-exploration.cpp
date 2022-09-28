#include <iostream>

int main()
{
    int num = 1;

    std::cout << num << ' ';

    for (int i = 0; i < 7; i++) {
        num % 2 == 0 ? num /= 2 : num = (num * 5) + 1;

        std::cout << num << ' ';
    }

    return 0;
}
