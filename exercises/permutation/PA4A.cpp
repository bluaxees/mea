#include <iostream>
#include <vector>
#include <fstream>

typedef std::vector<char> vChar; 

// Generates all unique permutations of a string
// using backtracking and stores it in a container
void permuteString(std::string str, vChar &strPerm, std::vector<bool> &inString, std::vector<vChar> &allPerms) {

    // Allocate memory for the 256 ASCII characters
    bool repeated[256] = {false};

    // Base case
    // Current permutation size matches original word size
    if (strPerm.size() == str.size()) {
        allPerms.emplace_back(strPerm);
    }

    else {

        // For every letter in the word
        for (int i = 0; i < str.size(); ++i) {
            if (!inString[i] && !repeated[str[i]]) {
                strPerm.emplace_back(str[i]);
                inString[i] = true;
                permuteString(str, strPerm, inString, allPerms);
                
                // Backtracking step
                strPerm.pop_back();
                inString[i] = false;
                repeated[str[i]] = true;
            }
        }
    }
}

// Helper function 
// Initializes containers for getting string permutations
// Returns a container of all unique permutations
std::vector<vChar> permuteHelper(std::string str) {
    std::vector<vChar> allPerms;
    vChar strPerm {};
    std::vector<bool> inString;
    for (int i = 0; i < str.size(); ++i) {
        inString.emplace_back(false);
    }
    permuteString(str, strPerm, inString, allPerms);
    return allPerms;
}

// Writes generated permutation to a text file
void output(std::vector<vChar> allPerms) {
    std::ofstream outf;
    outf.open("output.txt");
    for (int i = 0; i < allPerms.size(); ++i) {
        for (int j = 0; j < allPerms[i].size(); ++j) {
            outf << allPerms[i][j];
        }
        outf << '\n';
    }
    outf.close();
}

int main(int argc, char *argv[]) {

    // Code block for PA part A 
    if (argc != 2) {
        return 0;
    }
    std::string str = argv[1];
    std::vector<vChar> allPerms = permuteHelper(str);
    output(allPerms);

    return 0;
}