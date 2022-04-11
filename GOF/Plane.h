#pragma once

#include "DynamicObject.h"

class Plane : public DynamicObject {
public:

    void Draw() const override;
    
    inline void ChangePlaneY(double dy) { yDirection += dy; }
    virtual void DrawBody() const;
    virtual void DrawWings() const;
    virtual void DrawTail() const;
private:

};

class ColorPlane : public Plane {
public:
    void DrawBody() const override;
    void DrawWings() const override;
    void DrawTail() const override;
};

class  BigPlane : public Plane {
    void DrawBody() const override;
    void DrawWings() const override;
    void DrawTail() const override;
};