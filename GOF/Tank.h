#pragma once

#include <stdint.h>
#include <vector>

#include "DestroyableGroundObject.h"
#include "Mediator.h"
class Mediator;

class Tank : public DestroyableGroundObject
{
public:
	Tank(Mediator& m);
	
	bool __fastcall isInside(double x1, double x2) const override;

	inline uint16_t GetScore() const override { return score; }

	void Draw() const override;
	Mediator& mediator;
private:
	std::vector<std::string> messages;
	const uint16_t score = 30;
};

