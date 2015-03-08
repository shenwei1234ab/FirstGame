#include "CNode.h"



CNode::CNode():
	m_pParent(0),
	m_scale(1,1),
	m_rotation(0),
	m_visible(true),
	m_dirty(0),
	m_enable(true)
{
	
}


CNode::~CNode()
{
	RemoveAllChild();
}

void CNode::_Update(float deltaTime)
{
	if(!this->IsEnable())
	{
		return;
	}
	//子类的Update函数
	Update( deltaTime);
	//判断相对位置是否改变
	_CleanDirty();
	if(m_Childrens.empty())
	{
		return ;
	}
	//递归执行
	for(Childrens::iterator it =m_Childrens.begin();it!=m_Childrens.end();++it)
	{
		(*it)->_Update(deltaTime);
	}
}



void CNode::_Render()
{
	if(!this->IsEnable())
	{
		return;
	}
	//是否可见
	if(this->IsVisible())
	{
		Render();
	}
	
	if(m_Childrens.empty())
	{
		return ;
	}
	//递归执行
	for(Childrens::iterator it =m_Childrens.begin();it!=m_Childrens.end();++it)
	{
		(*it)->_Render();
	}
}


void CNode::AddChild(CNode *pChild)
{
	assert( pChild );
	pChild->addRef();
	if( pChild->m_pParent)
	{
		pChild->m_pParent->RemoveChild(pChild);
	}
	pChild->m_pParent = this;
	m_Childrens.push_back(pChild);
}


void CNode::RemoveChild(CNode *pChild)
{
	assert( pChild );
	for(Childrens::iterator  it = m_Childrens.begin();it!=m_Childrens.end();++it)
	{
		//找到儿子了
		if( (*it) == pChild)
		{
			pChild->m_pParent  = 0;
			pChild->release();
			m_Childrens.erase(it);
			break;
		}
	}
}
void CNode::RemoveAllChild()
{
	for( Childrens::iterator it = m_Childrens.begin();it != m_Childrens.end() ;++it)
	{
		(*it)->m_pParent = 0;
		(*it)->release();
	}
}

//相对父节点位置的改变
void CNode::SetPosition(const Vector2 &pos)
{
	//直接设置平移矩阵，因为是基矢量r3的唯一影响因素
	this->m_localMatrix.r3 = pos;
	m_dirty |= _d_world;
}



void CNode::SetScale(const Vector2 &scale)
{
	m_scale = scale;
	m_dirty |= _d_local;
}

//设置旋转（顺时针为+）
void CNode::SetRotate(float fRadDegree)
{
	m_rotation = -fRadDegree;
	m_dirty |= _d_local;
}

void CNode::_CleanDirty()
{
	//是否有旋转和缩放
	if( m_dirty & _d_local )
	{
	
		float c = ::cos(m_rotation);
		float s = ::sin(m_rotation);
		m_localMatrix.r1 = Vector2(c, s) * m_scale.x;
		m_localMatrix.r2 = Vector2(-s, c) * m_scale.y;

		m_dirty |= _d_world;
	}

	//是否有旋转或者缩放或者平移
	if (m_dirty & _d_world) 
	{
		if (m_pParent) 
		{
			m_worldMatrix.make_product(m_localMatrix, m_pParent->m_worldMatrix);
		} 
		else 
		{
			m_worldMatrix = m_localMatrix;
		}

		for (Childrens::iterator it= m_Childrens.begin(); it != m_Childrens.end(); ++it) 
		{
			//通知儿子改变了
			(*it)->m_dirty |= _d_world;
		} 
		OnCleanDirty();
	}
	
}




