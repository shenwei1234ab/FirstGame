#pragma once
#include "stdafx.h"
#include "RefCounted.h"
struct  Frame
{
	//��ͼ�ļ�������
	std::wstring textureFile;
	//�����
	int width;
	int height;
	//����
	int x;
	int y;
};

struct Animation: RefCounted
{
	//ÿ���֡��
	int fps;
	typedef std::vector<Frame > Frames;
	Frames m_Frames;

	Animation();
	bool Load(const std::string &file);
};


