/* ********************************************************
* 프로그램명 : SceneManager.c
* 작성자 : 박병직, 1조 올박(박신형, 박경덕, 박성진, 박수현)
* 작성일 : 2017.05.31
* 프로그램 설명 : 게임의 씬들을 조절하는 프로그램입니다.
******************************************************** */

#include "SceneManager.h"
#include "SettingScene.h"

// 현재 사용되는 장면
enum Scene sceneOrder = MainScene;

// 현재 사용되는 장면에 따라 실행되는 함수.
void RunSceneByorder()
{
	switch (sceneOrder)
	{
		case MainScene:
			InitMainScene();
			RenderMainScene();
			UpdateMainScene();
			break;

		case GameScene:
			InitGameScene();
			RenderGameScene();
			UpdateGameScene();
			break;

		case LoadGameScene:
			InitGameScene();
			RenderGameScene();
			UpdateGameScene();
			break;

		case SettingScene:
			InitSettingScene();
			RenderSettingScene();
			UpdateSettingScene();
			break;

		default:
			break;
	}
}

// 장면을 바꿔줍니다.
void ChangeScene(enum Scene sceneTarget)
{
	system("cls");
	sceneOrder = sceneTarget;
}


enum Scene GetNowScene()
{
	return sceneOrder;
}