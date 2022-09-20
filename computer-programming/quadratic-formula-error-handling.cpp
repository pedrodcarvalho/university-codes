#include <iostream>
#include <cmath>
#include <stdexcept>
#include <vector>

double getInputs(double &a, double &b, double &c)
{
    std::cout << "Please enter the values of a, b, and c: ";
    std::cin >> a >> b >> c;

    if (std::cin.fail() || !b || !c) {
        throw std::runtime_error("An error occurred: Malformed user input");
    }
    if (a == 0) {
        throw std::runtime_error("An error occurred: a must not be zero");
    }
    else {
        return 1.0;
    }
}

double calculateDiscriminant(double a, double b, double c)
{
    double discriminant;

    discriminant = (b * b) - (4 * a * c);

    return discriminant;
}

std::vector<double> calculateSolutions(double a, double b, double c, double discriminant)
{
    std::vector<double> solutions(2);

    solutions.at(0) = (-b + sqrt(discriminant)) / (2 * a);
    solutions.at(1) = (-b - sqrt(discriminant)) / (2 * a);

    return solutions;
}

int main()
{
    double a;
    double b;
    double c;
    double discriminant;
    std::vector<double> solutions(2);

    try {
        getInputs(a, b, c);
    }
    catch (std::runtime_error &except) {
        std::cout << except.what() << std::endl;

        return 1;
    }

    discriminant = calculateDiscriminant(a, b, c);
    solutions = calculateSolutions(a, b, c, discriminant);

    if (discriminant > 0) {
        std::cout << "There are 2 solutions.\n\n";
        std::cout << "The solutions are: " << solutions.at(0) << " and " << solutions.at(1) << std::endl;
    }
    else if (discriminant == 0) {
        std::cout << "There is 1 solution.\n\n";
        std::cout << "The solution is: " << solutions.at(0) << std::endl;
    }
    else {
        std::cout << "There is no solution." << std::endl;
    }

    return 0;
}
