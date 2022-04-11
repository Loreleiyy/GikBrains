#pragma once

#include <sstream>
#include "Plane.h"
#include "Bomb.h"
#include "MyTools.h"



class Visitor {
public:
	virtual void log(Plane* plane) = 0;
	virtual void log(Bomb* bomb) = 0;
	virtual ~Visitor(){}
};

class LogVisitor : public Visitor {
public:
	void log(Plane* plane) override {
		std::stringstream str;
		str << "Plane: coord X " << plane->GetX() << " Y " << plane->GetY() << " speed " << plane->GetSpeed() << " Direction " <<
			plane->GetDirectionX() << ":" << plane->GetDirectionY();
		MyTools::WriteToLog(str.str());
	}
	void log(Bomb* bomb) override {
		std::stringstream str;
		str << "Bomb: coord X " << bomb->GetX() << " Y " << bomb->GetY() << " speed " << bomb->GetSpeed() << " Direction " <<
			bomb->GetDirectionX() << ":" << bomb->GetDirectionY();
		MyTools::WriteToLog(str.str());
	}
};

