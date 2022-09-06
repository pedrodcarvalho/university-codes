#include <iostream>

int main()
{
    char op;
    float num1;
    float num2;
    float result;

    while (1)
    {
        std::cout << "Enter the expression: ";
        std::cin >> op;

        if (op == 'q')
            return 0;

        std::cin >> num1;
        std::cin >> num2;

        switch (op)
        {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            result = num1 / num2;
        }

        std::cout << num1 << " " << op << " " << num2 << " = " << result << std::endl;
    }
}
