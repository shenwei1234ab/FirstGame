#pragma once 
#include "base\Scene.h"
#include "base\SceneQuad.h"
#include "base\TextureManager.h"

class Scene2:public Scene
{
public:
	virtual bool Initialize()
	{
		SceneQuad *pBack = new SceneQuad(1024,800);
		Texture *tex = TextureManager::instance().loadFromPNG(L"res\\back2.png");
		pBack->SetTexture(tex);
		Vector2 min(0,0);
		Vector2 max(1,1);
		pBack->SetTexcoords(AABox2(min,max));
		this->AddChild(pBack);
		pBack->SetPosition(Vector2(512.F,400.F));
		return true;
	}


	virtual void Update(float deltaTime)
	{

	}

	virtual void Render()
	{

	}

	virtual void OnMouseEvent(const bosi::MouseEvent *pMe)
	{

	}

	virtual void OnKeyEvent(const bosi::KeyEvent *pKe)
	{

	}

protected:

};