#pragma once

#include <stdint.h>

#include "DestroyableGroundObject.h"

class House : public DestroyableGroundObject
{
public:
	House() {
		for (int i = 0; i < Ylook; ++i) {
			for (int j = 0; j < Xlook; ++j) {
				look[i][j] = ' ';
			}
		}
	}
	bool __fastcall isInside(double x1, double x2) const override;

	inline uint16_t GetScore() const override { return score; }

	void Draw() const override;
	friend class HouseBuilder;
	
private:
	const static int Ylook = 7;
	const static int Xlook = 14;
	char look[Ylook][Xlook];

	const uint16_t score = 40;
};

