#pragma once


#include <stdint.h>
#include <tuple>
#include "GameObject.h"

class Visitor;

class DynamicObject : public GameObject 
{
public:

    DynamicObject() : speed(0.0), xDirction(0.0), yDirection(0) { }

    inline void SetSpeed(double sp) { speed = sp; }
    inline void SetDirection(double dx, double dy) { xDirction = dx; yDirection = dy; }
    
    virtual void Move(uint16_t time) { x += xDirction * speed * time * 0.001; y += yDirection * speed * time * 0.001; };

    inline double  GetSpeed() { return speed; }
    inline double GetDirectionX() { return  xDirction; }
    inline double GetDirectionY() { return  yDirection; }
    virtual void __fastcall Accept(Visitor& v) {}
protected:

    double speed;
    double xDirction, yDirection;

};

