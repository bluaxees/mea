//PAUL ALLEN TRISTAN PATIO 2018-11844
#include <iostream>
#include <vector>
using namespace std;

template <typename p>
class Vec3d{
    private:
        p X,Y,Z;
    public:
        Vec3d(p X, p Y, p Z);
        Vec3d();
        ~Vec3d();
        void setX(p X) {this->X = X; };
        void setY(p Y) {this->Y = Y; };
        void setZ(p Z) {this->Z = Z; };
        Vec3d<p> operator + (const Vec3d &t);
        Vec3d<p> operator - (const Vec3d &t);
        //Vec3d<p> operator * (const Vec3d &t);
        Vec3d<p> operator * (const int &t);
        int operator * (const Vec3d &t);
        friend ostream& operator << (ostream &out, const Vec3d<p> &t) 
        {
        out << '(' << t.X << ',' << t.Y << ','<< t.Z <<')';
        return out;    
        }

        friend Vec3d<p> operator * (p out, const Vec3d<p> &t) 
        {
       // out << '(' << t.X << ',' << t.Y << ','<< t.Z <<')';
        return {out*t.X, out*t.Y , out*t.Z}; 
        }
       // int operator*(const Vec3d &t)
};

template <typename p>
Vec3d<p>::Vec3d(p X, p Y,p Z){
    (*this).X = X;
    (*this).Y = Y;
    (*this).Z = Z;
}

template <typename p>
Vec3d<p>::Vec3d(): X(0), Y(0), Z(0){}
template <typename p>
Vec3d<p>::~Vec3d(){}

template <typename p>
Vec3d<p> Vec3d<p>::operator +(const Vec3d<p> &t) {
    return {this->X+t.X, this->Y+t.Y, this->Z+t.Z};    
}
template <typename p>
Vec3d<p> Vec3d<p>::operator -(const Vec3d<p> &t) {
    return {this->X-t.X, this->Y-t.Y, this->Z-t.Z};    
}
template <typename p>
Vec3d<p> Vec3d<p>::operator *(const int &t) {
    return {this->X*t, this->Y*t, this->Z*t};    
}
template <typename p>
int Vec3d<p>::operator *(const Vec3d<p> &t) {
    return (this->X*t.X + this->Y*t.Y +this->Z*t.Z);    
}

int main () 
{
Vec3d <int> v1 {1 ,2 ,3};
Vec3d <int> v2 ;
v2.setX (-3) ;
v2.setY (1) ;
v2.setZ (2) ;
cout << v1 << endl ;
cout << v2 << endl ;
cout << v1 + v2 << endl ;
cout << v1 - v2 << endl ;
cout << v1 * 2 << endl ;
cout << 2 * v1 << endl ;
cout << v1 * v2 << endl ;
}