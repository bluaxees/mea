#include <iostream>     // std::cout
#include <algorithm>    // std::max
#include <fstream>      // std::fstream
#include <vector>       // std::vector

int N;
std::vector<int> w, v;

void get_items(std::string inputFile) {
    std::fstream infile(inputFile, std::ios::in);
    int weight, value;
    infile >> N;
    w.emplace_back(0);
    v.emplace_back(0);
    for(uint i = 0; i < N; ++i) {
        infile >> weight >> value;
        w.emplace_back(weight);
        v.emplace_back(value);
    }
}

int memo[6][100] = {{}};

int knapsack(int N, int W) {
    for (int n = 1; n <= N; ++n) {
        for (int x = 0; x <= W; ++x) {
            int ans1 = 0, ans2 = 0;
            // put nth item in KS
            if (x - w[n] >= 0) {
                ans1 = memo[n-1][x-w[n]] + v[n];
            }
            // don't put item in KS
            ans2 = memo[n-1][x];
            memo[n][x] = std::max(ans1, ans2);
        }
    }
    return memo[N][W];
}

int main(int argc, char *argv[]) {
    if(argc == 2) {
        get_items("input.txt");
        int W = atoi(argv[1]);
        std::cout << "Knapsack capacity: " << W << std::endl;
        for(int i = 0; i < w.size(); ++i) {
            std::cout << "item #" << i << " w=" << w[i]  << ", v=" << v[i] << '\n';
        }
        // Insert code here
        std::cout << knapsack(N, W) << '\n';

    }
}