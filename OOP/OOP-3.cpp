#include <iostream>
#include <string>

using std::cout;
using std::endl;

// 1 задание  использую самые простые варианты формул

class Figure {
    
public:
    virtual double area() = 0;
    Figure(){}
};

class Parallelogram : public Figure {
protected:
    int length;
    int height;
public:
    Parallelogram(){}
    Parallelogram(int length, int height) {
        this->length = length;
        this->height = height;
    }
    double area() override{
        return length * height;  }
};

class Circle : public Figure {
private:
    int radius;
    const double pi = 3.141592;
public:
    Circle(int radius) { this->radius = radius; }
    double area() override{
        return radius * radius * pi;
    }
};

class Rectangle : public Parallelogram {
public:
    Rectangle(int length, int width) : Parallelogram(length, width){}
    double area() override {
        return this->length * this->height;
    }
};


class Square : public Parallelogram {
private:
    double length;
public:
    Square(double length) { this->length = length; }
    double area() override {
        return length* length; }
};


class Rhombus : public Parallelogram {
private:
    double diagonala;
    double diagonalb;
public:
    Rhombus(double diagonala, double diagonalb) {
        this->diagonala = diagonala;
        this->diagonalb = diagonalb;
    }
    double area() override {
        return (diagonala * diagonalb) / 2;
    }
};


// 2 задание

class Car {
    std::string company;
    std::string model;
public:
    
    Car(std::string company = "", std::string model = "Car") { this->company = company;
    this->model = model;
    cout << company << " model " << model << " car " << endl;
    }
};

class PassengerCar : virtual public Car {
public:
    PassengerCar(std::string company = "", std::string model= "PassengerCar") : Car(company, model) {
        cout << company << " model " << model << " PassengerCar " << endl;
    }
};

class Bus : virtual public Car {
public:
    Bus(std::string company = "", std::string model = "Bus") : Car(company, model) {
        cout << company << " model " << model << " bus " << endl;
    }
};

class Minivan : public PassengerCar, public Bus {
public:
    Minivan(std::string company = "", std::string model = "Minivan") : PassengerCar(company, model),
        Bus(company, model), Car(company, model) {
        cout << company << " model " << model << " Minivan " << endl;
    }
};


// 3 задание

// приведение к общему знаменателю
void commonDenom(int &num1, int &denum1, int &num2, int &denum2) {
    {
        if (denum1 != denum2) {
            num1 *= denum2;
            num2 *= denum1;
            denum1 *= denum2;
            denum2 = denum1;
        }
    }
}

class Fraction {
private:
    int numerator=0;
    int denominator=1;
public:
    Fraction(int numerator, int denominator) {
        if (denominator == 0) {
            return;
      }  
        this->numerator = numerator;
        this->denominator = denominator;
    }
    friend Fraction operator+ (const Fraction& a, const Fraction& b);
    friend Fraction operator- (const Fraction& a, const Fraction& b);
    friend Fraction operator* (const Fraction& a, const Fraction& b);
    friend Fraction operator/ (const Fraction& a, const Fraction& b);
    friend std::ostream& operator<< (std::ostream& out, const Fraction& fract) {   // в задании не было, но так удобней
        out << fract.numerator << '/' << fract.denominator << ' ';
        return out;
    }
    Fraction operator- () const { return Fraction(-numerator, denominator); }
    friend bool operator== (const Fraction& a, const Fraction& b);
    friend bool operator!= (const Fraction& a, const Fraction& b);
    friend bool operator> (const Fraction& a, const Fraction& b);
    friend bool operator>= (const Fraction& a, const Fraction& b);
    friend bool operator< (const Fraction& a, const Fraction& b);
    friend bool operator<= (const Fraction& a, const Fraction& b);
};


Fraction operator+(const Fraction& a, const Fraction& b) {
    int num1 = a.numerator;
    int denum1 = a.denominator;
    int num2 = b.numerator;
    int denum2 = b.denominator;
    commonDenom(num1, denum1, num2, denum2);
    return Fraction((num1 + num2), denum1);
}

Fraction operator-(const Fraction& a, const Fraction& b) {
    int num1 = a.numerator;
    int denum1 = a.denominator;
    int num2 = b.numerator;
    int denum2 = b.denominator;
    commonDenom(num1, denum1, num2, denum2);
    return Fraction((num1 - num2), denum1);
}

Fraction operator*(const Fraction& a, const Fraction& b) {
    return Fraction((a.numerator * b.numerator), (a.denominator * b.denominator));
}

Fraction operator/(const Fraction& a, const Fraction& b) {
    return Fraction((a.numerator * b.denominator), (a.denominator * b.numerator));
}

bool operator== (const Fraction& a, const Fraction& b) {
    int num1 = a.numerator;
    int denum1 = a.denominator;
    int num2 = b.numerator;
    int denum2 = b.denominator;
    commonDenom(num1, denum1, num2, denum2);
    return (num1 == num2);
}

bool operator!= (const Fraction& a, const Fraction& b) {
    return !(a == b);
}

bool operator> (const Fraction& a, const Fraction& b) {
    int num1 = a.numerator;
    int denum1 = a.denominator;
    int num2 = b.numerator;
    int denum2 = b.denominator;
    commonDenom(num1, denum1, num2, denum2);
    return (num1 > num2);
}

bool operator<= (const Fraction& a, const Fraction& b) {
    return !(a > b);
}

bool operator< (const Fraction& a, const Fraction& b) {
    int num1 = a.numerator;
    int denum1 = a.denominator;
    int num2 = b.numerator;
    int denum2 = b.denominator;
    commonDenom(num1, denum1, num2, denum2);
    return (num1 < num2);
}

bool operator>= (const Fraction& a, const Fraction& b) {
    return !(a < b);
}

// 4 задание


class Card {
private:
    enum class Suit;
    enum class ValueCart;
    Suit suit;
    ValueCart valueCart;
    bool openCart;
public:
    void Flip() { !openCart; };
    ValueCart GetValue()const { return valueCart; }
};

// значения 3-6 выводят в консоль символы соответствующих мастей
enum class Card::Suit { hearts = 3, diamonds, cross, spades };

enum class Card::ValueCart {
    ace = 1, two, three, four, five,
    six, seven, eight, nine, ten,
    Jack = 10, Queen = 10, King = 10
};



int main()
{
    Fraction a(3, 4);
    Fraction b(5, 7);
    cout << a << b << b+a << endl;
    
    Fraction z = a / b;
    cout << z << endl;

    if (a > b)
        cout << "a > b  ";
    if (a == b)
        cout << "a == b  ";
    if (a < z)
        cout << "a < z  \n";
    if (a != b)
        cout << "a != b  ";
    Circle cir(5);
    
    Rhombus romb(2.5, 3.3);
    cout << cir.area() << ' ' << romb.area();

    Car car;
    PassengerCar passengerCar;
    Bus bus;
    Minivan minivan;

    cout << "\n";
    return 0;
}
