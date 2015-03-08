#pragma once 

#include "stdafx.h"
#include "Matrix3x2.h"
#include "RefCounted.h"

class CNode :public RefCounted
{
public:
	friend class Scene;
	CNode();
	virtual ~CNode();

	CNode* GetParent()const 
	{
		return m_pParent;
	}

	void AddChild(CNode *pChild);
	void RemoveChild(CNode *pChild);
	void RemoveAllChild();

	void SetPosition(const Vector2 &pos);

	//������������λ��
	const Vector2 & GetWorldPosition()const
	{
		return m_worldMatrix.r3;
	}

	//������Ը��ڵ��λ��
	 const Vector2 & GetPosition()const 
	 {
		 return m_localMatrix.r3;
	 }

	void SetScale(const Vector2 &scale);
	const Vector2 & GetScale()const 
	{
		return m_scale;
	}

	void SetRotate(float fRadDegree);

	float GetDegree()const 
	{
		return m_rotation;
	}

	void SetVisible(bool visible)
	{
		this->m_visible = visible;
	}
	void SetEnable(bool enable)
	{
		this->m_enable = enable;
	}

	//�ڵ��Ƿ�ɼ�
	bool IsVisible()const 
	{
		return m_visible;
	}
	//�ڵ��Ƿ�����
	bool IsEnable()const 
	{
		return m_enable;
	}
	// ������λ������״̬���任localMatrix,����m_worldMatrix��
	void _CleanDirty();

	//�ӿڶ���
	virtual void Update(float deltaTime){};
	//������λ�ƣ���ת������ʱҪ���еĴ���
	virtual void  OnCleanDirty(){};
	virtual void Render(){};

	void _Update(float deltaTime);
	void _Render();
protected:
	//����
	CNode * m_pParent;
	typedef std::list<CNode *> Childrens;
	Childrens m_Childrens;

	//��С����Ը��ڵ㣩
	Vector2 m_scale;

	//��ת ����Ը��ڵ㣩
	float m_rotation;

	//��Ը��ڵ�ľ���任
	Matrix3x2 m_localMatrix;

	//�������ľ���任
	Matrix3x2 m_worldMatrix;

	//�Ƿ����
	bool m_enable;
	//�Ƿ�ɼ�
	bool m_visible;

	//��λ���Ƿ���Ը��ڵ㷢��λ�ƣ���ת������
	enum
	{
		_d_local = 1,
		_d_world = 2,
	};

	unsigned int m_dirty;
};