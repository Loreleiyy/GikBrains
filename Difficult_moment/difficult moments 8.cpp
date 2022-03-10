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
        FullName() {}
        FullName(string n, string nlast, string p = "") : name(n), lastName(nlast), patronymic(p) {}

        friend std::ostream& operator<<(std::ostream& out, const FullName& full) {
            out << full.name << ' ' << full.lastName << ' ' << full.patronymic.value();
            return out;
        }
        friend bool operator== (const FullName& st1, const FullName& st2) {

            return (std::tie(st1.lastName, st1.name, st1.patronymic.value()) ==
                std::tie(st2.lastName, st2.name, st2.patronymic.value()));
        }

    };

    TEST(testname, FullName) {
        FullName n1("Baranova", "Vasilisa", "Leonidovna");
        FullName n2("Baranova", "Vasilisa");
        ASSERT_FALSE(n1 == n2);
        ASSERT_TRUE(n1 == FullName("Baranova", "Vasilisa", "Leonidovna"));
    }

    class Student {
    private:
        FullName fullName;
        std::vector<int> evaluations;   // оценки
        double averageScore = 0;        // средняя оценка
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
            return averageScore;
        }

        friend std::ostream& operator<<(std::ostream& out, Student& st) {
            out << st.fullName << " average score: " << st.getAverageScore() << " estimations \n";
            for (auto& n : st.evaluations) {
                out << n << ' ';
            }
            return out;
        }

        friend bool operator== (const Student& st1, const FullName& name) {

            return st1.fullName == name;
        }
    };


    TEST(student, Student) {
        Student st1("Baranova", "Vasilisa", "Leonidovna");
        FullName fn("Baranova", "Vasilisa");
        Student st2(fn);

        ASSERT_FALSE(st1 == fn);
        ASSERT_TRUE(st1 == FullName("Baranova", "Vasilisa", "Leonidovna"));
        st1.setEstimation(3);
        st1.setEstimation(4);
        std::vector<int> v{ 5,2,4,3 };
        st1.setEvaluations(v);
        ASSERT_DOUBLE_EQ(3.5, st1.getAverageScore());
        ASSERT_EQ(0, st2.getAverageScore());
    }
}

std::ostream& operator<<(std::ostream& out, const protobuf::FullName& name) {
    out << name.name() << ' ' << name.lastname() << ' ' << name.patronymic();
    return out;
}

// 3
class StudentsGroup : public noprotobuf::IMethods, public IRepository {
private:
    std::vector<noprotobuf::Student> students;
    protobuf::StudentsGroup group;
public:
    StudentsGroup() {}
    StudentsGroup(std::vector<noprotobuf::Student>& st) {
        students.resize(st.size());
        std::copy(st.begin(), st.end(), students.begin());

    }
    void setStudent(noprotobuf::Student& st) {
        students.push_back(st);
    }

    double GetAverageScore(const noprotobuf::FullName& name) override {
        auto it = std::find(students.begin(), students.end(), name);
        return it->getAverageScore();
    }

    string GetAllInfo(const noprotobuf::FullName& name) override {
        auto it = std::find(students.begin(), students.end(), name);
        std::stringstream ss;
        ss << *it;

        return ss.str();
    }

    string GetAllInfo() override {
        std::stringstream ss;
        for (auto& n : students) {
            ss << n << endl;
        }
        return ss.str();
    }

    StudentsGroup(protobuf::StudentsGroup& st) : group(st) {}

    void Open() override {
        std::ifstream in("group.bin", std::ios_base::binary);
        if (group.ParseFromIstream(&in)) {
            cout << "success \n";
        }
        else {
            cout << "Error!" << endl;
        }

    }
    void Save() override {
        std::ofstream ou("group.bin", std::ios_base::binary);
        group.SerializePartialToOstream(&ou);
    }
};


class StudentsGroupTest : public testing::Test {    // тестовый класс
protected:
    noprotobuf::Student* st1;
    noprotobuf::Student* st2;
    noprotobuf::FullName* fn;
    StudentsGroup group;
    void SetUp() override {
        fn = new noprotobuf::FullName("Baranova", "Vasilisa", "Leonidovna");
        st1 = new noprotobuf::Student(*fn);
        st2 = new noprotobuf::Student("Baranova", "Vasilisa");
        st1->setEstimation(3);
        st1->setEstimation(5);
        group.setStudent(*st1);
        group.setStudent(*st2);
        cout << group.GetAllInfo(*fn);
    }

    void TearDown() {
        delete st1;
        delete st2;
        delete fn;
    }
};

TEST_F(StudentsGroupTest, GetAver) {
    ASSERT_EQ(4, group.GetAverageScore(*fn));
}

TEST_F(StudentsGroupTest, tostring) {
    string s1 = "Baranova Vasilisa Leonidovna average score: 4 estimations \n3 5 ";
    ASSERT_STREQ(s1.c_str(), group.GetAllInfo(*fn).c_str());
    s1 += "\nBaranova Vasilisa  average score: 0 estimations \n\n";
    ASSERT_STREQ(s1.c_str(), group.GetAllInfo().c_str());
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
    StudentsGroup gr;
    gr.setStudent(stud);
    cout << gr.GetAverageScore(nfn) << '\n' << gr.GetAllInfo();
    
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();

}