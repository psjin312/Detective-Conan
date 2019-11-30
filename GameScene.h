/* ****************************************************************
* ���α׷��� : GameScene.h
* �ۼ��� : �ڽ���, 1�� �ù�(�ں���, �ڰ��, �ڼ���, �ڼ���)
* �ۼ��� : 2017.05.31
* ���α׷� ���� : ���α׷��� ���������� ���Ǵ� �Լ����� �����Դϴ�.
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

