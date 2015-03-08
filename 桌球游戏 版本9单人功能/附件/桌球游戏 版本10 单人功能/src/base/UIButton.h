#pragma  once
#include "UIElement.h"
#include "Quad.h"
#include "UISystem.h"
#include "Scene.h"
class UIButton:public UIElement
{
public:
	friend class MyGame;
	UIButton();
	virtual ~UIButton();
	virtual void Init(TiXmlElement* e);
	virtual void OnMouseEnter();
	virtual void OnMouseLeave();
	virtual void OnMouseLeftButtonDown(const Vector2 &pt,UISystem *pUI);
	virtual void OnMouseLeftButtonUp(const Vector2 &pt,UISystem *pUI);


	typedef void (Scene::*PFN_PRESSUP)(UIButton *sender);
	typedef void (Scene::*PFN_MOUSEMOVEIN)(UIButton *sender);
	typedef void (Scene::*PFN_MOUSEMOVEOUT)(UIButton *sender);


	void SetMouseHover(bool ifMouseHover)
	{
		m_mouseHover = ifMouseHover;
	}
	void SetMouseDown(bool ifMouseDown)
	{
		m_mouseDown = ifMouseDown;
	}

	//设置回调函数处理对象
	void SetEventHandler(Scene *handler)
	{
		m_eventHandler = handler; 
	}

#pragma region 设置回调函数指针
	void SetPressUpEvent(PFN_PRESSUP pfnPressUp)
	{
		m_pfnPressUp = pfnPressUp;
	}


	void SetMouseMoveInEvent(PFN_MOUSEMOVEIN pfnMouseIn)
	{
		m_pfnMouseIn = pfnMouseIn;
	}

	void SetMouseMoveOutEvent(PFN_MOUSEMOVEOUT pfnMouseOut)
	{
		m_pfnMouseOut = pfnMouseOut;
	}

#pragma endregion
	virtual void OnCleanDirty();
	virtual void Update(float deltaTime);
	virtual void Render();
protected:
	bool m_mouseHover;
	bool m_mouseDown;

	//函数指针
	PFN_PRESSUP  m_pfnPressUp;
	PFN_MOUSEMOVEIN m_pfnMouseIn;
	PFN_MOUSEMOVEOUT m_pfnMouseOut;



	//事件处理对象
	//Scene *m_eventHandler;

	ScenePtr m_eventHandler;
	
	Quad m_quad;
	
	//Texture* m_Texture;
	TexturePtr m_Texture;
};