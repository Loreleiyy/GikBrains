#include <iostream>
#include <set>
#include <map>
#include <fstream>
#include <vector>
#include <string>
#include <list>
#include <sstream>


using std::cout;
using std::endl;
using std::string;

// 1
template<typename T>
void uniqPrint(T begin, T end) {
    std::set<string> uniq;
    for (; begin != end; ++begin) {
        uniq.insert(*begin);
    }
   
    for (auto& n : uniq) {
        cout << n << ' ';
    }
    cout << endl;
}


// 2
class Sentences {
private:
    string sentences;
public:
    Sentences(string s) : sentences(s){}

    friend std::ostream& operator<< (std::ostream& out, const Sentences& sent) {
        out << sent.sentences << '.';
        return out;
    }

    friend bool operator< (const Sentences& sent, const Sentences& sent2) {
        return sent.sentences.size() < sent2.sentences.size();
    }
};

int main()
{
    // 1 задание
    std::ifstream file("PhoneBook.txt");        // последовательность слов
    if (!file.is_open()) {
        cout << "file not open \n";
    }

    string word = "";
    std::vector<string> text;

    while (file >> word) {
        text.push_back(word);
    }
    uniqPrint(text.begin(), text.end());
    
    cout << endl;
    std::list<string> textLst;
    file.clear();
    file.seekg(std::ios_base::beg);
   
    while (file >> word) {
        textLst.push_back(word);
    }

    uniqPrint(textLst.begin(), textLst.end());

    file.close();

    // 2 задание
    cout << '\n' << "enter text" << endl;
    string sent, str;
    std::getline(std::cin, str);
    std::stringstream sstr(str);

    std::set <Sentences> text2;
    
    while (std::getline(sstr, sent, '.')) {
        text2.insert(Sentences(sent));
    };

    copy(text2.begin(), text2.end(), std::ostream_iterator<Sentences>(cout, "\n"));
    
    return 0;
}