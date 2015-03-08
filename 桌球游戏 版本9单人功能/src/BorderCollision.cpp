#include "BorderCollision.h"
#include "Ball.h"
#include "base\ParticleContactCalculate.h"

BorderCollision::BorderCollision(std::vector<Ball *>&balls,const AABox2 &border):m_balls(balls),m_border(border)
{

}
	
void BorderCollision::GenerateContacts(Contacts &contacts)
{
	for( std::vector<Ball*>::iterator it =m_balls.begin();it!= m_balls.end();++it  )
	{
		const Vector2 &p = (*it)->GetParticle()->GetPosition();
		float r= (*it)->GetRadius();
		//left
		if (p.x - r <= m_border.min_corner.x) {
			ParticleContactCalculate c;
			c.Init((*it)->GetParticle(), 0, Vector2(-1, 0));
			contacts.push_back(c);
		}
		// top
		if (p.y - r <= m_border.min_corner.y) {
			ParticleContactCalculate c;
			c.Init((*it)->GetParticle(), 0, Vector2(0, -1));
			contacts.push_back(c);
		}
		// right
		if (p.x + r >= m_border.max_corner.x) {
			ParticleContactCalculate c;
			c.Init((*it)->GetParticle(), 0, Vector2(1, 0));
			contacts.push_back(c);
		}
		// bottom
		if (p.y + r >= m_border.max_corner.y) {
			ParticleContactCalculate c;
			c.Init((*it)->GetParticle(), 0, Vector2(0, 1));
			contacts.push_back(c);
		}

	}
}