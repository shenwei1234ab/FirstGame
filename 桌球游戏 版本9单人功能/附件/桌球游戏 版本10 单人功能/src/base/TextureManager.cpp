#include "TextureManager.h"

TextureManager::~TextureManager() {
	for (Textures::iterator it = m_textures.begin(); it != m_textures.end(); ++it) {
		it->second->release();
	}
}

Texture * TextureManager::loadFromPNG(const std::wstring &fileName) {
	std::pair<Textures::iterator, bool> ret = m_textures.insert(Textures::value_type(fileName, (Texture *)0));
	if (ret.second) {
		bosi::Texture tex = bosi::loadTextureFromPNG(fileName.c_str());
		if (tex) {
			ret.first->second = new Texture(tex);
		} else {
			m_textures.erase(ret.first);
			return 0;
		}
	}
	Texture *p = ret.first->second;
	p->addRef();
	return p;
}

TextureManager & TextureManager::instance() {
	static TextureManager s_ins;
	return s_ins;
}