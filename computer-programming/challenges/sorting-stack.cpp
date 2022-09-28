#include <iostream>
#include <stack>
#include <stdexcept>
#include <fstream>

std::stack<int> validateFileName(int argc, char *argv[])
{
    std::ifstream fileHandler;
    std::stack<int> numStack;
    int num;

    if (argc == 1) {
        throw std::runtime_error("an error occurred: no input file name given");
    }

    std::string fileName = argv[1];

    fileHandler.open(fileName);

    if (fileHandler.is_open()) {
        while (!fileHandler.fail()) {
            fileHandler >> num;

            if (!fileHandler.fail()) {
                numStack.push(num);
            }
        }

        fileHandler.close();
    }
    else {
        throw std::runtime_error("could not open input file " + fileName);
    }

    return numStack;
}

void sortStack(std::stack<int> &numStack, int &topStored, int &tempNum)
{
    topStored = numStack.top();
    numStack.pop();

    if (topStored < numStack.top()) {
        numStack.push(topStored);
        return;
    }
    else {
        tempNum = numStack.top();
        numStack.top() = topStored;
        topStored = tempNum;
    }

    sortStack(numStack, topStored, tempNum);
}

void printStack(std::stack<int> numStack)
{
    while (!numStack.empty()) {
        std::cout << numStack.top() << ' ';
        numStack.pop();
    }
}

int main(int argc, char *argv[])
{
    try {
        std::stack<int> numStack;
        numStack = validateFileName(argc, argv);

        int topStored = numStack.top();
        int tempNum = 0;

        if (numStack.size() < 2) {
            printStack(numStack);

            return 0;
        }

        sortStack(numStack, topStored, tempNum);

        printStack(numStack);
    }
    catch (std::runtime_error &except) {
        std::cout << except.what() << std::endl;
    }

    return 0;
}
