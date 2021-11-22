#include <iostream>
#include <vector>

using std::cout;
using std::cin;


// 1 задание

void valid(int& number) {
	bool fail;
	do {

		fail = false;
		cout << "enter an integer " << std::endl;;
		std::cin >> number;
		if (cin.fail()) {

			std::cerr << "number not integer \n";
			cin.clear();
			cin.ignore(32767, '\n');
			fail = true;
		}
		else {
			cin.ignore(32767, '\n');
			if (cin.gcount() > 1) {
				std::cerr << "number not integer \n";
				fail = true;
			}
		}
	} while (fail);

}


// 2 задание

class Manip {
private:
    const char newLine = '\n';
public:
    friend std::ostream& operator<< (std::ostream& out, const Manip& end) {
        out << end.newLine << end.newLine;
        out.flush();
        return out;
    }    
};


/////////// Blackjack

enum Suit { hearts = 3, diamonds = 4, cross = 5, spades = 6 };

enum ValueCart {
	ace = 1, 
	two, three,	four, 
	five, six, seven, 
	eight, nine, ten,
	Jack, Queen, King
};

class Card {
private:

	Suit suit;
	ValueCart valueCart;
	bool openCart = true;
public:
	Card(Suit suit, ValueCart valueCart) {
		this->suit = suit;
		this->valueCart = valueCart;
		
	}
	void Flip() { openCart = !openCart; };
	int GetValue()const;
	friend std::ostream& operator<< (std::ostream& out, const Card& card);
};

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

// набор карт
class Hand {
protected:
	std::vector<Card*> card;
public:
	void Add(Card* card) { this->card.push_back(card); }
	void clear();
	int GetTotal() const;

};

int Hand::GetTotal() const {
	int sum = 0;
	for (int i = 0; i < card.size(); ++i) {
		if (card[i]->GetValue() == ValueCart::ace && (sum < 11)) {
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


/// /

class GenericPlayer : public Hand {
protected:
	std::string name;
public:
	GenericPlayer(const std::string& name) {
		this->name = name;
	}
	virtual bool IsHitting() const = 0;
	bool Boosted() const {
		return (GetTotal() > 21);		
	}
	void Bust() const {
		if (Boosted())
			cout << this->name << " overly many cards \n";
	}
	friend std::ostream& operator<< (std::ostream& out, const GenericPlayer& generic);

	virtual ~GenericPlayer(){}
};

std::ostream& operator<< (std::ostream& out, const GenericPlayer& generic) {
	out << generic.name << ":\t";
	std::vector<Card*>::const_iterator pcard;
	if (!generic.card.empty()) {
		for (pcard = generic.card.begin(); pcard != generic.card.end(); ++pcard) {
			out << *(*pcard) << "\t";
			// тут идёт разыменовывание итератора, а потом разыменовывание указателя на карту?
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


// колода
class Deck : public Hand {
private:
	std::vector<Card*> deck;

public:
	void Populate();
	void Shuffle();
	void Deal(Hand& aHand);
	void AddltionalCards(GenericPlayer& aGenerlcPlayer) {}
};

void Deck::Populate() {
	std::vector<Suit> su;
	su = { hearts, diamonds, cross, spades };
	std::vector<ValueCart> val;
	val = { ace, two, three, four, five, six, seven, eight, nine, ten, Jack, Queen, King };


	deck.resize(52);
	for (int i = 0; i < su.size(); ++i) {
		for (int j = 0; j < val.size(); ++j) {
			deck[((i + 1) * (j + 1)) - 1] = new Card(su[i], val[j]);
		}
	}
}

void Deck::Shuffle() {
	int l, r;
	for (int i = 0; i < 200; ++i) {
		l = rand() % deck.size();
		r = rand() % deck.size();
		std::swap(deck[l], deck[r]);
	}
}

void Deck::Deal(Hand& aHand) {
	int ra = rand() % deck.size();
	aHand.Add(deck[ra]);

	std::swap(deck[ra], deck[deck.size() - 1]);
	deck.pop_back();
}


// игрок
class Player : public GenericPlayer {
public:
	Player(const std::string name = "") : GenericPlayer(name) {}
	virtual bool IsHitting() const override;
	void Win()const { cout << this->name << "You WIN \n"; }
	void Lose()const { cout << this->name << "GAME OVER \n"; }
	void Push()const { cout << this->name << "draw \n"; }
	virtual ~Player(){}
};

bool Player::IsHitting () const {
	char sm;
	cout << "need another card? Y/n \n";
	cin >> sm;
	return (sm == 'y' || sm == 'Y');
}


// ИИ
class House : public GenericPlayer {
public:
	House() : GenericPlayer("House"){}

	virtual bool IsHitting() const override { return GetTotal() <= 16; }
	void FlipFirstCard(); 

	virtual ~House(){}
};

void House::FlipFirstCard() {
	if (!(card.empty())) {
		this->card[0]->Flip();
	}
	else {
		cout << "No card to flip! \n";
	}
}

class Game {
private:
	Deck deck;
	House house;
	std::vector<Player> players;
	void Play() {}
};

int main()
{
    Manip endll;
    int number;
	valid(number);


    cout << number << std::endl;
    cout << 14 << endll;
    cout << 13 << std::endl;
    
    
    return 0;
}