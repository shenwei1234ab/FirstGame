#pragma once
#include "stdafx.h"
#include "RefCounted.h"
#include "ParticleContactCalculate.h"
//������ײ

typedef std::vector<ParticleContactCalculate> Contacts;
class IContactGenerator:public RefCounted
{
public:
	//��Ҫ���м�����ʵ���뵽ParticleContactCalculate
	virtual void GenerateContacts(Contacts &pContactCalcus)=0;
};