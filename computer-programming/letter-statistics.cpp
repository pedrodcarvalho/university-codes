#include <iostream>
#include <cctype>
#include <fstream>
#include <stdexcept>
#include <vector>

void countLetterOccurrences(std::string text, std::vector<int> &latinAlphabet)
{
    for (int i = 0; i < text.size(); i++) {
        if (isalpha(text[i])) {
            latinAlphabet.at(tolower(text[i]) - 97) += 1;
        }
    }
}

void findMostOccurrences(std::vector<int> latinAlphabet, int &indexVowel, int &indexConsonant, int &indexOverall)
{
    int maxVowel = 0, maxConsonant = 0, maxOverall = 0;

    for (int i = 0; i < latinAlphabet.size(); i++) {
        if (latinAlphabet.at(i) > maxVowel && (i == 0 || i == 4 || i == 8 || i == 14 || i == 20)) {
            maxVowel = latinAlphabet.at(i);
            indexVowel = i;
        }

        if (latinAlphabet.at(i) > maxConsonant && (i != 0 && i != 4 && i != 8 && i != 14 && i != 20)) {
            maxConsonant = latinAlphabet.at(i);
            indexConsonant = i;
        }

        if (latinAlphabet.at(i) > maxOverall) {
            maxOverall = latinAlphabet.at(i);
            indexOverall = i;
        }
    }
}

void printMostOccurrences(std::vector<int> latinAlphabet, int indexVowel, int indexConsonant, int indexOverall)
{
    std::cout << "\nMost frequent vowel: " << static_cast<char>(97 + indexVowel)
              << " (" << latinAlphabet.at(indexVowel) << " times)" << std::endl;
    std::cout << "Most frequent consonant: " << static_cast<char>(97 + indexConsonant)
              << " (" << latinAlphabet.at(indexConsonant) << " times)" << std::endl;
    std::cout << "Most frequent letter, overall: " << static_cast<char>(97 + indexOverall)
              << " (" << latinAlphabet.at(indexOverall) << " times)" << std::endl;
}

int validateCMDArguments(int argc, char *argv[])
{
    try {
        std::ifstream fileHandler;
        std::string fileName = argv[1];

        fileHandler.open(argv[1]);

        if (argc > 2) {
            throw std::runtime_error("cannot handle parameter list");
        }
        if (!fileHandler.is_open()) {
            throw std::runtime_error("cannot open input file " + fileName);
        }
    }
    catch (std::runtime_error &except) {
        std::cout << except.what() << std::endl;
        return 1;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    std::string text;
    std::vector<int> latinAlphabet(26, 0);
    int indexVowel = 0;
    int indexConsonant = 1;
    int indexOverall = 0;

    if (argv[1]) {
        int error = validateCMDArguments(argc, argv);

        if (!error) {
            std::ifstream fileHandler;
            std::string tmp;

            fileHandler.open(argv[1]);

            while (!fileHandler.eof()) {
                fileHandler >> tmp;
                text += tmp;
            }

            fileHandler.close();

            countLetterOccurrences(text, latinAlphabet);
            findMostOccurrences(latinAlphabet, indexVowel, indexConsonant, indexOverall);
            printMostOccurrences(latinAlphabet, indexVowel, indexConsonant, indexOverall);
        }
    }
    else {
        getline(std::cin, text, static_cast<char>(EOF));

        countLetterOccurrences(text, latinAlphabet);
        findMostOccurrences(latinAlphabet, indexVowel, indexConsonant, indexOverall);
        printMostOccurrences(latinAlphabet, indexVowel, indexConsonant, indexOverall);
    }

    return 0;
}
