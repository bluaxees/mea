//2018-04736

#include <iostream>        // std::cout
#include <fstream>         // file IO
#include <vector>          // std::vector for array container
#include <queue>           // priority queue
#include <stack>           // proper sorting of path
#include <algorithm>       // std::sort

typedef unsigned int uint;
typedef std::pair<int,int> pint;

// Sorting convinience for the potentialShortest paths
bool prio_sort(std::pair<std::vector<pint>, uint> i, std::pair<std::vector<pint>, uint> j) {
    return (i.second < j.second);
}

// A class containing an implementation of a graph using 
// adjacency list representation with methods for standard traversal
class Graph {
private:
    std::vector<std::vector<pint>> adjList; // adjacency list of edges and edge weight
    std::vector<int> predArray;             // predecessor array
    std::vector<int> distArray;             // shortest distance of node from source
    void init_helper(int node, std::vector<pint> nodeList);
    int distance_helper(int curNode, int nexNode);
    void clearVisited();
public:
    Graph() {};
    pint init(std::string inputFile);
    void disconnect(std::vector<std::vector<pint>> edgeList);
    std::pair<std::vector<pint>, uint> dijkistra(int srcNode, int desNode, bool isOut, bool isFirst);
    void yen(int srcNode, int desNode);
    void output(std::pair<std::stack<int>, uint> shorter_nodePath);
};

// Initializes a node with a vector of its adjacent node IDs + distances
void Graph::init_helper(int node, std::vector<pint> nodeList) {
    for(uint i = 0; i < nodeList.size(); ++i) {
        this->adjList[node].emplace_back(nodeList[i]);
    }
}

// Returns nexNode's index in curNode's adjList
int Graph::distance_helper(int curNode, int nexNode) {
    int out = 0;
    for (out = 0; out < this->adjList[curNode].size(); ++out) {
        if (this->adjList[curNode][out].second == nexNode) {
            break;
        }
    }
    return out;
}

// Restores original state of predArray and distArray
void Graph::clearVisited() {
    for(uint i = 0; i < this->adjList.size(); ++i) {
        predArray[i] = -1;
        distArray[i] = 10000001;
    }
}

// Removes edgeList from the graph
void Graph::disconnect(std::vector<std::vector<pint>> edgeList) {
    for (uint i = 0; i < edgeList.size(); ++i) {
        for (uint j = 0; j < edgeList[i].size(); ++j) {
            int k = distance_helper(edgeList[i][j].first, edgeList[i][j].second);
            this->adjList[edgeList[i][j].first][k].first = 10000001;
        }
    }
}

// Reads inputFile and creates a Graph object
// Returns a pair <source node, destination node>
pint Graph::init(std::string inputFile) {
    int numNodes = 0;
    int numEdges = 0;
    int u = 0;
    int v = 0;
    std::fstream fh(inputFile, std::ios_base::in);
    fh >> numNodes >> numEdges >> u >> v;
    for(uint i = 0; i < numNodes; ++i) {
        this->adjList.emplace_back(std::vector<pint> {});
        this->predArray.emplace_back(-1);
        this->distArray.emplace_back(10000001);
    }
    int src = 0;
    int dest = 0;
    int dist = 0;
    int temp = 0;
    std::vector<pint> nodeList = {};
    fh >> src >> dest >> dist;
    temp = src;
    for (uint i = 0; i < numEdges; ++i) {    
        if (src == temp) {
            nodeList.emplace_back(std::make_pair(dist, dest));
        }
        else {
            init_helper(temp, nodeList);
            nodeList = {};
            nodeList.emplace_back(std::make_pair(dist, dest));
            temp = src;
        }
        if (i == numEdges - 1) {
            init_helper(temp, nodeList);
            break;
        }
        fh >> src >> dest >> dist;
    }
    fh.close();
    return std::make_pair(u, v);
}

// Implementation of Dijkistra's algorithm
// Returns edgeList and length of shortestPath
std::pair<std::vector<pint>, uint> Graph::dijkistra(int srcNode, int desNode, bool isOut, bool isFirst) {
    std::pair<std::vector<pint>, uint> out;

    // Note that this implementation of pq may contain duplicate nodes
    // Loop iteration works due to distance_helper
    std::priority_queue <pint, std::vector<pint>, std::greater<pint>> pq;

    // Initialize all nodes with no ancestors and has distance MAX from srcNode
    // srcNode has zero distance from itself
    // Worst case, MAX is 10000*1000 + 1
    clearVisited();
    this->distArray[srcNode] = 0;

    // Push srcNode to priority queue, continue until queue is not empty
    pq.push(std::make_pair(0, srcNode));
    while (!pq.empty()) {

        // Initialize topmost element as curNode
        // Remove it from the queue
        int curNode = pq.top().second;
        pq.pop();

        // For every neighbor of curNode
        for(uint i = 0; i < this->adjList[curNode].size(); ++i) {
            int adjNode = this->adjList[curNode][i].second;
            int cur_adjDist = this->adjList[curNode][distance_helper(curNode, adjNode)].first;

            // if d[y] > d[x] + w(x,y)
            if (this->distArray[adjNode] > this->distArray[curNode] + cur_adjDist) {
                // Update predArray and distArray
                this->distArray[adjNode] = this->distArray[curNode] + cur_adjDist;
                this->predArray[adjNode] = curNode;
                // Push neighbor node to queue
                pq.push(std::make_pair(this->distArray[adjNode], adjNode));
            }
        }
    }

    // Processing result into a stack nodeList
    std::stack<int> revPath;
    int curNode = desNode;
    bool noPath = false;
    revPath.push(curNode);
    while (this->predArray[curNode] != srcNode) {
        revPath.push(this->predArray[curNode]);
        curNode = this->predArray[curNode];
        if (curNode == -1) {
            noPath = true;
            break;
        }
    }
    revPath.push(srcNode);
    std::stack<int> shortest_nodePath;
    int shortestDistance = this->distArray[desNode];
    if (noPath) {
        shortestDistance = -1;
        shortest_nodePath.push(desNode);
        shortest_nodePath.push(-1);
    }
    else {
        shortest_nodePath = revPath;
    }

    // Writes output to a text file
    if (isOut) {
        output(std::make_pair(shortest_nodePath, shortestDistance));
        return out;
    }

    // Processing result into an array edgeList
    std::vector<pint> shortest_edgePath;
    int temp = shortest_nodePath.top();
    int copyTemp = temp;
    shortest_nodePath.pop();
    if (isFirst) {
        std::cout << "First shortest path is:\n";
    }
    while(!shortest_nodePath.empty()) {
        if (isFirst) {
            std::cout << temp << ' ';
        }
        shortest_edgePath.emplace_back(std::make_pair(temp, shortest_nodePath.top()));
        temp = shortest_nodePath.top();
        shortest_nodePath.pop();
    }
    if (isFirst) {
        if (copyTemp != -1) {
            std::cout << desNode;
        }
        std::cout << "\nIt has length " << shortestDistance << '\n';
    }
    out = std::make_pair(shortest_edgePath, shortestDistance);
    return out;
}

// Modified implementation of Yen's k Shortest Path algorithm
// Finds the shortest path in a graph when all edges from
// shortest path is removed
void Graph::yen(int srcNode, int desNode) {

    // Find first shortest path using dijkistra
    std::pair<std::vector<pint>, uint> firstShortest = dijkistra(srcNode, desNode, false, true);

    // List of shortest paths and potential shortest paths
    std::vector<std::vector<pint>> allShortest {};
    std::vector<std::pair<std::vector<pint>, uint>> potentialShortest {};
    allShortest.emplace_back(firstShortest.first);

    std::vector<std::vector<pint>> copy_adjList = this->adjList;    
    uint shortestDistance = firstShortest.second;
    uint rootDistance = 0;
    int numShortest = 1;

    // Handles the case when no shortest path exists
    if (allShortest[0][0].first == -1) {
        dijkistra(srcNode, desNode, true, false);
        return;
    }

    // Iterate until all shortest paths are found
    while (firstShortest.second == shortestDistance) {

        // For every node in the kth shortest path
        for (uint i = 0; i < allShortest[numShortest-1].size(); ++i) {

            // Initialize current node as spurNode
            int spurNode = allShortest[numShortest-1][i].first;

            // Initialize rootPath as the edges (in the current shortest path)
            // connecting srcNode to spurNode
            std::vector<pint> copyShortest = allShortest[numShortest-1];
            copyShortest.resize(i);
            std::vector<pint> rootPath = copyShortest;
            rootDistance = 0;

            // Remove every node in rootPath except spurNode
            for (uint j = 0; j < rootPath.size(); ++j) {
                rootDistance += this->adjList[rootPath[j].first][distance_helper(rootPath[j].first, rootPath[j].second)].first;
                std::vector<pint> noAdjacent {};
                this->adjList[rootPath[j].first] = noAdjacent;
            }

            // For every path p in allShortest
            for (uint k = 0; k < allShortest.size(); ++k) {
                std::vector<pint> copy_kShortest = allShortest[k];
                copy_kShortest.resize(i);

                // If rootPath is a subset of p
                // Remove the edge in p that has spurNode as starting node
                if (rootPath == copy_kShortest) {
                    int indShortest = distance_helper(allShortest[k][i].first, allShortest[k][i].second);
                    this->adjList[allShortest[k][i].first][indShortest].first = 10000001;
                }
            }

            // Find shortest path from spurNode to desNode
            // with some nodes and edges removed
            std::pair<std::vector<pint>, uint> spurPath = dijkistra(spurNode, desNode, false, false);
            int noPath = spurPath.first[0].first;
            
            // Combine rootPath and spurPath
            rootPath.insert(rootPath.end(), spurPath.first.begin(), spurPath.first.end());
            spurPath.first = rootPath;
            spurPath.second += rootDistance;

            // Restore the edges and nodes removed
            this->adjList = copy_adjList;
            
            // Append combined paths to potentialShortest list if the path exists
            if (noPath == -1) {
                continue;
            }
            potentialShortest.emplace_back(spurPath);
        }
        
        // Handles case when all spurNodes have been exhausted
        // or there is no more shortest path
        if (potentialShortest.empty()) {
            break;
        }

        // Sort the potentialShortest paths by distance
        // Append first element to allShortest list,
        // if its distance from srcNode is equal to paths in allShortest,
        // else iteration will end
        std::sort(potentialShortest.begin(), potentialShortest.end(), prio_sort);
        if (shortestDistance == potentialShortest[0].second) {
            allShortest.emplace_back(potentialShortest[0].first);
            potentialShortest.erase(potentialShortest.begin());
        }
        shortestDistance = potentialShortest[0].second;
        ++numShortest;
    }

    // [BONUS]
    std::pair<std::vector<pint>, uint> bonusShortest {};
    this->adjList = copy_adjList;
    std::vector<std::vector<pint>> copy_allShortest = allShortest;
    bool hasPath = false;

    // For each edge e in allShortest paths
    // Remove all edges in allShortest except e
    for (uint i = 0; i < allShortest.size(); ++i) {
        for (uint j = 0; j < allShortest[i].size(); ++j) {
            int k = distance_helper(allShortest[i][j].first, allShortest[i][j].second);
            int edgeWeight = this->adjList[allShortest[i][j].first][k].first;
            std::cout << "Edge added: " << allShortest[i][j].first << " , " << allShortest[i][j].second << '\n';
            allShortest[i].erase(allShortest[i].begin() + j);
            disconnect(allShortest);
            allShortest = copy_allShortest;
            bonusShortest = dijkistra(srcNode, desNode, false, false);

            // Continue iteration if there is no path
            // or the edge restored is more than 20% of new valid route
            if (bonusShortest.second == -1 || 5*edgeWeight >= bonusShortest.second) {
                this->adjList = copy_adjList;
                continue;
            }
            else {
                hasPath = true;
                break;
            }
        }

        // Process output when valid route is found
        if (hasPath) {
            std::cout << "A path is found using bonus algorithm.\n";
            dijkistra(srcNode, desNode, false, true);
            return;
        }
    }

    this->adjList = copy_adjList;
    disconnect(copy_allShortest);

    // No valid path is found even with an edge restored
    // Try original algorithm
    std::cout << "No valid path is found using bonus algorithm.\nNow using original algorithm.\n";
    dijkistra(srcNode, desNode, true, false);

}

// Writes to an output file output.txt
void Graph::output(std::pair<std::stack<int>, uint> shorter_nodePath) {
    std::ofstream outFile;
    outFile.open("output.txt");
    int shorterDistance = shorter_nodePath.second;
    if (shorter_nodePath.second >= 10000001) {
        shorterDistance = -1;
    }
    outFile << shorterDistance << '\n';
    while (!shorter_nodePath.first.empty()) {
        int curNode = shorter_nodePath.first.top();
        outFile << curNode << ' ';
        shorter_nodePath.first.pop();
        if (curNode == -1) {
            break;
        }
    }
    outFile.close();
}

int main() {
    Graph g;
    pint path = g.init("input.txt");
    g.yen(path.first, path.second);
}