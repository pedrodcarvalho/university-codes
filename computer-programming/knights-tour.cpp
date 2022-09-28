#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

std::vector<int> validateCMDArguments(int argc, char *argv[])
{
    if (argc != 4 || !isdigit(*argv[1])) {
        throw std::runtime_error("invalid parameter list");
    }

    std::vector<int> positionIndexes;
    std::string CMDArguments;

    for (int i = 1; i < 4; i++) {
        CMDArguments = CMDArguments + argv[i] + ' ';
    }

    std::istringstream inputStringStream(CMDArguments);

    int boardSize;
    std::string startPos, endPos;

    inputStringStream >> boardSize >> startPos >> endPos;

    if (boardSize > 26) {
        throw std::runtime_error("invalid parameter list");
    }
    else if (*argv[1] == '2') {
        throw std::runtime_error("could not find a knight's tour");
    }

    int startPosLetter = startPos[0] - 96;
    int endPosLetter = endPos[0] - 96;
    int startPosNumber = startPos[1] - 48;
    int endPosNumber = endPos[1] - 48;

    if (startPosNumber > boardSize || endPosNumber > boardSize || startPosLetter > boardSize || endPosLetter > boardSize) {
        throw std::runtime_error("invalid parameter list");
    }

    positionIndexes.push_back(startPosLetter);
    positionIndexes.push_back(startPosNumber);
    positionIndexes.push_back(endPosLetter);
    positionIndexes.push_back(endPosNumber);
    positionIndexes.push_back(boardSize);

    return positionIndexes;
}

bool findKnightsTour(std::vector<std::vector<bool>> &board, std::vector<int> positionIndexes, int BOARD_SIZE, std::vector<int> iMoves, std::vector<int> jMoves, std::vector<int> currentIndex, std::string moveset, bool moved, int backtrack)
{
    for (int i = 0; i < iMoves.size(); i++) {
        if ((currentIndex.at(0) + iMoves.at(i)) > (BOARD_SIZE - 1) || (currentIndex.at(0) + iMoves.at(i)) < 0) {
            continue;
        }
        else if ((currentIndex.at(1) + jMoves.at(i)) > (BOARD_SIZE - 1) || (currentIndex.at(1) + jMoves.at(i)) < 0) {
            continue;
        }
        else {
            if (board.at(currentIndex.at(0) + iMoves.at(i)).at(currentIndex.at(1) + jMoves.at(i)) != 1) {
                board.at(currentIndex.at(0)).at(currentIndex.at(1)) = 1;

                moveset = moveset + static_cast<char>(currentIndex.at(1) + 97) + static_cast<char>((BOARD_SIZE - currentIndex.at(0)) + 48) + ' ';

                currentIndex.at(0) += iMoves.at(i);
                currentIndex.at(1) += jMoves.at(i);

                moved = true;

                break;
            }
        }

        moved = false;
    }

    bool continueRecursion = false;

    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board.size(); j++) {
            if (board.at(i).at(j) == 0) {
                continueRecursion = true;
                break;
            }
        }
    }

    if (board.at(positionIndexes.at(3)).at(positionIndexes.at(2)) == 1) {
        std::cout << moveset << std::endl;

        return true;
    }
    else if (!moved) {
        iMoves.push_back(iMoves.at(0));
        jMoves.push_back(jMoves.at(0));
        iMoves.erase(iMoves.begin());
        jMoves.erase(jMoves.begin());

        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board.size(); j++) {
                board.at(i).at(j) = 0;
            }
        }

        currentIndex = {positionIndexes.at(1), positionIndexes.at(0)};

        moveset = "";

        backtrack++;

        if (backtrack < 8) {
            return findKnightsTour(board, positionIndexes, BOARD_SIZE, iMoves, jMoves, currentIndex, moveset, moved, backtrack);
        }
        else {
            return false;
        }
    }
    else if (continueRecursion) {
        return findKnightsTour(board, positionIndexes, BOARD_SIZE, iMoves, jMoves, currentIndex, moveset, moved, backtrack);
    }

    return false;
}

int main(int argc, char *argv[])
{
    try {
        std::string moveset;
        bool moved = false;
        int backtrack = 0;
        std::vector<int> positionIndexes;
        positionIndexes = validateCMDArguments(argc, argv);

        const int BOARD_SIZE = positionIndexes.at(4);

        std::vector<std::vector<bool>> board(BOARD_SIZE, std::vector<bool>(BOARD_SIZE, 0));

        std::vector<int> iMoves = {-2, -1, 1, 2, 2, 1, -1, -2};
        std::vector<int> jMoves = {-1, -2, -2, -1, 1, 2, 2, 1};

        positionIndexes.at(0)--;
        positionIndexes.at(1) = BOARD_SIZE - positionIndexes.at(1);
        positionIndexes.at(2)--;
        positionIndexes.at(3) = BOARD_SIZE - positionIndexes.at(3);

        std::vector<int> currentIndex = {positionIndexes.at(1), positionIndexes.at(0)};

        bool completeTour = findKnightsTour(board, positionIndexes, BOARD_SIZE, iMoves, jMoves, currentIndex, moveset, moved, backtrack);

        if (completeTour) {
            return 0;
        }
        else {
            std::cout << "could not find a knight's tour" << std::endl;
        }
    }
    catch (std::runtime_error &except) {
        std::cout << except.what() << std::endl;
    }

    return 0;
}
