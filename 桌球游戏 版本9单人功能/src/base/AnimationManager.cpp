#include "AnimationManager.h"
AnimationManager& AnimationManager::GetInstance()
{
	static AnimationManager s_an;
	return s_an;
}

Animation*  AnimationManager::Load(const std::string  &strName)
{
	std::pair<Animations::iterator ,bool > ret =  m_Animations.insert(std::make_pair(strName,(Animation*)0));
	//插入成功，说明是新的
	if(ret.second )
	{
		ret.first->second = new Animation;
		//载入文件失败
		if(false ==  ret.first->second->Load(strName))
		{
			delete ret.first->second;
			m_Animations.erase(ret.first);
			return 0;
		}
	}
	//插入失败，说明原本有了
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
