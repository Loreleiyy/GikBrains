#include <iostream>
#include "BombDecorator.h"
#include "MyTools.h"


void BombDecorator::Move(uint16_t time) {
	bomb->Move(time * 1.6);
}

void BombDecorator::Draw() const {
	bomb->Draw();

	MyTools::GotoXY(bomb->GetX(), bomb->GetY() - 1);
	std::cout << "|";
}

void BombDecorator::SetSpeed(double sp) { bomb->SetSpeed(sp); }
void BombDecorator::SetPos(double nx, double ny) { bomb->SetPos(nx, ny); }

uint16_t BombDecorator::GetWidth() const { return bomb->GetWidth(); }

double BombDecorator::GetY() const { return bomb->GetY(); }
double BombDecorator::GetX() const { return bomb->GetX(); }
void BombDecorator::SetWidth(uint16_t widthN) { bomb->SetWidth(widthN); }

void BombDecorator::SetDirection(double dx, double dy) {
	bomb->SetDirection(dx, dy);
}