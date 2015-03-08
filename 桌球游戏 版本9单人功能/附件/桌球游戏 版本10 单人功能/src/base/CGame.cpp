#include "CGame.h"


CGame::CGame()
{

}
CGame::~CGame()
{

}

CGame& CGame::GetInstance(void)
{ 
	static CGame sGame;
	return sGame;
}


int CGame::Run(unsigned int nWidth,unsigned int nHeight,const wchar_t *pCaption,IDelegate* pDelegate )
{
	m_pDelegate =  pDelegate;
	if( ! m_pDelegate )
	{
		return -1;
	}
	if( !pCaption  ) 
	{
		return -2;
	}
	//��ʼ������
	bosi::startup(nWidth,nHeight,pCaption);
	//���ýӿ������Init
	m_pDelegate->Initialize();
	//��Ϸ��ʼ��ʱ��
	unsigned int lastTime = bosi::time();

	bosi::setMouseEventRoutine(&OnMouseEvent);
	bosi::setKeyEventRoutine(&OnKeyEvent);
	//֡ѭ��
	while(bosi::run())
	{
		unsigned int nowTime = bosi::time();
		float deltaTime = (nowTime-lastTime) * 1e-3f;
		lastTime = nowTime;
		m_pDelegate->Update(deltaTime);
		if( bosi::begin() )
		{
			bosi::clear(0xFF000000);
			m_pDelegate->Render();
			bosi::end();
		}
	}
	m_pDelegate->Final();
	bosi::cleanup();
	return 0;
}


void CGame::OnMouseEvent(const bosi::MouseEvent* pMe)
{
	GetInstance().m_pDelegate->OnMouseEvent(pMe);
}

void  CGame::OnKeyEvent(const bosi::KeyEvent *pKe)
{
	GetInstance().m_pDelegate->OnKeyEvent(pKe);
}
