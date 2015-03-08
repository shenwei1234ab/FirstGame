#pragma once
#include "Vector2.h"

class UIElement;

class UISystem
{
public:
	UISystem();
	~UISystem();
	void SetRoot(UIElement* p);
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

	UIElement* m_root;
	UIElement *m_mouseHover,*m_mouseCapture;
};



