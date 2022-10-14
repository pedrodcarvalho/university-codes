#include <iostream>
#include <vector>

class BST {
  public:
    BST();
    ~BST();
    void insertKey(int newKey);
    bool hasKey(int searchKey);
    std::vector<int> inOrder();
    int getHeight();

  private:
    int key;
    BST *left;
    BST *right;
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

int main()
{
    BST tree;
    int key;
    int keyToSearch;
    std::vector<int> treeInOrder;

    std::cout << "Enter the numbers to be stored (end with a letter): ";

    while (!std::cin.fail()) {
        std::cin >> key;

        if (!std::cin.fail()) {
            tree.insertKey(key);
        }
    }

    std::cin.clear();
    std::cin.ignore(999, '\n');

    std::cout << "Which number do you want to look up? ";
    std::cin >> keyToSearch;

    std::cout << keyToSearch << " is in the tree: ";

    if (tree.hasKey(keyToSearch)) {
        std::cout << "yes\n";
    }
    else {
        std::cout << "no\n";
    }

    std::cout << "The numbers in sorted order: ";

    treeInOrder = tree.inOrder();

    for (int i = 0; i < treeInOrder.size(); i++) {
        if (treeInOrder.at(i) != -1) {
            std::cout << treeInOrder.at(i) << ' ';
        }
    }

    std::cout << "\nHeight of the tree: " << tree.getHeight() << std::endl;

    return 0;
}
