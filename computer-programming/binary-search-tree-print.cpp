#include <iostream>
#include <iomanip>
#include <vector>

class BST {
  public:
    BST();
    ~BST();
    void insertKey(int newKey);
    bool hasKey(int searchKey);
    std::vector<int> inOrder();
    int getHeight();
    void prettyPrint();

  private:
    int key;
    BST *left;
    BST *right;
    std::vector<int> treeInOrder;
    std::vector<int> treeUnsorted;
};

BST::BST()
{
    key = -1;
    left = nullptr;
    right = nullptr;
}

BST::~BST()
{
    delete left;
    delete right;
}

void BST::insertKey(int newKey)
{
    treeUnsorted.push_back(newKey);

    if (key == -1) {
        key = newKey;
    }
    else if (newKey < key) {
        if (left == nullptr) {
            left = new BST();
        }

        left->insertKey(newKey);
    }
    else {
        if (right == nullptr) {
            right = new BST();
        }

        right->insertKey(newKey);
    }
}

bool BST::hasKey(int searchKey)
{
    if (key == searchKey) {
        return true;
    }
    else if (searchKey < key) {
        if (left == nullptr) {
            return false;
        }

        return left->hasKey(searchKey);
    }
    else {
        if (right == nullptr) {
            return false;
        }

        return right->hasKey(searchKey);
    }
}

std::vector<int> BST::inOrder()
{
    std::vector<int> keysInOrder;

    if (left != nullptr) {
        std::vector<int> leftKey = left->inOrder();

        keysInOrder.insert(keysInOrder.end(), leftKey.begin(), leftKey.end());
    }

    keysInOrder.push_back(key);

    if (right != nullptr) {
        std::vector<int> rightKey = right->inOrder();

        keysInOrder.insert(keysInOrder.end(), rightKey.begin(), rightKey.end());
    }

    treeInOrder = keysInOrder;

    return keysInOrder;
}

int BST::getHeight()
{
    int leftHeight = 0;
    int rightHeight = 0;

    if (this->key == -1) {
        return 0;
    }

    if (left != nullptr) {
        leftHeight = left->getHeight();
    }
    if (right != nullptr) {
        rightHeight = right->getHeight();
    }

    if (leftHeight > rightHeight) {
        return leftHeight + 1;
    }
    else {
        return rightHeight + 1;
    }
}

void BST::prettyPrint()
{
    std::vector<std::vector<int>> matrix(getHeight(), std::vector<int>(treeInOrder.size(), -1));

    for (int i = 0; i < getHeight(); i++) {
        for (int j = 0; j < treeUnsorted.size(); j++) {
            if (treeInOrder.at(j) == treeInOrder.at(i)) {
                matrix.at(i).at(j) = treeInOrder.at(j);
            }
        }
    }

    for (int i = 0; i < matrix.size(); i++) {
        std::cout << std::setfill('-') << std::setw((treeInOrder.size() * 5) + 1) << "" << '\n';
        std::cout << std::setfill(' ');

        for (int j = 0; j < matrix.at(0).size(); j++) {
            std::cout << '|' << std::setw(4);

            matrix.at(i).at(j) == -1 ? std::cout << " " : std::cout << matrix.at(i).at(j);
        }

        std::cout << '|' << '\n';
    }

    if (matrix.size() > 0) {
        std::cout << std::setfill('-') << std::setw((treeInOrder.size() * 5) + 1) << "" << '\n';
    }
}

int main()
{
    BST tree;
    int key;
    std::vector<int> treeInOrder;

    std::cout << "Enter the numbers to be stored: ";

    while (!std::cin.fail()) {
        std::cin >> key;

        if (!std::cin.fail()) {
            tree.insertKey(key);
        }
    }

    std::cin.clear();
    std::cin.ignore(999, '\n');

    std::cout << "The numbers in sorted order: ";

    treeInOrder = tree.inOrder();

    for (int i = 0; i < treeInOrder.size(); i++) {
        if (treeInOrder.at(i) != -1) {
            std::cout << treeInOrder.at(i) << ' ';
        }
    }

    std::cout << '\n';

    tree.prettyPrint();

    std::cout << std::endl;

    return 0;
}
