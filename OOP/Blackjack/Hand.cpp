#include "Hand.h"



int Hand::GetTotal() const {
	int sum = 0;
	for (int i = 0; i < card.size(); ++i) {
		if (card[i]->GetValue() == Card::ValueCart::ace && (sum < 11)) {
			sum += static_cast<int>(card[i]->GetValue()) + 10;
		}
		else {
			sum += static_cast<int>(card[i]->GetValue());
		}
	}
	return sum;
}

void Hand::clear() {
	for (int i = 0; i < card.size(); ++i) {
		delete card[i];
		card[i] = nullptr;
	}
	card.clear();

}

void Hand::Add(Card* card) { 
	this->card.push_back(card);
}