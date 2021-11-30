#pragma once
#include "Hand.h"


class GenericPlayer : public Hand {
protected:
	std::string name;
public:
	GenericPlayer(const std::string& name);
	virtual bool IsHitting() const = 0;
	bool Boosted() const;
	void Bust() const;
	friend std::ostream& operator<< (std::ostream& out, const GenericPlayer& generic);

	virtual ~GenericPlayer() {}
};