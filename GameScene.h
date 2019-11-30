/* ****************************************************************
* 프로그램명 : GameScene.h
* 작성자 : 박신형, 1조 올박(박병직, 박경덕, 박성진, 박수현)
* 작성일 : 2017.05.31
* 프로그램 설명 : 프로그램에 전반적으로 사용되는 함수들의 집합입니다.
**************************************************************** */

#pragma once
#include "Util.h"

typedef struct
{
	char TextFileName[50];
	char ImageFileName[50];
	int nextSceneCount;
	int * nextScene;
}Scene;

void InitGameScene();
void SetGameOrder(char * str);
int BackAndSave(int key);
void UpdateGameScene();
void SceneRunning();
void InputWait();
void RenderGameScene();

