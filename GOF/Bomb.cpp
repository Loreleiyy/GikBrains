
#include <iostream>
#include <vector>

#include "Bomb.h"
#include "MyTools.h"
#include "DestroyableGroundObject.h"
#include "SBomber.h"




using namespace std;
using namespace MyTools;

void Bomb::Draw() const
{
    MyTools::SetColor(CC_LightMagenta);
    GotoXY(x, y);
    cout << "*";
}

void __fastcall Bomb::Accept(Visitor& v) {
    v.log(this);
}

void __fastcall Bomb::CheckDestoyableObjects(SBomber& game) {
    
    std::vector<DestroyableGroundObject*> vecDestoyableObjects = game.FindDestoyableGroundObjects();
    
    const double size_2 = width / 2;
    
        const double x1 = x - size_2;
        const double x2 = x1 + width;
        for (size_t i = 0; i < vecDestoyableObjects.size(); i++)
        {
            if (vecDestoyableObjects[i]->isInside(x1, x2))          // HandleInsideCheck
            {
                game.score += vecDestoyableObjects[i]->GetScore();
                game.DeleteStaticObj(vecDestoyableObjects[i]);
        }
    }
}