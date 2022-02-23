#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <numeric>

template<typename T>
void insert_sorted(std::vector<T> &numer ,T newN) {
    auto it = lower_bound(numer.begin(), numer.end(), newN);
    numer.insert(it, newN);
}

template<typename T>
void printVector(const std::vector<T>& vec) {
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<T>{std::cout, " "});
    std::cout << std::endl;
}

int main()
{
    srand(time(NULL));
    // 2 задание
    std::vector<double> a(100);
    
    
    std::generate(a.begin(), a.end(), []() {  return ((rand() % 1000) / 100.0); });

    std::vector<int> b(a.size());
    
    std::copy(a.begin(), a.end(), b.begin());
    printVector(a);
    printVector(b);

    // сделал 2 способами (так получилось)
    // 1 способ
    std::vector<double> c;
    c.reserve(a.size());

    auto miss = [](double i) {double q = i - static_cast<int>(i);
    return q * q; };
    std::transform(a.begin(), a.end(), std::back_inserter(c), miss);
    double mistake = std::accumulate(c.begin(), c.end(), 0.0);
    
    std::cout << std::endl;

    // 2 способ
    double mistake2 = std::inner_product(a.begin(), a.end(), b.begin(), 0.0, [](double i, double j) {return i+j*j; },
        [](double i, double j) {return  i - j; });

    std::cout << mistake << std::endl;
    std::cout << mistake2 << std::endl;

    // 1 задание
    std::vector<int> d(20);
    std::generate(d.begin(), d.end(), []() {return rand() % 100; });
    sort(d.begin(), d.end());
    printVector(d);

    int numer = rand() % 100;
    std::cout << numer << std::endl;
    insert_sorted(d, numer);
    printVector(d);
    
    std::cout << std::endl;
    return 0; 
}