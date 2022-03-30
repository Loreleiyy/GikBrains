#pragma once

#include "Plane.h"
#include <vector>

class AbstractCommand{
public:
	virtual void Execute() = 0;
	virtual ~AbstractCommand(){}
};

class ComDeleteDynamic : public AbstractCommand {
private:
	DynamicObject* pObj;
	std::vector<DynamicObject*> &vecDynamicObj;
public:
	ComDeleteDynamic(DynamicObject* Obj, std::vector<DynamicObject*> &vec) : vecDynamicObj(vec), pObj(Obj) {}

	void Execute() override;
};

class ComDeleteStatic : public AbstractCommand {
private:
	GameObject* pObj;
	std::vector<GameObject*> &vecStaticObj;
public:
	ComDeleteStatic(GameObject* Obj, std::vector<GameObject*> &vec) : pObj(Obj), vecStaticObj(vec) {}

	void Execute() override;
};

class ComDropBomb : public AbstractCommand {
private:
	const Plane* plane;
	std::vector<DynamicObject*> &vecDynamicObj;
	uint16_t bombsNumber;
public:
	ComDropBomb(const Plane* p, std::vector<DynamicObject*> &vec, uint16_t bombs) : plane(p), vecDynamicObj(vec), bombsNumber(bombs) {}

	void Execute() override;
};