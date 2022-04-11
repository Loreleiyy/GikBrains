#pragma once

#include "DynamicObject.h"

class SBomber;
class DynamicObject;


class Bomb : public DynamicObject
{
public:
	
	static const uint16_t BombCost = 10; // стоимость бомбы в очках

	void Draw() const override;
	void __fastcall Accept(Visitor& v) ;
	void __fastcall CheckDestoyableObjects(SBomber& game);
	
private:
	
};

