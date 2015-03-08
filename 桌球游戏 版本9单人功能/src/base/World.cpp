#include "stdafx.h"
#include "World.h"
#include "Particle.h"
#include "ParticleContactCalculate.h"
#include "IContactGenerator.h"
World::World():m_timer(0.0F),ifUpdating(false)
{
	
}


World::~World()
{
	//删除所有的质点
	for(Particles::iterator it = m_particles.begin();it != m_particles.end();++it )
	{
		(*it)->release();
	}
}

void World::Update(float deltaTime)
{

#ifdef _PHICS_FRAMETEST
	static float s_timer = 0;
	static int s_count = 0;

	s_timer += deltaTime;
#endif 
	if(m_particles.empty())
	{
		return ;
	}
	m_timer +=deltaTime;
	//保证物理计算不受帧数的影响
	while(m_timer >= KDT)
	{
		m_timer -=KDT;
		//开始更新了
		ifUpdating = true;

		//更新每个质点的力
		for(Particles::iterator it= m_particles.begin();it!= m_particles.end();++it)
		{
			(*it)->UpdateForce();
		}

		//质点 的Update函数
		for(Particles::iterator it= m_particles.begin();it!= m_particles.end();++it)
		{
			(*it)->Update(KDT);
		}

		//要进行计算particle的分离速度的集合
		Contacts contacts;
		contacts.reserve(1024);

		//遍历碰撞接触的集合
		for(ContactsGenerators::iterator it = m_contactsGenerators.begin();it!= m_contactsGenerators.end();++it)
		{
			//调用继承IContactGenerator的碰撞检测子类的GeneratorContacts方法，把符合碰撞检测的ParticleContactCalculate对象放入入碰撞计算的集合去计算particle的分离速度
			(*it)->GenerateContacts(contacts);
		}



		//计算particle的分离速度
	/*for(std::list<ParticleContactCalculate>::iterator it =contacts.begin();it!= contacts.end();++it )
		{
			if( (*it).CalculateCloseSpeed()>0)
			{
				(*it).Resolve();
			}
		}	*/
		size_t count = contacts.size() *2;
		while (count--) 
		{
			float fast = 0;
			Contacts::iterator best = contacts.end();
			for (Contacts::iterator it = contacts.begin(); it != contacts.end(); ++it) 
			{
				float t = it->CalculateCloseSpeed();
				if (t > fast) 
				{
					fast = t;
					best = it;
				}
			}
			if (best != contacts.end()) 
			{
				best->Resolve();
#ifdef _PHICS_FRAMETEST
				++s_count;
#endif
			} else 
			{
				break;
			}
		};
		//重置标志位
		ifUpdating = false;
		//遍历完添加或者删除节点
		m_particles.insert(m_particles.end(),m_incomingParticles.begin(),m_incomingParticles.end());
		for(Particles::iterator it = m_removedParticles.begin();it!= m_removedParticles.end();++it)
		{
			_remove(*it);
		}
		m_incomingParticles.clear();
		m_removedParticles.clear();
	}
#ifdef _PHICS_FRAMETEST
	if (s_timer >= 1.f) {
		printf("world: time %.2f count %d | %.2f\n", s_timer, s_count, s_count / s_timer);
		s_timer = 0;
		s_count = 0;
	}
#endif
}

void World::AddParticle(Particle* p)
{
	assert(p!=NULL);
	p->addRef();
	if(ifUpdating)
	{
		m_incomingParticles.push_back(p);
	}
	else
	{
		m_particles.push_back(p);
	}
	
}



void World::RemoveParticle(Particle* p)
{
	assert(p!=NULL);
	p->addRef();
	if(ifUpdating)
	{
		m_removedParticles.push_back(p);
	}
	else
	{
		_remove(p);
	}
}


void World::AddContact(IContactGenerator *pc)
{
	pc->addRef();
	m_contactsGenerators.push_back(pc);

}

void World::RemoveContact(IContactGenerator *pc)
{
	assert(pc != NULL);
	for(ContactsGenerators::iterator it = m_contactsGenerators.begin();it!= m_contactsGenerators.end();++it)
	{
		if(*it == pc)
		{
			pc->release();
			m_contactsGenerators.erase(it);
			break;
		}
	}
}

void World::_remove(Particle* p)
{
	assert( p!= NULL);
	for ( Particles::iterator it = m_particles.begin();it!= m_particles.end();++it )
	{
		if(  *it == p )
		{
			(*it)->release();
			m_particles.erase(it);
			break;
		}
	}
}