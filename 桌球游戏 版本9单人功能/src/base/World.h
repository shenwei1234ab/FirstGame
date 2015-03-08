#pragma once 

#include "stdafx.h"
class Particle;
class IContactGenerator;
//�����߼���������е��ʵ��˶�����ײ
class World
{
public:
	World();
	~World();

	void Update(float deltaTime);
	
	//ռʱ���ȷ���m_incomingParticles��m_removedParticles��ʱ��������
	void AddParticle(Particle* p);
	void RemoveParticle(Particle* p);




	void AddContact(IContactGenerator *pc);
	void RemoveContact(IContactGenerator *pc);
	

	void SetUpdating(bool _ifUpdaing)
	{
		ifUpdating = _ifUpdaing;
	}
protected:

	void _remove(Particle* p);
	//���е��ʵ�
	typedef std::vector<Particle *>Particles;
	Particles m_particles,m_incomingParticles,m_removedParticles;

	//���е���ײ
	typedef std::vector<IContactGenerator*>ContactsGenerators;
	ContactsGenerators m_contactsGenerators;


	//ʱ�����
	float m_timer;

	//�ж��Ƿ��ʵ��ڸ��µı�־λ(����߱����߸��½ڵ���ɵĵ�������ʧЧ)
	bool ifUpdating;

	
};