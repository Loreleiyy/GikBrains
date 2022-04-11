#pragma once


#include "LevelGUI.h"

class LevelGUI;

class Mediator {
private:
	LevelGUI& level;
	
public:
	Mediator(LevelGUI& l) : level(l){}

	void setMessage(std::string str) {
		
		level.setMessage(str);
	}
	void setPrint() {
		level.popMessage();
	}
	
};