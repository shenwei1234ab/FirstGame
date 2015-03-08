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
	//ɾ�����е��ʵ�
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
	//��֤������㲻��֡����Ӱ��
	while(m_timer >= KDT)
	{
		m_timer -=KDT;
		//��ʼ������
		ifUpdating = true;

		//����ÿ���ʵ����
		for(Particles::iterator it= m_particles.begin();it!= m_particles.end();++it)
		{
			(*it)->UpdateForce();
		}

		//�ʵ� ��Update����
		for(Particles::iterator it= m_particles.begin();it!= m_particles.end();++it)
		{
			(*it)->Update(KDT);
		}

		//Ҫ���м���particle�ķ����ٶȵļ���
		Contacts contacts;
		contacts.reserve(1024);

		//������ײ�Ӵ��ļ���
		for(ContactsGenerators::iterator it = m_contactsGenerators.begin();it!= m_contactsGenerators.end();++it)
		{
			//���ü̳�IContactGenerator����ײ��������GeneratorContacts�������ѷ�����ײ����ParticleContactCalculate�����������ײ����ļ���ȥ����particle�ķ����ٶ�
			(*it)->GenerateContacts(contacts);
		}



		//����particle�ķ����ٶ�
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
		//���ñ�־λ
		ifUpdating = false;
		//��������ӻ���ɾ���ڵ�
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