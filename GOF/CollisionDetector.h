#pragma once


#include <vector>
#include "SBomber.h"
#include "AdapterTank.h"
#include "House.h"

using std::vector;

class CollisionDetector {
    
public:
    
    virtual void CheckPlaneAndLevelGUI() = 0;
    virtual void CheckBombsAndGround() = 0;
    virtual void __fastcall CheckDestoyableObjects(Bomb* pBomb) = 0;
    virtual ~CollisionDetector(){}
};

class WinCollisionDetector : public CollisionDetector {
protected:
    bool& exitFlag;
    int16_t& score;
    std::vector<DynamicObject*>& vecDynamicObj;
    std::vector<GameObject*>& vecStaticObj;
public:
    WinCollisionDetector(bool& exit, int16_t& s, std::vector<DynamicObject*>& vD, std::vector<GameObject*>& vS)
        : exitFlag(exit), score(s), vecDynamicObj(vD), vecStaticObj(vS) {}

    void CheckPlaneAndLevelGUI()
    {
        if (FindPlane()->GetX() > FindLevelGUI()->GetFinishX())
        {
            exitFlag = true;
        }
    }

    void CheckBombsAndGround()
    {
        vector<Bomb*> vecBombs = FindAllBombs();
        Ground* pGround = FindGround();
        const double y = pGround->GetY();
        for (size_t i = 0; i < vecBombs.size(); i++)
        {
            if (vecBombs[i]->GetY() >= y)// Пересечение бомбы с землей
            {
                pGround->AddCrater(vecBombs[i]->GetX());
                CheckDestoyableObjects(vecBombs[i]);
                DeleteDynamicObj(vecBombs[i]);
            }
        }

    }

    void CheckDestoyableObjects(Bomb* pBomb)
    {
        vector<DestroyableGroundObject*> vecDestoyableObjects = FindDestoyableGroundObjects();
        const double size = pBomb->GetWidth();
        const double size_2 = size / 2;
        for (size_t i = 0; i < vecDestoyableObjects.size(); i++)
        {
            const double x1 = pBomb->GetX() - size_2;
            const double x2 = x1 + size;
            if (vecDestoyableObjects[i]->isInside(x1, x2))
            {
                score += vecDestoyableObjects[i]->GetScore();
                DeleteStaticObj(vecDestoyableObjects[i]);
            }
        }
    }

    void DeleteDynamicObj(DynamicObject* pObj)
    {
        auto it = vecDynamicObj.begin();
        for (; it != vecDynamicObj.end(); it++)
        {
            if (*it == pObj)
            {
                auto ptrTemp = *it;
                vecDynamicObj.erase(it);
                delete ptrTemp;
                break;
            }
        }
    }

    void DeleteStaticObj(GameObject* pObj)
    {
        auto it = vecStaticObj.begin();
        for (; it != vecStaticObj.end(); it++)
        {
            if (*it == pObj)
            {
                auto ptrTemp = *it;
                vecStaticObj.erase(it);
                delete ptrTemp;
                break;
            }
        }
    }

    vector<DestroyableGroundObject*> FindDestoyableGroundObjects() const
    {
        vector<DestroyableGroundObject*> vec;
        AdapterTank* pTank;
        House* pHouse;
        for (size_t i = 0; i < vecStaticObj.size(); i++)
        {
            pTank = dynamic_cast<AdapterTank*>(vecStaticObj[i]);
            if (pTank != nullptr)
            {
                vec.push_back(pTank);
                continue;
            }

            pHouse = dynamic_cast<House*>(vecStaticObj[i]);
            if (pHouse != nullptr)
            {
                vec.push_back(pHouse);
                continue;
            }
        }

        return vec;
    }

    Ground* FindGround() const
    {
        Ground* pGround;

        for (size_t i = 0; i < vecStaticObj.size(); i++)
        {
            pGround = dynamic_cast<Ground*>(vecStaticObj[i]);
            if (pGround != nullptr)
            {
                return pGround;
            }
        }

        return nullptr;
    }

    vector<Bomb*> FindAllBombs() const
    {
        vector<Bomb*> vecBombs;

        for (size_t i = 0; i < vecDynamicObj.size(); i++)
        {
            Bomb* pBomb = dynamic_cast<Bomb*>(vecDynamicObj[i]);
            if (pBomb != nullptr)
            {
                vecBombs.push_back(pBomb);
            }
        }

        
        return vecBombs;
    }

    Plane* FindPlane() const
    {
        for (size_t i = 0; i < vecDynamicObj.size(); i++)
        {
            Plane* p = dynamic_cast<Plane*>(vecDynamicObj[i]);
            if (p != nullptr)
            {
                return p;
            }
        }

        return nullptr;
    }

    LevelGUI* FindLevelGUI() const
    {
        for (size_t i = 0; i < vecStaticObj.size(); i++)
        {
            LevelGUI* p = dynamic_cast<LevelGUI*>(vecStaticObj[i]);
            if (p != nullptr)
            {
                return p;
            }
        }

        return nullptr;
    }

};