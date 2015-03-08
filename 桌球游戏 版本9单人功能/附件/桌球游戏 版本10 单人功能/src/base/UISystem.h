#pragma once
#include "Vector2.h"
#include "RefCounted.h"
#include "UIElement.h"

class UISystem:public RefCounted
{
public:
	UISystem();
	~UISystem();
	void SetRoot(UIElement* p);
	const UIElement* GetRoot()const 
	{
		return m_root.get();
	}
	UIElement* GetRoot();
	void Update(float deltaTime);
	void Render();
	bool DispatchMouseLeftButtonDown(const Vector2 &pt);
	bool DispatchMouseLeftButtonUp(const Vector2 &pt);
	static Vector2 UISystem::_getMousePosition();
	void CaptureMouse(UIElement* e);
	void ReleaseMouse(UIElement* e);
	
protected:
private:
	UIElementPtr m_root;
	UIElementPtr m_mouseHover,m_mouseCapture;
};
typedef RefCountedPtr<UISystem> UISystemPtr;


