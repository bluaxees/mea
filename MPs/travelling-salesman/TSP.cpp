//2018-04736

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

// Representation of a point in the Cartesian plane
class Coordinate {
public:

    // The x and y coordinates are public members
    float x;
    float y;

    // Constructors for Coordinate objects
    // May take two floats as parameters
    // Sets coordinate as origin if no parameters are passed
    Coordinate() {
        this->x = 0;
        this->y = 0;
    };
    Coordinate(float x, float y) {
        this->x = x;
        this->y = y;
    };

    // Method for computing Euclidian distance between two coordinates
    // Returns a float
    float getDist(Coordinate c){
        float xDist = this->x - c.x;
        float yDist = this->y - c.y;
        return sqrt(pow(xDist, 2) + pow(yDist,2));
    };
};

// Adjacency matrix representation of a graph
class graphMatrix {
public:
    
    // The adjacency matrix may be accessed outside of the class
    std::vector<std::vector<float>> adjMatrix;

    // Constructor of graphMatrix object
    // Takes a list of Coordinate objects as parameter
    // and creates a complete graph
    graphMatrix() {};
    graphMatrix(std::vector<Coordinate> destList) {
        for (uint i = 0; i < destList.size(); ++i) {
            std::vector<float> emptyVec {};
            adjMatrix.emplace_back(emptyVec);
            for (uint j = 0; j < destList.size(); ++j) {
                float distance = destList[i].getDist(destList[j]);
                adjMatrix[i].emplace_back(distance);
            }
        }
    };
};

// Bottom up implementation of the Held-Karp algorithm using bitmasking
// Returns starting and ending point of the path with minimum distance,
// as well as the minimum path distance
std::pair<float, std::pair<int, int>> doPseudoTSP(std::vector<std::vector<float>> _adjMatrix, float H) {

    // Use long int (64 bits) since there are 
    // at most 50 delivery locations
    long int numSet = pow(2, _adjMatrix.size());

    // Initialize a 2^numNodes by numNodes array to store
    // the minimum path distance between the subset and the node
    std::vector<std::vector<float>> minDistances {};
    for (int i = 0; i < numSet; ++i) {
        std::vector<float> emptyVecF {};
        minDistances.emplace_back(emptyVecF);
        for (int j = 0; j < _adjMatrix.size(); ++j) {
            minDistances[i].emplace_back(-1);
        }
    }

    // Base case, only the starting node has been visited
    for (int i = 0; i < _adjMatrix.size(); i++) {
        int x = pow(2,i);
        minDistances[x][i] = 0;
    }

    // Iterate through every subset-node pairings
    // Subsets must not be empty
    for (int curSet = 1; curSet < numSet; ++curSet) {
        for (int curNode = 0; curNode < _adjMatrix.size(); ++curNode) {

            // curNode is already visited (i.e. in curSet)
            if (!(curSet && 1 << curNode)) {
                continue;
            }

            // Base case, no need to iterate
            if (curSet == 1 << curNode) {
                continue;
            }

            // Iterate through every node n in the subset
            for (int prevNode = 0; prevNode < _adjMatrix.size(); ++prevNode) {

                // Remove node n from the subset
                int prevSet = curSet ^ (1 << prevNode);

                // Determine the cheaper subpath between the subset and node n
                float a = minDistances[curSet][prevNode];
                float b = minDistances[prevSet][curNode] + _adjMatrix[curNode][prevNode];
                if (a == -1) {
                    if (minDistances[prevSet][curNode] == -1) {
                        minDistances[curSet][prevNode] = -1;
                    }
                    else {
                        minDistances[curSet][prevNode] = b;
                    }
                }
                else {
                    if (minDistances[prevSet][curNode] == -1) {
                        minDistances[curSet][prevNode] = a;
                    }
                    else {
                        minDistances[curSet][prevNode] = (a < b) ? a:b;
                        }
                }
            }
        }  
    }

    // Determine the minimum path distance
    // and the path's source
    float minPathDistance = -1;
    int tempIndex = 0;
    int srcNode = 0;

    // Iterate only through the sets where all nodes
    // are visited (i.e. minDistances' last row)
    for (int i = 0; i < _adjMatrix.size(); i++) {
        float a = minPathDistance;
        float b = minDistances[numSet - 1][i];
        float tempDist = (a < b) ? a:b;
        tempIndex = (a < b) ? tempIndex:i;
        minPathDistance = (a == -1) ? b:tempDist;
        srcNode = (a == -1) ? i:tempIndex;
    }

    // Determine the destination node by searching a
    // path with equivalent minimum path distance but
    // different source node
    int destNode = 0;
    for (int i = 0; i < _adjMatrix.size(); ++i) {

        // Compare up to three decimal places only to
        // avoid errors in floating points
        if (floorf(minDistances[numSet-1][i]*1000)/1000 == floorf(minPathDistance*1000)/1000) {
            if (i == srcNode) {
                continue;
            }
            destNode = i;
        }
    }

    // Process return value
    minPathDistance += 2*H*(_adjMatrix.size()-1);
    std::pair<int, int> endPoints = std::make_pair(srcNode, destNode);
    return (std::make_pair(minPathDistance, endPoints));
}

// Reads input file and converts it to a graph
// Held-Karp's algorithm is performed on the graph
// The output is written to a separate file
void ioFile(std::string fileName) {

    // Some initializations
    int numTest = 0;
    std::fstream inFile(fileName, std::ios_base::in);
    std::ofstream outFile;
    outFile.open("output.txt");
    inFile >> numTest;
    int N = 0;
    float H = 0;
    
    // Iterate through every test cases
    for (uint i = 0; i < numTest; ++i) {
        inFile >> N >> H;

        // Create a list of package destinations
        std::vector<Coordinate> destList {};
        for (uint j = 0; j < N; ++j) {
            float x = 0, y = 0;
            inFile >> x >> y;
            Coordinate cc {x, y};
            destList.emplace_back(cc);
        }

        // Construct an adjacency matrix using the coordinate list
        graphMatrix M {destList};
        std::vector<std::vector<float>> _adjMatrix = M.adjMatrix;

        // Perform Held-Karp's algorithm to the graph M
        std::pair<float, std::pair<int, int>> outHeldKarp = doPseudoTSP(_adjMatrix, H);

        // Write to output file
        outFile << round(outHeldKarp.first) << '\n';
        std::pair<int, int> destIndex = outHeldKarp.second;
        outFile << destList[destIndex.first].x << ' ' << destList[destIndex.first].y << ' ';
        outFile << destList[destIndex.second].x << ' ' << destList[destIndex.second].y << '\n';
    }

    // Close both files
    inFile.close();
    outFile.close();
}

int main() {
    ioFile("input.txt");
    return 0;
}