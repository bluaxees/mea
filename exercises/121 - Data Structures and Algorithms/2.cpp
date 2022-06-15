#include <iostream>

int arraySum(int arr[][3], int row, int col) {
    int sum = 0;
    for (int i = 0; i < row; i += 1) {
        for (int j = 0; j < col; j+= 1) {
            sum += arr[i][j];
        }
    }
    return sum;
}

int *pointerss(int size) {
    int *iArray = new int[size];
    return iArray;
}

int main() {
    //int iArray[3][3] = {{1,2,3}, {4,5,6}, {7,8,9}};
    //std::cout << arraySum(iArray, 3, 3) << '\n';
    int iarray[3] = {1,2,3};
    int *ptr = pointerss(3);
    std::cout << (*ptr) << '\n';
    std::cout << (*ptr+1) << '\n';
    std::cout << (*ptr+2) << '\n';
    delete[] ptr;
}

//notes
//reference = &
//dereference = *
//std::cout << *(iArr+0) is same as iArr[0]