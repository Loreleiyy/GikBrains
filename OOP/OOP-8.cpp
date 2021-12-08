#include <iostream>
#include <string>

using std::cout;
using std::endl;


// не ДЗ (ради интереса)
void deMemoryErr(int* mem) {
    delete mem;
    //delete mem;
}


// 1 задание

template <class T1, class T2>
T1 div(T1 one, T2 two) {
    if (two == 0) {
        throw "DivisionByZero";
    }
    return one / two;
}

// 2 задание

class Ex {
private:
    double x;
public:
    Ex(double ax) : x(ax) {}
    friend std::ostream& operator<< (std::ostream & ou, const Ex & ex){
        ou << ex.x;
        return ou;
    }
};

class Bar {
private:
    double y;
public:
    Bar(double by = 0) : y(by) {}
    void set(double a){
        if ((y + a) > 100) {
            throw Ex(a * y);
        }
        else {
            y = a;
        }
    
    }
};

// 3

class coord {
protected:
    int x;
    int y;
public:
    coord(int ax, int ay) : x(ax), y(ay){}
    
};

// ошибка выхода за карту

class OffTheField : public coord {
private:
    std::string direction;
    int dx;
    int dy;
public:
    OffTheField(int x, int y, int nx, int ny) : coord(x, y), dx(nx), dy(ny) {}
        
    void directionMovement() {
        if ((this->x - dx) > 0) {
            direction = "right";
        }
        else if ((this->x - dx) < 0) {
            direction = "left";
        }
        else if ((this->y - dy) > 0) {
            direction = "up";
        }
        else if ((this->y - dy) < 0) {
            direction = "down";
        }
    }
    
    std::string what() {
        directionMovement();
        std::string message = "Error, the robot has gone beyond the map border coord x: " + std::to_string(this->x) +
            " coord y: " + std::to_string(this->y) + " direction of movement: " + direction;
        return message;
    }
};

// ошибка направления (сделал так, иначе непонятная ошибка)

class IllegalCommand : public coord {

public:
    IllegalCommand(int x, int y) : coord(x, y) { }
    
    std::string what() {
        std::string message = "Error, the robot cannot move diagonally, coord x " + std::to_string(this->x) +
            " coord y " + std::to_string(this->y);
        return message;
    }
};

// робот

class Robot : public coord{
private:
    
    static const int size = 10;
    
public:
    Robot(int ax = 1, int ay = 1) : coord(ax, ay) {}
    friend std::ostream& operator<< (std::ostream& ou, Robot &rob) {
        ou << rob.x << ' ' << rob.y;
        return ou;
    }

    void nextPosition(int nx, int ny);
};

void Robot::nextPosition(int nx, int ny) {
    
    if (nx > this->size || ny > this->size) {
        throw OffTheField(this->x, this->y, nx, ny);
    }
    else if(this->x - nx != 0 && this->y - ny != 0){
        throw IllegalCommand(this->x, this->y);
    }
    else {
        this->x = nx;
        this->y = ny;
    }
}



int main()
{
    double xa;
    int xb;
    xa = 4.9;
    xb = 0;
    int *mem = new int;
    *mem = 5;

    // 1
    try {
        deMemoryErr(mem);
        cout << div(xa, xb) << endl;
    }
    catch (char const*) {
        cout << "catch char \n";
    }
    catch (const std::exception& exc) {
        std::cerr << "Standard exception: " << exc.what() << '\n';
    }
    catch (...) {
        cout << "catch all \n";
    }

    // 2
    Bar bar;
    int n = 1;
    try {
        while (n != 0) {
            cout << "enter number, to complete, enter 0 \n";
            std::cin >> n;
            bar.set(n);
        } 
    }catch(const Ex& ex){
        cout << "error, an exception was caused " << ex << endl;
    }

    // 3
    Robot robot;
    int x, y;
    cout << "This robot can move in a straight line on the map 10X10 \nexit enter the -1 coordinate \n";
    cout << "start x = 1, y = 1 \n";
    try {
        do {
            cout << "enter the new coordinate (x and y) \n";
            std::cin >> x;
            std::cin >> y;
            robot.nextPosition(x, y);
            cout << "position " << robot << endl;
        } while (x != -1 || y != -1);
    }
    catch (OffTheField& off) {
        cout << off.what() << endl;
    }
    catch (IllegalCommand& notleg) {
        cout << notleg.what() << endl;
    }

    cout << "end" << endl;
    return 0;
}
