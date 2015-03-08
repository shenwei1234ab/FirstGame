#pragma once 

#include "stdafx.h"
class Particle;
class IContactGenerator;
//物理逻辑，检测所有的质点运动和碰撞
class World
{
public:
	World();
	~World();

	void Update(float deltaTime);
	
	//占时的先放入m_incomingParticles，m_removedParticles临时的容器中
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
	//所有的质点
	typedef std::vector<Particle *>Particles;
	Particles m_particles,m_incomingParticles,m_removedParticles;

	//所有的碰撞
	typedef std::vector<IContactGenerator*>ContactsGenerators;
	ContactsGenerators m_contactsGenerators;


	//时间计数
	float m_timer;

	//判断是否质点在跟新的标志位(避免边遍历边更新节点造成的迭代器的失效)
	bool ifUpdating;

	
};