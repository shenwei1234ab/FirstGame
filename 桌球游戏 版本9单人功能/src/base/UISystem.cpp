#include "stdafx.h"
#include "UISystem.h"
#include "UIElement.h"

UISystem::UISystem():m_mouseCapture(0),m_mouseHover(0),m_root(0)
{

}

UISystem::~UISystem()
{

}

void UISystem::SetRoot(UIElement* root)
{
	assert(root);
	if( m_root )
	{
		m_root->release();
	}
	if((m_root = root))
	{
		root->addRef();
	}
}


UIElement* UISystem::GetRoot()
{
	return this->m_root;
}

void UISystem::Update(float deltaTime)
{
	if( m_root )
	{
		bosi::PointI nowPost = bosi::getMousePosition();
		UIElement *e = m_root->pick(Vector2((float)nowPost.x,(float)nowPost.y));
		if( e != m_mouseHover )
		{
			if( m_mouseHover )
			{
				m_mouseHover->OnMouseLeave();
				m_mouseHover->release();
			}
			if((m_mouseHover = e))
			{
				m_mouseHover->addRef();
				m_mouseHover->OnMouseEnter();
			}
		}
		m_root->_Update(deltaTime);
	}
}


void UISystem::Render()
{
	if( m_root)
	{
		m_root->_Render();
	}
}



bool UISystem::DispatchMouseLeftButtonDown(const Vector2 &pt)
{
	if ( !m_mouseHover)
	{
		return false;
	}
	m_mouseCapture = m_mouseHover;
	m_mouseCapture->OnMouseLeftButtonDown(pt,this);
	return true;
}

 Vector2 UISystem::_getMousePosition() 
{
	bosi::PointI pt = bosi::getMousePosition();
	return Vector2((float)pt.x, (float)pt.y);
}

bool UISystem::DispatchMouseLeftButtonUp(const Vector2 &pt)
{
	if( !m_mouseCapture )
	{
		return false;
	}
	m_mouseCapture->OnMouseLeftButtonUp(pt,this);
	m_mouseCapture = 0;
	m_mouseHover = 0;
	return true;
}


void UISystem::CaptureMouse(UIElement* e)
{
	if( m_mouseCapture )
	{
		m_mouseCapture->release();
	}
	if(m_mouseCapture = e)
	{
		m_mouseCapture->addRef();
	}
}
void UISystem::ReleaseMouse(UIElement* e)
{
	if( e&&  e == m_mouseCapture  )
	{
		m_mouseCapture->release();
		m_mouseCapture = 0;
	}
}
