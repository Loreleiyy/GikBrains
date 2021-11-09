#include <iostream>
#include <vector>

using std::cout;
using std::endl;

// 1 задание

template <typename T> class Pair1 {
private:
    T one;
    T two;
public:
    Pair1(T first, T second) {
        this->one = first;
        this->two = second;
    }
    T first() const { return one; }
    T second() const { return two; }
};

// 2 задание

template <typename T1, typename T2> class Pair {
private:
    T1 one;
    T2 two;
public:
    Pair(T1 first, T2 second) {
        this->one = first;
        this->two = second;
    }
    T1 first() const;
    T2 second() const;
};

template <typename T1, typename T2>
T1 Pair<T1,T2>::first() const{ return one; }

template <typename T1, typename T2>
T2 Pair<T1, T2>::second() const { return two; }

// 3* задание

template <typename T2> class Pair<std::string, T2> {
public:
    std::string one;
    T2 two;
public:
    Pair(std::string first, T2 second) {
        this->one = first;
        this->two = second;
    }
    std::string first() const { return one; }
    T2 second() const { return two; }
};

template <typename T> class StringValuePair : public Pair<std::string, T> {
private:
    
public:
    StringValuePair(std::string one, T two) : Pair<std::string, T>(one, two){  }
};

// 4 Blackjack просто чтоб было

class GenericPlayer : public Hand {
private:
    std::string name;
public:
    virtual bool IsHitting() const = 0;
    bool Boosted() {
        if (GetValue() > 21)
            return true;
        else
            return false;
    }
    void Bust() {
        if (Boosted())
            cout << this->name << " overly many cards \n";
    }
};

int main()
{
    // 1
    Pair1<int> p1(6, 9);
    cout << "Pair1: " << p1.first() << ' ' << p1.second() << '\n';

    const Pair1<double> p2(3.4, 7.8);
    cout << "Pair1: " << p2.first() << ' ' << p2.second() << '\n';
    // 2

    Pair<int, double> p3(6, 7.8);
    cout << "Pair: " << p3.first() << ' ' << p3.second() << '\n';

    const Pair<double, int> p4(3.4, 5);
    cout << "Pair: " << p4.first() << ' ' << p4.second() << '\n';

    // 3

    StringValuePair<int> svp("Amazing", 7);
    std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';


    return 0;
}