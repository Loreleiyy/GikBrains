#include "specialchar.h"

SpecialChar::SpecialChar(QString text)
{
    txt = text;

    list = {
        {"EURO", "€"},
        {"RUB", "₽"},
        {"PROMILE", "‰"},
        {"COPY", "©"},
        {"TRADEMARC", "®"}};

}

QString SpecialChar::parse()
{
    for (const auto &i : list){
        if(i.first == txt){
            return i.second;
        }
    }
    return "";
}
