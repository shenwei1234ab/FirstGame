#pragma once

#include "Quad.h"
#include "GameObject.h"
#include "Texture.h"
#include "AABox2.h"


class SceneQuad : public CNode 
{
public:
	SceneQuad(float  width,float  height):m_width(width),m_height(height),m_texture(0)
	{
		m_location.min_corner.x= -m_width/2;
		m_location.min_corner.y = -m_height/2;
		m_location.max_corner.x= m_width/2;
		m_location.max_corner.y = m_height/2;
	}

	void SetColor(unsigned int color)
	{
		m_quad.SetColor(color);
	}

	
	virtual void Update()
	{
	}

	virtual void Render()
	{
		if (m_texture.get()) 
		{
			m_texture->bind();
		} 
		else 
		{
			bosi::setTexture(0);
		}
		m_quad.Render();
	}


	void SetTexcoords(const AABox2 &rect );

	void SetTexture(Texture* p)
	{
		m_texture = p;
	}

	virtual void OnCleanDirty()
	{
			Vector2 p[4];
			//把物体坐标装换为世界坐标
			//Vector2 pos = this->GetPosition();
			p[0] = m_worldMatrix.transform_vector(m_location.corner_0());
			p[1] = m_worldMatrix.transform_vector(m_location.corner_1());
			p[2] = m_worldMatrix.transform_vector(m_location.corner_2());
			p[3] = m_worldMatrix.transform_vector(m_location.corner_3());
		for (int i = 0; i < 4; ++i) 
			{
				m_quad.v[i].x = p[i].x;
				m_quad.v[i].y = p[i].y;
			}
	}

protected:
	float m_width;
	float m_height;
	TexturePtr m_texture;
	Quad m_quad;

	//相对父类的位置
	AABox2 m_location;
};


typedef RefCountedPtr<SceneQuad> SceneQuadPtr;