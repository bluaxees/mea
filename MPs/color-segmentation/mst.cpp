//2018-04736
#include "MP1.h"
  
// Main program
int main(int argc, char *argv[]) {

    if (argc != 5) {
        return 0;
    }
    CImg<uchar> img(argv[1]);
    int k = atoi(argv[2]);
    float T1 = atof(argv[3]);
    float T2 = atof(argv[4]);

    Graph g;
    std::pair<int, int> dimensions = g.imageToGraph(img);
    g.createMST(k, T1, T2);
    g.graphToImage(dimensions.first, dimensions.second, img);

    return 0;
}
