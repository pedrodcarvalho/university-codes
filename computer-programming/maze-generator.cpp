#include <iostream>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <chrono>
#include <sys/time.h>
#include <ctime>
#include <vector>

class Arguments {
  public:
    Arguments(int argc, char *argv[]);
    int validateArguments(int argc);
    std::vector<int> getCoordinates();

  private:
    int rows, columns, seed = -1;
    std::string CMDArguments;
};

Arguments::Arguments(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        CMDArguments = CMDArguments + argv[i] + ' ';
    }
}

std::vector<int> Arguments::getCoordinates()
{
    std::vector<int> coordinates;

    coordinates.push_back(rows);
    coordinates.push_back(columns);

    if (seed) {
        coordinates.push_back(seed);
    }
    else {
        coordinates.push_back(-1);
    }

    return coordinates;
}

int Arguments::validateArguments(int argc)
{
    for (int i = 0; i < CMDArguments.size(); i++) {
        if (isalpha(CMDArguments.at(i))) {
            throw std::runtime_error("invalid parameter list");
        }
    }

    std::istringstream inputStringStream(CMDArguments);
    rows, columns, seed;

    if (argc == 3) {
        inputStringStream >> rows >> columns;
    }
    else if (argc == 4) {
        inputStringStream >> rows >> columns >> seed;
    }
    else {
        throw std::runtime_error("parameter list should have the format: \"int row int column int seed(optional)\"");
    }

    return 0;
}

class Maze {
  public:
    Maze(Arguments argumentsObj);
    void initializeMaze();
    void generateMaze(std::vector<int> currentCoordinate, std::vector<bool> possibleMoves, std::vector<int> moves);
    int randomPath(std::vector<bool> possibleMoves, int SEED);
    std::vector<std::vector<char>> getMaze();
    int getColumns();

  private:
    std::vector<int> coordinates;
    int ROWS;
    int COLUMNS;
    int SEED;
    std::vector<std::vector<char>> maze;

    std::vector<int> currentCoordinate = {1, 2};
    std::vector<bool> possibleMoves = {false, false, false, false};
    std::vector<int> moves;
};

Maze::Maze(Arguments argumentsObj)
{
    coordinates = argumentsObj.getCoordinates();

    ROWS = coordinates.at(0);
    COLUMNS = coordinates.at(1);

    if (coordinates.size() == 3) {
        SEED = coordinates.at(2);
    }

    Maze::initializeMaze();
    Maze::generateMaze(currentCoordinate, possibleMoves, moves);
}

void Maze::initializeMaze()
{
    maze.resize((ROWS * 2) + 1);

    for (int i = 0; i < maze.size(); i++) {
        for (int j = 0; j < (COLUMNS * 4) + 1; j++) {
            if (j % 4 == 0 && i % 2 == 0) {
                maze.at(i).push_back('+');
            }
            else if (j % 4 == 0 && i % 2 == 1) {
                maze.at(i).push_back('|');
            }
            else if (i % 2 == 0) {
                maze.at(i).push_back('-');
            }
            else {
                maze.at(i).push_back(' ');
            }
        }
    }
}

void Maze::generateMaze(std::vector<int> currentCoordinate, std::vector<bool> possibleMoves, std::vector<int> moves)
{
    int currentRow = currentCoordinate.at(0);
    int currentColumn = currentCoordinate.at(1);

    maze.at(currentRow).at(currentColumn) = '.';

    int visited = 0;
    for (int i = 1; i < maze.size() - 1; i++) {
        for (int j = 2; j < (COLUMNS * 4) - 1; j++) {
            if (maze.at(i).at(j) == '.') {
                visited++;
            }
        }
    }

    if (visited == ROWS * COLUMNS) {
        for (int i = 1; i < maze.size() - 1; i++) {
            for (int j = 2; j < (COLUMNS * 4) - 1; j += 4) {
                if (maze.at(i).at(j) == '.') {
                    maze.at(i).at(j) = ' ';
                }
            }
        }

        return;
    }

    moves.push_back(currentRow);
    moves.push_back(currentColumn);

    if (currentColumn != 2 && maze.at(currentRow).at(currentColumn - 4) != '.') {
        possibleMoves.at(0) = true;
    }
    if (currentRow != 1 && maze.at(currentRow - 2).at(currentColumn) != '.') {
        possibleMoves.at(1) = true;
    }
    if (currentColumn != (maze.at(0).size() - 3) && maze.at(currentRow).at(currentColumn + 4) != '.') {
        possibleMoves.at(2) = true;
    }
    if (currentRow != (maze.size() - 2) && maze.at(currentRow + 2).at(currentColumn) != '.') {
        possibleMoves.at(3) = true;
    }

    if ((possibleMoves.at(0) == false && possibleMoves.at(1) == false && possibleMoves.at(2) == false && possibleMoves.at(3) == false) || (currentRow == maze.size() - 2 && currentColumn == maze.at(0).size() - 3)) {
        currentCoordinate.at(0) = moves.at(moves.size() - 4);
        currentCoordinate.at(1) = moves.at(moves.size() - 3);
        currentRow = currentCoordinate.at(0);
        currentColumn = currentCoordinate.at(1);

        moves.pop_back();
        moves.pop_back();
        moves.pop_back();
        moves.pop_back();
    }

    int pathToChoose = Maze::randomPath(possibleMoves, SEED);

    int move = -1;

    for (int i = 0; i < possibleMoves.size(); i++) {
        if (possibleMoves.at(i) == true) {
            move++;
        }
        if (move == pathToChoose) {
            if (i == 0) {
                maze.at(currentRow).at(currentColumn - 2) = ' ';
                currentCoordinate.at(1) -= 4;
                break;
            }
            else if (i == 1) {
                maze.at(currentRow - 1).at(currentColumn) = ' ';
                maze.at(currentRow - 1).at(currentColumn - 1) = ' ';
                maze.at(currentRow - 1).at(currentColumn + 1) = ' ';
                currentCoordinate.at(0) -= 2;
                break;
            }
            else if (i == 2) {
                maze.at(currentRow).at(currentColumn + 2) = ' ';
                currentCoordinate.at(1) += 4;
                break;
            }
            else if (i == 3) {
                maze.at(currentRow + 1).at(currentColumn) = ' ';
                maze.at(currentRow + 1).at(currentColumn - 1) = ' ';
                maze.at(currentRow + 1).at(currentColumn + 1) = ' ';
                currentCoordinate.at(0) += 2;
                break;
            }
        }
    }

    for (int i = 0; i < possibleMoves.size(); i++) {
        possibleMoves.at(i) = false;
    }

    Maze::generateMaze(currentCoordinate, possibleMoves, moves);
}

int Maze::randomPath(std::vector<bool> possibleMoves, int SEED)
{
    int paths = 0;

    for (int i = 0; i < possibleMoves.size(); i++) {
        if (possibleMoves.at(i) == true) {
            paths++;
        }
    }

    struct timeval time_now {};
    gettimeofday(&time_now, nullptr);
    time_t msecs_time = time_now.tv_usec;

    if (SEED == -1) {
        srand(msecs_time);
        if (paths == 0) {
            return 1;
        }
        return (rand() % paths);
    }
    else {
        srand(SEED);
        return (rand() % paths);
    }
}

std::vector<std::vector<char>> Maze::getMaze()
{
    return maze;
}

int Maze::getColumns()
{
    return COLUMNS;
}

class MazeSolver {
  public:
    MazeSolver(Maze mazeObj);
    void solveMaze(std::vector<std::vector<char>> &maze, std::vector<int> currentCoordinate, int COLUMNS, std::stack<std::vector<int>> tempCoordinate, std::stack<std::vector<int>> coordinateStack);
    bool checkTwoPaths(std::vector<std::vector<char>> maze, std::vector<int> currentCoordinate, int COLUMNS);
    void printMaze();

  private:
    std::vector<std::vector<char>> maze;
    int COLUMNS;
    std::vector<int> currentCoordinate = {1, 2};
    std::stack<std::vector<int>> tempCoordinate;
    std::stack<std::vector<int>> coordinateStack;
};

MazeSolver::MazeSolver(Maze mazeObj)
{
    maze = mazeObj.getMaze();
    COLUMNS = mazeObj.getColumns();

    MazeSolver::solveMaze(maze, currentCoordinate, COLUMNS, tempCoordinate, coordinateStack);
}

void MazeSolver::solveMaze(std::vector<std::vector<char>> &maze, std::vector<int> currentCoordinate, int COLUMNS, std::stack<std::vector<int>> tempCoordinate, std::stack<std::vector<int>> coordinateStack)
{
    int currentRow = currentCoordinate.at(0);
    int currentColumn = currentCoordinate.at(1);

    maze.at(currentRow).at(currentColumn) = '.';

    if (currentRow == maze.size() - 2 && currentColumn == maze.at(0).size() - 3) {
        for (int i = 1; i < maze.size() - 1; i++) {
            for (int j = 2; j < (COLUMNS * 4) - 1; j += 4) {
                if (maze.at(i).at(j) == 'v') {
                    maze.at(i).at(j) = ' ';
                }
            }
        }

        MazeSolver::printMaze();

        return;
    }
    else {
        bool twoPaths = MazeSolver::checkTwoPaths(maze, currentCoordinate, COLUMNS);

        coordinateStack.push(currentCoordinate);

        if (twoPaths) {
            std::vector<int> backtrack = {currentRow, currentColumn};
            tempCoordinate.push(backtrack);
        }

        if (maze.at(currentRow).at(currentColumn - 2) == ' ' && maze.at(currentRow).at(currentColumn - 4) != '.' && maze.at(currentRow).at(currentColumn - 4) != 'v') {
            currentCoordinate.at(1) -= 4;
        }
        else if (maze.at(currentRow - 1).at(currentColumn) == ' ' && maze.at(currentRow - 2).at(currentColumn) != '.' && maze.at(currentRow - 2).at(currentColumn) != 'v') {
            currentCoordinate.at(0) -= 2;
        }
        else if (maze.at(currentRow).at(currentColumn + 2) == ' ' && maze.at(currentRow).at(currentColumn + 4) != '.' && maze.at(currentRow).at(currentColumn + 4) != 'v') {
            currentCoordinate.at(1) += 4;
        }
        else if (maze.at(currentRow + 1).at(currentColumn) == ' ' && maze.at(currentRow + 2).at(currentColumn) != '.' && maze.at(currentRow + 2).at(currentColumn) != 'v') {
            currentCoordinate.at(0) += 2;
        }
        else {
            while (coordinateStack.top() != tempCoordinate.top()) {
                maze.at(coordinateStack.top().at(0)).at(coordinateStack.top().at(1)) = 'v';
                coordinateStack.pop();
            }

            currentCoordinate.at(0) = tempCoordinate.top().at(0);
            currentCoordinate.at(1) = tempCoordinate.top().at(1);

            tempCoordinate.pop();
        }
    }

    MazeSolver::solveMaze(maze, currentCoordinate, COLUMNS, tempCoordinate, coordinateStack);
}

bool MazeSolver::checkTwoPaths(std::vector<std::vector<char>> maze, std::vector<int> currentCoordinate, int COLUMNS)
{
    int paths = 0;

    if (maze.at(currentCoordinate.at(0)).at(currentCoordinate.at(1) - 2) == ' ' && maze.at(currentCoordinate.at(0)).at(currentCoordinate.at(1) - 4) != '.' && maze.at(currentCoordinate.at(0)).at(currentCoordinate.at(1) - 4) != 'v') {
        paths++;
    }
    if (maze.at(currentCoordinate.at(0) - 1).at(currentCoordinate.at(1)) == ' ' && maze.at(currentCoordinate.at(0) - 2).at(currentCoordinate.at(1)) != '.' && maze.at(currentCoordinate.at(0) - 2).at(currentCoordinate.at(1)) != 'v') {
        paths++;
    }
    if (maze.at(currentCoordinate.at(0)).at(currentCoordinate.at(1) + 2) == ' ' && maze.at(currentCoordinate.at(0)).at(currentCoordinate.at(1) + 4) != '.' && maze.at(currentCoordinate.at(0)).at(currentCoordinate.at(1) + 4) != 'v') {
        paths++;
    }
    if (maze.at(currentCoordinate.at(0) + 1).at(currentCoordinate.at(1)) == ' ' && maze.at(currentCoordinate.at(0) + 2).at(currentCoordinate.at(1)) != '.' && maze.at(currentCoordinate.at(0) + 2).at(currentCoordinate.at(1)) != 'v') {
        paths++;
    }

    if (paths > 1) {
        return true;
    }
    else {
        return false;
    }
}

void MazeSolver::printMaze()
{
    for (int i = 0; i < maze.size(); i++) {
        for (int j = 0; j < (COLUMNS * 4) + 1; j++) {
            std::cout << maze.at(i).at(j);
        }

        std::cout << std::endl;
    }
}

int main(int argc, char *argv[])
{
    Arguments argumentsObj(argc, argv);

    try {
        argumentsObj.validateArguments(argc);
    }
    catch (std::runtime_error &except) {
        std::cout << except.what() << std::endl;
        return 1;
    }

    Maze mazeObj(argumentsObj);
    MazeSolver solverObj(mazeObj);

    return 0;
}
