#include <iostream>
#include <vector>
#include <list>
#include <ctime>


using std::cout;
using std::endl;

// 1
void averageToList(std::list<double>& lst) {
    double sum = 0;
    for (const auto& n : lst) {
        sum += n;
    }
    lst.push_back(sum / lst.size());
    
}

void printList(const std::list<double>& lst) {
    for (auto n : lst) {
        cout << n << ' ';
    }
    cout << endl;
}

// 2 матрица
class Matrix {
private:
    std::vector<std::vector<int> > matrix;
public:
    Matrix(std::vector<std::vector<int> > &matr) {
        matrix = matr;
    }
    Matrix(){}

    int Determ();
};

// определитель
int Matrix::Determ() {
    int sz = matrix.size();
    if (sz == 2) {
        return (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]);
    }
    int determinant = 0;
    for (int i = 0; i < matrix.size(); ++i) {
        int A = matrix[0][i];
        Matrix matr2;
        matr2.matrix.resize(sz - 1);
        for (int q = 0; q < sz - 1; ++q) {
            matr2.matrix[q].resize(sz - 1);
        }
        
        for (int j = 0; j < sz-1; ++j) {
            for (int z = 0; z < sz-1; ++z) {
                matr2.matrix[j][z] = matrix[j + 1][z >= i ? z + 1 : z];
            }
        }
        determinant += A * (i % 2 == 1 ? -1 : 1) * matr2.Determ();      // рекурсия
    }
    return determinant;
}


// 3 итератор
class Iterator {
private:
    int* iter;
public:
    Iterator() : iter(nullptr){}
    Iterator(int *arr) {
        iter = arr;
    }
    
    friend bool operator!=(const Iterator& it1, const Iterator& it2);
    Iterator& operator++();
    Iterator& operator++(int);
    int& operator* ();
};

bool operator!= (const Iterator& it1, const Iterator& it2) {
    return (it1.iter != it2.iter);
}

Iterator& Iterator::operator++() {
    ++iter;
    return *this;
}

Iterator& Iterator::operator++(int) {
    Iterator temp(iter);
    ++iter;
    return temp;
}

int& Iterator::operator*() {
    
    return *iter;
}

//контейнер int
class Container {
private:
    int* arr;
    int length;
public:
    Container() : length(0), arr(nullptr) {}
    Container(int len) : length(len){
        arr = new int[len];        // не уверен будет ли везде работает, альтернатива    arr = new int[len+1];
       
    }

    Iterator& begin();
    Iterator& end();
    int& operator[](int index);

    ~Container() {
        delete[] arr;
    }
};

Iterator& Container::begin() {
    Iterator it(&arr[0]);
    return it;
}

Iterator& Container::end() {
    Iterator it(&arr[length]);
    return it;
}

int& Container::operator[](int index) {
    if (index >= 0 && index < length) {
        return arr[index];
    }
}


void printContainer(Container& con) {
    for (auto n : con) {
        cout << n << ' ';
    }
    cout << endl;
}

int main()
{
    srand(time(NULL));
    
    std::list<double> lst;
    for (int i = 0; i < 20; ++i) {
        lst.push_back(static_cast<double>(rand() % 1000) / 100);
    }

    printList(lst);
    averageToList(lst);
    printList(lst);
    
    // 2
    std::vector<std::vector<int> > matr{ {2, -5, 1, 2},
                                         {-3, 7, -1, 4},
                                        {5, -9, 2, 7},
                                        {4, -6, 1, 2} };
    cout << matr.size() << ' ' << matr[0].size() << endl;
    Matrix det(matr);
    
    cout << det.Determ() << endl;
    


    // 3
    Container contInt(20);
    for (auto& n : contInt) {
        n = rand() % 50;
    }

    printContainer(contInt);

    return 0;
}