/* ******************************************************************
* 프로그램명 : main.c
* 작성자 : 박수현, 1조 올박(박신형, 박경덕, 박성진, 박병직)
* 작성일 : 2017.05.31
* 프로그램 설명 : 명탐정 코난을 기반으로 한 탐정 시뮬레이션 게임입니다.
****************************************************************** */

#include "Main_Scene.h"
#include "GameScene.h"
#include <Windows.h>

void main()
{
	fullscreen();
	_loadSetting();

	system("mode con:cols=500 lines=500");
	system("title Detective Conan"); 

	changeTextColor(WHITE);

	while (1)
	{
		RunSceneByorder();
	}
}