#pragma once
#include "stdafx.h"
#include "Animation.h"
class AnimationManager
{
public :
	static AnimationManager& GetInstance();
	//���ݶ����ļ������ֲ���ָ���Ķ��� :������ �ļ�����
	//����ֵ   ��0���ļ���ʧ��
	Animation*  Load(const std::string  &strName);
	~AnimationManager();
private:
	AnimationManager();
	typedef std::map<std::string ,Animation *> Animations;
	Animations m_Animations;

};