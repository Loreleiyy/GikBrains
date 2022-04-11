
#include <iostream>

#include "Plane.h"
#include "MyTools.h"

using namespace std;
using namespace MyTools;

void Plane::Draw() const
{
    /*
    MyTools::SetColor(CC_LightBlue);
    GotoXY(x, y);
    cout << "=========>";
    GotoXY(x - 2, y - 1);
    cout << "===";
    GotoXY(x + 3, y - 1);
    cout << "\\\\\\\\";
    GotoXY(x + 3, y + 1);
    cout << "////";
    */
    DrawBody();
    DrawWings();
    DrawTail();
}

void Plane::DrawBody() const {                //  фюзеляж
    MyTools::SetColor(CC_LightBlue);
    GotoXY(x, y);
    cout << "=========>";
}
void Plane::DrawWings() const {               // крылья
    GotoXY(x - 2, y - 1);
    cout << "===";
}
void Plane::DrawTail() const {                // хвост
    GotoXY(x + 3, y - 1);
    cout << "\\\\\\\\";
    GotoXY(x + 3, y + 1);
    cout << "////";
}

void ColorPlane::DrawBody() const{
    SetColor(CC_LightRed);
    GotoXY(x, y);
    cout << "=========>";
}
void ColorPlane::DrawWings() const{
    SetColor(CC_LightMagenta);
    GotoXY(x - 2, y - 1);
    cout << "===";
}
void ColorPlane::DrawTail() const{
    SetColor(CC_Yellow);
    GotoXY(x + 3, y - 1);
    cout << "\\\\\\\\";
    GotoXY(x + 3, y + 1);
    cout << "////";
}



void BigPlane::DrawBody() const{
    SetColor(CC_LightBlue);
    GotoXY(x, y);
    cout << "=========>";
    GotoXY(x, y-1);
    cout << "========";
}
void BigPlane::DrawWings() const{
    GotoXY(x - 5, y - 2);
    cout << "======";
}
void BigPlane::DrawTail() const{
    GotoXY(x + 3, y - 2);
    cout << "\\\\\\\\";
    GotoXY(x + 3, y + 1);
    cout << "////";
    GotoXY(x + 3, y - 3);
    cout << "\\\\\\\\";
    GotoXY(x + 3, y + 2);
    cout << "////";
}