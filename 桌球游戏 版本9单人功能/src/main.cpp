#include "base\CGame.h"
#include "MyGame.h"
#include "Scene1.h"
#include "MyGame.h"
#include <Windows.h>

#ifdef _DEBUG
int main(){
#else 
	int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdline,int nCmdShow){
#endif
	return CGame::GetInstance().Run(WINDOWS_WIDTH,WINDOWS_HEIGTH,L"b2d01",&MyGame::GetInstance());
}

