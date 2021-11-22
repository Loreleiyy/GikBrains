#pragma once
#include "Deck.h"
#include "House.h"
#include "Player.h"

class Game {
private:
	Deck deck;
	House house;
	std::vector<Player> players;
public:
	Game(const std::vector<std::string>& names);
	~Game();
	void Play();
};