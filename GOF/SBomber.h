#pragma once

#include <vector>

#include "LevelGUI.h"
#include "Plane.h"
#include "Bomb.h"
#include "Ground.h"
#include "Tank.h"
#include "ProxyLogger.h"


class SBomber
{
public:

    SBomber();
    ~SBomber();
    
    inline bool GetExitFlag() const { return exitFlag; }

    void ProcessKBHit();
    void TimeStart();
    void TimeFinish();

    void DrawFrame();
    void MoveObjects();
    void CheckObjects();
    
private:
    InterfaceFileLogger* proxy = new ProxyLogger(&FileLoggerSingletone::getInstance());
    void CheckPlaneAndLevelGUI();
    void CheckBombsAndGround();
    void __fastcall CheckDestoyableObjects(Bomb* pBomb);

    void __fastcall DeleteDynamicObj(DynamicObject * pBomb);
    void __fastcall DeleteStaticObj(GameObject* pObj);

    Ground * FindGround() const;
    Plane * FindPlane() const;
    LevelGUI * FindLevelGUI() const;
    std::vector<DestroyableGroundObject*> FindDestoyableGroundObjects() const;
    std::vector<Bomb*> FindAllBombs() const;

    void DropBomb();

    std::vector<DynamicObject*> vecDynamicObj;
    std::vector<GameObject*> vecStaticObj;
    
    bool exitFlag;

    uint64_t startTime, finishTime, passedTime;
    uint16_t bombsNumber, deltaTime, fps;
    int16_t score;

public:
    class BombIterator {
    private:
        std::vector<DynamicObject*> arr;
        int index;
        DynamicObject* ptr;
    public:
        BombIterator(std::vector<DynamicObject*> CoArr) : arr(CoArr), index(-1), ptr(nullptr) { ++(*this); }
        void reset() { index = -1;  ptr = nullptr; }

        BombIterator& operator++() {
            ++index;
            for (; index < arr.size(); ++index) {
                
                
                //if (typeid( Bomb* ) == typeid(arr[index])) {        // такой способ не работает
                   
                Bomb* pBomb = dynamic_cast<Bomb*>(arr[index]);
                if (pBomb != nullptr) {
                    ptr = arr[index];
                    break;
                }
                
            }
            if (index == arr.size()) {
                index = -1;
                ptr = nullptr;
            }
            return *this;
        }
        BombIterator& operator++(int) {
            auto temp = *this;
            ++(*this);
            return temp;
        }

        BombIterator& operator--() {
            --index;
           
            for (; index >= 0; --index) {
                Bomb* pBomb = dynamic_cast<Bomb*>(arr[index]);
                if (pBomb != nullptr) {
                    ptr = arr[index];
                    break;
                }
            }
            if (index <= 0) {
                index = -1;
                ptr = nullptr;
            }
            return *this;
        }
        BombIterator& operator--(int) {
            auto temp = *this;
            --(*this);
            return temp;
        }

        DynamicObject*& operator*() {
            return arr.at(index);
        }
        bool operator==(BombIterator it) {
            if (ptr == it.ptr && arr == it.arr) {
                return true;
            }
            return false;
        }
        bool operator!=(BombIterator it) {
            return !(it == *this);
        }
      
    };
    BombIterator begin() const {
        BombIterator it(vecDynamicObj);
        return it;
    }
    BombIterator end() const {
        BombIterator it(vecDynamicObj);
        it.reset();
        return it;
    }
};