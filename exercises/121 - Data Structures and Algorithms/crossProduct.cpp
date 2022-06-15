#include <iostream>
#include <array>

std::array<int, 3> crossvector(std::array<int, 3> u, std::array<int, 3> v) {
    int x;
    int y;
    int z;
    std::array<int,3> product;
    x = (u.at(1))*(v.at(2)) - (u.at(2))*(v.at(1));
    y = (u.at(2))*(v.at(0)) - (u.at(0))*(v.at(2));
    z = (u.at(0))*(v.at(1)) - (u.at(1))*(v.at(0));
    product[0] = x;
    product[1] = y;
    product[2] = z;
    return product;
}

int main() {
    std::array<int, 3> m {2,3,4};
    std::array<int, 3> n {5,6,7};
    std::array<int, 3> crossArray crossvector(m,n);
    for (std::array<int,3>::iterator it = crossArray.begin(); it != crossArray.end(); ++it) {
        std::cout << *it << '\n';
    }
}

