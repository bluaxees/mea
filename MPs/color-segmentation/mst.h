#include <iostream>
#include <vector> 
#include "CImg.h"

using namespace cimg_library;

typedef unsigned char uchar;

typedef unsigned int uint;

// Edge struct containing values for the
// edge's source, destination and weight
typedef struct pixelEdge {
    int src, des;
    float weight;
} Edge;

// An implementation of Weighted Quick Union DS using disjoint sets
// Has path compression
class disjointSet {
private:
    std::vector<int> predArray;
public:
    std::vector<int> treeSize;
    disjointSet() {};
    disjointSet(int setSize);
    int getRoot(int node);
    void bindNode(int uNode, int vNode);
};

// disjointSet object constructor
// Accepts an int n and initializes arrays predArray and
// treeSize to contain n elements
disjointSet::disjointSet(int setSize) {
    for (uint nodeIndex = 0; nodeIndex < setSize; ++nodeIndex) {
        this->predArray.emplace_back(nodeIndex);
        this->treeSize.emplace_back(1);
    }
}

// Returns predecessor of input node
// Accepts an int n, traverses n's predecessors and
// applies path compression to the visited nodes
int disjointSet::getRoot(int node) {
    if (predArray[node] != node) {
        predArray[node] = getRoot(predArray[node]);
    }
    return predArray[node];
}

// Combines two disjoint sets 
// Size comparison is used to determine new parent
void disjointSet::bindNode(int uNode, int vNode) {
    int uParent = getRoot(uNode);
    int vParent = getRoot(vNode);

    if (this->treeSize[uParent] < this->treeSize[vParent]) {
        this->predArray[uParent] = vParent;
        this->treeSize[vParent] += this->treeSize[uParent];
    }
    else {
        this->predArray[vParent] = uParent;
        this->treeSize[uParent] += this->treeSize[vParent];
    }
}

// Color object containing RGB values
class Color {
public:
    float red, green, blue;
    Color();
    Color(float r, float g, float b);
    void operator=(const Color &c);
    Color operator+(const Color &c);
    Color operator*(const float &i);
    float getHue();
    float getAveRGB(Color c);
    float getWeight(Color c);
};

// Color object constructor (default - initialized to black)
Color::Color() {
    this->red = 0;
    this->green = 0;
    this->blue = 0;
}

// Color object constructor
// Accepts 3 floats (r, g, b) and initializes RGB values base on input
Color::Color(float r, float g, float b) {
    this->red = r;
    this->green = g;
    this->blue = b;
}

// copy operator
void Color::operator=(const Color &c) {
    this->red = c.red;
    this->green = c.green;
    this->blue = c.blue;
}

// Adds RBG values of two Colors respectively
// Returns a Color with the summed RGB values
Color Color::operator+(const Color &c) {
    Color out;
    out.red = this->red + c.red;
    out.green = this->green + c.green;
    out.blue = this->blue + c.blue;
    return out;
}

// Divides each RGB value of a Color by input n
// Returns a Color object with the divided RGB values
Color Color::operator*(const float &i) {
    Color out;
    out.red = this->red * i;
    out.green = this->green * i;
    out.blue = this->blue * i;
    return out;
}

// Returns hue (value) of a Color
float Color::getHue() {
    float min = std::min(std::min(this->red, this->green), this->blue);
    float max = std::max(std::max(this->red, this->green), this->blue);

    if (min == max) {
        return 0;
    }

    float hue = 0;

    if (max == this->red) {
        hue = (60*(this->green - this->blue))/(max - min);
    }
    if (max == this->green) {
        hue = (60*(this->blue - this->red))/(max - min) + 120;
    }
    if (max == this->blue) {
        hue = (60*(this->red - this->green))/(max - min) + 240;
    }
    if (hue < 0) {
        hue += 360;
    }

    return hue;
}

// Returns the average RGB values between two Colors
float Color::getAveRGB(Color c) {
    float rgbDiff = (std::abs(this->red - c.red) + std::abs(this->green - c.green) + std::abs(this->blue - c.blue))/3;
    return rgbDiff;
}

// Returns the weight between two colors
// Formula is based on specification document
float Color::getWeight(Color c) {
    float hueDiff = std::abs(getHue() - c.getHue());
    if (hueDiff > 180) {
        hueDiff = 360 - hueDiff;
    }
    float rgbDiff = getAveRGB(c);

    float weight = (hueDiff + 1)*rgbDiff;
    return weight;
}

// Representation of a graph using adjacency list
class Graph {
private:
    std::vector<std::vector<Edge>> adjList; // adjacency list containing edges
    std::vector<Color> pixelList; // list of the vertices
public:
    Graph() {};
    std::pair<int, int> imageToGraph(CImg<uchar> inputImage);
    void graphToImage(int cols, int rows, CImg<uchar> inputImage);
    void createMST(int k, float T1, float T2);
    void display(int cols) {
        for (uint i = 0; i < adjList.size(); ++i) {
            std::cout << adjList[i].size() << " ";
            if ((i+1) % cols == 0) {
                std::cout << '\n';
            }
        }
    }
};

// Converts image to Graph object
// Returns the dimensions of the inputImage
std::pair<int, int> Graph::imageToGraph(CImg<uchar> inputImage) {

    int rows = inputImage.height();
    int cols = inputImage.width();

    // Initialize the nodes of the adjacency list
    for (uint nodeIndex = 0; nodeIndex < rows*cols; ++nodeIndex) {
        this->adjList.emplace_back(std::vector<Edge> {});
    }

    // Read the image pixel by pixel, from left to right downwards
    // Place the pixels inside the array pixelList
    for(uint rowIndex = 0; rowIndex < rows; ++rowIndex) {
        for(uint colIndex = 0; colIndex < cols; ++colIndex) {
            float r = inputImage(colIndex, rowIndex, 0);
            float g = inputImage(colIndex, rowIndex, 1);
            float b = inputImage(colIndex, rowIndex, 2);
            Color pixel = {r, g, b};
            this->pixelList.emplace_back(pixel);
        }
    }

    // Read the image pixel by pixel, from left to right downwards
    int pixelCount = 0;
    for(uint rowIndex = 0; rowIndex < rows; ++rowIndex) {
        for(uint colIndex = 0; colIndex < cols; ++colIndex) {
            // Set each pixel as the vertex v
            // Visit v's neighbors (nodes exactly a pixel away) and get weight between
            // the nodes then place Edge object inside the array adjList
            if (colIndex != 0) {
                float weight = this->pixelList[pixelCount].getWeight(this->pixelList[pixelCount-1]);
                Edge curEdge = {pixelCount, pixelCount-1, weight};
                this->adjList[pixelCount].emplace_back(curEdge);   
            }
            if (colIndex != (cols - 1)) {
                float weight = this->pixelList[pixelCount].getWeight(this->pixelList[pixelCount+1]);
                Edge curEdge = {pixelCount, pixelCount+1, weight};
                this->adjList[pixelCount].emplace_back(curEdge);
            }
            if (rowIndex != 0) {
                float weight = this->pixelList[pixelCount].getWeight(this->pixelList[pixelCount-cols]);
                Edge curEdge = {pixelCount, pixelCount-cols, weight};
                this->adjList[pixelCount].emplace_back(curEdge);
            }
            if (rowIndex != (rows-1)) {
                float weight = this->pixelList[pixelCount].getWeight(this->pixelList[pixelCount+cols]);
                Edge curEdge = {pixelCount, pixelCount+cols, weight};
                this->adjList[pixelCount].emplace_back(curEdge);
            }
            ++pixelCount;
        }
    }

    std::cout << "Image converted to graph.\n";
    return std::make_pair(cols, rows);
}

// Converts Graph object to an CImg object and saves it in png format
void Graph::graphToImage(int cols, int rows, CImg<uchar> inputImage) {

    int pixelCount = 0;
    CImg<uchar> copyImage(inputImage);

    // Visit every node of the graph and recolor the image object
    for(uint rowIndex = 0; rowIndex < rows; ++rowIndex) {
        for(uint colIndex = 0; colIndex < cols; ++colIndex) {
            copyImage(colIndex, rowIndex, 0) = pixelList[pixelCount].red;
            copyImage(colIndex, rowIndex, 1) = pixelList[pixelCount].green;
            copyImage(colIndex, rowIndex, 2) = pixelList[pixelCount].blue;
            ++pixelCount;
        }
    }

    copyImage.save_png("output.png");
    std::cout << "Graph back to image format.\n";
}

// MST algorithm that transforms the graph into
// a pseudoMST with at least k component trees
void Graph::createMST(int k, float T1, float T2) {

    int comTrees = this->adjList.size();
    int pixelCount = comTrees;
    std::vector<std::vector<Edge>> copy_adjList = this->adjList;
    disjointSet dSet = comTrees;

    std::vector<Edge> shortestEdges {};
    Edge e = {0, 0, -1};
    for (int i = 0; i < comTrees; ++i) {
        shortestEdges.emplace_back(e);
    }

    std::cout << "MST prelims initialized. Entering loop.\n";

    // While there are more than k component trees
    while (comTrees > k) {

        // Determines if there there is no decrease on
        // the component trees' count
        bool treeDecrease = false;

        // Find the minimum-weight edge connecting current component to another component
        for (int i = 0; i < pixelCount; ++i) {
            for (int j = 0; j < this->adjList[i].size(); ++j) {
                int m = dSet.getRoot(i);
                int n = dSet.getRoot(adjList[i][j].des);

                if (m == n) {
                    continue;
                }

                if (shortestEdges[m].weight == -1 || adjList[i][j].weight < shortestEdges[m].weight) {
                    Edge curEdge = {i, j, adjList[i][j].weight};
                    shortestEdges[m] = curEdge;
                }
                
                if (shortestEdges[n].weight == -1 || adjList[i][j].weight < shortestEdges[n].weight) {
                    Edge curEdge = {i, j, adjList[i][j].weight};
                    shortestEdges[n] = curEdge;
                }
            }
        }

        for (int i = 0; i < pixelCount; ++i) {

            // Handles case when there is no minimum-weight edge found 
            if (shortestEdges[i].weight == -1) {
                continue;
            }

            // Handles the case where both nodes of the edge
            // are part non distinct component trees
            Edge curEdge = this->adjList[shortestEdges[i].src][shortestEdges[i].des];
            int m = dSet.getRoot(curEdge.src);
            int n = dSet.getRoot(curEdge.des);
            if (m == n) {
                continue;
            }

            // Component trees may only be merge if the 
            // minimum-weight edge between them is less than T1 and
            // the averRGB component difference of the two pixels is less than T2
            float minCrossingEdge = curEdge.weight;
            float aveRGB = this->pixelList[curEdge.src].getAveRGB(this->pixelList[curEdge.des]);
            if (minCrossingEdge >= T1 || aveRGB >= T2) {
                continue;
            }

            if (true) {
                
                // Recolor the component trees' root before combining
                Color treeColor = ((this->pixelList[m]*dSet.treeSize[m]) + (this->pixelList[n]*dSet.treeSize[n]));
                float treeCount = (dSet.treeSize[m] + dSet.treeSize[n]);
                treeColor = treeColor*(1/treeCount);
                this->pixelList[m] = treeColor;
                this->pixelList[n] = treeColor;

                // Combine the two component trees
                dSet.bindNode(m, n);
                --comTrees;
                treeDecrease = true;
            }
            
        }

        // Reset shortestEdges array
        // Change color of every node to the color of its parent
        for (uint i = 0; i < pixelCount; ++i) {
            shortestEdges[i] = e;
            int r = dSet.getRoot(i);
            this->pixelList[i] = this->pixelList[r];
        }

        // Update edges that are not part of the MST
        for (uint i = 0; i < this->adjList.size(); ++i) {
            for (uint j = 0; j < this->adjList[i].size(); ++j) {
                Edge curEdge = this->adjList[i][j];
                int m = dSet.getRoot(curEdge.src);
                int n = dSet.getRoot(curEdge.des);
                if (m != n) {
                    if (pixelList[m].getAveRGB(pixelList[n])==0) {
                        continue;
                    }
                    float originalWeight = copy_adjList[i][j].weight;
                    this->adjList[i][j].weight = originalWeight*(this->pixelList[m].getWeight(this->pixelList[n]));
                }
            }
        }

        if (!treeDecrease) {
            break;
        }

        std::cout << "Component tree count: " << comTrees << '\n';

    }

    std::cout << "Pseudo MST created.\n";
}

