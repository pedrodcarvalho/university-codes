#include <iostream>
#include <stack>

double reversePolishNotation(std::string equation)
{
    int a, b, result;
    std::stack<double> resultStack;

    for (int i = 0; i < equation.size(); i++) {
        if (equation.at(i) == '+' || equation.at(i) == '-' || equation.at(i) == '*' || equation.at(i) == '/') {
            a = resultStack.top();
            resultStack.pop();

            b = resultStack.top();
            resultStack.pop();

            if (equation.at(i) == '+') {
                result = b + a;
            }
            else if (equation.at(i) == '-') {
                result = b - a;
            }
            else if (equation.at(i) == '*') {
                result = b * a;
            }
            else if (equation.at(i) == '/') {
                result = b / a;
            }

            resultStack.push(result);
        }
        else if (equation.at(i) >= '0' && equation.at(i) <= '9') {
            resultStack.push(int(equation.at(i) - '0'));
        }
    }

    return resultStack.top();
}

int main()
{
    std::string equation = "4 5 - 3 *";
    std::cout << "The result is: " << reversePolishNotation(equation) << std::endl;
    return 0;
}
