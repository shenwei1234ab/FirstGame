#pragma once
#include "stdafx.h"
#include "RefCounted.h"
struct  Frame
{
	//贴图文件的名字
	std::wstring textureFile;
	//长宽高
	int width;
	int height;
	//坐标
	int x;
	int y;
};

struct Animation: RefCounted
{
	//每秒的帧数
	int fps;
	typedef std::vector<Frame > Frames;
	Frames m_Frames;

	Animation();
	bool Load(const std::string &file);
};


