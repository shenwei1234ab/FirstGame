#pragma  once
#include "UIElement.h"
#include "Quad.h"
#include "UISystem.h"
#include "Scene.h"
#include <functional>

class EvenetHandler
{

};

class UIButton:public UIElement
{
public:
	UIButton();
	virtual ~UIButton();
	virtual void Init(TiXmlElement* e);
	virtual void OnMouseEnter();
	virtual void OnMouseLeave();
	virtual void OnMouseLeftButtonDown(const Vector2 &pt,UISystem *pUI);
	virtual void OnMouseLeftButtonUp(const Vector2 &pt,UISystem *pUI);




	void SetMouseHover(bool ifMouseHover)
	{
		m_mouseHover = ifMouseHover;
	}
	void SetMouseDown(bool ifMouseDown)
	{
		m_mouseDown = ifMouseDown;
	}

	//设置回调函数处理对象
	void SetEventHandler(EvenetHandler *handler)
	{
		m_eventHandler = handler; 
	}

#pragma region 设置回调函数指针
	/*void SetPressUpEvent(PFN_PRESSUP pfnPressUp)
	{
		m_pfnPressUp = pfnPressUp;
	}*/

	void SetPressUpEvent(std::function<void(UIButton *pSender)> funObj)
	{
		m_Funtions[0] = funObj;
	}


	void SetMouseMoveInEvent(std::function<void(UIButton *pSender)> funObj)
	{
		m_Funtions[1] = funObj;
	}

	void SetMouseMoveOutEvent(std::function<void(UIButton *pSender)> funObj)
	{
		m_Funtions[2] = funObj;
	}

	

#pragma endregion
	virtual void OnCleanDirty();
	virtual void Update(float deltaTime);
	virtual void Render();
protected:
	bool m_mouseHover;
	bool m_mouseDown;

	//函数对象数组
	std::function<void(UIButton *pSender)>  m_Funtions[3];


	//处理鼠标弹起的对象
	EvenetHandler *m_eventHandler;
	//处理鼠标移进的对象
	
	Quad m_quad;
	Texture* m_Texture;
};