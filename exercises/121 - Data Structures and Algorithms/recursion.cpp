// combinatorial search
// recursive backtracking

#include <iostream>
#include <vector>

// helper function
void generateBinary(int N, std::string bits) {
    if (N == 0) {
        std::cout << bits << '\n';
    }
    // Choose
    // Recurse
    // Deselect
    else {
        generateBinary(N - 1, bits + "0");
        generateBinary(N - 1, bits + "1");
    }
}

// actual funtion for problem
void generateBinary(int N) {
    generateBinary(N, "");
}

// helper function
void generateBinary2(int N, int k, std::string bits) {
    if (N == 0 && k == 0) {
        std::cout << bits << '\n';
    }
    // Choose
    // Recurse
    // Deselect
    else {
        if (N > k) {
            generateBinary2(N - 1, k, bits + "0");
        }
        if (k >= 0) {
        generateBinary2(N - 1, k-1, bits + "1");
        }
    }
}

// actual funtion for problem
void generateBinary2(int N, int k) {
    generateBinary2(N, k, "");
}

void displayRolls(std::vector<int> diceRolls) {
    for (int i = 0; i < diceRolls.size(); ++i) {
        std::cout << diceRolls[i] << ' ';
    }
    std::cout << '\n';
}

void rolldDice(int N, int S, int curSum, std::vector<int> &diceRolls) {
    if (curSum == S && N == 0) {
        displayRolls(diceRolls);
    }
    else if (curSum < S) {
        for (int choice = 1; choice <= 6; ++choice) {
            if (curSum + choice + 6*(N-1) >= S && curSum + choice + 1*(N-1) <= S) {
                diceRolls.emplace_back(choice);
                rolldDice(N - 1, S, curSum + choice, diceRolls);
                diceRolls.pop_back();
            }
        }
    }
}

void rolldDice(int N, int S) {
    std::vector<int> diceRolls;
    rolldDice(N, S, 0, diceRolls);
}



int main(int argc, char *argv[]) {
    if (argc == 2) {
        //int N = atoi(argv[1]);
        //std::cout << N << '\n';
        //generateBinary(N);
    }
    if (argc == 3) {
        //int N = atoi(argv[1]);
        //int k = atoi(argv[2]);
        //std::cout << N  << " , " << k <<'\n';
        //generateBinary2(N, k);
    }
    if (argc == 3) {
        //int N = atoi(argv[1]);
        //int S = atoi(argv[2]);
        //std::cout << N  << " , " << S <<'\n';
        //rolldDice(N, S);
    }
    if (argc == 2) {
        std::string input = argv[1];
    }
    return 0;
}