#include "Animation.h"
#include "stdafx.h"
 Animation::Animation():fps(60)
 {
	 m_Frames.reserve(10);
 }

 bool Animation::Load(const std::string &file)
 {
	 std::wifstream fs;
	 fs.open(file.c_str(),std::ios_base::in);
	 //文件打开失败
	 if(fs.fail())
	 {
		 return false;
	 }
	 fs >> fps;
	 while(fs.good())
	 {
		 Frame frame;
		 fs >>frame.textureFile>>frame.x>>frame.y>>frame.width>>frame.height;
		 m_Frames.push_back(frame);
	 }
	 return true;
 }