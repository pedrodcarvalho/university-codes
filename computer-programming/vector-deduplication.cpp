#include <iostream>
#include <vector>

void deduplicateVector(std::vector<int> &nums)
{
    std::vector<int> numsDeduplicated;
    int duplicatedNum;

    for (int i = 0; i < nums.size(); i++) {
        for (int j = 0; j < numsDeduplicated.size(); j++) {
            if (nums.at(i) == numsDeduplicated.at(j)) {
                duplicatedNum++;
            }
        }
        if (duplicatedNum == 0) {
            numsDeduplicated.push_back(nums.at(i));
        }
        else {
            duplicatedNum = 0;
        }
    }

    nums = numsDeduplicated;
}

void printVector (std::vector<int> nums)
{
    std::cout << "The deduplicated vector is: [";

    for (int i = 0; i < nums.size(); i++) {
        if (i != nums.size() - 1) {
            std::cout << nums.at(i) << ",";
        }
        else {
            std::cout << nums.at(i) << "]" << std::endl;
        }
    }
}

int main()
{
    std::vector<int> nums;
    int input;

    std::cout << "Enter the vector elements: ";

    while(std::cin.good()) {
        std::cin >> input;

        if (std::cin.good() || std::cin.eof()) {
            nums.push_back(input);
        }
    }

    deduplicateVector(nums);
    printVector(nums);

    return 0;
}
