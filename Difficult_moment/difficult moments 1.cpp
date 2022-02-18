#include <iostream>
#include <optional>
#include <tuple>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <iomanip>



using std::cout;
using std::endl;
using std::string;


// 1 человек
struct Person {
    string lastName;
    string firstName;
    std::optional<string> patronymic;
};



std::ostream& operator<< (std::ostream& out, const Person& human) {
    out << std::setw(12) << std::right << human.lastName <<  std::setw(15) << std::right << human.firstName << " ";
    if (human.patronymic.has_value()) {
        out << std::setw(20) << std::right << human.patronymic.value();
    }
    else {
        out << "\t\t\t";
    }
    return out;
}

bool operator< (const Person& hum1, const Person& hum2) {
    if (hum1.patronymic.has_value() && hum2.patronymic.has_value()) {
        return std::tie(hum1.lastName, hum1.firstName, hum1.patronymic) < std::tie(hum2.lastName, hum2.firstName, hum2.patronymic);
    }
    else {
        return std::tie(hum1.lastName, hum1.firstName) < std::tie(hum2.lastName, hum2.firstName);
    }
}

bool operator== (const Person& hum1, const Person& hum2) {
    if (hum1.patronymic.has_value() && hum2.patronymic.has_value()) {
        return std::tie(hum1.lastName, hum1.firstName, hum1.patronymic) == std::tie(hum2.lastName, hum2.firstName, hum2.patronymic);
    }
    else {
        return std::tie(hum1.lastName, hum1.firstName) == std::tie(hum2.lastName, hum2.firstName);
    }
}

// 2 телефон
struct PhoneNumber {
    int countryCode;
    int cityCode;
    string number;
    std::optional<int> extensiunNum;
};

std::ostream& operator<< (std::ostream& out, const PhoneNumber& phone) {
    out << '+' << phone.countryCode << '(' << phone.cityCode << ')' <<
        phone.number << ' ';
    if (phone.extensiunNum.has_value()) {
        out << phone.extensiunNum.value();
    }
    else {
        out << "\t";
    }
    return out;
}

bool operator< (const PhoneNumber& phone1, const PhoneNumber& phone2) {
    if (phone1.extensiunNum.has_value() && phone2.extensiunNum.has_value()) {
        return std::tie(phone1.countryCode, phone1.cityCode, phone1.number, phone1.extensiunNum.value()) <
            std::tie(phone2.countryCode, phone2.cityCode, phone2.number, phone2.extensiunNum.value());
    }
    else {
        return std::tie(phone1.countryCode, phone1.cityCode, phone1.number) <
            std::tie(phone2.countryCode, phone2.cityCode, phone2.number);
    }
}

bool operator== (const PhoneNumber& phone1, const PhoneNumber& phone2) {
    if (phone1.extensiunNum.has_value() && phone2.extensiunNum.has_value()) {
        return std::tie(phone1.countryCode, phone1.cityCode, phone1.number, phone1.extensiunNum.value()) ==
            std::tie(phone2.countryCode, phone2.cityCode, phone2.number, phone2.extensiunNum.value());
    }
    else {
        return std::tie(phone1.countryCode, phone1.cityCode, phone1.number) ==
            std::tie(phone2.countryCode, phone2.cityCode, phone2.number);
    }
}

// 3 телефонная книга
class PhoneBook {
private:
    std::vector<std::pair<Person, PhoneNumber>> phoneBooks;
public:
    PhoneBook(std::ifstream& file) {
        
        string test;
        Person person;
        PhoneNumber phone;
        std::pair<Person, PhoneNumber> pairs;

        while (!file.eof()) {
            file >> person.lastName >> person.firstName;
            file >> test;
            if (test == "-") {
                person.patronymic = std::nullopt;
            }
            else {
                person.patronymic = test;
            }


            file >> phone.countryCode >> phone.cityCode >> phone.number;
            file >> test;
            if (test == "-") {
                phone.extensiunNum = std::nullopt;
            }
            else {
                phone.extensiunNum =  stoi(test);
            }
            pairs.first = person;
            pairs.second = phone;
            phoneBooks.push_back(pairs);
            
        }
    }

    friend std::ostream& operator<< (std::ostream& out, PhoneBook& book);


    void SortByName();
    void SortByPhone();
    std::tuple<string, PhoneNumber> GetPhoneNumber(string name);
    void ChangePhoneNumber(const Person& human, const PhoneNumber& phone);
};

std::ostream& operator<< (std::ostream& out, PhoneBook& book) {
    for (auto& [human, phone] : book.phoneBooks) {
        out << human << '\t' << phone << endl;
    }
    return out;
}

void PhoneBook::SortByName() {
    std::sort(phoneBooks.begin(), phoneBooks.end(), [](std::pair<Person, PhoneNumber>& hum1, std::pair<Person, PhoneNumber>& hum2) {
        return hum1.first < hum2.first; });
}

void PhoneBook::SortByPhone() {
    std::sort(phoneBooks.begin(), phoneBooks.end(), [](std::pair<Person, PhoneNumber>& hum1, std::pair<Person, PhoneNumber>& hum2) {
        return hum1.second < hum2.second; });
}

std::tuple<string, PhoneNumber> PhoneBook::GetPhoneNumber(string surname) {
    int quant = 0;
    PhoneNumber tel{ 0, 0, "0", 0 };
    for (auto& [human, phone] : phoneBooks) {
        if (human.lastName == surname) {
            quant++;
            tel = phone;
        }
    }
    if (quant == 0) {
        return std::make_tuple("not found", tel);
    }
    else {
        return (quant == 1 ? std::make_tuple("", tel) : std::make_tuple("found more than 1", tel));
    }
}

void PhoneBook::ChangePhoneNumber( const Person& human, const PhoneNumber& phone) {
    for (auto& [hum, pho] : phoneBooks) {
        if (hum == human) {
            pho = phone;
        }
    }
}

int main()
{
    std::ifstream file("PhoneBook.txt");  // путь к файлу PhoneBook.txt
    
    
    PhoneBook book(file);
    cout << book;
    
    cout << "------SortByPhone-------" << endl;
    book.SortByPhone();
    cout << book;

    cout << "------SortByName--------" << endl;
    book.SortByName();
    cout << book;

    cout << "-----GetPhoneNumber-----" << endl;
    // лямбда функция, которая принимает фамилию и выводит номер телефона этого    	человека, либо строку с ошибкой
    auto print_phone_number = [&book](const string& surname) {
        cout << surname << "\t";
        auto answer = book.GetPhoneNumber(surname);
        if (std::get<0>(answer).empty())
            cout << std::get<1>(answer);
        else
            cout << std::get<0>(answer);
        cout << endl;
    };

    // вызовы лямбды
    print_phone_number("Ivanov");
    print_phone_number("Petrov");
    print_phone_number("Solovev");

    cout << "----ChangePhoneNumber----" << endl;
    book.ChangePhoneNumber(Person{ "Kotov", "Vasilii", "Eliseevich" }, PhoneNumber{ 7, 123, "15344458", std::nullopt });
    book.ChangePhoneNumber(Person{ "Mironova", "Margarita", "Vladimirovna" }, PhoneNumber{ 16, 465, "9155448", 13 });
    cout << book;

    return 0;
}