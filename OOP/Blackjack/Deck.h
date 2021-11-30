#pragma once
#include "GenericPlayer.h"


class Deck : public Hand {
private:
	std::vector<Card*> deck;

public:
	Deck();
	void Populate();
	void Shuffle();
	void Deal(Hand& aHand);
	void AddltionalCards(GenericPlayer& player);
	virtual ~Deck();
};
