/* ****************************************************************
* 프로그램명 : Util.c
* 작성자 : 박수현, 1조 올박(박신형, 박경덕, 박성진, 박수현)
* 작성일 : 2017.05.31
* 프로그램 설명 : 프로그램에 전반적으로 사용되는 함수들의 집합입니다.
**************************************************************** */

#include "Util.h"

// 설정의 초기값.
int _speedSelected = 2;
int _colorSeleted = 1;
int _soundSelected = 2;


int LoadedSettings[3];
char BlankImage[44][158] = { NULL };

int textX = 36;
int textY = 52;

int iMusic = 0;

// 커서의 좌표를 원하는 곳으로 옮깁니다. - 박수현
void gotoxy(int x, int y)
{
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// 콘솔창 내의 모든 글자들의 색상을 변경합니다. - 박성진
void changeTextColor(int colorID)
{
	HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(stdHandle, colorID);
}

// 입력한 글자들의 색상을 원하는 색상으로 변경하여 출력합니다. - 박성진
void printColoredText(char* str, int colorID)
{
	HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	changeTextColor(colorID);
	printf("%s", str);
	changeTextColor(WHITE);
}

// 텍스트 파일을 읽어오고 화면에 출력합니다. - 박경덕
void PrintTextFile(char * fileName)
{
	FILE* fp = fopen(fileName, "r");
	int i, speeeed;
	char strTemp[255]; // 줄 단위 읽어오기
	char *pStr;
	char ch = ' ';

	// 에러 처리
	if (fp == NULL)
	{
		printf("파일 불러오기 실패\n");
		return;
	}

	textX = 36;
	textY = 52;

	gotoxy(textX, textY);

	speeeed = getSpeed();

	while (1)
	{
		if (kbhit())
		{
			switch (getch())
			{
			case 13:
				speeeed = 0;
				break;
			default:
				break;
			}
		}
		if (ch == '\n')
		{
			gotoxy(textX, textY += 2);
		}

		ch = fgetc(fp);

		if (ch == '\n') {
			system("pause>Null");
		}

		if (ch == EOF) {
			break;
		}

		changeTextColor(getColor());
		putchar(ch);
		changeTextColor(WHITE);

		Sleep(speeeed);		//	글자 단위로 출력
	}
	printf("\n");

	fclose(fp);
}

// 대사 창을 깔끔하게 지워줍니다. - 박경덕
void printBlank()
{
	int i, j;

	if (BlankImage[0][0] == NULL)
	{
		FILE* fp = fopen("대본 blank.txt", "rb");


		if (fp == NULL) {
			printf("파일 불러오기 실패\n");
			return;
		}

		fread(BlankImage, sizeof(char), 44 * 158, fp);

		for (i = 0; i < 44; i++) {
			strcpy(&BlankImage[i][158], "\0");
		}

		fclose(fp);
	}


	for (i = 0; i < 44; i++)
	{
		gotoxy(36, 52 + i);
		for (j = 0; j < 158; j++)
		{
			printf("%c", BlankImage[i][j]);
		}
	}
	gotoxy(1, 1);
}

// 파일의 이름, 순서, 파일형을 입력받고 해당하는 파일을 찾아 화면에 내용을 출력합니다. - 박경덕
void PrintTextFileP(char name[], char order[], char format[])
{
	char *procedure;

	strcat(name, order);		//	"(파일명)_(인덱스)" 구조
	strcat(name, format);		//	"(파일명)_(인덱스).txt" 구조완성
	procedure = name;		//	procedure에 파일명과 확장자 저장

	PrintTextFile(procedure);
}

// 파일의 이름을 반환합니다. - 박경덕
char * getTextFileName(char * name, int i)
{
	char format[] = ".txt";
	char *procedure;
	char * order = (char *)malloc(sizeof(char) * 3);
	itoa(i, order, 10);
	char pName[30];

	strcpy(pName, name);

	strcat(pName, order);		//	"(파일명)_(인덱스)" 구조
	strcat(pName, format);		//	"(파일명)_(인덱스).txt" 구조완성
	procedure = pName;		//	procedure에 파일명과 확장자 저장

	return procedure;
}

// 크기와 위치를 입력받은 후 상자를 그려줍니다. - 박성진
void DrawBox(int x, int y, int width, int height)
{
	int i, j;
	unsigned char a = 0xa6;

	// 맨 위 가로줄
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos); // 커서 위치 이동
	printf("%c%c", a, 0xa3);

	for (i = 0; i < width - 2; i++)
		printf("%c%c", a, 0xa1);

	printf("%c%c\n", a, 0xa4);


	// 중간 좌우 세로줄 및 중간 여백
	for (j = 0; j < height - 2; j++)
	{
		y++; // x좌표의 위치는 그대로 둔 채 y좌표만 아래줄로 이동
		gotoxy(x, y); // 커서 위치 이동
		printf("%c%c", a, 0xa2);

		for (i = 0; i < width - 2; i++)
			printf("  ");

		printf("%c%c\n", a, 0xa2);
	}


	// 맨 아래 가로줄
	y++; // x좌표의 위치는 그대로 둔 채 y좌표만 아래줄로 이동
	gotoxy(x, y); // 커서 위치 이동
	printf("%c%c", a, 0xa6);

	for (i = 0; i < width - 2; i++)
		printf("%c%c", a, 0xa1);

	printf("%c%c\n", a, 0xa5);
}

// 풀스크린으로 출력합니다. - 박병직
void fullscreen()
/* function definition for fullscreen */
{
	keybd_event(VK_MENU, 0x38, 0, 0);
	keybd_event(VK_RETURN, 0x1c, 0, 0);
	keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
}

// 풀스크린으로 출력합니다. - 박병직
void setSpeedSelected(int select)
{
	_speedSelected = select;
}

// 풀스크린으로 출력합니다. - 박병직
void setColorSelected(int select)
{
	_colorSeleted = select;
}

// 풀스크린으로 출력합니다. - 박신형
void setSoundSelected(int select)
{
	_soundSelected = select;
}

// 풀스크린으로 출력합니다. - 박신형
int getSpeed()
{
	int speed = 0;

	if (_speedSelected == 0)	  speed = 25;
	else if (_speedSelected == 1) speed = 50;
	else if (_speedSelected == 2) speed = 100;

	return speed;
}

int getSpeedOrder()
{
	return _speedSelected;
}

// 풀스크린으로 출력합니다. - 박신형
int getSoundOrder()
{
	return _soundSelected;
}


// 풀스크린으로 출력합니다. - 박신형
int getColor()
{
	int color = 0;

	if (_colorSeleted == 0)	  color = WHITE;
	else if (_colorSeleted == 1) color = GRAY;
	else if (_colorSeleted == 2) color = CYAN;

	return color;
}

int getColorOrder()
{
	return _colorSeleted;
}

// 풀스크린으로 출력합니다. - 박신형
void ESC()
{
	if (kbhit())
	{
		switch (getch())
		{
			case 27:
				system("cls");
				printf("게임이 종료되었습니다.\n");
				exit(1);
				break;
			default:
				break;
		}
	}
}

// 풀스크린으로 출력합니다. - 박신형
void StartBGMusic()
{
	if (_soundSelected != 2)
	{
		if (iMusic == 0)
		{
			PlaySound(NULL, NULL, SND_PURGE | SND_NOWAIT | SND_ASYNC);
			PlaySound(TEXT("음악/메인 배경음.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

			iMusic = 1;
		}
	}
}

void StartGameBGMusic()
{
	if (_soundSelected !=2)
	{
		PlaySound(NULL, NULL, SND_PURGE | SND_NOWAIT | SND_ASYNC);
		PlaySound(TEXT("음악/게임 브금.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

		iMusic = 0;
	}
}

void StartClearMusic()
{
	if (_soundSelected != 2)
	{
		PlaySound(NULL, NULL, SND_PURGE | SND_NOWAIT | SND_ASYNC);
		PlaySound(TEXT("음악/해결.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

		iMusic = 0;
	}
}

void StartFailMusic()
{
	if (_soundSelected != 2)
	{
		PlaySound(NULL, NULL, SND_PURGE | SND_NOWAIT | SND_ASYNC);
		PlaySound(TEXT("음악/실패.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

		iMusic = 0;
	}
}

// 풀스크린으로 출력합니다. - 박신형
void EndMusic()
{
	PlaySound(NULL, NULL, SND_PURGE | SND_NOWAIT | SND_ASYNC);
	iMusic = 0;
}

// 세팅정보 불러오기. - 박신형
void _loadSetting()
{
	FILE* fp = fopen("Settings.txt", "r");
	int i;

	if (fp == NULL) {
		printf("에러\n");
		return;
	}

	fscanf(fp, "%d %d %d", &LoadedSettings[0], &LoadedSettings[1], &LoadedSettings[2]);

	setSpeedSelected(LoadedSettings[0]);	// 스피드	
	setColorSelected(LoadedSettings[1]);	// 색깔
	setSoundSelected(LoadedSettings[2]);	// 사운드

	fclose(fp);
}

int _loadGame()
{
	int LoadedGame;

	FILE* fp = fopen("GameSaved.txt", "r");
	int i;

	if (fp == NULL) {
		printf("정보를 불러오지 못했습니다.\n");
		return;
	}

	fscanf(fp, "%d", &LoadedGame);

	fclose(fp);
	return LoadedGame;
}

int _saveGame(int n)
{
	FILE* fp = fopen("GameSaved.txt", "w");

	if (fp == NULL) {
		printf("정보를 불러오지 못했습니다.\n");
		return;
	}

	fprintf(fp, "%d", n);

	fclose(fp);
}