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

	//返回世界的左边位置
	const Vector2 & GetWorldPosition()const
	{
		return m_worldMatrix.r3;
	}

	//返回相对父节点的位置
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

	//节点是否可见
	bool IsVisible()const 
	{
		return m_visible;
	}
	//节点是否有用
	bool IsEnable()const 
	{
		return m_enable;
	}
	// 处理脏位（根据状态量变换localMatrix,跟新m_worldMatrix）
	void _CleanDirty();

	//接口定义
	virtual void Update(float deltaTime){};
	//当发生位移，旋转，缩放时要进行的处理
	virtual void  OnCleanDirty(){};
	virtual void Render(){};

	void _Update(float deltaTime);
	void _Render();
protected:
	//处理
	CNode * m_pParent;
	typedef std::list<CNode *> Childrens;
	Childrens m_Childrens;

	//大小（相对父节点）
	Vector2 m_scale;

	//旋转 （相对父节点）
	float m_rotation;

	//相对父节点的矩阵变换
	Matrix3x2 m_localMatrix;

	//相对世界的矩阵变换
	Matrix3x2 m_worldMatrix;

	//是否可用
	bool m_enable;
	//是否可见
	bool m_visible;

	//脏位，是否相对父节点发生位移，旋转，缩放
	enum
	{
		_d_local = 1,
		_d_world = 2,
	};

	unsigned int m_dirty;
};