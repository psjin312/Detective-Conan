/* ****************************************************************
* 프로그램명 : GameScene.c
* 작성자 : 박경덕, 1조 올박(박병직, 박신형, 박성진, 박수현)
* 작성일 : 1587.05.31
* 프로그램 설명 : 프로그램에 전반적으로 사용되는 함수들의 집합입니다.
**************************************************************** */

#include "GameScene.h"

void _setGameImage(char * str);
void _RenderImageBox();
void _RenderGameImage();
void _initSceneList();

void printClear();

void printFail();

char GameImage[47][158];

int bGameSceneInit = 0;     // 게임씬의 데이터 로드 여부
int bGameRender = 0;		// 게임씬 최초 렌더링 초기화

Scene * sceneList;

Scene nowScene;
int _order;

int bGameRun = 1;
int gameOrder;

// 게임씬의 초기화
void InitGameScene()
{
	if (bGameSceneInit == 0)
	{
		_initSceneList();
		bGameSceneInit = 1;
	}
}

// 한 번만 그려주면 되는 이미지를 그려줍니다.
void RenderGameScene()
{
	if (bGameRender == 0)
	{
		StartGameBGMusic();
		_RenderImageBox();
		_setGameImage(nowScene.ImageFileName);
		_RenderGameImage();
		bGameRender = 1;
	}
}

// 업데이트 해줍니다.
void UpdateGameScene()
{
	if (bGameRender == 1)
	{
		if (bGameRun == 1) {
			SceneRunning();
		}

		else {
			InputWait();
		}
	}
}

// 게임에 사용할 이미지를 설정합니다.
void _setGameImage(char * str)
{
	FILE* fp = fopen(str, "rb");
	int i;

	if (fp == NULL) {
		printf("ddddddd");
		return;
	}

	fread(GameImage, sizeof(char), 47 * 158, fp);

	for (i = 0; i < 47; i++) {
		strcpy(&GameImage[i][158], "\0");
	}

	fclose(fp);
}

void SetGameOrder(char * str)
{
	if (str == "LoadGameScene"){
		gameOrder = _loadGame();		
	}

	else if (str == "GameScene"){
		gameOrder = 0;
	}


	if (sceneList != NULL) {
		nowScene = sceneList[gameOrder];
	}
}

int BackAndSave(int key)
{
	int iBool = 0;

	if (key == 27)
	{
		bGameRun = 1;
		bGameRender = 0;
		_saveGame(gameOrder);
		iBool = 1;

		ChangeScene(MainScene);
	}

	return iBool;
}

void SceneRunning()
{
	PrintTextFile(nowScene.TextFileName);

	if (nowScene.nextSceneCount == 0 || nowScene.nextSceneCount == -1)
	{
		if (nowScene.nextSceneCount == 0) 
		{
			StartClearMusic();
			printClear();

			gameOrder = 0;
			_saveGame(0);
		}

		else if (nowScene.nextSceneCount == -1) 
		{
			StartFailMusic();
			printFail();

			gameOrder = 0;
			_saveGame(0);
		}
	}

	else if (nowScene.nextSceneCount == 1 || nowScene.nextScene > 1)
	{
		gotoxy(190, 60);

		if(nowScene.nextSceneCount == 1)
			printf("엔터 입력");
		else
			printf("선택지 입력");
	}

	bGameRun = 0;
}

void InputWait()
{
	int key;

	// 승 / 패배
	if (nowScene.nextSceneCount == 0 || nowScene.nextSceneCount == -1)
	{
		if (kbhit())
		{
			bGameRun = 1;
			bGameRender = 0;
			_saveGame(0);

			ChangeScene(MainScene);
		}
	}

	// 씬 하나
	else if (nowScene.nextSceneCount == 1)
	{
		if (kbhit())
		{
			key = getch();

			if (BackAndSave(key) == 1) {
				return;
			}

			if (key != 27)
			{
				if (key == 13)
				{
					gameOrder = *nowScene.nextScene;
					nowScene = sceneList[gameOrder];
					_setGameImage(nowScene.ImageFileName);

					gotoxy(190, 60);
					printf("          ");


					gotoxy(36, 3);
					_RenderGameImage();
					printBlank();

					bGameRun = 1;
				}
			}
		}
	}

	// 여러개의 씬
	else if (nowScene.nextScene > 1)
	{
		if (kbhit())
		{
			key = getch();

			if (BackAndSave(key) == 1) {
				return;
			}

			if (key != 27)
			{
				if (key >= 49 && key <= 49 + (nowScene.nextSceneCount - 1))
				{
					gameOrder = nowScene.nextScene[key - 49];
					nowScene = sceneList[gameOrder];
					_setGameImage(nowScene.ImageFileName);

					gotoxy(190, 60);
					printf("                    ");

					gotoxy(36, 3);
					_RenderGameImage();
					printBlank();

					bGameRun = 1;
				}
			}
		}
	}
}

// 박스를 그려줍니다.
void _RenderImageBox()
{
	DrawBox(2, 2, 117, 50);
}

// 이미지를 그려줍니다.
void _RenderGameImage()
{
	int i = 0, j;

	for (i = 0; i < 47; i++)
	{
		gotoxy(36, 3 + i);

		if (GameImage[i][0] == '\0') {
			printf("%s", GameImage[i] + 1);
		}
		else {
			printf("%s", GameImage[i]);
		}
	}
}

// 씬에 대한 정보들을 초기화합니다.
void _initSceneList()
{
	int i;
	sceneList = (Scene *)malloc(sizeof(Scene) * 50);

	for (i = 0; i < 50; i++)
	{
		strcpy(sceneList[i].TextFileName, getTextFileName("대본/대본 ", i));
		strcpy(sceneList[i].ImageFileName, getTextFileName("이미지/이미지 ", i));
	}

	// 씬 (0)  - 1, 2, 3, 4
	sceneList[0].nextSceneCount = 4;
	sceneList[0].nextScene = (int *)malloc(sizeof(int) * 4);

	sceneList[0].nextScene[0] = 1; // 1번 누를 경우 - 1번쨰 씬
	sceneList[0].nextScene[1] = 2; // 2번 누를 경우 - 2번째 씬
	sceneList[0].nextScene[2] = 3; // 3번 누를 경우 = 3번째 씬
	sceneList[0].nextScene[3] = 4; // 4번 누를 경우 - 4번째 씬

								   // 씬 (1) - 5, 6, 7, 0
	sceneList[1].nextSceneCount = 4;
	sceneList[1].nextScene = (int *)malloc(sizeof(int) * 4);

	sceneList[1].nextScene[0] = 5; // 1번 누를 경우 - 5번쨰 씬
	sceneList[1].nextScene[1] = 6; // 2번 누를 경우 - 6번쨰 씬
	sceneList[1].nextScene[2] = 7; // 3번 누를 경우 - 7번쨰 씬
	sceneList[1].nextScene[3] = 0; // 4번 누를 경우 - 0번쨰 씬

								   // 씬 (2) - 8, 11, 14, 0
	sceneList[2].nextSceneCount = 4;
	sceneList[2].nextScene = (int *)malloc(sizeof(int) * 4);

	sceneList[2].nextScene[0] = 8;  // 1번 누를 경우 - 8번쨰 씬
	sceneList[2].nextScene[1] = 11; // 2번 누를 경우 - 11번쨰 씬
	sceneList[2].nextScene[2] = 14; // 3번 누를 경우 - 14번쨰 씬
	sceneList[2].nextScene[3] = 0;  // 4번 누를 경우 - 0번쨰 씬

	// 씬 (3) - 0
	sceneList[3].nextSceneCount = 1;
	sceneList[3].nextScene = (int *)malloc(sizeof(int) * 1);

	*sceneList[3].nextScene = 0;	//	뒤로가기

									// 씬 (4) - 17 18, 0
	sceneList[4].nextSceneCount = 3;
	sceneList[4].nextScene = (int *)malloc(sizeof(int) * 3);

	sceneList[4].nextScene[0] = 17;  // 1번 누를 경우 - 17번쨰 씬
	sceneList[4].nextScene[1] = 18;  // 2번 누를 경우 - 18번쨰 씬
	sceneList[4].nextScene[2] = 0;   // 3번 누를 경우 - 14번쨰 씬

									 // 씬 (5) - 0
	sceneList[5].nextSceneCount = 1;
	sceneList[5].nextScene = (int *)malloc(sizeof(int) * 1);

	*sceneList[5].nextScene = 0;	//	뒤로가기

									// 씬 (6) - 0
	sceneList[6].nextSceneCount = 1;
	sceneList[6].nextScene = (int *)malloc(sizeof(int) * 1);

	*sceneList[6].nextScene = 0;	//	뒤로가기

									// 씬 (7) - 0 
	sceneList[7].nextSceneCount = 1;
	sceneList[7].nextScene = (int *)malloc(sizeof(int) * 1);

	*sceneList[7].nextScene = 0;	//	뒤로가기

									// 씬 (8) - 9
	sceneList[8].nextSceneCount = 1;
	sceneList[8].nextScene = (int *)malloc(sizeof(int) * 1);

	*sceneList[8].nextScene = 9;	//	9번째 씬

									// 씬 (9) - 10 
	sceneList[9].nextSceneCount = 1;
	sceneList[9].nextScene = (int *)malloc(sizeof(int) * 1);

	*sceneList[9].nextScene = 10;	//	10번째 씬

									// 씬 (10) - 2 
	sceneList[10].nextSceneCount = 1;
	sceneList[10].nextScene = (int *)malloc(sizeof(int) * 1);

	*sceneList[10].nextScene = 0;	//	뒤로 돌아가기

									// 씬 (11) - 12 
	sceneList[11].nextSceneCount = 1;
	sceneList[11].nextScene = (int *)malloc(sizeof(int) * 1);

	*sceneList[11].nextScene = 12;	//	12번째 씬

									// 씬 (12) - 13 
	sceneList[12].nextSceneCount = 1;
	sceneList[12].nextScene = (int *)malloc(sizeof(int) * 1);

	*sceneList[12].nextScene = 13;	//	13번째 씬

									// 씬 (13) - 2 
	sceneList[13].nextSceneCount = 1;
	sceneList[13].nextScene = (int *)malloc(sizeof(int) * 1);

	*sceneList[13].nextScene = 2;	//	2번째 씬

									// 씬 (14) - 15 
	sceneList[14].nextSceneCount = 1;
	sceneList[14].nextScene = (int *)malloc(sizeof(int) * 1);

	*sceneList[14].nextScene = 15;	//	15번째 씬

									// 씬 (15) - 16 
	sceneList[15].nextSceneCount = 1;
	sceneList[15].nextScene = (int *)malloc(sizeof(int) * 1);

	*sceneList[15].nextScene = 16;	//	16번째 씬

									// 씬 (16) - 2 
	sceneList[16].nextSceneCount = 1;
	sceneList[16].nextScene = (int *)malloc(sizeof(int) * 1);

	*sceneList[16].nextScene = 2;	//	2번째 씬

									// 씬 (17) - ?
	sceneList[17].nextSceneCount = -1;
	sceneList[17].nextScene = NULL;

	// 씬 (18) - 19, 20, 21
	sceneList[18].nextSceneCount = 3;
	sceneList[18].nextScene = (int *)malloc(sizeof(int) * 3);

	sceneList[18].nextScene[0] = 19;  // 1번 누를 경우 - 19번쨰 씬
	sceneList[18].nextScene[1] = 20;  // 2번 누를 경우 - 20번쨰 씬
	sceneList[18].nextScene[2] = 21;  // 3번 누를 경우 - 21번쨰 씬

									  // 씬 (19) - Fail
	sceneList[19].nextSceneCount = -1;
	sceneList[19].nextScene = NULL;

	// 씬 (20) - Fail
	sceneList[20].nextSceneCount = -1;
	sceneList[20].nextScene = NULL;

	// 씬 (21) - 22, 24, 23
	sceneList[21].nextSceneCount = 3;
	sceneList[21].nextScene = (int *)malloc(sizeof(int) * 3);

	sceneList[21].nextScene[0] = 22;  // 1번 누를 경우 - 22번쨰 씬
	sceneList[21].nextScene[1] = 24;  // 2번 누를 경우 - 24번쨰 씬
	sceneList[21].nextScene[2] = 23;  // 3번 누를 경우 - 23번쨰 씬

									  // 씬 (22) - Fail
	sceneList[22].nextSceneCount = -1;
	sceneList[22].nextScene = NULL;

	// 씬 (23) - Fail
	sceneList[23].nextSceneCount = -1;
	sceneList[23].nextScene = NULL;

	// 씬 (24) - 25, 26
	sceneList[24].nextSceneCount = 2;
	sceneList[24].nextScene = (int *)malloc(sizeof(int) * 2);

	sceneList[24].nextScene[0] = 25;  // 1번 누를 경우 - 25번쨰 씬
	sceneList[24].nextScene[1] = 26;  // 2번 누를 경우 - 26번쨰 씬

									  // 씬 (25) - 27, 28
	sceneList[25].nextSceneCount = 2;
	sceneList[25].nextScene = (int *)malloc(sizeof(int) * 2);

	sceneList[25].nextScene[0] = 27;  // 1번 누를 경우 - 27번쨰 씬
	sceneList[25].nextScene[1] = 28;  // 2번 누를 경우 - 28번쨰 씬

									  // 씬 (26) - Fail
	sceneList[26].nextSceneCount = -1;
	sceneList[26].nextScene = NULL;

	// 씬 (27) - 29
	sceneList[27].nextSceneCount = 1;
	sceneList[27].nextScene = (int *)malloc(sizeof(int) * 1);

	*sceneList[27].nextScene = 29;  // 1번 누를 경우 - 24번쨰 씬

									// 씬 (28) - Fail
	sceneList[28].nextSceneCount = -1;
	sceneList[28].nextScene = NULL;

	// 씬 (29) - Clear
	sceneList[29].nextSceneCount = 0;
	sceneList[29].nextScene = NULL;

	// 현재 씬을 선택합니다.
	nowScene = sceneList[gameOrder];
}


void printClear()
{
	system("cls");
	gotoxy(80, 10);  printf("┌────────────────────────────────────────┐\n");
	gotoxy(80, 11); printf("│      ■■■■      ■            ■■■■■■          ■        ■■■■■    │\n");
	gotoxy(80, 12); printf("│    ■        ■    ■            ■                    ■        ■        ■  │\n");
	gotoxy(80, 13); printf("│  ■                ■            ■                  ■  ■      ■        ■  │\n");
	gotoxy(80, 14); printf("│  ■                ■            ■                  ■  ■      ■        ■  │\n");
	gotoxy(80, 15); printf("│  ■                ■            ■■■■■■      ■      ■    ■■■■■    │\n");
	gotoxy(80, 16); printf("│  ■                ■            ■                ■      ■    ■        ■  │\n");
	gotoxy(80, 17); printf("│  ■                ■            ■                ■■■■■    ■        ■  │\n");
	gotoxy(80, 18); printf("│  ■                ■            ■              ■          ■  ■        ■  │\n");
	gotoxy(80, 19); printf("│    ■        ■    ■            ■              ■          ■  ■        ■  │\n");
	gotoxy(80, 20); printf("│      ■■■■      ■■■■■■  ■■■■■■    ■          ■  ■        ■  │\n");
	gotoxy(80, 21); printf("└────────────────────────────────────────┘\n");

	return;
}

void printFail()
{
	system("cls");
	gotoxy(80, 10); printf("┌──────────────────────────┐\n");
	gotoxy(80, 11); printf("│  ■■■■■■        ■        ■    ■            │\n");
	gotoxy(80, 12); printf("│  ■                  ■        ■    ■            │\n");
	gotoxy(80, 13); printf("│  ■                ■  ■      ■    ■            │\n");
	gotoxy(80, 14); printf("│  ■                ■  ■      ■    ■            │\n");
	gotoxy(80, 15); printf("│  ■■■■■      ■      ■    ■    ■            │\n");
	gotoxy(80, 16); printf("│  ■              ■      ■    ■    ■            │\n");
	gotoxy(80, 17); printf("│  ■              ■■■■■    ■    ■            │\n");
	gotoxy(80, 18);	printf("│  ■            ■          ■  ■    ■            │\n");
	gotoxy(80, 19);	printf("│  ■            ■          ■  ■    ■            │\n");
	gotoxy(80, 20); printf("│  ■            ■          ■  ■    ■■■■■■  │\n");
	gotoxy(80, 21);	printf("└──────────────────────────┘\n");

	gotoxy(60, 23); printf("                                                                                                                                \n");
	gotoxy(60, 24);	printf("  ★        ★    ★        ★★★★      ★          ★★★★★★                ★★★★★★    ★        ★★★★★★★★    \n");
	gotoxy(60, 25); printf("  ★        ★    ★      ★        ★    ★        ★            ★                  ★          ★        ★            ★    \n");
	gotoxy(60, 26); printf("  ★★★★★★★★★      ★        ★    ★          ★★★★★★                    ★★        ★★★    ★            ★    \n");
	gotoxy(60, 27); printf("  ★        ★    ★      ★        ★    ★                                        ★    ★      ★        ★★★★★★★★    \n");
	gotoxy(60, 28); printf("  ★        ★    ★      ★        ★    ★      ★★★★★★★★★★            ★        ★    ★                ★          \n");
	gotoxy(60, 29); printf("  ★★★★★★    ★        ★★★★      ★                                                      ★                ★          \n");
	gotoxy(60, 30); printf("                                          ★        ★★★★★★★★                ★★★★★★★★      ★★★★★★★★★★  \n");
	gotoxy(60, 31); printf("    ★★★★★★★★                      ★                      ★                              ★                            \n");
	gotoxy(60, 32); printf("    ★            ★        ★                      ★★★★★★★★                ★★★★★★★★                ★          \n");
	gotoxy(60, 33); printf("    ★            ★        ★                      ★                              ★                          ★★  ★★      \n");
	gotoxy(60, 34); printf("    ★★★★★★★★        ★★★★★★★★        ★★★★★★★★                ★★★★★★★★        ★★          ★★  \n");
	gotoxy(60, 35); printf("                                                                                                                                \n");
	gotoxy(60, 36); printf("                                                                                                                                                  \n");
	gotoxy(60, 37); printf("  ★★★★★★★  ★        ★★★★★★★★        ★★      ★  ★                ★            ★              ★      ★★★★★★    ★      \n");
	gotoxy(60, 38); printf("        ★        ★        ★            ★                  ★  ★              ★★            ★              ★      ★              ★      \n");
	gotoxy(60, 39); printf("        ★        ★        ★            ★    ★★★★★★  ★  ★            ★    ★          ★              ★      ★              ★      \n");
	gotoxy(60, 40); printf("        ★        ★        ★★★★★★★★        ★★      ★★★        ★★        ★★      ★              ★      ★              ★      \n");
	gotoxy(60, 41); printf("        ★        ★                ★            ★    ★    ★  ★                              ★              ★      ★              ★      \n");
	gotoxy(60, 42); printf("      ★  ★      ★      ★★★★★★★★★★    ★    ★    ★  ★      ★★★★★★★★★★    ★              ★      ★              ★★★  \n");
	gotoxy(60, 43); printf("      ★  ★      ★                                ★★      ★  ★                              ★              ★      ★              ★      \n");
	gotoxy(60, 44); printf("    ★      ★    ★        ★★★★★★★★                                ★            ★      ★              ★      ★              ★      \n");
	gotoxy(60, 45); printf("    ★      ★    ★                      ★            ★      ★          ★★★★★★★★      ★              ★      ★              ★      \n");
	gotoxy(60, 46); printf("  ★          ★  ★                      ★          ★  ★  ★  ★        ★            ★      ★★★★★★★  ★      ★★★★★★★  ★      \n");
	gotoxy(60, 47); printf("                  ★                      ★      ★★      ★      ★      ★★★★★★★★                      ★                      ★      \n");
	gotoxy(60, 48); printf("                                                                                                                                                  \n");


	return;
}