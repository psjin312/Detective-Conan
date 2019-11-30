/* ********************************************************
* 프로그램명 : Main_Scene.c
* 작성자 : 박수현, 1조 올박(박신형, 박경덕, 박성진, 박병직)
* 작성일 : 2017.05.31
* 프로그램 설명 : 메인 메뉴에 사용될 프로그램입니다.
******************************************************** */

#include "Main_Scene.h"

void _RenderMainTitle();	// 메인 타이틀의 렌더링 부분
void _setTitleImage();		// 화면에 띄워줄 타이틀 이미지를 세팅합니다.
void _RenderMainImage();	// 타이틀 이미지를 렌더링합니다.
void _RenderMainMenu();		// 메뉴 부분을 렌더링합니다.
void _RenderArrow();		// 화살표를 그려줍니다.
void _RemoveArrow();		// 화살표를 지워줍니다.
void _RenderMadeBy();

void _inputKey();			// 키보드의 입력을 담당합니다.
void _ArrowEvent();

char titleImage[40][142];	// 타이틀 이미지
int bMainSceneInit = 0;     // 메인씬의 데이터 로드 여부
int bMainRender = 0;		// 게임씬 최초 렌더링 초기화

int order = 0;              // 선택한 메뉴 번호
int arrowY = 35;			// 화살표의 좌표

// 씬에 들어오면 초기화해줍니다. (데이터)
void InitMainScene()
{
	if (bMainSceneInit == 0)
	{
		_setTitleImage();
		bMainSceneInit = 1;
	}
}

// 한번만 그려주면 되는 이미지를 그려줍니다.
void RenderMainScene()
{
	if (bMainRender == 0)
	{
		order = -1;

		StartBGMusic();
		_RenderMainImage();
		_RenderArrow();
		_RenderMainMenu();
		_RenderMainTitle();
		_RenderMadeBy();

		bMainRender = 1;
	}
}

// 메인 메뉴의 업데이트 처리
void UpdateMainScene()
{
	_inputKey();

	if (order == -1) {
		order = 0;
	}
}

void _inputKey()
{
	char cChar, DirKey;

	if (_kbhit())
	{
		cChar = _getch();
		switch (cChar)
		{
		case 13:         // 엔터키
			_ArrowEvent();

		case -32:
			DirKey = _getch();

			switch (DirKey)
			{
			case 72:
				if (order > 0)
				{
					_RemoveArrow();
					order -= 1;
					_RenderArrow();
					_RenderMainMenu();
				}
				break;

			case 80:
				if (order < 3)
				{
					_RemoveArrow();
					order += 1;
					_RenderArrow();
					_RenderMainMenu();
				}
				break;
			}

			break;
		}
	}
}

// Made by를 화면에 그려줍니다.
void _RenderMadeBy()
{
	gotoxy(138, 18);
	printf("Made By All Park!");
}

// 타이틀에 사용되는 이미지 파일의 값을 얻어옵니다.
void _setTitleImage()
{
	FILE* fp = fopen("title_image.txt", "rb");
	int i;

	if (fp == NULL) {
		printf("ddddddd");
		return;
	}

	fread(titleImage, sizeof(char), 40 * 142, fp);

	for (i = 0; i < 40; i++) {
		strcpy(&titleImage[i][141], "\0");
	}

	fclose(fp);
}

// 타이틀 이미지를 화면에 그려줍니다.
void _RenderMainImage()
{
	int i, j;

	gotoxy(58, 18);
	for (i = 0; i < 40; i++)
	{
		for (j = 0; j < 142; j++) {
			printf("%c", titleImage[i][j]);
		}
		printf("\n");
	}
}

// 타이틀 문구를 화면에 그려줍니다.
void _RenderMainTitle()
{
	gotoxy(55, 1); printf("\n");
	gotoxy(55, 2); printf("\n");
	gotoxy(55, 3); printf("  ■■■■■■■  ■■    ■■■■■■■■■      ■■■■■■■■■■    ■■■■■■■■■      ■■          ■■      \n");
	gotoxy(55, 4); printf("  ■■■  ■■■■■■    ■■          ■■          ■■      ■■■                  ■■      ■■          ■■      \n");
	gotoxy(55, 5); printf("  ■■■  ■■■  ■■    ■■■■■■  ■■■■      ■■■■■■■■                  ■■      ■■          ■■      \n");
	gotoxy(55, 6); printf("  ■■■  ■■■■■■    ■■          ■■        ■■■■    ■■■    ■■■■■■■■■      ■■          ■■■■  \n");
	gotoxy(55, 7); printf("  ■■■■■■■  ■■    ■■■■■■■■■      ■■■■■■  ■■■                  ■■      ■■          ■■      \n");
	gotoxy(55, 8); printf("                  ■■                  ■■    ■■■    ■■■■■■          ■■■  ■■      ■■■■■■■■■      \n");
	gotoxy(55, 9); printf("                                                                                ■■■  ■■                    ■■      \n");
	gotoxy(55, 10); printf("      ■■■■■■■        ■■■■■■■■          ■■■■■■■            ■■■              ■■        ■■      \n");
	gotoxy(55, 11); printf("    ■■■      ■■■      ■■        ■■        ■■■      ■■■  ■■■■■■■■■■■■    ■■                  \n");
	gotoxy(55, 12); printf("    ■■■      ■■■      ■■        ■■        ■■■      ■■■                              ■■                  \n");
	gotoxy(55, 13); printf("      ■■■■■■■        ■■■■■■■■          ■■■■■■■                                ■■■■■■■■■    \n");
	gotoxy(55, 14); printf("\n");
	gotoxy(55, 15); printf("\n");

	gotoxy(138, 45);
	printColoredText("[ 게임 설명 ]", YELLOW);
	gotoxy(123, 47);
	printColoredText("Enter를 누르면 다음 대사나 씬으로 이동합니다.", YELLOW);
	gotoxy(121, 48);
	printColoredText("선택지가 나오는 경우 원하는 번호를 입력하면 됩니다.", YELLOW);
}

// 타이틀 메뉴를 출력합니다.
void _RenderMainMenu()
{
	int target = (order == -1) ? 0 : order;

	gotoxy(114, 20); printf("┌────────────────────────────┐");
	gotoxy(114, 21); printf("│■■      ■■  ■■■■■  ■■    ■■■■■■  ■■■│");
	gotoxy(114, 22); printf("│  ■      ■    ■      ■    ■■    ■    ■      ■  │");
	gotoxy(114, 23); printf("│  ■■  ■■    ■            ■■    ■    ■      ■  │");
	gotoxy(114, 24); printf("│  ■■  ■■    ■    ■      ■  ■  ■    ■      ■  │");
	gotoxy(114, 25); printf("│  ■  ■  ■    ■■■■      ■  ■  ■    ■      ■  │");
	gotoxy(114, 26); printf("│  ■  ■  ■    ■    ■      ■    ■■    ■      ■  │");
	gotoxy(114, 27); printf("│  ■  ■  ■    ■            ■    ■■    ■      ■  │");
	gotoxy(114, 28); printf("│  ■      ■    ■      ■    ■      ■    ■      ■  │");
	gotoxy(114, 29); printf("│■■■  ■■■  ■■■■■  ■■■    ■      ■■■    │");
	gotoxy(114, 30); printf("└────────────────────────────┘");


	gotoxy(140, 35);
	if (target == 0) printColoredText("새로하기", RED);
	else printf("새로하기");

	gotoxy(140, 36);
	if (target == 1) printColoredText("이어하기", RED);
	else printf("이어하기");

	gotoxy(140, 37);
	if (target == 2) printColoredText("설정", RED);
	else printf("설정");

	gotoxy(140, 38);
	if (target == 3) printColoredText("종료", RED);
	else printf("종료");
}


void _RenderArrow()
{
	int target = (order == -1) ? 0 : order;

	gotoxy(138, arrowY + (target * 1)); printf("▶");
}

void _RemoveArrow()
{
	int target = (order == -1) ? 0 : order;

	gotoxy(138, arrowY + (order * 1)); printf(" ");
}

void _ArrowEvent()
{
	switch (order)
	{
	case 0:
		bMainRender = 0;
		SetGameOrder("GameScene");
		ChangeScene(GameScene);

		return;
		break;

	case 1: //이어하기
		bMainRender = 0;
		SetGameOrder("LoadGameScene");
		ChangeScene(LoadGameScene);
		return;
		break;

	case 2:
		bMainRender = 0;
		ChangeScene(SettingScene);
		return;
		break;

	case 3:
		exit(1);
		break;

	default:
		break;
	}
}