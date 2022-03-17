#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>
#include <sstream>
#include <gtest/gtest.h>

#include "StudentsGroup1.pb.h"

using std::cout;
using std::endl;
using std::string;

class IRepository {
    virtual void Open() = 0; // бинарная десериализация в файл
    virtual void Save() = 0; // бинарная сериализация в файл
};

// 2

namespace noprotobuf {
  
    class FullName;

    class IMethods {
        virtual double GetAverageScore(const FullName& name) = 0;
        virtual string GetAllInfo(const FullName& name) = 0;
        virtual string GetAllInfo() = 0;
    };

    class FullName {
    private:
        string name;
        string lastName;
        std::optional<string> patronymic;
    public:
        FullName(){}
        FullName(string n, string nlast, string p="") : name(n), lastName(nlast), patronymic(p) {}

        friend std::ostream& operator<<(std::ostream& out, const FullName& full) {
            out << full.name << ' ' << full.lastName << ' ' << full.patronymic.value();
            return out;
        }
        friend bool operator== (const FullName& st1, const FullName& st2) {

            return (std::tie(st1.lastName, st1.name, st1.patronymic.value()) ==
                std::tie(st2.lastName, st2.name, st2.patronymic.value()));
        }
        
    };

    class Student {
    private:
        FullName fullName;
        std::vector<int> evaluations;   // оценки
        double averageScore;        // средняя оценка
        void averScor() {
            double sum = 0;
            for (int n : evaluations) {
                sum += n;
            }
            averageScore = sum / evaluations.size();        // подсчёт средней оценки
        }
    public:
        Student() {}
        Student(FullName& Fn) : fullName(Fn) {}
        Student(string n, string nlast, string p = "") {
            FullName name(n, nlast, p);
            fullName = name;
        }

        void setEstimation(int esm) {       // добавить 1 оценку
            evaluations.push_back(esm);
            averScor();
            
        }

        void setEvaluations(std::vector<int> estim) {       // добавить несколько оценок
            int end = evaluations.end() - evaluations.begin();
            evaluations.resize(evaluations.size() + estim.size());
            std::copy(estim.begin(), estim.end(), evaluations.begin() + end);
            averScor();
        }


        double getAverageScore() {
            return evaluations.empty() ? 0 : averageScore;
        }

        friend std::ostream& operator<<(std::ostream& out,  Student& st) {
            out << st.fullName << " average score: " << st.getAverageScore() << " estimations \n";
            for (auto &n : st.evaluations) {
                out << n << ' ';
            }
            return out;
        }

        friend bool operator== (const Student& st1, const FullName& name) {

            return st1.fullName == name;
        }
    };

    // 3.2

    class StudentsGroup : public IMethods {
    private:
        std::vector<Student> students;
    public:
        StudentsGroup(){}
        StudentsGroup(std::vector<Student>& st) {
            students.resize(st.size());
            std::copy(st.begin(), st.end(), students.begin());
            
        }
        void setStudent(Student& st) {
            students.push_back(st);
        }

        double GetAverageScore(const FullName& name) override {
            auto it = std::find(students.begin(), students.end(), name);
            return it->getAverageScore();
        }

        string GetAllInfo(const FullName& name) override {
            auto it = std::find(students.begin(), students.end(), name);
            std::stringstream ss;
            ss << *it;
            
            return ss.str();
        }

        string GetAllInfo() override {
            std::stringstream ss;
            for (auto &n : students) {
                ss << n << endl;
            }
            return ss.str();
        }
    };
}


// 3.1


class StudentsGroup : public IRepository {
private:
    protobuf::StudentsGroup group;
public:
    StudentsGroup(protobuf::StudentsGroup &st) : group(st) {}
    void Open() override {
        std::ifstream in("./group.bin", std::ios_base::binary);
        if (group.ParseFromIstream(&in)) {
            cout << "success \n";
        }
        else {
            cout << "Error!" << endl;
        }
    
    }
    void Save() override {
        std::ofstream ou("./group.bin", std::ios_base::binary);
        group.SerializePartialToOstream(&ou);
    }
    
};

std::ostream& operator<<(std::ostream& out, const protobuf::FullName& name) {
    out << name.name() << ' ' << name.lastname() << ' ' << name.patronymic();
    return out;
}



int main()
{
    protobuf::Student st1;
    protobuf::FullName fn1;
    fn1.set_name("Petr");
    fn1.set_lastname("Ivanov");
    fn1.set_patronymic("Sergeevich");
    
    
    std::ofstream ou("./group.bin", std::ios_base::binary);
    fn1.SerializePartialToOstream(&ou);
    std::ifstream in("./group.bin", std::ios_base::binary);
    if (fn1.ParseFromIstream(&in)) {
        cout << "success \n";
    }
    else {
        cout << "Error!" << endl;
    }
    
    cout << st1.fullname().lastname();

    noprotobuf::FullName nfn("Roman", "Romanov");
    noprotobuf::Student stud(nfn);
    stud.setEstimation(4);
    std::vector<int> v{ 3,4,3,5,5,4, 3 };
    stud.setEvaluations(v);
    cout << stud.getAverageScore() << endl;
    noprotobuf::StudentsGroup gr;
    gr.setStudent(stud);
    cout << gr.GetAverageScore(nfn) << '\n' << gr.GetAllInfo();
    
    return 0;
}