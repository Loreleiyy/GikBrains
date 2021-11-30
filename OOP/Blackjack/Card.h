#pragma once
#include <iostream>




class Card {
public:
	enum Suit { hearts = 3, diamonds = 4, cross = 5, spades = 6 };

	enum ValueCart {
		ace = 1,
		two, three, four,
		five, six, seven,
		eight, nine, ten,
		Jack, Queen, King
	};
private:

	Suit suit;
	ValueCart valueCart;
	bool openCart = true;
public:
	Card(Suit suit, ValueCart valueCart);
	void Flip();
	int GetValue()const;
	friend std::ostream& operator<< (std::ostream& out, const Card& card);
};