#pragma once
#include "stdafx.h"
#include "RefCounted.h"
#include "ParticleContactCalculate.h"
//物理碰撞

typedef std::vector<ParticleContactCalculate> Contacts;
class IContactGenerator:public RefCounted
{
public:
	//把要进行计算的质点加入到ParticleContactCalculate
	virtual void GenerateContacts(Contacts &pContactCalcus)=0;
};