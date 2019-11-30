/* ********************************************************
* ���α׷��� : SceneManager.c
* �ۼ��� : �ں���, 1�� �ù�(�ڽ���, �ڰ��, �ڼ���, �ڼ���)
* �ۼ��� : 2017.05.31
* ���α׷� ���� : ������ ������ �����ϴ� ���α׷��Դϴ�.
******************************************************** */

#include "SceneManager.h"
#include "SettingScene.h"

// ���� ���Ǵ� ���
enum Scene sceneOrder = MainScene;

// ���� ���Ǵ� ��鿡 ���� ����Ǵ� �Լ�.
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

// ����� �ٲ��ݴϴ�.
void ChangeScene(enum Scene sceneTarget)
{
	system("cls");
	sceneOrder = sceneTarget;
}


enum Scene GetNowScene()
{
	return sceneOrder;
}