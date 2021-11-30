#pragma once
#include "Card.h"
#include <vector>
#include <iostream>

class Hand {
protected:
	std::vector<Card*> card;
public:
	void Add(Card* card);
	void clear();
	int GetTotal() const;

};
