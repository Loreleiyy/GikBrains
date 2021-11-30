#include "House.h"

House::House() : GenericPlayer("House") {}


void House::FlipFirstCard() {
	if (!(card.empty())) {
		this->card[0]->Flip();
	}
	else {
		std::cout << "No card to flip! \n";
	}
}

bool House::IsHitting() const { 
	return GetTotal() <= 16; 
}