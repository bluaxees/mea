#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

typedef unsigned int uint;

template <typename T>
class BinaryHeap {
private:
    std::vector<T> heap;
    uint size;
    // Helper methods
    uint left_child(uint node_index) {return 2*node_index; };
    uint right_child(uint node_index) {return 2*node_index+1; };
    uint parent(uint node_index) {return node_index/2; };
    bool in_heap(uint node_index) {return node_index > 0 and node_index<=this->size; };
    bool has_left_child(uint node_index) { return in_heap(left_child(node_index)); };
    bool has_right_child(uint node_index) { return in_heap(right_child(node_index)); };
public:
    BinaryHeap();
    BinaryHeap(std::vector<T> array);
    void insert(T key);
    T extract();    
    void display();
};

template <typename T>
BinaryHeap<T>::BinaryHeap() {
    //heap.reserve(2);
    heap.emplace_back(0);   // unused node
    this->size = 0;
}

template <typename T>
BinaryHeap<T>::BinaryHeap(std::vector<T> array) {
    heap.emplace_back(0);   // unused node
    this->size = 0;
    for(uint i = 0; i < array.size(); ++i) {
        this->insert(array.at(i));
    }
}

template <typename T>
void BinaryHeap<T>::insert(T key) {
    if (this->heap.size() == 1) {
        this->heap.emplace_back(key);
    }
    else {
        this->heap.emplace_back(key);
        int kru = this->heap.size()-1;
        while (this->heap[kru/2] < this->heap.at(kru)) {
            std::swap(this->heap[kru/2], this->heap[kru]);
            kru = kru/2;
            if (kru == 1) {
                break;
            }
        }
    }
}

template <typename T>
T BinaryHeap<T>::extract() {
    T ret = this->heap.at(1);
    this->heap.at(1) = this->heap.at(this->heap.size()-1);
    this->heap.pop_back();
    int kru = 1;
    while (this->heap[kru] < this->heap[2*kru] || this->heap[kru] < this->heap[2*kru+1]) {
        if (this->heap[kru] > this->heap[2*kru]) {
            std::swap(this->heap[kru], this->heap[2*kru+1]);
            kru = 2*kru + 1;
        }
        else {
            std::swap(this->heap[kru], this->heap[2*kru]);
            kru = 2*kru;
        }
    }
    return ret;
}

template <typename T>
void BinaryHeap<T>::display() {
    for(uint i = 1; i < this->heap.size(); ++i) {
        std::cout << heap[i] << std::endl;
    }    
}


int main() {
    /*
    prio queue default implementation
    std::priority_queue<int> pq;
    //std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
    pq.push(1);
    pq.push(2);
    pq.push(7);
    pq.push(5);
    pq.push(4);
    pq.push(3);
    pq.push(6); 
    */
    std::vector<int> A = {45, 35, 23, 27, 21, 22, 4, 19};
    BinaryHeap<int> h(A);
    std::cout << "-- Display Start --\n";
    h.display();
    std::cout << "-- Display End --\n";
    h.insert(42);
    std::cout << "-- Display Start --\n";
    h.display();
    std::cout << "-- Display End --\n";
    
    std::cout << "Top of heap removed: " << h.extract() << std::endl;
    std::cout << "-- Display Start --\n";
    h.display();
    std::cout << "-- Display End --\n";
    
}

/*lec
predescessor-previous node pag nag inorder traversal
successor-next node pag nag inorder traversal(right child)

HEAPS
-based on prio queue adt
--form of queue
--each object has an associated prio value
--first out, higher prio
--two operations: insert with no restrictions; delete object with highest prio
-binary heap: complete binary tree
-property: parent is always greater (called max heap) or less than its child nodes
-insertion should follow last two properties^^
-deletion only deletes top node; with highest prio; there will be no root node  so modify the heap

*/


/*
mar12
*/


/*
Exam Monday 4-6pm

Coverage:
Algorithm Complexity
-big O notation
-analyze which is faster
-recursive functions

Invariants and Proof of Correctness
-iterative; identify appropriate loop invariant
-steps for proof of correctness; initialization, maintenance, termination
-sorting algo

Linear Data Structures
-application and definition; lists and forward lists????

Non-Linear Data Structures
-trees, bst
-heap
-hash table
*/