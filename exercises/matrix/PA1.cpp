//2018-04736

#include <iostream>
#include <vector>

template <typename T>
class Matrix {
private:
    unsigned int m_, n_;
    std::vector<T> elements_;
public:
    Matrix(unsigned int m, unsigned int n, std::vector<T> elements);
    Matrix(Matrix<T> &M);
    Matrix<T> operator=(Matrix<T> &M);
    template <typename T_>
    friend std::ostream &operator<<(std::ostream &out, const Matrix<T_> &M);
    T& at(unsigned int i, unsigned int j);
    Matrix<T> operator+(const Matrix<T> &M);
    Matrix<T> operator-(const Matrix<T> &M);
    Matrix<T> operator*(const Matrix<T> &M);
    Matrix<T> operator*(const T &c);
    template <typename T_>
    friend Matrix<T> operator*(const T_ &c, const Matrix<T> &M) {
        std::vector<T> elements;
        for (int i = 0; i < M.elements_.size(); i++) {
            elements.push_back(M.elements_.at(i)*c);
        }
        Matrix<T> outM {M.m_, M.n_, elements};
        return outM;
    };
    static Matrix<T> eye(unsigned int m);
    static Matrix<T> zeros(unsigned int m, unsigned int n);
    static Matrix<T> ones(unsigned int m, unsigned int n);
    T *operator[](unsigned int i);
};

//Default Constructor
template <typename T>
Matrix<T>::Matrix(unsigned int m, unsigned int n, std::vector<T> elements) {
    m_ = m;
    n_ = n;
    elements_ = elements;
}

//Copy Constructor
template <typename T>
Matrix<T>::Matrix(Matrix<T> &M) {
    m_ = M.m_;
    n_ = M.n_;
    elements_ = M.elements_;
}

//Copy Constructor using Operator =
template <typename T>
Matrix<T> Matrix<T>::operator=(Matrix<T> &M) {
    Matrix<T> outM;
    unsigned int m = M.m_;
    unsigned int n = M.n_;
    std::vector<T> elements = M.elements_;
    outM = {m, n, elements};
    return outM;
}

//Print
template <typename T>
std::ostream &operator<<(std::ostream &out, const Matrix<T> &M) {
    std::vector<T> elements = M.elements_;
    unsigned int m = M.m_;
    unsigned int n = M.n_;
    for (int i = 0; i != m; i++) {
        for (int j = 0; j != n; j++) {
            out << elements.at(i*n+j) << "   ";
        }
        if (i != m-1) {
            out << '\n';
        }
    }
    return out;
}

//Indexing using at keyword
template <typename T>
T& Matrix<T>::at(unsigned int i, unsigned int j) {
    T& out = elements_.at((i-1)*(n_) + (j-1));
    return out;
}

//Matrix Addition
template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &M) {
    std::vector<T> elements;
    for (int i = 0; i < M.elements_.size(); i++) {
        elements.push_back(elements_.at(i) + M.elements_.at(i));
    }
    Matrix<T> outM {m_, n_, elements};
    return outM;
}

//Matrix Addition
template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &M) {
    std::vector<T> elements;
    for (int i = 0; i < M.elements_.size(); i++) {
        elements.push_back(elements_.at(i) - M.elements_.at(i));
    }
    Matrix<T> outM {m_, n_, elements};
    return outM;
}

//Matrix to Matrix Multiplication
template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &M) {
    std::vector<T> product;
    for (int i = 0; i < m_; i++) {
        for (int j = 0; j < m_; j++) {
            T sum = 0;
            for (int k = 0; k < n_; k++) {
                sum += elements_.at(i*n_ + k)*M.elements_.at(k*M.n_ + j);
            }
            product.push_back(sum);
        }
    }
    Matrix<T> outM {m_, M.n_, product};
    return outM;
}

//Scalar Multiplication
template <typename T>
Matrix<T> Matrix<T>::operator*(const T &c) {
    std::vector<T> elements;
    for (int i = 0; i < elements_.size(); i++) {
        elements.push_back(elements_.at(i)*c);
    }
    Matrix<T> outM {m_, n_, elements};
    return outM;
}

//Static Initializer Eye
template <typename T>
Matrix<T> Matrix<T>::eye(unsigned int m) {
    Matrix<T> &&outM = Matrix<int>::zeros(m, m);
    for (int i = 1; i <= m; i++) {
        outM.at(i, i) = 1;
        outM.at(i, m - i + 1) = 1;
    }
    return outM;
}

//Static Initializer Zeros
template <typename T>
Matrix<T> Matrix<T>::zeros(unsigned int m, unsigned int n) {
    std::vector<T> elements;
    for (int i = 0; i < m*n; i++) {
        elements.push_back(0);
    }
    Matrix<T> outM {m, n, elements};
    return outM;
}

//Static Initializer Ones
template <typename T>
Matrix<T> Matrix<T>::ones(unsigned int m, unsigned int n) {
    std::vector<T> elements;
    for (int i = 0; i < m*n; i++) {
        elements.push_back(1);
    }
    Matrix<T> outM {m, n, elements};
    return outM;
}

//Indexing using Operator []
template <typename T>
T *Matrix<T>::operator[](unsigned int i) {
    T *ptr = &elements_[(i-1)*n_-1];
    return ptr;
}

int main() {
    std::vector<float> vec1 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    std::vector<float> vec2 {1.1, 2.2, 3.4, 5.6, 1.2, 1.3, 2.5, 7.8, 9.6, 3.2, 4.3, 4.6, 5.7, 6.1, 9.1};
    Matrix<float> mtx1 {3, 5, vec1};
    Matrix<float> mtx2 {3, 5, vec2};
    Matrix<float> copy1 = mtx1;
    Matrix<float> copy2 {mtx2};   

    std::cout << "Matrix 1:\n" << mtx1 << '\n'
              << "Matrix 2:\n" << mtx2 << '\n'
              << "Matrix 1 Copy:\n" << copy1 << '\n';
    mtx1.at(3,4) = 42;
    mtx2[2][3] = 1.7;
    std::cout << "Matrix 1 at (3,4) set to 42\n"
              << "Matrix 1 at (3,4): " << mtx1.at(3,4) << '\n'
              << "Matrix 2 at [2][3] set to 1.7\n"
              << "Matrix 2 at [2][3]: " << mtx2[2][3] << '\n'
              << "Updated Matrix 1:\n" << mtx1 << '\n'
              << "Updated Matrix 2:\n" << mtx2 << '\n'
              << "Sum of Matrix 1 & 2:\n" << mtx1 + mtx2 << '\n'
              << "Difference of Matrix 1 & 2:\n" << mtx1 - mtx2 << '\n';
    int c = 3;
    std::vector<int> veca {1,2,3,4,5,6};
    Matrix<int> mtxa {2,3, veca};
    std::vector<int> vecb {7,8,9,10,11,12};
    Matrix<int> mtxb {3,2,vecb};
    std::cout << "Initializing Matrix A and B for multiplication . . .\n"
              << "Matrix A:\n" << mtxa << '\n'
              << "Matrix B:\n" << mtxb << '\n'
              << "Matrix Multiplication (A*B):\n" << mtxa*mtxb << '\n'
              << "Scalar Multiplication (A*3):\n" << mtxa*c << '\n'
              << "Scalar Multiplication (3*B):\n" << c*mtxb << '\n'
              << "Static Initializers . . .\n"
              << "4 by 7 Zeros:\n" << Matrix<int>::zeros(4,7) << '\n'
              << "8 by 5 Ones:\n"  << Matrix<int>::ones(8,5) << '\n'
              << "Eye of 4:\n" << Matrix<int>::eye(4) << '\n'
              << "Eye of 7:\n" << Matrix<int>::eye(7) << '\n';
}