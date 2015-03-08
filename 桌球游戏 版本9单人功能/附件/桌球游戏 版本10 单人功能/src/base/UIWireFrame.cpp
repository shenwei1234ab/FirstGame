#include "UIWireFrame.h"

 UIWireFrame::UIWireFrame()
:m_mouseDown(false)
{
	m_quad.SetColor(0xFFFFFFFF);
}



void UIWireFrame::Update(float deltaTime)
{

}

void UIWireFrame::Render()
{
	bosi::setTexture(0);
	m_quad.RenderWireFrame();
}


void UIWireFrame::OnMouseEnter()
{
	
}
void UIWireFrame::OnMouseLeave()
{
	
}



void UIWireFrame::OnMouseLeftButtonDown(const Vector2 &pt)
{
	m_mouseDown = true;
	m_lastPos = pt;
	this->m_quad.SetColor(0xFFFFFF00);

}

void UIWireFrame::OnMouseLeftButtonUp(const Vector2 &pt)
{
	if(m_mouseDown)
	{
		m_mouseDown = false;
	}
	this->m_quad.SetColor(0xFFFFFFFF);
}


void UIWireFrame::OnCleanDirty()
{
	UIElement::OnCleanDirty();
	m_quad.SetLocation(m_WorldBox);
}