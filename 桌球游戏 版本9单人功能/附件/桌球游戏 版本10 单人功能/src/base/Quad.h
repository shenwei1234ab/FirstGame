#pragma once
#include "stdafx.h"
#include "AABox2.h"
#include "Texture.h"
struct Quad
{
	bosi::Vertex v[4];
	
	void Render()
	{
		static unsigned short s_indices[] = {0, 1, 2, 0, 2, 3};
		bosi::draw(bosi::kTriangles, 2, v, 4, s_indices);
	}

	void RenderWireFrame() 
	{
		static unsigned short s_indices[] = {0, 1, 1, 2, 2, 3, 3, 0};
		bosi::draw(bosi::kLines, 4, v, 4, s_indices);
	}

	void SetColor(unsigned int color)
	{
		for (int i = 0; i < 4; ++i) {
			v[i].color = color;
		}
	}

	void SetLocation(const AABox2 &rect) 
	{
		v[0].x = rect.min_corner.x;
		v[0].y = rect.min_corner.y;
		v[1].x = rect.max_corner.x;
		v[1].y = rect.min_corner.y;
		v[2].x = rect.max_corner.x;
		v[2].y = rect.max_corner.y;
		v[3].x = rect.min_corner.x;
		v[3].y = rect.max_corner.y;
	}

	

	void setTexcoords(const AABox2 &rect,Texture *pText) 
	{
		bosi::Texture texture = pText->GetTexture();
		float  RateHeight=(float)(bosi::getTextureContentSize(texture).height)/(float)(bosi::getTextureSize(texture).height);
	float RateWidth=(float)(bosi::getTextureContentSize(texture).width)/(float)(bosi::getTextureSize(texture).width);	

		v[0].u = rect.min_corner.x*RateWidth;
		v[0].v = rect.min_corner.y*RateHeight;
		v[1].u = rect.max_corner.x*RateWidth;
		v[1].v = rect.min_corner.y*RateHeight;
		v[2].u = rect.max_corner.x*RateWidth;
		v[2].v = rect.max_corner.y*RateHeight;
		v[3].u = rect.min_corner.x*RateWidth;
		v[3].v = rect.max_corner.y*RateHeight;
	}


};