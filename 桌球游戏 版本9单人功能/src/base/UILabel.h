#pragma once
#include "stdafx.h"
#include "UIElement.h"
#include "UIButton.h"

class UILabel:public UIElement
{
public:
	UILabel();
	virtual void Init(TiXmlElement *e);
	virtual void Render();

	void SetFont(bosi::Font font)
	{	m_font = font;
	}
	void SetColor(unsigned int color)
	{
		m_color = color;
	}
	void SetText(const std::wstring &text)
	{
		m_text = text;
	}

	void SetOffset(const Vector2 &offset)
	{
		m_offset = offset;
	}

	virtual void OnMouseEnter()
	{

		std::cout<<"Label Enter"<<std::endl;
	}

	virtual void OnMouseLeftButtonUp(const Vector2 &pt,UISystem *pUI)
	{
		//ÊÇ·ñ¸¸Ç×ÊÇbutton
		if(m_pParent)
		{
			UIButton *pButton =  dynamic_cast<UIButton *>(m_pParent);
			if(pButton)
			{
				pButton->SetMouseDown(true) ;
				pButton->SetMouseHover(true);
				pButton->OnMouseLeftButtonUp(pt,pUI);
			}
		}
	}
protected:
	unsigned int m_DefaultFontHeight;
	bosi::Font m_font;
	std::wstring m_text;
	unsigned int m_color;
	Vector2 m_offset;
};