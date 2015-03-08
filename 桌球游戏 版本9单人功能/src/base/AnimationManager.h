#pragma once
#include "stdafx.h"
#include "Animation.h"
class AnimationManager
{
public :
	static AnimationManager& GetInstance();
	//根据动作文件的名字查找指定的动作 :参数： 文件名字
	//返回值   ：0：文件打开失败
	Animation*  Load(const std::string  &strName);
	~AnimationManager();
private:
	AnimationManager();
	typedef std::map<std::string ,Animation *> Animations;
	Animations m_Animations;

};