
#include <iostream>

#include "Tank.h"
#include "MyTools.h"
#include "Mediator.h"

using namespace std;
using namespace MyTools;

bool Tank::isInside(double x1, double x2) const
{
	const double XBeg = x + 2;
	const double XEnd = x + width - 1;

	if (x1 < XBeg && x2 > XEnd)
	{
		return true;
	}

	if (x1 > XBeg && x1 < XEnd)
	{
		return true;
	}

	if (x2 > XBeg && x2 < XEnd)
	{
		return true;
	}

	return false;
}

void Tank::Draw() const
{
	MyTools::SetColor(CC_Brown);
	GotoXY(x, y - 3);
	cout << "    #####";
	GotoXY(x-2, y - 2);
	cout << "#######   #";
	GotoXY(x, y - 1);
	cout << "    #####";
	GotoXY(x,y);
	cout << " ###########";
	int ind;
	ind = rand() % 5;
	if (ind < messages.size()) {
		mediator.setMessage(messages[ind]);
	}
	mediator.setPrint();
}

Tank::Tank(Mediator& m) : mediator(m) {
	messages.push_back("now you tear up!!!");
	messages.push_back("we will fight as heroes))");
	messages.push_back("I didn't understand how I got here");
	messages.push_back("you're tired of running, let's fight normally...");
	messages.push_back("Go quickly, I don't want to wait");
	
}