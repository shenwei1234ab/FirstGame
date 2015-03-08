#pragma once 

#include "UIElement.h"
class UIWireFrame:public UIElement
{
public:
	UIWireFrame();
	//virtual void Init(TiXmlElement* e);
	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void OnMouseEnter();
	virtual void OnMouseLeave();
	virtual void OnMouseLeftButtonDown(const Vector2 &pt);
	virtual void OnMouseLeftButtonUp(const Vector2 &pt);
	virtual void OnCleanDirty();
protected:
	Quad m_quad;
	Vector2 m_lastPos;
	bool m_mouseDown;
};