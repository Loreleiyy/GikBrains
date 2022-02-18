#include <iostream>
#include <utility>
#include "Timer.h"
#include <vector>
#include <fstream>
#include <algorithm>



using std::cout;
using std::endl;
using std::string;

// 1
template<typename T>
void Swap(T&& one, T&& two) {
    T temp = one;
    one = two;
    two = temp;
}

// 2
template<typename T>
void  SortPointers(std::vector<T>& vpoin) {
    for (int i = 1; i < vpoin.size(); ++i) {
        for (int j = 1; j < vpoin.size(); ++j) {
            if (*(vpoin[j]) < *(vpoin[j - 1])) {
                Swap(std::move(vpoin[j]), std::move(vpoin[j - 1]));
            }
        }
    }
}

template<typename T>
void printVector(const std::vector<T>& v) {
    for (T n : v) {
        cout << n << ' ' << *n << '\n';
    }
}



// 3 поиск гласных букв в тексте

int for_forVowel(string& sfile, string& sim) {
    int sum = 0;
    for (char s : sfile) {
        for (char csim : sim) {
            if (s == csim) {
                ++sum;
                break;
            }
        }
    }
    return sum;
}



int countFind(string& sfile, string& sim) {
    int sum = 0;
    sum = std::count_if(sfile.begin(), sfile.end(), [sim](char csim) {
        int pos = 0;
        pos = sim.find(csim);
        if (pos != -1) {
            return true;
        }
        else {
            return false;
        }
       
        });
    return sum;
}

int countFor(string& sfile, string& sim) {
    int sum = 0;
    sum = std::count_if(sfile.begin(), sfile.end(), [sim](char csim) {
        for (char n : sim) {
            if (csim == n) {
                return true;
            }
            
        }
        return false;
        });
    return sum;
}

int forFind(string& sfile, string& sim) {
    int sum = 0;
    int pos = 0;
    for (char s : sfile) {
        pos = sim.find(s);
        if (pos != -1) {
            ++sum;
        }
    }
    return sum;
}

int main()
{
    setlocale(LC_ALL, "ru");

    // 1
    int a, b;
    a = 5;
    b = 10;
    int* ptr1 = &a;
    int* ptr2 = &b;
    
    cout << "ptr1 " << *ptr1 << ' ' << ptr1 << '\n' <<
        "ptr2 " << *ptr2 << ' ' << ptr2 << endl;
    Swap(std::move(ptr1), std::move(ptr2));
    cout << "swap ptr \n";
    cout << "ptr1 " << *ptr1 << ' ' << ptr1 << '\n' <<
        "ptr2 " << *ptr2 << ' ' << ptr2 << '\n' << endl;

    // 2

    std::vector<int*> vptr;
    vptr.reserve(b);
    for (int i = 0; i < b; ++i) {
        vptr.push_back(new int);
        *(vptr[i]) = rand() % 1000;
    }
    
    printVector(vptr);
    SortPointers(vptr);
    cout << "\nsort points \n";
    printVector(vptr);
    
    // 3

    std::ifstream file("War and peace.txt");
    if (!file.is_open()) {
        cout << "file not open\n";
        return 0;
    }
    file.seekg(0, std::ios::end);
    int size = file.tellg();
    file.seekg(0);
    string s(size, ' ');
    file.read(&s[0], size);

    cout << size << endl;
    string sim{ "оОеЕёЁаАиИуУяЯыЫюЮэЭeEaAiIuUoOyY" };   // буквы расположены по частоте встречаемости в языке


    Timer time("for for Vowel");
    cout << for_forVowel(s, sim) << '\n' << endl;
    time.print();
    time.start("for find");
    cout << forFind(s, sim) << '\n' << endl;
    time.print();
    time.start("count_if for");
    cout << countFor(s, sim) << '\n' << endl;
    time.print();
    time.start("count_if find");
    cout << countFind(s, sim) << '\n' << endl;
    time.print();
    
}
