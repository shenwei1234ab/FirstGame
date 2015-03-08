#pragma once
#include "stdafx.h"
#include "Vector2.h"
#include "AABox2.h"
#include "Vector2.h"
#include "Quad.h"
#include "CNode.h"
class TiXmlElement;
class UISystem;


class UIElement : public CNode
{
public:
	
	UIElement();
	virtual ~UIElement();
	virtual void Init(TiXmlElement* e);
	virtual void Update(float deltaTime){};
	virtual void Render(){};
	virtual bool Contains(const Vector2 &point);
	virtual void  OnCleanDirty();

	virtual void OnMouseEnter(){}
	virtual void OnMouseLeave(){}
	virtual void OnMouseLeftButtonDown(const Vector2 &pt,UISystem *pUI){}
	virtual void OnMouseLeftButtonUp(const Vector2 &pt,UISystem *pUI){}
	virtual void OnBoundingBoxUpdated(){};
	std::string& GetName()
	{
		return m_name;
	}

	void SetPosition(const Vector2 &pos);
	void SetSize(const Vector2 &size);

	//�������ֺ�Ԫ��ָ��Ķ�Ӧ
	void BuildNameElementMap(std::map<std::string,UIElement*>&result);


	const Vector2& GetPosition()const
	{
		return m_position;
	}

	const Vector2& GetSize()const
	{
		return m_size;
	}


	const AABox2& GetBoundingBox()const
	{
		return m_boundingBox;
	}

	UIElement* pick(const Vector2 &pt);


protected:
	
	//��¼��Ը��ڵ��λ��
	Vector2 m_position;
	//��¼��Ը��ڵ�Ĵ�С
	Vector2 m_size;


	//������ϵ�еĸ������λ��
	AABox2 m_boundingBox;
	//����������Ϸ�е�����
	AABox2 m_WorldBox;

	bool m_boundingBoxDirty;
	//id
	std::string m_name;	
	 unsigned int m_color ;
};
typedef RefCountedPtr<UIElement> UIElementPtr;




