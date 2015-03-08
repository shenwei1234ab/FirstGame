#pragma once
#include "stdafx.h"
class UIElement;
class TiXmlElement;
class UIFactory
{
public:
	~UIFactory();
	static UIFactory& GetInstance();
	UIElement* CreateElements(TiXmlElement* root);
	UIElement* CreateElement(const std::string &name);

protected:

private:
	UIFactory();
	
};