#include "BallCollision.h"
#include "Ball.h"
#include "base\ParticleContactCalculate.h"
BallCollision::BallCollision(std::vector<Ball *> &balls)
: m_balls(balls) 
{

}




//�ж���ײ����ִ��OnContact����
 void BallCollision::OnContacts(std::vector<Ball *> &FistBalls,std::vector<Ball *> &SecondBalls)
 {
	 typedef std::vector<Ball *> Balls;
	 for(Balls::iterator itFir = FistBalls.begin();itFir != FistBalls.end(); ++itFir)
	 {
		 for(Balls::iterator itSed = SecondBalls.begin();itSed != SecondBalls.end(); ++itSed)
		 {
			 Ball *b0 = *itFir, *b1 = *itSed;
			float r = b0->GetRadius() + b1->GetRadius() ;
			Vector2 d = b1->GetLocalPosition() - b0->GetLocalPosition();
			//Vector2 d = b1->GetPosition()-b1->GetPosition();
			float len = d.normalize();
			if (len <= r) 
			{
				(*itFir)->OnContact(*itSed);
				(*itSed)->OnContact(*itFir);
			}
		 }
	 }
 }


//�ж���ײ������contact�У���������ٶȣ�
void BallCollision::GenerateContacts(Contacts &contacts)
{
	if (m_balls.size() <= 1) 
	{
		return ;
	}
	//������������m_balls����
	for (std::vector<Ball *>::iterator first = m_balls.begin(), last = --m_balls.end(); first != last; ++first) 
	{
		for (std::vector<Ball *>::iterator it = first + 1; it != m_balls.end(); ++it) {
			Ball *b0 = *first, *b1 = *it;
			float r = b0->GetRadius() + b1->GetRadius() ;
			//Vector2 d = b1->GetParticle()->GetPosition() - b0->GetParticle()->GetPosition();
			Vector2 d = b1->GetLocalPosition() - b0->GetLocalPosition();
			
			float len = d.normalize();
			//�Ƿ������ײ
			if (len <= r) 
			{
				//������������ٶȵ�������
				ParticleContactCalculate c;
				c.Init(b0->GetParticle(), b1->GetParticle(), d);
				contacts.push_back(c);
			}
		}
	}
}


