//2018-04736
#include <fstream>
#include "exercise12.h"

// Typical recursive postorder DFS (for connected graph)
void Graph::postorderDFS(int node) {
    // Set current node as visited
    this->visitedNodes[node] = true;
    // For each unvisited neighbor of the current node, apply DFS
    for(uint i = 0; i < this->adjList[node].size(); ++i) {
        if(!visitedNodes[this->adjList[node][i]]) {
            postorderDFS(this->adjList[node][i]);
        }
    }
    std::cout << this->nodeLabels[node] << ' ';    // Process node, e.g. print node label
}

// Typical iterative breadth-first search (BFS)
void Graph::BFS(int node) {
    // Push the starting node onto the queue and mark it as visited
    this->visitedNodes[node] = true;
    std::queue<int> bfs;
    bfs.push(node);
    // While the queue is not empty 
    while (!bfs.empty()) {
        int temp = bfs.front();
        std::cout << this->nodeLabels[temp] << ' ';
        // Pop the front of the queue
        bfs.pop();
        // For each unvisited neighbor of the popped node
        for(uint i = 0; i < this->adjList[temp].size(); ++i) {
            if(!visitedNodes[this->adjList[temp][i]]) {
                // Push node onto queue and mark as visited
                this->visitedNodes[this->adjList[temp][i]] = true;
                bfs.push(this->adjList[temp][i]);
            }
        }
    }   
}

void Graph::shortest(int node, int v) {
    for(uint i = 0; i < this->visitedNodes.size(); ++i) {
        visitedNodes[i] = false;
    }
    if (node == v) {
        std::cout << this->nodeLabels[node] << ' ';
    }
    this->visitedNodes[node] = true;
    std::queue<int> bfs;
    bfs.push(node);
    while (!bfs.empty()) {
        int temp = bfs.front();
        bfs.pop();
        for(uint i = 0; i < this->adjList[temp].size(); ++i) {
            if(!visitedNodes[this->adjList[temp][i]]) {
                this->visitedNodes[this->adjList[temp][i]] = true;
                bfs.push(this->adjList[temp][i]);
                if (this->adjList[temp][i] == v) {
                    std::cout << this->nodeLabels[this->adjList[temp][i]] << ' ';
                    shortest(node, temp);
                }
            }            
        }
    }
}

//single source
void Graph::shortpred(int u, int v) {
    // Push the starting node onto the queue and mark it as visited
    std::vector<int> predecessor;
    for (uint i = 0; i < this->adjList.size(); ++i) {
        predecessor.emplace_back(-1);
    }
    this->visitedNodes[u] = true;
    std::queue<int> bfs;
    bfs.push(u);
    // While the queue is not empty 
    while (!bfs.empty()) {
        int temp = bfs.front();
        //std::cout << this->nodeLabels[temp] << ' ';
        // Pop the front of the queue
        bfs.pop();
        // For each unvisited neighbor of the popped node
        for(uint i = 0; i < this->adjList[temp].size(); ++i) {
            int neighborNode = adjList[temp][i];
            if(!visitedNodes[this->adjList[temp][i]]) {
                // Push node onto queue and mark as visited
                this->visitedNodes[this->adjList[temp][i]] = true;
                bfs.push(this->adjList[temp][i]);
                predecessor[neighborNode] = temp;
            }
        }
    }

    std::stack<int> to_print;
    int node = v;
    to_print.push(node);
    while (predecessor[node] != u) {
        to_print.push(predecessor[node]);
        node = predecessor[node];
    }
    to_print.push(u);

    while(!to_print.empty()) {
        std::cout << this->nodeLabels[to_print.top()] << ' ';
        to_print.pop();
    }
}

void Graph::init(std::string inputFile) {

    int numNodes = 0;
    int numEdges = 0;
    std::fstream fh(inputFile, std::ios_base::in);
    fh >> numNodes >> numEdges;
    for(uint i = 0; i < numNodes; ++i) {
        this->adjList.emplace_back(std::vector<int>{});
        this->visitedNodes.emplace_back(false);
    }
    for(uint i = 0; i < this->adjList.size(); ++i) {
        std::string label  = "";
        fh >> label;
        this->nodeLabels[i] = label;
    }
    int endOne = 0;
    int endTwo = 0;
    int temp = 0;
    int node = 0;
    std::vector<int> nodeList = {};
    bool execute = false;
    bool first = true;

    for(uint i = 0; i < numEdges; ++i) {    
        fh >> endOne >> endTwo;
        if (first) {
            temp = endOne;
            first = false;
        }
        if (endOne != temp) {
            node = temp;
            temp = endOne;
            execute = true;
        }
        else {
            nodeList.push_back(endTwo);
        }
        if (execute) {
            init_manual_helper(node, nodeList);
            nodeList = {};
            nodeList.push_back(endTwo);
            execute = false;
        }
    }
    fh.close();
}

int main() {
    Graph g;
    // g.init_manual();    // Comment out when using g.init() instead

    // Define the init method to read the graph from file instead of manually generating it through the code
    g.init("exercise12.in");

    std::cout << "Preorder DFS from A: \n\t";
    g.clearVisited();
    g.preorderDFS(0);
    std::cout << '\n';

    std::cout << "Postorder DFS from A: \n\t";
    g.clearVisited();
    g.postorderDFS(0);
    std::cout << '\n';

    std::cout << "BFS from A: \n\t";
    g.clearVisited();
    g.BFS(0);
    std::cout << '\n';

    std::cout << "Shortest from A to E: \n\t";
    g.clearVisited();
    g.shortest(5,6);
    std::cout << '\n';

    std::cout << "Shortest from A to E: \n\t";
    g.clearVisited();
    g.shortpred(5,6);
    std::cout << '\n';
}