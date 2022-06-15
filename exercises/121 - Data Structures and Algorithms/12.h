#include <iostream>        // std::cout
#include <vector>          // std::vector for array container
#include <queue>           // BFS
#include <unordered_map>   // node int key to string label hash table
#include <stack>

typedef unsigned int uint;

// A class containing an implementation of a graph using 
// adjacency list representation with methods for standard traversal
class Graph {
private:
    std::vector<std::vector<int>> adjList;
    std::unordered_map<int,std::string> nodeLabels;
    std::vector<bool> visitedNodes;
    void init_manual_helper(int node, std::vector<int> nodeList);
public:
    Graph() {};
    void init_manual();
    void init(std::string inputFile);
    void clearVisited();
    void preorderDFS(int node);
    void postorderDFS(int node);
    void BFS(int node);
    void shortest(int u, int v);
    void shortpred(int u, int v);
    void toposort_recur(int current, std::queue<int> &q);
    void toposort();
};


// Initializes a node with a vector of its adjacent node IDs
void Graph::init_manual_helper(int node, std::vector<int> nodeList) {
    for(uint i = 0; i < nodeList.size(); ++i) {
        this->adjList[node].emplace_back(nodeList[i]);
    }
}


// Generate the graph manually (not recommended in actual applications)
void Graph::init_manual() {

    // Create a graph with 8 vertices/nodes
    int numNodes = 8;
    for(uint i = 0; i < numNodes; ++i) {
        this->adjList.emplace_back(std::vector<int>{});
        this->visitedNodes.emplace_back(false);
    }

    // Sets the labels to uppercase characters:
    //      0:A, 1:B, 2:C, and so on...
    for(uint i = 0; i < this->adjList.size(); ++i) {
        this->nodeLabels[i] = std::string(1, i+'A');
    }

    init_manual_helper(0, {1, 2, 4});        // A is connected to B, C, E
    init_manual_helper(1, {0, 2, 3});        // B is connected to A, C, D
    init_manual_helper(2, {0, 1, 3, 5});     // C is connected to A, B, D, F
    init_manual_helper(3, {1, 2});           // D is connected to B, C
    init_manual_helper(4, {0, 6, 7});        // E is connected to A, G, H
    init_manual_helper(5, {2});              // F is connected to C
    init_manual_helper(6, {4, 7});           // G is connected to E, H
    init_manual_helper(7, {4, 6});           // H is connected to E, G
}


// Clears visited nodes member
void Graph::clearVisited() {
    for(uint i = 0; i < this->visitedNodes.size(); ++i) {
        visitedNodes[i] = false;
    }
}


// Typical recursive preorder depth-first search (DFS)
void Graph::preorderDFS(int node) {
    std::stack<int> dfs;
    dfs.push(node);
    while (!dfs.empty()) {
        int temp = dfs.top();
        if (!this->visitedNodes[temp]) {
        std::cout << this->nodeLabels[temp] << ' ';}
        this->visitedNodes[temp] = true;
        bool execute = false;
        int i = 0;
        while (true) {
            if(i == this->adjList[temp].size()) {
                execute = true;
                break;
            }
            if(!visitedNodes[this->adjList[temp][i]]) {
                dfs.push(this->adjList[temp][i]);
                break;
            }
            i++;            
        }
        if (execute) {
            dfs.pop();
        }
    }
}

