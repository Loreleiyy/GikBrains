#include <iostream>
#include "Card.h"
#include "Game.h"


using std::cout;
using std::endl;

class Date {
private:
    int day;
    int mounth;
    int year;
public:
    Date(){}
    Date(int day, int mou, int year) {
        this->day = day;
        this->mounth = mou;
        this->year = year;
    }

    int getDay() const { return day; }
    int getMounth() const { return mounth; }
    int getYear() const { return year; }
    void setDay(int day) { this->day = day; }
    void setMounth(int mounth) { this->mounth = mounth; }
    void setYear(int year) { this->year = year; }
    friend std::ostream& operator<< (std::ostream& ou, const Date& date);
};

std::ostream& operator<< (std::ostream& ou, const Date& date) {
    ou << date.day << "." << date.mounth << "." << date.year;
    return ou;
}


class DatePoint {
private:
    Date* point;
public:
    DatePoint(Date *point = nullptr) { this->point = point; }
    ~DatePoint() {
        delete point;
        point = nullptr;
    }
    friend Date& operator* (DatePoint &poin) { return *poin.point; }
    DatePoint& operator= (DatePoint& dat) {
        this->point = dat.point;
        dat.point = nullptr;
        return *this;
    }
    friend std::ostream& operator<< (std::ostream& ou, const DatePoint& date) {
        ou << date.point;
        return ou;
    }
};

DatePoint& LastData(DatePoint& dat1, DatePoint& dat2) {
    if ((*dat1).getYear() > (*dat2).getYear()) {
        return dat1;
    }
    else if ((*dat1).getYear() < (*dat2).getYear()) {
        return dat2;
    }
    else if ((*dat1).getMounth() > (*dat2).getMounth()) {
        return dat1;
    }
    else if ((*dat1).getMounth() < (*dat2).getMounth()) {
        return dat2;
    }
    else {
        return ((*dat1).getDay() > (*dat2).getDay() ? dat1 : dat2);
    }
}

void SwapData(DatePoint& dat1, DatePoint& dat2) {
    DatePoint temp = dat1;
    dat1 = dat2;
    dat2 = temp;
}


int main()
{
    // 1
    DatePoint today = new Date;
    (*today).setDay(11);
    (*today).setMounth(11);
    (*today).setYear(2021);
    DatePoint date;
    cout << *today << endl;
    date = today;
    cout << *date << endl;
    cout << date << ' ' << today << endl;
    DatePoint date1 = new Date(25, 10, 2021);
    DatePoint date2 = new Date(15, 07, 2022);
    cout << *date1 << ' ' << *date2 << endl;
    cout << *LastData(date1, date2) << '\n';
    SwapData(date1, date2);
    cout << *date1 << ' ' << *date2 << endl;
  
    /////
    // Blackjack //
    /////

    cout << "\n\t\tWelcome to Blackjack!\n\n";

    int numPlayer = 0;
    do {
        cout << "How many players? (1 - 7): ";
        std::cin >> numPlayer;
    } while (numPlayer < 1 || numPlayer > 7);

    std::vector<std::string> names;
    std::string name;
    for (int i = 0; i < numPlayer; ++i) {
        cout << "Enter player name: ";
        std::cin >> name;
        names.push_back(name);
    }
    cout << '\n';
    Game game(names);
    char again = 'n';
    do {
        system("cls");
        game.Play();
        cout << "\nDo you want to play again? (Y/N): ";
        std::cin >> again;
    } while (again == 'Y' || again == 'y');

    return 0;
}
