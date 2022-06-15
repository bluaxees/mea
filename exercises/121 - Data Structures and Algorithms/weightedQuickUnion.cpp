

#include <iostream>
#include <vector>

typedef unsigned int uint;

class WQUnion {
private:
    std::vector<int> pred_array;
    std::vector<int> setsize;
public:
    WQUnion() {};
    void init(int s);
    bool find(int u, int v);
    void connect(int u, int v);
    void disp();
    int rootnode(int s);
};

void WQUnion::init(int s) {
    for(uint i = 0; i < s; ++i) {
        this->pred_array.emplace_back(i);
        this->setsize.emplace_back(1);
    }
} 

void WQUnion::disp() {
    std::cout << "Nodes: ";
    for(uint i = 0; i < this->pred_array.size(); ++i) {
        std::cout << this->pred_array[i] << ' ';
    }
    std::cout << '\n' << "Size: ";
    for(uint i = 0; i < this->setsize.size(); ++i) {
        std::cout << this->setsize[i] << ' ';
    }
    std::cout << '\n';    
}


int WQUnion::rootnode(int s) {
    while(s != this->pred_array[s]) {
        s  = this->pred_array[s];
    }
    return s;
}

void WQUnion::connect(int u, int v) {
    int node1 = rootnode(u);
    int node2 = rootnode(v);
    if(this->setsize[node1] < this->setsize[node2]) {
        this->pred_array[node1] = this->pred_array[node2];
        this->setsize[node2] += this->setsize[node1];   
    }
    else {
        this->pred_array[node2] = this->pred_array[node1];
        this->setsize[node1] += this->setsize[node2];   
    }
}

bool WQUnion::find(int u, int v) {
    return rootnode(u) == rootnode(v);
}

int main() {
    WQUnion wqu;
    wqu.init(7);
    wqu.disp();
    wqu.connect(1,6);
    wqu.disp();
    wqu.connect(4,3);
    wqu.disp();
    wqu.connect(5,2);
    wqu.disp();
    wqu.connect(3,2);
    wqu.disp();
    wqu.connect(6,2);
    wqu.disp();
}