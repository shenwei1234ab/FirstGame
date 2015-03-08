#include "SceneQuad.h"


void SceneQuad::SetTexcoords(const AABox2 &rect )
{
	this->m_quad.setTexcoords(rect,m_texture.get());
}