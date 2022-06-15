//2018-04736
#include <iostream>
#include <string>
#include <cmath>
#include <vector>

class Point {
private:
    int x, y;
public:
    Point(int x, int y);
    Point();
    ~Point();
    void getPoint();
    int getX() {return x; };
    int getY() {return y; };
    void setX(int x) {(*this).x = x; };
    void setY(int y) {(*this).y = y; };
    double distance(Point &other);
};

Point::Point(int x, int y) {
    (*this).x = x;
    (*this).y = y;
}

Point::Point() {
    (*this).x = 0;
    (*this).y = 0;
}

Point::~Point() {
	//I commented these out for readability of output.
    //std::cout << "Point at (" << (*this).x << ',' << (*this).y << ')' << " has been deleted." << '\n';
}

void Point::getPoint() {
    std::cout << "(" << (*this).x << ',' << (*this).y << ')' << '\n';
}

double Point::distance(Point &other) {
    double dist = sqrt(pow(((*this).x - other.getX()), 2) + pow(((*this).y - other.getY()), 2));
    return dist;
}

class Polygon {
private:
    std::string name;
    std::vector<Point> vec;
    int a;
public:
    Polygon(std::string name, const std::vector<Point> &vec);
    ~Polygon();
    std::string getName() {return name; };
    int getNum() {return vec.size(); };
    Point getVer(int i) {return vec.at(i-1); };
    void getCoor();
    double getPeri();
};

Polygon::Polygon(std::string name, const std::vector<Point> &vec) {
    (*this).name = name;
    (*this).vec = vec;
}

Polygon::~Polygon() {
	std::cout << "Polygon " << (*this).name << " has been deleted." << '\n';
}

void Polygon::getCoor() {
    std::cout << (*this).name << "\'s Point Coordinates: " << '\n';
    for (int i = 0; i != (*this).vec.size(); ++i) {
    	Point other = (*this).vec.at(i);
    	other.getPoint();
    }
}

double Polygon::getPeri() {
	double perimeter = 0;
	for (int i = 0; i != (*this).vec.size(); ++i) {
		if (i == 0) {
			Point other = (*this).vec.at(i);
			Point another = (*this).vec.at((*this).vec.size()-1);
			perimeter += another.distance(other);
		}
		else {
			Point other = (*this).vec.at(i);
			Point another = (*this).vec.at(i-1);
			perimeter += another.distance(other, (*this).vec.at(i-1));
        }
		
	}
	return perimeter;
}

int main() {
	double distance;
	double perimeter;
    Point A = {0, 0};
    Point B = {3, 4};
    A.getPoint();
    B.getPoint();
    distance = A.distance(B);
    std::cout << "The distance between A and B is " << distance << '\n';
    Point C;
    C.setX(0); //Output tests for setter methods of Point
    C.setY(1);

    std::vector<Point> vec = {A, B, C};
    Polygon tri = {"Triangle", vec};
    Point D = tri.getVer(1); //Output tests for getter methods of Polygon
    D.getPoint();
    std::cout << "The polygon has " << tri.getNum() << " vertices" << '\n';
    tri.getCoor();
    perimeter = tri.getPeri();
    std::cout << perimeter << '\n';
    return 0;
}