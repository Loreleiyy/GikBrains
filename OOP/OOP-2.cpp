#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

// 1


class Person {
private:
    std::string name;
    int age;
    int weight;
    std::string gender;
public:
    
    void setName(string name) {
        this->name = name;
    }
    void setAge(int age) {
        this->age = age;
    }
    void setWeight(int weight) {
        this->weight = weight;
    }
    Person(string name, int age, int weight, string gender) {
        this->name = name;
        this->age = age;
        this->weight = weight;
        this->gender = gender;
    }
    void printPerson();
};

void Person::printPerson() {
    printf("%s  age %d  weight %d  %s  ", name.c_str(), age, weight, gender.c_str());
}


class Student : public Person {
private:
    int yearStudy = 0;
    static int students;        // колличество студентов
public:
    
    void setYearSt(int year) {
        this->yearStudy = year;
    }
    void AddYearSt() {
        ++this->yearStudy;
    }
    Student(string name, int age, int weight, string gender, int yearStudy = 1) : Person(name, age, weight, gender) {
        this->yearStudy = yearStudy;
        ++students;
    }
    void printStudy();
    
    int getStudents() { return students; }
    ~Student() {
        --students;
    }
};

void Student::printStudy() {
    printPerson();
    cout << "year study " << yearStudy << endl;
}

int Student::students = 0;
 // 2

class Fruit {
private:
    string name;
    string color;
public:
    Fruit(){}
    Fruit(string name, string color){
        this->name = name;
        this->color = color;
    }
    string getName() { return name; }
    string getColor() { return color; }
};

class Apple : public Fruit {
public:
    Apple() : Fruit("apple", "green") {}
    Apple(string color) : Fruit("apple", color) { }
    Apple(string name, string color) : Fruit(name +=" apple", color) { }
};

class Banana : public Fruit {
public:
    Banana() : Fruit("banana", "yellow") {}
};

class GrannySmith : public Apple {
public:
    GrannySmith() : Apple("Granny Smith", "green") {}
};

int main()
{
    // 1
    Student st1("Anton", 18, 60, "men");
    Student st2("Sergey", 20, 65, "men", 3);
    Student st3("Anna", 19, 50, "women");
    Student* group[]{ &st1, &st2, &st3 };
    for (int i = 0; i < st1.getStudents(); ++i) {
        group[i]->printStudy();
    }
    
    cout << st1.getStudents() << endl;
    
    // 2
    Apple a("red");
    Banana b;
    GrannySmith c;
    
    std::cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
    std::cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
    std::cout << "My " << c.getName() << " is " << c.getColor() << ".\n";


    return 0;

}

/*В игре Blackjack 2 основных класса - "карта" и "игрок" от игрока можно сделать дочерний класс "диллер"
возможно стоит сделать перечисление для карт(enum), всем картинкам присвоить значение 10, туз - 1
а уже при подсчёте добавлять 10 в зависимости от условий. Карты можно всегда определять как открытые
так как в игре только 1 карта закрыта у диллера, но он всё равно вступает в игру после всех игроков,
можно отрисовывать закрытую карту, но выдать 1 в начале, а потом уже получает карты как обычный игрок.
Вариан для бесконечной колоды, определять карты случайно*/