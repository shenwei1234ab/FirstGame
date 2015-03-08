#pragma once 
#include "base\stdafx.h"
#include "base\IContactGenerator.h"
#include "base\AABox2.h"

class Ball;
class BorderCollision:public IContactGenerator
{
public:
	BorderCollision(std::vector<Ball *>&balls,const AABox2 &border);
	virtual void GenerateContacts(Contacts &contacts);
protected:
	std::vector<Ball *> & m_balls;
	AABox2 m_border;

};