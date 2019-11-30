/* ********************************************************
* 프로그램명 : SceneManager.h
* 작성자 : 박병직, 1조 올박(박신형, 박경덕, 박성진, 박수현)
* 작성일 : 2017.05.31
* 프로그램 설명 : 게임의 씬들을 조절하는 프로그램입니다.
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