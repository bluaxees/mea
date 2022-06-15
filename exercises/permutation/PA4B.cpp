//2018-04736

#include <iostream>
#include <vector>
#include <fstream>

// Read input file
// Returns the change M and an array of the denominations
std::pair<int, std::vector<int>> readFile(std::string inputFile) {
    std::vector<int> coinsAtHand {};
    std::ifstream inF;
    inF.open(inputFile);
    int numCoins = 0, M = 0;
    inF >> numCoins >> M;
    for (int i = 0; i < numCoins; ++i) {
        int m = 0;
        inF >> m;
        coinsAtHand.emplace_back(m);
    }
    inF.close();
    return std::make_pair(M, coinsAtHand);
}

// Given parameters change M and denominations coinsAtHand
// return the number of combinations that sum up to M
int findCombinations(int M, std::vector<int> coinsAtHand) {

    // Minimum output value is always 1
    std::vector<int> combinations {1};

    // Initialize number of combinations per change M to zero
    for (int i = 0; i < M; ++i) {
        combinations.emplace_back(0);
    }

    // Iterate through every coin value
    for (int i = 0; i < coinsAtHand.size(); ++i) {
        for (int j = 1; j < M+1; ++j) {

            // Recurrence relation, iterate number of combinations
            // if change M is greater than or equal to current coin
            if (j - coinsAtHand[i] >= 0) {
                combinations[j] += combinations[j-coinsAtHand[i]];
            }
        }
    }

    return combinations[M]; 
}

int main() {

    // Code block for Part B
    std::pair<int, std::vector<int>> v = readFile("input.txt");
    int M = v.first;
    std::vector<int> coinsAtHand = v.second;
    std::cout << findCombinations(M, coinsAtHand) << '\n';

    return 0;
}