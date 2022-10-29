#ifndef SPECIALCHAR_H
#define SPECIALCHAR_H

#include <QString>
#include <map>

class SpecialChar
{
private:
    QString txt;
    std::map<QString, QString> list;
public:
    SpecialChar(QString text);
    QString parse();
};

#endif // SPECIALCHAR_H
