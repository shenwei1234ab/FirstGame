#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS
#include "UILabel.h"
#include "tinyxml.h"
#include "UISystem.h"


UILabel::UILabel():m_font(0),m_color(0xFFFFFFFF),m_DefaultFontHeight(10)
{
	
}

void UILabel::Init(TiXmlElement *e)
{
	UIElement::Init(e);
	//����Ĭ������
	//��ѯtxt����
	std::string txt;
	if(e->QueryStringAttribute("text",&txt) == TIXML_SUCCESS)
	{
		wchar_t buf[512];
		int ret = swprintf(buf,L"%S",txt.c_str());
		m_text.assign(buf,ret);
	}

	//����
	std::wstring font;
	if(e->QueryStringAttribute("font",&txt)== TIXML_SUCCESS)
	{
		wchar_t buf[512];
		int ret = swprintf(buf,L"%S",txt.c_str());
		font.assign(buf,ret);
	}
	//�����С
	e->QueryUnsignedAttribute("height",&m_DefaultFontHeight); 
	m_font = bosi::createFont(font.c_str(),m_DefaultFontHeight);
	e->QueryFloatAttribute("off_x",&m_offset.x);
	e->QueryFloatAttribute("off_y",&m_offset.y);
}

void UILabel::Render()
{
	Vector2 pt = m_WorldBox.min_corner + m_offset;
	bosi::drawText(m_font, pt.x, pt.y, m_color, m_text.c_str(), m_text.length());
	//UIElement::Render();
}
