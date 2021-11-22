#include "Deck.h"
#include <algorithm>

void Deck::Populate() {

	clear();


	deck.resize(52);
	for (int s = Card::hearts; s <= Card::spades; ++s) {
		for (int r = Card::ace; r < Card::King; ++r) {
			Add(new Card(static_cast<Card::Suit> (s), static_cast<Card::ValueCart> (r)));
		}
	}
}

void Deck::Shuffle() {
	std::random_shuffle(card.begin(), card.end());
}

void Deck::Deal(Hand& hand) {
	if (!card.empty()) {
		hand.Add(card.back());
		card.pop_back();		
	}
	else {
		std::cout << "Out of cards. Unable to deal. \n";
	}
}

void Deck::AddltionalCards(GenericPlayer& player) {
	std::cout << '\n';
	while (!(player.Boosted()) && player.GetTotal() != 21 && player.IsHitting()) {
		Deal(player);
		std::cout << player << std::endl;
		if (player.Boosted()) {
			player.Bust();
		}
	}
}

Deck::Deck() {
	card.reserve(52);
	Populate();
}

Deck::~Deck(){}