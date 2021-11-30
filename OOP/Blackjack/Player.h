#pragma once
#include "GenericPlayer.h"

class Player : public GenericPlayer {
public:
	Player(const std::string name = "") : GenericPlayer(name) {}
	virtual bool IsHitting() const override;
	void Win()const;
	void Lose()const;
	void Push()const;
	virtual ~Player() {}
};