#include <iostream>     // std::cout
#include <algorithm>    // std::max
#include <fstream>      // std::fstream
#include <vector>       // std::vector

int N;
std::vector<int> S;

void get_items(std::string inputFile) {
    std::fstream infile(inputFile, std::ios::in);
    int element;
    infile >> N;
    for(uint i = 0; i < N; ++i) {
        infile >> element;
        S.emplace_back(element);
    }
}

int L[20] = {};

int LIS(int N) {
    L[0] = 1;
    for (int n = 1; n < N; ++n) {
        int ans = 1;
        for (int i = 0; i < n; ++i) {
            if (S[n] >= S[i]) {
                ans = std::max(ans, L[i] + 1);
            }
        }
        L[n] = ans;
    }
    return 0;
}

int main() {
    get_items("input.txt");

    std::cout << LIS(N) << '\n';
    for(int i = 0; i < S.size(); ++i) {
        std::cout << "item #" << i << " L=" << L[i] << '\n';
    }
    // Insert code here
}