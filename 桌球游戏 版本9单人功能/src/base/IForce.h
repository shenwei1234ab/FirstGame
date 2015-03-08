#pragma once 
#include "RefCounted.h"
class Particle;
class IForce:public RefCounted
{
public:
	virtual void GenerateForce(Particle *pParticle)=0;
};