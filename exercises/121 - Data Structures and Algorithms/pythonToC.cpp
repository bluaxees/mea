#include <iostream>
#include <string>
#include <cmath>
#include <vector>

class Player {
private:
    static int numPlayers;
    int id;
    std::string name;
    int HP, atk_, mDef;
public:
    Player(std::string name, int HP, int Atk, int Def);
    Player();
    ~Player();
    void getStatus();
    std::string getName() {return name; };
    int getHP() {return HP; };
    int getAtk() {return atk_; };
    int getDef() {return mDef; };
    void setName(std::string name) {(*this).name = name; };
    void setHP(int HP) {(*this).HP = HP; };
    void setAtk(int Atk) {atk_ = Atk; };
    void setDef(int Def) {mDef = Def; };
};

Player::Player() {
    (*this).name = "";
    this->HP = 0; //same as above line
    atk_ = 0;
    mDef = 0;
    (*this).id = ++numPlayers;
}

Player::~Player() {
    std::cout << "Player " << (*this).name << " has been deleted." << '\n';
}

Player::Player(std::string name, int HP, int Atk, int Def) {
    (*this).name = name;
    this->HP = HP; //same as above line
    atk_ = Atk;
    mDef = Def;
    (*this).id = ++numPlayers;
}

int Player::numPlayers = 0;

void Player::getStatus() {
    std::cout << "Name: " << (*this).name << '\n'
                << "HP: " << (*this).HP << '\t'
                << "Atk: " << (*this).atk_ << '\t'
                << "Def: " << (*this).mDef << '\t'
                << "ID: " << (*this).id << '/' << (*this).numPlayers << '\n';
}

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
    std::cout << "Point at (" << (*this).x << ',' << (*this).y << ')' << " has been deleted." << '\n';
}

void Point::getPoint() {
    std::cout << "Point : (" << (*this).x << ',' << (*this).y << ')' << '\n';
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
};

Polygon::Polygon(std::string name, const std::vector<Point> &vec) {
    (*this).name = name;
    (*this).vec = vec;
}

Polygon::~Polygon() {
    std::cout << "Polygon " << (*this).name << " has been deleted." << '\n';
}

void Polygon::getCoor() {
    std::cout << "lul";
}

int main() {
    Point A = {1, 4};
    Point B = {2, 3};
    Point C = {5, 6};
    std::vector<Point> vec = {A, B, C};
    Polygon tri = {"Triangle", vec};
    Point D = tri.getVer(1);
    D.getPoint();
    std::cout << tri.getNum() << '\n';
    //B.setX(2);
    //B.setY(3);
    //B.getPoint();
    //double m = A.distance(B);
    //std::cout << m << '\n';
    return 0;
}