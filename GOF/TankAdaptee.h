#pragma once

#include <iostream>
#include <stdint.h>
#include "MyTools.h"

using std::cout;

class TankAdaptee {
public:
	TankAdaptee() : x(0.0), y(0.0), width(0) { }
	void Paint() const {
		MyTools::SetColor(MyTools::ConsoleColor::CC_Brown);		// в методичке не было реализации
		MyTools::GotoXY(x, y - 3);								// скопировал из Tank.cpp
		cout << "    #####";
		MyTools::GotoXY(x - 2, y - 2);
		cout << "#######   #";
		MyTools::GotoXY(x, y - 1);
		cout << "    #####";
		MyTools::GotoXY(x, y);
		cout << " ###########";
	}
	bool __fastcall isInRange(double x1, double x2) const {
		const double XBeg = x + 2;
		const double XEnd = x + width - 1;

		if (x1 < XBeg && x2 > XEnd)
		{
			return true;
		}

		if (x1 > XBeg && x1 < XEnd)
		{
			return true;
		}

		if (x2 > XBeg && x2 < XEnd)
		{
			return true;
		}

		return false;
	}
	inline uint16_t GetScore() const { return score; }
	inline void SetPos(double nx, double ny) { x = nx; y = ny; }
	inline double GetY() const { return y; }
	inline double GetX() const { return x; }
	inline void SetWidth(uint16_t widthN) { width = widthN; }
	inline uint16_t GetWidth() const { return width; }
protected:
	double x, y;
	uint16_t width;
	const uint16_t score = 30;
};
