/* ******************************************************************
* ���α׷��� : main.c
* �ۼ��� : �ڼ���, 1�� �ù�(�ڽ���, �ڰ��, �ڼ���, �ں���)
* �ۼ��� : 2017.05.31
* ���α׷� ���� : ��Ž�� �ڳ��� ������� �� Ž�� �ùķ��̼� �����Դϴ�.
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