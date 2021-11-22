#pragma once
#include "GenericPlayer.h"

class House : public GenericPlayer {
public:
	House();

	virtual bool IsHitting() const override;
	void FlipFirstCard();

	virtual ~House() {}
};