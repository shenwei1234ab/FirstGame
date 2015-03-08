#pragma once

#include "b2d.h"

#include "RefCounted.h"
#include "Vector2.h"

class Texture : public RefCounted {
public:
	Texture(bosi::Texture tex) : m_texture(tex) {}
	virtual ~Texture() {
		if (m_texture) {
			bosi::freeTexture(m_texture);
			m_texture = 0;
		}
	}
	
	Vector2 size() const {
		bosi::SizeI t = bosi::getTextureSize(m_texture);
		return Vector2((float)t.width, (float)t.height);
	}

	Vector2 contentSize() const {
		bosi::SizeI t = bosi::getTextureContentSize(m_texture);
		return Vector2((float)t.width, (float)t.height);
	}

	void bind() 
	{
		bosi::setTexture(m_texture);
	}

	const bosi::Texture GetTexture()const 
	{
		return m_texture;
	}

private:
	bosi::Texture m_texture;
};

typedef RefCountedPtr<Texture> TexturePtr;


