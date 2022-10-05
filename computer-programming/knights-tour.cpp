#include <iostream>
#include <cctype>
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
    int startPosNumber;
    int endPosNumber;

    startPos[2] ? startPosNumber = (startPos[1] - 48) * 10 + (startPos[2] - 48) : startPosNumber = startPos[1] - 48;

    endPos[2] ? endPosNumber = (endPos[1] - 48) * 10 + (endPos[2] - 48) : endPosNumber = endPos[1] - 48;

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

bool findKnightsTour(std::vector<std::vector<bool>> board, std::vector<int> positionIndexes, int BOARD_SIZE, std::vector<int> iMoves, std::vector<int> jMoves, std::vector<int> currentIndex, std::string moveset, bool moved, bool continueRecursion, int backtrack, int iMovement, int jMovement)
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

                moveset = moveset + static_cast<char>(currentIndex.at(1) + 97) + static_cast<char>(BOARD_SIZE - currentIndex.at(0) > 9 ? static_cast<char>(((BOARD_SIZE - currentIndex.at(0)) / 10) + 48) : (BOARD_SIZE - currentIndex.at(0)) + 48);

                if ((BOARD_SIZE - currentIndex.at(0)) > 9) {
                    moveset = moveset + static_cast<char>(((BOARD_SIZE - currentIndex.at(0)) % 10) + 48) + ' ';
                }
                else {
                    moveset = moveset + ' ';
                }

                iMovement = iMoves.at(i);
                jMovement = jMoves.at(i);

                currentIndex.at(0) += iMovement;
                currentIndex.at(1) += jMovement;

                moved = true;

                break;
            }
        }

        moved = false;
    }

    continueRecursion = false;

    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board.size(); j++) {
            if (board.at(i).at(j) == false) {
                continueRecursion = true;
                break;
            }
        }
    }

    if (board.at(positionIndexes.at(3)).at(positionIndexes.at(2)) == true) {
        std::cout << moveset << std::endl;

        return true;
    }
    else if (!moved) {
        iMoves.push_back(iMoves.at(0));
        jMoves.push_back(jMoves.at(0));

        for (int i = 0; i < iMoves.size() - 1; i++) {
            iMoves.at(i) = iMoves.at(i + 1);
            jMoves.at(i) = jMoves.at(i + 1);
        }

        if (BOARD_SIZE > 9) {
            if (currentIndex.at(0) >= 0 && currentIndex.at(1) >= 0) {
                board.at(currentIndex.at(0)).at(currentIndex.at(1)) = false;
            }

            currentIndex = {positionIndexes.at(1) -= jMovement, positionIndexes.at(0) -= iMovement};

            moveset.resize(4);
        }
        else {
            for (int i = 0; i < board.size(); i++) {
                for (int j = 0; j < board.size(); j++) {
                    board.at(i).at(j) = false;
                }
            }

            currentIndex = {positionIndexes.at(1), positionIndexes.at(0)};

            moveset = "";
        }

        backtrack++;

        if (backtrack < 8) {
            return findKnightsTour(board, positionIndexes, BOARD_SIZE, iMoves, jMoves, currentIndex, moveset, moved, continueRecursion, backtrack, iMovement, jMovement);
        }
        else {
            return false;
        }
    }
    else if (continueRecursion) {
        return findKnightsTour(board, positionIndexes, BOARD_SIZE, iMoves, jMoves, currentIndex, moveset, moved, continueRecursion, backtrack, iMovement, jMovement);
    }

    return false;
}

int main(int argc, char *argv[])
{
    try {
        std::string moveset;
        bool moved = false;
        bool continueRecursion = false;
        int backtrack = 0;
        int iMovement = 0;
        int jMovement = 0;

        std::vector<int> positionIndexes;
        positionIndexes = validateCMDArguments(argc, argv);

        const int BOARD_SIZE = positionIndexes.at(4);

        std::vector<std::vector<bool>> board(BOARD_SIZE, std::vector<bool>(BOARD_SIZE, false));

        std::vector<int> iMoves, jMoves;

        if (BOARD_SIZE < 10) {
            iMoves = {-2, -1, 1, 2, 2, 1, -1, -2};
            jMoves = {-1, -2, -2, -1, 1, 2, 2, 1};
        }
        else {
            iMoves = {-2, -2, -1, 1, 2, 2, 1, -1};
            jMoves = {1, -1, -2, -2, -1, 1, 2, 2};
        }

        positionIndexes.at(0)--;
        positionIndexes.at(1) = BOARD_SIZE - positionIndexes.at(1);
        positionIndexes.at(2)--;
        positionIndexes.at(3) = BOARD_SIZE - positionIndexes.at(3);

        std::vector<int> currentIndex = {positionIndexes.at(1), positionIndexes.at(0)};

        bool completeTour = findKnightsTour(board, positionIndexes, BOARD_SIZE, iMoves, jMoves, currentIndex, moveset, moved, continueRecursion, backtrack, iMovement, jMovement);

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
