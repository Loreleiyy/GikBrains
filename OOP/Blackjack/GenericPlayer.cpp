#include "GenericPlayer.h"

std::ostream& operator<< (std::ostream& out, const GenericPlayer& generic) {
	out << generic.name << ":\t";
	std::vector<Card*>::const_iterator pcard;
	if (!generic.card.empty()) {
		for (pcard = generic.card.begin(); pcard != generic.card.end(); ++pcard) {
			out << *(*pcard) << "\t";
			
		}
		if (generic.GetTotal() != 0) {
			out << '(' << generic.GetTotal() << ')';					
		}
	}
	else {
		out << "<empty>";
	}
	return out;
}

GenericPlayer::GenericPlayer(const std::string& name) {
	this->name = name;
}

bool GenericPlayer::Boosted() const {
	return (GetTotal() > 21);
}

void GenericPlayer::Bust() const {
	if (Boosted())
		std::cout << this->name << " overly many cards \n";
}

