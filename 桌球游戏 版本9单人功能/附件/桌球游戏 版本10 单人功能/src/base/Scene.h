#pragma once 
#include "CNode.h"
#include "World.h"
#include "UISystem.h"
class Scene:public CNode
{
public:
	Scene();
	virtual ~Scene();
	virtual bool Initialize()=0;
	//设置物理世界
	void SetPhysicWorld(World* pWorld);
	void SetUISystem(UISystem* pUI);
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
	WorldPtr m_World;
	UISystemPtr m_uiSystem;
};

typedef RefCountedPtr<Scene> ScenePtr;
