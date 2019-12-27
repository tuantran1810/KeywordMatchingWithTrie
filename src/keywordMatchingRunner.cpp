#include <iostream>
#include "keywordMatcher.h"
using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "invalid input!" << std::endl;
        return 0;
    }

    std::string inputFileName(argv[1]);

    KeywordMatcher matcher = KeywordMatcher("../data/keywordTable.txt");
    auto& dataloader = DataLoader::GetInstance();
    dataloader(inputFileName);
    dataloader.AcquireDataAll([&](const std::string& matchingStr) {
        std::cout << "Input string: " << matchingStr << std::endl;
        matcher.FindKeywords(matchingStr);
    });

    return 0;
}
