#include "Command.h"
#include "Bomb.h"
#include "Ground.h"
#include "BombDecorator.h"

void ComDeleteDynamic::Execute() {

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

void ComDeleteStatic::Execute() {
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

void ComDropBomb::Execute() {
	if (bombsNumber > 0)
	{

		double x = plane->GetX() + 4;
		double y = plane->GetY() + 2;

		Bomb* bomb = new Bomb;
		DynamicObject* pBomb = new BombDecorator(bomb);
		
		pBomb->SetDirection(0.3, 1);
		pBomb->SetSpeed(2);
		pBomb->SetPos(x, y);
		pBomb->SetWidth(SMALL_CRATER_SIZE);

		vecDynamicObj.push_back(pBomb);

	}
}