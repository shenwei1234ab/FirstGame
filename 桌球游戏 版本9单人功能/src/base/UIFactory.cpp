#include "UIFactory.h"
#include "UIElement.h"
#include "UIButton.h"
#include "UILabel.h"
#include <string>
#include "tinyxml.h"
#include "UIWireFrame.h"
UIFactory::UIFactory()
{

}
UIFactory::~UIFactory()
{

}

UIFactory& UIFactory::GetInstance()
{
	static UIFactory s_Fact;
	return s_Fact;
}

UIElement* UIFactory::CreateElement(const std::string &name)
{
	if(name == "WireFrame")
	{
		return new UIWireFrame();
	}
	else if (name == "Label")
	{
		return new UILabel();
	}
	else if ( name == "Button")
	{
		return new UIButton();
	} 
	return 0;
}

UIElement* UIFactory::CreateElements(TiXmlElement* root)
{
	if(!root)
	{
		return  NULL;
	}
	UIElement* p = CreateElement(root->ValueStr());
	if(!p)
	{
		std::cout<<"Unknown Element \""<<root->Value()<<"\""<<std::endl;
		return 0;
	}
	p->Init(root);
	for(TiXmlElement *xml = root->FirstChildElement();xml;xml = xml->NextSiblingElement())
	{
		UIElement* child = CreateElements(xml);
		if(child)
		{
			p->AddChild(child);
			child->release();
		}
	}
	return p;
}
