#include "AnimationManager.h"
AnimationManager& AnimationManager::GetInstance()
{
	static AnimationManager s_an;
	return s_an;
}

Animation*  AnimationManager::Load(const std::string  &strName)
{
	std::pair<Animations::iterator ,bool > ret =  m_Animations.insert(std::make_pair(strName,(Animation*)0));
	//����ɹ���˵�����µ�
	if(ret.second )
	{
		ret.first->second = new Animation;
		//�����ļ�ʧ��
		if(false ==  ret.first->second->Load(strName))
		{
			delete ret.first->second;
			m_Animations.erase(ret.first);
			return 0;
		}
	}
	//����ʧ�ܣ�˵��ԭ������
	ret.first->second->addRef();
	return ret.first->second;
}

AnimationManager::AnimationManager()
{

}
AnimationManager::~AnimationManager()
{
	for(Animations::iterator it = m_Animations.begin();it!= m_Animations.end();++it)
	{
		it->second->release();
	}
}
