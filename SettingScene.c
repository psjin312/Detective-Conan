/* *******************************************************************************************
* 프로그램명 : SettingScene.c
* 작성자 : 1조 올박(박신형, 박경덕, 박수현, 박병직)
* 작성일 : 2017.06.07
* 프로그램 설명 : 설정창에 들어가서 메뉴를 선택했을 때의 이벤트를 처리하는 프로그램입니다.
******************************************************************************************* */

#include "SettingScene.h"
#include "Util.h"

int bSettingSceneInit = 0;  // 메인씬의 데이터 로드 여부
int bSettingRender = 0;		// 게임씬 최초 렌더링 초기화

void RenderSettingScene();	// 설정창 렌더링
void InitSettingScene();	// 초기화
void UpdateSettingScene();  // 화면 업데이트

void _printTitle();			// SETTINGS 글자 출력
void _printSettingMenu();	// 설정 메뉴 출력
void _updateSettingMenu();	// 업데이트
void _SettingInputKey();	// 키보드 방향키 또는 엔터를 받아와서 처리

void _SRenderArrow();		// 설정 메뉴를 선택하는 화살표(▶)를  표시
void _SRemoveArrow();		// 설정 메뉴를 선택하는 화살표(▶)를  삭제

void _SRenderArrow2(int targetSet);	// 설정 메뉴를 선택했을 때 상 중 하를 선택하는 화살표(▼)를 표시
void _SRemoveArrow2(int targetSet); // 설정 메뉴를 선택했을 때 상 중 하를 선택하는 화살표(▼)를 삭제

void setTargetSet(int changer);		// (▼)화살표의 X좌표를 원하는 수만큼 움직이는 함수
int getTargetSet();					// TargetSet 값을 받아오는 함수
int getUseTargetSet();				// (▼)화살표의 좌, 우 한계를 정해 놓는 함수

int getUseTargetSetByValue(int target); // 원하는 설정에 대한 값을 받아오는 함수
void _printLevel(int value, int y);		// (출력 속도, 소리 크기의 상 중 하) 또는 (글자 색상의 빨강, 초록, 파랑)을 선택하는 함수


void _SArrowEvent();		// 설정 메뉴를 선택해 Enter를 눌렀을 때
void _LoadSetting();
void _SaveSetting();


int _order = 0;				// 선택한 메뉴 넘버

int _arrowY = 28;			// (▶)화살표의 Y좌표

int _arrowX2 = 68;			// (▼)화살표의 X좌표
int _arrowY2 = 28;			// (▼)화살표의 Y좌표

int _setSpeed = 0;			// 출력 속도의 상 중 하 선택 값
int _setColor = 0;			// 글자 색상의 흰색 초록 파랑 선택 값
int _setScale = 0;			// 소리 크기의 상 중 하 선택 값

							// 설정에 대한 권한
int _bSpeed = 0;
int _bColor = 0;
int _bScale = 0;


// 초기화					- 박성진
void InitSettingScene()
{
	if (bSettingSceneInit == 0)
	{
		_LoadSetting();
		bSettingSceneInit = 1;
	}
}

// 화면 업데이트			- 박신형
void UpdateSettingScene()
{
	_updateSettingMenu();
}

// 설정창 렌더링			- 박성진
void RenderSettingScene()
{
	if (bSettingRender == 0)
	{
		_printTitle();
		_printSettingMenu();
		_SRenderArrow();
		bSettingRender = 1;
	}
}


void _LoadSetting()
{
	_setSpeed = getSpeedOrder() * 4;
	_setColor = getColorOrder() * 4;
	_setScale = getSoundOrder() * 4;
}




// SETTINGS 글자 출력		- 박성진
void _printTitle()
{
	gotoxy(30, 6);  printf("  ■■■■      ■■■■■■    ■■■■■■■  ■■■■■■■  ■    ■■        ■        ■■■■        ■■■■  \n");
	gotoxy(30, 7);  printf("■        ■    ■                    ■              ■        ■    ■■        ■      ■        ■    ■        ■\n");
	gotoxy(30, 8);  printf("■        ■    ■                    ■              ■        ■    ■■        ■    ■          ■    ■        ■\n");
	gotoxy(30, 9);  printf("■              ■                    ■              ■        ■    ■  ■      ■    ■                ■          \n");
	gotoxy(30, 10); printf("  ■■          ■■■■■■          ■              ■        ■    ■   ■     ■    ■    ■■■■      ■■      \n");
	gotoxy(30, 11); printf("      ■■      ■                    ■              ■        ■    ■    ■    ■    ■          ■          ■■  \n");
	gotoxy(30, 12); printf("          ■    ■                    ■              ■        ■    ■      ■  ■    ■          ■              ■\n");
	gotoxy(30, 13); printf("■        ■    ■                    ■              ■        ■    ■      ■  ■    ■          ■    ■        ■\n");
	gotoxy(30, 14); printf("■        ■    ■                    ■              ■        ■    ■        ■■      ■      ■■    ■        ■\n");
	gotoxy(30, 15); printf("  ■■■■      ■■■■■■          ■              ■        ■    ■        ■■        ■■■  ■      ■■■■  \n");

}

// 설정 메뉴 출력			 - 박성진
void _printSettingMenu()
{
	gotoxy(50, 28);
	if (_order == 0) printColoredText("글자 출력속도", RED);
	else printf("글자 출력속도");
	_printLevel(getUseTargetSetByValue(1), 28);

	gotoxy(50, 30);
	if (_order == 1) printColoredText("글자 색상", RED);
	else printf("글자 색상");
	_printLevel(getUseTargetSetByValue(2), 30);

	gotoxy(50, 32);
	if (_order == 2) printColoredText("소리 크기", RED);
	else printf("소리 크기");
	_printLevel(getUseTargetSetByValue(3), 32);

	gotoxy(50, 34);
	if (_order == 3) printColoredText("뒤로 가기", RED);
	else printf("뒤로 가기");
}

// (출력 속도, 소리 크기의 상 중 하) 또는 (글자 색상의 빨강, 초록, 파랑)을 선택하는 함수     - 박성진
void _printLevel(int value, int y)
{
	if (y == 28)
	{
		gotoxy(68, y);
		(value == 0) ? printColoredText("상", RED) : printf("상");

		gotoxy(76, y);
		(value == 1) ? printColoredText("중", RED) : printf("중");

		gotoxy(84, y);
		(value == 2) ? printColoredText("하", RED) : printf("하");
	}

	else if (y == 32)
	{
		gotoxy(68, y);
		(value == 0) ? printColoredText("ON", RED) : printf("ON");

		gotoxy(84, y);
		(value == 2) ? printColoredText("OFF", RED) : printf("OFF");
	}

	else if (y == 30)
	{
		gotoxy(67, y);
		(value == 0) ? printColoredText("흰색", RED) : printf("흰색");

		gotoxy(75, y);
		(value == 1) ? printColoredText("회색", RED) : printf("회색");

		gotoxy(83, y);
		(value == 2) ? printColoredText("청록", RED) : printf("청록");
	}
}

// 설정 화면을 업데이트				- 박신형
void _updateSettingMenu()
{
	_SettingInputKey();
}

// 키보드 방향키 또는 엔터를 받아와서 처리			- 박성진
void _SettingInputKey()
{
	char cChar, DirKey;

	if (_kbhit())
	{
		cChar = _getch();
		switch (cChar)
		{
		case 13:			// 엔터키
			_SArrowEvent();

		case -32:
			DirKey = _getch();

			// 설정 중 고르기
			if (_bSpeed == 0 && _bColor == 0 && _bScale == 0)
			{
				switch (DirKey)
				{
				case 72:		// 키보드 위 방향키
					if (_order > 0)
					{
						_SRemoveArrow();
						_order -= 1;
						_printSettingMenu();
						_SRenderArrow();
					}
					break;

				case 80:		// 키보드 아래 방향키
					if (_order < 3)
					{
						_SRemoveArrow();
						_order += 1;
						_printSettingMenu();
						_SRenderArrow();
					}
					break;
				}
			}

			// 고른 후
			else
			{
				switch (DirKey)
				{
				case 75:		// 키보드 왼쪽 방향키
				{
					_SRemoveArrow2(getTargetSet());
					if (getUseTargetSet() > 0) {
						setTargetSet(-4);
						_printLevel(getUseTargetSetByValue(_order + 1), 28 + (_order * 2));
					}
					_SRenderArrow2(getTargetSet());
				}
				break;

				case 77:		// 키보드 오른쪽 방향키
					_SRemoveArrow2(getTargetSet());
					if (getUseTargetSet() < 2) {
						setTargetSet(4);
						_printLevel(getUseTargetSetByValue(_order + 1), 28 + (_order * 2));
					}
					_SRenderArrow2(getTargetSet());
					break;
				}
			}

			break;
		}
	}
}

// 설정 메뉴를 선택하는 화살표(▶)를 표시		- 박신형
void _SRenderArrow()
{
	gotoxy(45, _arrowY + (_order * 2)); printf("▶");
}

// 설정 메뉴를 선택하는 화살표(▶)를 삭제		- 박신형
void _SRemoveArrow()
{
	gotoxy(45, _arrowY + (_order * 2)); printf(" ");
}

// 설정 메뉴를 선택했을 때 상 중 하를 선택하는 화살표(▼)를 표시		- 박신형
void _SRenderArrow2(int targetSet)
{
	if (_order == 1)
	{
		gotoxy(_arrowX2 + (targetSet * 2), _arrowY + 1); printf("▼");
	}

	else if (_order == 2)
	{
		gotoxy(_arrowX2 + (targetSet * 2), _arrowY + 3); printf("▼");
	}

	else
	{
		gotoxy(_arrowX2 + (targetSet * 2), _arrowY - 1); printf("▼");
	}
}


// 설정 메뉴를 선택했을 때 상 중 하를 선택하는 화살표(▼)를 삭제		- 박신형
void _SRemoveArrow2(int targetSet)
{
	if (_order == 1)
	{
		gotoxy(_arrowX2 + (targetSet * 2), _arrowY + 1); printf("   ");
		gotoxy(_arrowX2, _arrowY + 1); printf("   ");
	}

	else if (_order == 2)
	{
		gotoxy(_arrowX2 + (targetSet * 2), _arrowY + 3); printf("   ");
		gotoxy(_arrowX2, _arrowY + 3); printf("   ");
	}

	else
	{
		gotoxy(_arrowX2 + (targetSet * 2), _arrowY - 1); printf("   ");
		gotoxy(_arrowX2, _arrowY - 1); printf("   ");
	}
}

// TargetSet 값을 받아오는 함수			- 박신형
int getTargetSet()
{
	int targetSet = -1;
	
	if (_bSpeed == 1) {
		targetSet = _setSpeed;
	}

	else if (_bColor == 1)
	{
		targetSet = _setColor;
	}

	else if (_bScale == 1)
	{
		targetSet = _setScale;
	}

	return targetSet;
}

// (▼)화살표의 좌, 우 한계를 정해놓는 함수			- 박성진
int getUseTargetSet()
{
	int targetSet = -1;

	if (_bSpeed == 1) {
		targetSet = _setSpeed / 4;
	}

	else if (_bColor == 1)
	{
		targetSet = _setColor / 4;
	}

	else if (_bScale == 1)
	{
		targetSet = _setScale / 4;
	}

	return targetSet;
}

// 원하는 설정에 대한 값을 받아오는 함수			- 박신형
int getUseTargetSetByValue(int target)
{
	int targetSet = -1;

	if (target == 1) {
		targetSet = _setSpeed / 4;
	}

	else if (target == 2)
	{
		targetSet = _setColor / 4;
	}

	else if (target == 3)
	{
		targetSet = _setScale / 4;
	}

	return targetSet;
}

// (▼)화살표의 X좌표를 원하는 수만큼 움직이는 함수			- 박성진
void setTargetSet(int changer)
{
	if (_bSpeed == 1) {
		_setSpeed += changer;
	}

	else if (_bColor == 1)
	{
		_setColor += changer;
	}

	else if (_bScale == 1)
	{
		_setScale += changer * 2;
	}
}

// 설정 메뉴를 선택해 Enter를 눌렀을 때			- 박성진
void _SArrowEvent()
{
	// 선택
	if (_bSpeed == 0 && _bColor == 0 && _bScale == 0)
	{
		switch (_order)
		{
		case 0:		// 글자 출력속도
			_bSpeed = 1;
			_SRenderArrow2(getTargetSet());
			break;

		case 1:		// 글자 색상
			_bColor = 1;
			_SRenderArrow2(getTargetSet());
			break;

		case 2:		// 소리 크기
			_bScale = 1;
			_SRenderArrow2(getTargetSet());
			break;

		case 3:		// 뒤로 가기
			system("cls");
			ChangeScene(MainScene);
			_SaveSetting();
			bSettingRender = 0;
			break;

		default:
			break;
		}
	}

	// 지워줍니다.
	else
	{
		_SRemoveArrow2(getTargetSet());

		if (_bSpeed == 1)
		{
			_bSpeed = 0;
		}

		else if (_bColor == 1)
		{
			_bColor = 0;
		}

		else if (_bScale == 1)
		{
			_SaveSetting();

			if (getSoundOrder() == 0) 
			{
				StartBGMusic();
			}

			else {
				EndMusic();
			}

			_bScale = 0;

			
		}
	}
}

void _SaveSetting()
{
	setSpeedSelected(getUseTargetSetByValue(1));
	setSoundSelected(getUseTargetSetByValue(3));
	setColorSelected(getUseTargetSetByValue(2));

	// 파일 쓰기( 설정정보를 Settings.txt에 저장)
	FILE* fp = fopen("Settings.txt", "w");
	int i;

	if (fp == NULL) {
		printf("에러\n");
		return;
	}

	// 1 스피드, 2 색깔, 3 사운드
	fprintf(fp, "%d %d %d", getUseTargetSetByValue(1), getUseTargetSetByValue(2), getUseTargetSetByValue(3));
	fclose(fp);
}