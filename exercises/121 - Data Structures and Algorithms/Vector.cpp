#include <iostream>

template <typename T>
class Vector {
private:
    T x_, y_, z_;
public:
    Vector(T x_, T y_, T z_);
    Vector();
    ~Vector();
    void setX(T x_) {(*this).x_ = x_; };
    void setY(T y_) {(*this).y_ = y_; };
    void setZ(T z_) {(*this).z_ = z_; };
    friend std::ostream &operator<<(std::ostream &out, const Vector &V) {
        out << '(' << V.x_ << ',' << V.y_ << ',' << V.z_ << ')';
        return out;
    };
    Vector<T> operator+(const Vector &V);
    Vector<T> operator-(const Vector &V);
    friend Vector<T> operator*(const Vector<T> &out, const int &c) {
        int i = out.x_*c;
        int j = out.y_*c;
        int k = out.z_*c;
        Vector<int> ans {i,j,k};
        return ans;
    };
    friend Vector<T> operator*(const int &c, const Vector<T> &out) {
        int i = out.x_*c;
        int j = out.y_*c;
        int k = out.z_*c;
        Vector<int> ans {i,j,k};
        return ans;
    };
    int operator*(const Vector &V);
};

template <typename T>
Vector<T>::Vector(T x_, T y_, T z_) {
    (*this).x_ = x_;
    (*this).y_ = y_;
    (*this).z_ = z_;
}

template <typename T>
Vector<T>::Vector(){
    (*this).x_ = 0;
    (*this).y_ = 0;
    (*this).z_ = 0;
}

template <typename T>
Vector<T>::~Vector() {}

template <typename T>
Vector<T> Vector<T>::operator+(const Vector<T> &V) {
    int i = (*this).x_ + V.x_;
    int j = (*this).y_ + V.y_;
    int k = (*this).z_ + V.z_;
    Vector<int> ans {i,j,k};
    return ans;
}

template <typename T>
Vector<T> Vector<T>::operator-(const Vector<T> &V) {
    int i = (*this).x_ - V.x_;
    int j = (*this).y_ - V.y_;
    int k = (*this).z_ - V.z_;
    Vector<int> ans {i,j,k};
    return ans;
}

template <typename T>
int Vector<T>::operator*(const Vector<T> &V) {
    int i = (*this).x_ * V.x_;
    int j = (*this).y_ * V.y_;
    int k = (*this).z_ * V.z_;
    return i + j + k;
}

int main() {
    Vector<int> v1 {1,2,3};
    Vector<int> v2;
    v2.setX(-3);
    v2.setY(1);
    v2.setZ(2);
    std::cout << v1 << '\n';
    std::cout << v2 << '\n';
    std::cout << v1 + v2 << '\n';
    std::cout << v1 - v2 << '\n';
    std::cout << v1 *2 << '\n';
    std::cout << 2 * v1 << '\n';
    std::cout << v1 * v2 << '\n';
}

