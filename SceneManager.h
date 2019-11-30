/* ********************************************************
* ���α׷��� : SceneManager.h
* �ۼ��� : �ں���, 1�� �ù�(�ڽ���, �ڰ��, �ڼ���, �ڼ���)
* �ۼ��� : 2017.05.31
* ���α׷� ���� : ������ ������ �����ϴ� ���α׷��Դϴ�.
******************************************************** */

#pragma once
#include <Windows.h>

enum Scene
{
	MainScene,
	GameScene,
	LoadGameScene,
	SettingScene,
};

enum Scene GetNowScene();

void RunSceneByorder();
void ChangeScene(enum Scene sceneTarget);