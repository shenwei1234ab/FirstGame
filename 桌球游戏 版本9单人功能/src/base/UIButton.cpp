#include "UIButton.h"
#include "UISystem.h"
#include "tinyxml.h"
#include "Texture.h"
#include "TextureManager.h"
#include "Vector2.h"

UIButton::UIButton()
: m_mouseHover(false)
, m_mouseDown(false)
,m_Texture(0)
,m_eventHandler(0)
{

}

UIButton::~UIButton()
{

}

void UIButton::Init(TiXmlElement* e)
{
	UIElement::Init(e);
	//string转wstring
	std::string texStr;
	if(e->QueryStringAttribute("texture",&texStr) == TIXML_SUCCESS)
	{
		wchar_t buf[512];
		int ret = swprintf(buf,L"%S",texStr.c_str());
		std::wstring texWStr;
		texWStr.assign(buf,ret);
		//查询贴图
		m_Texture = TextureManager::instance().loadFromPNG(texWStr.c_str());
		
	}
}


void UIButton::OnMouseLeftButtonUp(const Vector2 &pt, UISystem *pUI)
{
	if (!m_mouseDown)
	{
		return;
	}
	m_mouseDown = false;
	pUI->ReleaseMouse(this);
	if (m_mouseHover)
	{
		//执行回调函数
		if (m_eventHandler && m_Funtions[0])
		{
			int i = 1;
			//(m_eventHandler->*m_pfnPressUp)(this);
			m_Funtions[0](this);
		}
	}
}
void UIButton::OnMouseEnter() 
{
	m_mouseHover = true;
	if (m_eventHandler && m_Funtions[1])
	{
		m_Funtions[1](this);
	}
}


void UIButton::OnMouseLeave() 
{
	m_mouseHover = false;
	if (m_eventHandler && m_Funtions[2])
	{
		m_Funtions[2](this);
	}
}

void UIButton::OnMouseLeftButtonDown(const Vector2 &pt,UISystem *pUI) 
{
	m_mouseDown = true;
	pUI->CaptureMouse(this);

}




void UIButton::Render()
{
	if(m_Texture)
	{
		m_Texture->bind();
		Vector2 min(0,0);
		Vector2 max(1,1);
		m_quad.setTexcoords(AABox2(min,max),m_Texture);
	}
	else
	{
		bosi::setTexture(0);
		m_quad.SetColor(m_color);
	}
	m_quad.Render();
}



void UIButton::OnCleanDirty()
{
	UIElement::OnCleanDirty();
	m_quad.SetLocation(m_WorldBox);
}

void UIButton::Update(float deltaTime)
{
	UIElement::Update(deltaTime);
}



