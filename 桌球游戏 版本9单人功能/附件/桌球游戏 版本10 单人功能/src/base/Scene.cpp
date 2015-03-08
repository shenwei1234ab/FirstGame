#include "Scene.h"
#include "GameObject.h"
#include "CNode.h"
#include "World.h"
#include "UISystem.h"


Scene::Scene():m_World(0),m_uiSystem(0)
{

}

Scene::~Scene()
{
	//free all childNode
	if(!m_Childrens.empty())
	{
		for( Childrens::iterator it = m_Childrens.begin();it != m_Childrens.end();++it )
		{
			(*it)->release();
		}
	}
	////////////////////////
	if(m_World.get())
	{
		m_World->release();
	}
	if(m_uiSystem.get())
	{
		m_uiSystem->release();
	}

}
void Scene::SetPhysicWorld(World* pWorld)
{
		assert(pWorld);
		WorldPtr pwPtr(pWorld);
		m_World = pwPtr;
}

void Scene::SetUISystem(UISystem* pUI)
{
		assert(pUI);
		UISystemPtr uiPtr(pUI);
		m_uiSystem = uiPtr;
}


void Scene::PhicalWorldUpdate(float deltaTime)
{
	if(m_World)
	{
		m_World->Update(deltaTime);
	}
}

void Scene::UISystemUpdate(float deltaTime)
{

	if(m_uiSystem.get())
	{
		m_uiSystem->Update(deltaTime);
	}
}

void Scene::Update(float deltaTime)
{

}


void Scene::Render()
{

}

World*  Scene::GetPhysicWorld()
{
	return m_World.get();
}
