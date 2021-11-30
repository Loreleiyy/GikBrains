#include "Game.h"

Game::Game(const std::vector<std::string>& names) {
	std::vector<std::string>::const_iterator iName;
	for (iName = names.begin(); iName != names.end(); ++iName) {
		players.push_back(Player(*iName));
	}
	srand(static_cast<unsigned int> (time(0)));
	deck.Populate();
	deck.Shuffle();
}

Game::~Game() {}

void Game::Play() {
	std::vector<Player>::iterator iPl;
	for (int i = 0; i < 2; ++i) {
		for (iPl = players.begin(); iPl != players.end(); ++iPl) {
			deck.Deal(*iPl);
		}
		deck.Deal(house);
	}

	house.FlipFirstCard();
	std::cout << house << "\n\n\n";
	for (iPl = players.begin(); iPl != players.end(); ++iPl) {
		std::cout << *iPl << std::endl;
	}

	for (iPl = players.begin(); iPl != players.end(); ++iPl) {
		deck.AddltionalCards(*iPl);
	}

	house.FlipFirstCard();
	std::cout << '\n' << house;
	deck.AddltionalCards(house);

	if (house.Boosted()) {
		for (iPl = players.begin(); iPl != players.end(); ++iPl) {
			if (!((*iPl).Boosted())) {
				(*iPl).Win();
			}
		}
	}
	else {
		for (iPl = players.begin(); iPl != players.end(); ++iPl) {
			if (!((*iPl).Boosted())) {
				if (iPl->GetTotal() > house.GetTotal()) {
					iPl->Win();
				}
				else if (iPl->GetTotal() < house.GetTotal()) {
					iPl->Lose();
				}
				else {
					iPl->Push();
				}
			}
		}
	}
	for (iPl = players.begin(); iPl != players.end(); ++iPl) {
		iPl->clear();
	}
	house.clear();
	deck.clear();
	deck.Populate();
	deck.Shuffle();
}