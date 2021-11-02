#include <iostream>
#include <vector>
#include <ctime>
#include "Array.h"

using std::cout;
using std::endl;

// 1 всё в 1 файле для простоты

class Array {
private:
	int lenght;
	int* data;
public:
	Array() : lenght(0), data(nullptr) {}
	Array(int lenght) {
		this->lenght = lenght;
		if (lenght > 0) {
			data = new int[lenght];
		}
		else {
			data = nullptr;
		}
	}
	~Array() {
		delete data;
	}
	void clear();
	int getLength() { return lenght; }
	int& operator[](int index){
		if(index >= 0 && index < lenght)
			return data[index];
	}

	int pop_back();
	int pop_front();
	void sortArr();
	void print();
};

void Array::clear() {
	delete[] data;
	lenght = 0;
	data = nullptr;
}

int Array::pop_back() {
	int back = this->data[--lenght];

	int* data = new int[lenght];
	for (int i = 0; i < lenght; ++i) {
		data[i] = this->data[i];
	}
	delete[] this->data;
	this->data = data;
	return back;
}

int Array::pop_front() {
	int front = this->data[0];
	int* data = new int[lenght - 1];
	for (int i = 1; i < lenght; ++i) {
		data[i-1] = this->data[i];
	}
	--lenght;
	delete[] this->data;
	this->data = data;
	return front;
}

void Array::sortArr() {
	for (int i = 0; i < lenght; ++i) {
		for (int j = 1; j < lenght; ++j) {
			if (data[j - 1] > data[j]) {
				std::swap(data[j - 1], data[j]);
			}
		}
	}
}

void Array::print() {
	for (int i = 0; i < lenght; ++i) {
		cout << data[i] << ' ';
	}
	cout << endl;
}

// 2 бинарное дерео поиска

class Tree {
private:
	class Node {
	public:
		int data;
		Node* left;
		Node* right;
		Node(int data) {
			left = nullptr;
			right = nullptr;
			this->data = data;
		}
	};
	Node* head;
	int size;
	void deleteTree(Node* elem);
public:
	Tree(){
		head = nullptr;
		size = 0;
	}
	~Tree() {
		deleteTree(head);
	}
	int getSize()const { return size; }
	void push(int data);
};

void Tree::push(int data) {
	if (head == nullptr) {
		head = new Node(data);
		++size;
	}
	Node* elem = head;
	
	while (elem->data != data) {
	
		 if (data < elem->data) {
			 if (elem->left == nullptr) {
				 elem->left = new Node(data);
				 ++size;
				 return;
			 }
			 else
				 elem = elem->left;
		}
		else if (data > elem->data) {
			 if (elem->right == nullptr) {
				 elem->right = new Node(data);
				 ++size;
				 return;
			 }
			 else
				 elem = elem->right;
		}
		
	}
}

void Tree::deleteTree(Node* elem){
	if (elem != nullptr) {
		deleteTree(elem->left);
		deleteTree(elem->right);
		delete elem;
	}
}





/// Blackjack

enum Suit { hearts = 3, diamonds = 4, cross = 5, spades = 6 };

enum ValueCart {
	ace   = 1, two   = 2, three = 3,
	four  = 4, five  = 5, six   = 6,
	seven = 7, eight = 8, nine  = 9,
	ten   = 10,
	Jack  = 10, Queen = 10, King = 10
};

class Card {
private:
	
	Suit suit;
	ValueCart valueCart;
	bool openCart = false;
public:
	Card(Suit suit, ValueCart valueCart) {
		this->suit = suit;
		this->valueCart = valueCart;
	}
	void Flip() { openCart = !openCart; };
	ValueCart GetValue()const { return valueCart; }
};




class Hand {
private:
	std::vector<Card*> card;
public:
	void Add(Card* card) { this->card.push_back(card); }
	void clear();
	int GetValue();
	
};

int Hand::GetValue(){
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
private:
	std::string name;
public:
	virtual bool IsHitting() const = 0;
	bool Boosted() {
		if (GetValue() > 21)
			return true;
		else
			return false;
	}
	void Bust()  { 
		if (Boosted())
			cout << this->name << " overly many cards \n";	
	}
};

class Deck : public Hand{
private:
	std::vector<Card*> deck;
	
public:
	void Populate();
	void Shuffle();
	void Deal(Hand& aHand);
	void AddltionalCards(GenericPlayer& aGenerlcPlayer){}
};

void Deck::Populate() {
	std::vector<Suit> su;
	su = { hearts, diamonds, cross, spades };
	std::vector<ValueCart> val;
	val = { ace, two, three, four, five, six, seven, eight, nine, ten, Jack, Queen, King };

	
	deck.resize(52);
	for (int i = 0; i < su.size(); ++i) {
		for (int j = 0; j < val.size(); ++j) {
			deck[((i+1)*(j+1))-1] = new Card(su[i], val[j]); 
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

	std::swap(deck[ra], deck[deck.size() -1]);
	deck.pop_back();
}

class Player : public GenericPlayer {
	void Win()const{}
	void Lose()const{}
	void Push()const{}
};

class House : public GenericPlayer {
	virtual bool IsHitting() const{}
	void FlipFirstCard(){}
};

class Game {
private:
	Deck deck;
	House house;
	std::vector<Player> players;
	void Play(){}
};

//
void printArr(std::vector<int> arr, int SZ) {
	for (int i = 0; i < SZ; ++i) {
		cout << arr[i] << ' ';
	}
	cout << endl;
}




int main()
{
	// 1
	Array a(20);
	for (int i = 0; i < a.getLength(); ++i) {

		a[i] = rand() % 30;
	}
	a.print();
	a.sortArr();
	a.print();
	cout << a.pop_back() << ' ' << a.getLength() << ' ' << a.pop_front() << ' ' << a.getLength() << endl;
	// 2

	srand(time(0));
	
	std::vector<int> arr;
	arr.resize(30);

	for (int i = 0; i < arr.size(); ++i) {
		
		arr[i] = rand() % 30;
	}
	printArr(arr, arr.size());
	Tree bin;
	for (int i = 0; i < arr.size(); ++i){
		bin.push(arr[i]);
	}
	cout << bin.getSize() << endl;
	
    return 0;
}

