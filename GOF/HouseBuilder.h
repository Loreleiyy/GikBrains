#pragma once

#include "House.h"
#include <unordered_map>
#include <functional>

class HouseBuilder {
private:
	House* house = nullptr;
public:
	virtual ~HouseBuilder(){}
	virtual void createHouse() {
		house = new House;
	}
	virtual void constructFloor() {
		for (int i = 1; i < House::Xlook - 1; ++i) {
			house->look[House::Ylook - 1][i] = '#';
		}
	}
	virtual void constructWall() {
		for (int i = 3; i < House::Ylook; ++i) {
			house->look[i][0] = '#';
			house->look[i][House::Xlook - 1]='#';
		}
	}
	virtual void constructRoof() {
		for (int i = 0; i < House::Xlook; ++i) {
			house->look[3][i] = '#';
		}
		house->look[2][0] = '#';
		house->look[2][House::Xlook - 1] = '#';
		for (int i = 1; i < House::Xlook - 1; ++i) {
			house->look[1][i] = '#';
		}
	}
	virtual void constructThimn() {
		house->look[0][6] = '#';
		house->look[0][7] = '#';

	}

	virtual void constructWindow() {
		house->look[4][6] = '[';
		house->look[4][7] = ']';
	}
	virtual House* getResult() { return house; }
};

class HouseBuilderFull : public HouseBuilder {
private:
public:
};

class HouseBuilderWall : public HouseBuilder {
private:
	void constructRoof() {}
	void constructThimn(){}
	void constructWindow(){}
};

class HouseBuilderNoThimn : public HouseBuilder {
private:
	void constructThimn() {}
};

class HouseBuilderNOWindow : public HouseBuilder {
private:
	void constructWindow() {}
};

class HouseDirector {
private:
	std::unordered_map< uint32_t, std::function< HouseBuilder* ()> > map;
	std::shared_ptr<HouseBuilder> createPtr(int id) {
		auto it = map.find(id);
		if (it != map.end()) {
			return std::shared_ptr<HouseBuilder>{it->second()};
		}
		return nullptr;
	}
	
public:
	House* createHouse(int b) {
		std::shared_ptr<HouseBuilder> builder = createPtr(b);
		if (builder == nullptr) {
			return new House;
		}
		builder->createHouse();
		builder->constructFloor();
		builder->constructWall();
		builder->constructRoof();
		builder->constructWindow();
		builder->constructThimn();
		return (builder->getResult());
	}
	HouseDirector() {
		map.emplace(1, [] {return new HouseBuilderWall; });
		map.emplace(2, [] {return new HouseBuilderNoThimn; });
		map.emplace(3, [] {return new HouseBuilderNOWindow; });
		map.emplace(4, [] {return new HouseBuilderFull; });
	}
};