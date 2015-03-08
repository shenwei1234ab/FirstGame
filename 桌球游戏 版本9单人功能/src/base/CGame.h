#pragma once
#include "stdafx.h"

//��Ϸ��ͨ�ÿ����,����
class CGame
{
public:	
	//����ӿ�
	class IDelegate
	{
	public://��ʼ��
		virtual bool Initialize()=0;
		virtual void Render(){};
		virtual void Update(float fDeltaTime){};
		virtual void Final(void){};
		//����¼�
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