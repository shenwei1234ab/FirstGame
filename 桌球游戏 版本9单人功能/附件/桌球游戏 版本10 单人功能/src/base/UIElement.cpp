#define _CRT_SECURE_NO_WARNINGS
#include "UIElement.h"
#include "UISystem.h"
#include "tinyxml.h"
#include "CNode.h"

UIElement::UIElement():m_color(0XFFFFFFFF)
{

}

 UIElement::~UIElement()
 {
	 RemoveAllChild();
 }

void UIElement::Init(TiXmlElement *e)
{
	e->QueryFloatAttribute("x",&m_position.x);
	e->QueryFloatAttribute("y",&m_position.y);
	e->QueryFloatAttribute("w",&m_size.x);
	e->QueryFloatAttribute("h",&m_size.y);
	e->QueryBoolAttribute("enabled",&m_enable);
	e->QueryBoolAttribute("visibled",&m_visible);
	e->QueryStringAttribute("name",&m_name);
	//将字符串转换为unsigned int 
	std::string strColor ;
	e->QueryStringAttribute("color",&strColor);
	sscanf(strColor.c_str(),"%x", &m_color);
		//m_boundingBoxDirty = true;
		Vector2 localposMin(0,0);
		Vector2 localposMax= localposMin+m_size;
		m_boundingBox.min_corner =localposMin;
		m_boundingBox.max_corner = localposMax;
		//发生位移
		this->SetPosition(m_position);

}




//相对当前父节点发生位移，旋转，缩放时
void  UIElement::OnCleanDirty()
{
	m_WorldBox.min_corner = m_worldMatrix.transform_vector(m_boundingBox.min_corner);
	m_WorldBox.max_corner = m_worldMatrix.transform_vector(m_boundingBox.max_corner);
}


bool UIElement::Contains(const Vector2 &point) 
{
	return point >= m_WorldBox.min_corner && point < m_WorldBox.max_corner;
}

 void UIElement::SetPosition(const Vector2 &pos)
 {
	 m_position = pos;
	 CNode::SetPosition(pos);
 }

 void UIElement::SetSize(const Vector2 &size)
 {
	 m_size = size;
	 CNode::SetScale(size);
 }

 
 //拾取，遍历节点判断是否点击到某个UIElement
 UIElement * UIElement::pick(const Vector2 &pt)
 {
	 //反向遍历
	 for(Childrens::reverse_iterator iter = m_Childrens.rbegin();iter != m_Childrens.rend();++iter)
	 {
		 UIElement *pChild = static_cast<UIElement *>(*iter);
		 UIElement *e =pChild->pick(pt);
		 if( e )
		 {
			 return e;
		 }
	 }
	 if(m_enable && Contains(pt) )
	 {
		 return this;
	 }
	 return 0;
 }

 void UIElement::BuildNameElementMap(std::map<std::string,UIElement*>&result)
 {
	 if(!m_name.empty())
	 {
		  result[m_name] = this;
		  result[m_name]->addRef();
	 }
	 for(Childrens::iterator it= m_Childrens.begin();it != m_Childrens.end();++it)
	 {
		 UIElement *pChild =static_cast<UIElement*>(*it); 
		 pChild->BuildNameElementMap(result);
	 }
 }



