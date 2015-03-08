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
	//������������
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
	//�ж��Ƿ���������ʵ�
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
	//��������
	World* m_World;
	UISystem* m_uiSystem;
};