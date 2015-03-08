#pragma once 
#include "CNode.h"
class World;
class UISystem;
class Scene:public CNode
{
public:
	Scene();
	virtual ~Scene();
	virtual bool Initialize()=0;
	//设置物理世界
	void SetPhysicWorld(World* pWorld)
	{
		assert(pWorld);
		m_World = pWorld;
	}
	void SetUISystem(UISystem* pUI)
	{
		assert(pUI);
		m_uiSystem = pUI;
	}
	//判断是否有物理的质点
	World*  GetPhysicWorld();
	void PhicalWorldUpdate(float deltaTime);
	void UISystemUpdate(float deltaTime);
	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void OnMouseEvent(const bosi::MouseEvent *pMe)=0;
	virtual void OnKeyEvent(const bosi::KeyEvent *pKe)=0;
	virtual void AfterUpdate(float deltaTime){};
	virtual void AfterRender(){};
	virtual void Final(){};
protected:
	//物理世界
	World* m_World;
	UISystem* m_uiSystem;
};