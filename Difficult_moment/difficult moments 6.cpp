#include <iostream>
#include <iomanip>
#include <thread>
#include <mutex>
#include <chrono>
#include <cmath>
#include <vector>
#include <algorithm>
#include <exception>
#include <ctime>
#include <future>
#include "C:\C++\Timer.h"


using std::endl;
using ms = std::chrono::milliseconds;       // у меня не работает - просто написать 1s +500ms
using s = std::chrono::seconds;


std::mutex dz1;
std::mutex dz3;

// 1
class Pcout {
public:
    friend std::ostream & operator<<(std::ostream & out, Pcout& pco){
        std::lock_guard lg(dz1);
        out << pco;
        
        return out;
    }

    template<typename T>
    Pcout& operator<< ( const T& Tout) {
        std::lock_guard lg(dz1);
        std::cout << Tout;
        
        return *this;
    }
};

// 2
int primeNumber(int& i) {
    Timer timer("prime Number");

    if (i == 1)
        return 2;

    int prime = 3;          // второе простое число
    int j = 5;              // обход начинается с 3 простого числа
   
    i -= 2;
    while (i > 0) {
        
        int squar = sqrt(j);
        for (int k = 2; k <= squar; ++k) {
            if (j % k == 0) {
                
                break;
            }
            if (k >= squar) {
                prime = j;
                
                --i;
                
            }
        }
        ++j;
        
    }
    timer.print();
    return prime;
}

void progressCalc(int& i) {
    Pcout cout;
    char sim = 219;             // белый прямоугольник
    int primeI;
    
    primeI = i;
    
    if (primeI == 1)
        return;
    int percent = primeI / 100;
    cout << "progress calculate prime number \n";
    int sumSim = 0;
    cout << sim;
    
    do {
        
        
        
        if ((primeI - i) > sumSim*percent) {        // не смог придумать более равномерного способа
            cout << sim;
            ++sumSim;
        }
        
    } while(sumSim < 99);
    std::cout << endl;
}

// 3
void owner(std::vector<int>& house) {
    int sz;
    Pcout cout;
    do {
        {
            std::lock_guard l3o(dz3);
            sz = house.size();
            house.push_back(rand() % 1000);


        }
        cout << " owner ";

        std::this_thread::sleep_for(s(1));
    } while (sz > 0 && sz < 10);
}

void thief(std::vector<int>& house) {
    int sz;
    Pcout cout;
    do {
        {
            std::lock_guard l3t(dz3);
            sz = house.size();
            auto max = std::max_element(house.begin(), house.end());
            house.erase(max);

        }

        cout << " thief ";
        std::this_thread::sleep_for(ms(500));
    } while (sz > 1 && sz < 10);
    
}

void printVector(std::vector<int>& house) {
    std::lock_guard l3p(dz3);
    for (int n : house) {
        Pcout cout;
        cout << n << ' ';
        
    }
    std::cout << endl;
}

void test() {
    std::cout << "valid ar \n";
}



int main()
{
    srand(time(NULL));
    Pcout pcout;
    pcout << "enter enter\n" << 146 << 'w' << '\n';
    // 2
   
    int i = 100000;
    std::thread progress(progressCalc, std::ref(i));
    progress.detach();
    
    auto prime(std::async(std::launch::async, primeNumber, std::ref(i)));
    
    
    std::cout << endl;
    pcout << prime.get() << '\n';
    
    
    

    // 3
    std::vector<int> house(5);
    std::generate(house.begin(), house.end(), []() {return (rand() % 1000); });
    printVector(house);
 
    std::thread own(owner, std::ref(house));
    own.detach();

    std::thread thi(thief, std::ref(house));
    
    /* раньше иногда вылазила такая ошибка 
    mutex destroyed while busy
    но я не помню, как нужно изменить код, чтоб она снова появилась
    (это про вопрос на вебинаре)*/

    thi.join();

    
    

    return 0;
}
