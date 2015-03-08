#pragma once
#include "stdafx.h"

//游戏的通用框架类,单例
class CGame
{
public:	
	//定义接口
	class IDelegate
	{
	public://初始化
		virtual bool Initialize()=0;
		virtual void Render(){};
		virtual void Update(float fDeltaTime){};
		virtual void Final(void){};
		//鼠标事件
		virtual void OnMouseEvent(const bosi::MouseEvent *pMe){};
		virtual void OnKeyEvent(const bosi::KeyEvent *pKe){};
	};

	static CGame& GetInstance(void);

	int Run(unsigned int nWidth,unsigned int nHeight,const wchar_t *pCaption,IDelegate* pDelegate );

protected:

private:
	CGame();
	~CGame();

	static void OnMouseEvent(const bosi::MouseEvent*pMe);
	static void  OnKeyEvent(const bosi::KeyEvent *pKe);

	IDelegate* m_pDelegate;
};