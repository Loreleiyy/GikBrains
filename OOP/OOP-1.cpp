#include <iostream>
#include <cmath>
#include <cstdint>


using std::cout;
using std::endl;

// 1 задание

class Power {
    double a = 0.0;
    double exp = 0.0;
public:
    void setCalculate(double a, double exp) {
        this->a = a;
        this->exp = exp;
    }
    void calculate() {
        cout << pow(a, exp) << endl;
    }
    
};

// 2 задание

class RGBA {
private:
    std::uint8_t m_red;
    std::uint8_t m_green;
    std::uint8_t m_blue;
    std::uint8_t m_alpha;
    
public:
    RGBA(uint8_t red=0, uint8_t green=0, uint8_t blue=0, uint8_t alpha=255) :
        m_red(red), m_green(green), m_blue(blue), m_alpha(alpha){}

    void print();
};

void RGBA::print() {

    cout << "red " << static_cast<int>(m_red) << " green " << static_cast<int>(m_green) <<
        " blue " << static_cast<int>(m_blue) << " alpha " << static_cast<int>(m_alpha) << endl;
}

// 3 задание

class Stack {
private:
    const int sz = 10;
    int arr[10];
    int sizeSteck;
public:
    void reset();
    bool push(int a);
    int pop();
    void print();
};

void Stack::reset() {
    sizeSteck = 0;
    for (int i = 0; i < sz; ++i) {
        arr[i] = 0;
    }
}

bool Stack::push(int a) {
    if (sizeSteck >= sz) {
        return false;
    }
    arr[sizeSteck] = a;
    ++sizeSteck;
    return true;
}

int Stack::pop() {
    if (sizeSteck == 0) {
        cout << "error stack is empty \n";
        return -1;
    }
    --sizeSteck;
    int a = arr[sizeSteck];
    arr[sizeSteck] = 0;
    
    return a;
}

void Stack::print() {
    cout << '(';
    for (int i = 0; i < sizeSteck; ++i) {
        cout << arr[i] << ' ';
    }
    cout << ")\n";
}

int main()
{
    // 1 
    Power a;
    a.calculate();
    a.setCalculate(4.5, 3.1);
    a.calculate();

    // 2 

    RGBA blak;
    blak.print();
    RGBA sg(125, 125, 125, 200);
    sg.print();

    //3

    Stack stack;
    stack.reset();
    stack.print();

    stack.push(3);
    stack.push(7);
    stack.push(5);
    stack.print();

    stack.pop();
    stack.print();

    stack.pop();
    stack.pop();
    
    stack.print();
    stack.pop();
    
    return 0;
}