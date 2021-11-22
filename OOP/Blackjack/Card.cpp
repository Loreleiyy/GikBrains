#include "Card.h"

int Card::GetValue() const {
	int val = 0;
	if (openCart) {
		val = valueCart;
		if (val > 10) {
			val = 10;
		}
	}
	return val;
}

	
std::ostream& operator<< (std::ostream& out, const Card& card) {


	const std::string RANKS[] = { "0", "A", "2", "3", "4", "5", "6", "7", "8",
		"9", "10", "J", "Q", "K" };

	if (card.openCart) {
		out << RANKS[card.valueCart] << static_cast<char> (card.suit);

	}
	else {
		out << "XX";
	}

	return out;
}

Card::Card(Suit suit, ValueCart valueCart) {
	this->suit = suit;
	this->valueCart = valueCart;

}

void Card::Flip() { 
	openCart = !openCart; 
}