#include "Player.h"



bool Player::IsHitting() const {
	char sm;
	std::cout << this->name << " need another card? Y/n \n";
	std::cin >> sm;
	return (sm == 'y' || sm == 'Y');
}

void Player::Win()const { 
	std::cout << this->name << " You WIN \n"; 
}
void Player::Lose()const { 
	std::cout << this->name << " GAME OVER \n"; 
}
void Player::Push()const { 
	std::cout << this->name << " draw \n"; 
}