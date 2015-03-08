#pragma once
#include "base\IContactGenerator.h"

//���������ײ���

class Ball;
class BallCollision:public IContactGenerator
{
public:
	BallCollision(std::vector<Ball *> &balls);
	virtual void GenerateContacts(Contacts &contacts);
	
	static void OnContacts(std::vector<Ball *> &FistBalls,std::vector<Ball *> &SecondBalls);
	
protected:
	std::vector<Ball *> &m_balls;
};