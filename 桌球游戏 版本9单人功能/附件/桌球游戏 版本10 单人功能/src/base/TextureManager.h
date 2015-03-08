#pragma once

#include "Texture.h"
#include "stdafx.h"

class TextureManager {
public:
	~TextureManager();

	Texture * loadFromPNG(const std::wstring &fileName);

	static TextureManager & instance();

private:
	TextureManager() {}
	typedef std::map<std::wstring, Texture *> Textures;
	Textures m_textures;
};