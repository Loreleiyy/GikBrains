#pragma once

#include "DestroyableGroundObject.h"
#include "TankAdaptee.h"

class AdapterTank : public DestroyableGroundObject {
private:
	TankAdaptee tank;
public:
	
	void SetPos(double nx, double ny) override { tank.SetPos(nx, ny); }
	uint16_t GetWidth()  { return tank.GetWidth(); }
	void Draw() const override { tank.Paint(); }
	bool __fastcall isInside(double x1, double x2) const override { return tank.isInRange(x1, x2); }
	inline uint16_t GetScore() const override { return tank.GetScore(); }
	inline double GetY() const override { return tank.GetY(); }
	inline double GetX() const override { return tank.GetX(); }
	inline void SetWidth(uint16_t widthN) override { tank.SetWidth(widthN); }
	
};