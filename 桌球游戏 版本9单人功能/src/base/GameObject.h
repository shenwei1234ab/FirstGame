#pragma once 
#include "RefCounted.h"
#include "CNode.h"

class GameObject:public CNode
{
public:
	virtual void Update(float deltaTime)
	{

	}

	virtual void Render()
	{

	}

	virtual ~GameObject()
	{

	}
};