/* ********************************************************
* ���α׷��� : Main_Scene.c
* �ۼ��� : �ڼ���, 1�� �ù�(�ڽ���, �ڰ��, �ڼ���, �ں���)
* �ۼ��� : 2017.05.31
* ���α׷� ���� : ���� �޴��� ���� ���α׷��Դϴ�.
******************************************************** */

#include "Main_Scene.h"

void _RenderMainTitle();	// ���� Ÿ��Ʋ�� ������ �κ�
void _setTitleImage();		// ȭ�鿡 ����� Ÿ��Ʋ �̹����� �����մϴ�.
void _RenderMainImage();	// Ÿ��Ʋ �̹����� �������մϴ�.
void _RenderMainMenu();		// �޴� �κ��� �������մϴ�.
void _RenderArrow();		// ȭ��ǥ�� �׷��ݴϴ�.
void _RemoveArrow();		// ȭ��ǥ�� �����ݴϴ�.
void _RenderMadeBy();

void _inputKey();			// Ű������ �Է��� ����մϴ�.
void _ArrowEvent();

char titleImage[40][142];	// Ÿ��Ʋ �̹���
int bMainSceneInit = 0;     // ���ξ��� ������ �ε� ����
int bMainRender = 0;		// ���Ӿ� ���� ������ �ʱ�ȭ

int order = 0;              // ������ �޴� ��ȣ
int arrowY = 35;			// ȭ��ǥ�� ��ǥ

// ���� ������ �ʱ�ȭ���ݴϴ�. (������)
void InitMainScene()
{
	if (bMainSceneInit == 0)
	{
		_setTitleImage();
		bMainSceneInit = 1;
	}
}

// �ѹ��� �׷��ָ� �Ǵ� �̹����� �׷��ݴϴ�.
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

// ���� �޴��� ������Ʈ ó��
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
		case 13:         // ����Ű
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

// Made by�� ȭ�鿡 �׷��ݴϴ�.
void _RenderMadeBy()
{
	gotoxy(138, 18);
	printf("Made By All Park!");
}

// Ÿ��Ʋ�� ���Ǵ� �̹��� ������ ���� ���ɴϴ�.
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

// Ÿ��Ʋ �̹����� ȭ�鿡 �׷��ݴϴ�.
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

// Ÿ��Ʋ ������ ȭ�鿡 �׷��ݴϴ�.
void _RenderMainTitle()
{
	gotoxy(55, 1); printf("\n");
	gotoxy(55, 2); printf("\n");
	gotoxy(55, 3); printf("  ��������  ���    ����������      �����������    ����������      ���          ���      \n");
	gotoxy(55, 4); printf("  ����  �������    ���          ���          ���      ����                  ���      ���          ���      \n");
	gotoxy(55, 5); printf("  ����  ����  ���    �������  �����      ���������                  ���      ���          ���      \n");
	gotoxy(55, 6); printf("  ����  �������    ���          ���        �����    ����    ����������      ���          �����  \n");
	gotoxy(55, 7); printf("  ��������  ���    ����������      �������  ����                  ���      ���          ���      \n");
	gotoxy(55, 8); printf("                  ���                  ���    ����    �������          ����  ���      ����������      \n");
	gotoxy(55, 9); printf("                                                                                ����  ���                    ���      \n");
	gotoxy(55, 10); printf("      ��������        ���������          ��������            ����              ���        ���      \n");
	gotoxy(55, 11); printf("    ����      ����      ���        ���        ����      ����  �������������    ���                  \n");
	gotoxy(55, 12); printf("    ����      ����      ���        ���        ����      ����                              ���                  \n");
	gotoxy(55, 13); printf("      ��������        ���������          ��������                                ����������    \n");
	gotoxy(55, 14); printf("\n");
	gotoxy(55, 15); printf("\n");

	gotoxy(138, 45);
	printColoredText("[ ���� ���� ]", YELLOW);
	gotoxy(123, 47);
	printColoredText("Enter�� ������ ���� ��糪 ������ �̵��մϴ�.", YELLOW);
	gotoxy(121, 48);
	printColoredText("�������� ������ ��� ���ϴ� ��ȣ�� �Է��ϸ� �˴ϴ�.", YELLOW);
}

// Ÿ��Ʋ �޴��� ����մϴ�.
void _RenderMainMenu()
{
	int target = (order == -1) ? 0 : order;

	gotoxy(114, 20); printf("������������������������������������������������������������");
	gotoxy(114, 21); printf("�����      ���  ������  ���    �������  ���ᦢ");
	gotoxy(114, 22); printf("��  ��      ��    ��      ��    ���    ��    ��      ��  ��");
	gotoxy(114, 23); printf("��  ���  ���    ��            ���    ��    ��      ��  ��");
	gotoxy(114, 24); printf("��  ���  ���    ��    ��      ��  ��  ��    ��      ��  ��");
	gotoxy(114, 25); printf("��  ��  ��  ��    �����      ��  ��  ��    ��      ��  ��");
	gotoxy(114, 26); printf("��  ��  ��  ��    ��    ��      ��    ���    ��      ��  ��");
	gotoxy(114, 27); printf("��  ��  ��  ��    ��            ��    ���    ��      ��  ��");
	gotoxy(114, 28); printf("��  ��      ��    ��      ��    ��      ��    ��      ��  ��");
	gotoxy(114, 29); printf("������  ����  ������  ����    ��      ����    ��");
	gotoxy(114, 30); printf("������������������������������������������������������������");


	gotoxy(140, 35);
	if (target == 0) printColoredText("�����ϱ�", RED);
	else printf("�����ϱ�");

	gotoxy(140, 36);
	if (target == 1) printColoredText("�̾��ϱ�", RED);
	else printf("�̾��ϱ�");

	gotoxy(140, 37);
	if (target == 2) printColoredText("����", RED);
	else printf("����");

	gotoxy(140, 38);
	if (target == 3) printColoredText("����", RED);
	else printf("����");
}


void _RenderArrow()
{
	int target = (order == -1) ? 0 : order;

	gotoxy(138, arrowY + (target * 1)); printf("��");
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

	case 1: //�̾��ϱ�
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