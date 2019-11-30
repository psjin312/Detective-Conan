/* *******************************************************************************************
* ���α׷��� : SettingScene.c
* �ۼ��� : 1�� �ù�(�ڽ���, �ڰ��, �ڼ���, �ں���)
* �ۼ��� : 2017.06.07
* ���α׷� ���� : ����â�� ���� �޴��� �������� ���� �̺�Ʈ�� ó���ϴ� ���α׷��Դϴ�.
******************************************************************************************* */

#include "SettingScene.h"
#include "Util.h"

int bSettingSceneInit = 0;  // ���ξ��� ������ �ε� ����
int bSettingRender = 0;		// ���Ӿ� ���� ������ �ʱ�ȭ

void RenderSettingScene();	// ����â ������
void InitSettingScene();	// �ʱ�ȭ
void UpdateSettingScene();  // ȭ�� ������Ʈ

void _printTitle();			// SETTINGS ���� ���
void _printSettingMenu();	// ���� �޴� ���
void _updateSettingMenu();	// ������Ʈ
void _SettingInputKey();	// Ű���� ����Ű �Ǵ� ���͸� �޾ƿͼ� ó��

void _SRenderArrow();		// ���� �޴��� �����ϴ� ȭ��ǥ(��)��  ǥ��
void _SRemoveArrow();		// ���� �޴��� �����ϴ� ȭ��ǥ(��)��  ����

void _SRenderArrow2(int targetSet);	// ���� �޴��� �������� �� �� �� �ϸ� �����ϴ� ȭ��ǥ(��)�� ǥ��
void _SRemoveArrow2(int targetSet); // ���� �޴��� �������� �� �� �� �ϸ� �����ϴ� ȭ��ǥ(��)�� ����

void setTargetSet(int changer);		// (��)ȭ��ǥ�� X��ǥ�� ���ϴ� ����ŭ �����̴� �Լ�
int getTargetSet();					// TargetSet ���� �޾ƿ��� �Լ�
int getUseTargetSet();				// (��)ȭ��ǥ�� ��, �� �Ѱ踦 ���� ���� �Լ�

int getUseTargetSetByValue(int target); // ���ϴ� ������ ���� ���� �޾ƿ��� �Լ�
void _printLevel(int value, int y);		// (��� �ӵ�, �Ҹ� ũ���� �� �� ��) �Ǵ� (���� ������ ����, �ʷ�, �Ķ�)�� �����ϴ� �Լ�


void _SArrowEvent();		// ���� �޴��� ������ Enter�� ������ ��
void _LoadSetting();
void _SaveSetting();


int _order = 0;				// ������ �޴� �ѹ�

int _arrowY = 28;			// (��)ȭ��ǥ�� Y��ǥ

int _arrowX2 = 68;			// (��)ȭ��ǥ�� X��ǥ
int _arrowY2 = 28;			// (��)ȭ��ǥ�� Y��ǥ

int _setSpeed = 0;			// ��� �ӵ��� �� �� �� ���� ��
int _setColor = 0;			// ���� ������ ��� �ʷ� �Ķ� ���� ��
int _setScale = 0;			// �Ҹ� ũ���� �� �� �� ���� ��

							// ������ ���� ����
int _bSpeed = 0;
int _bColor = 0;
int _bScale = 0;


// �ʱ�ȭ					- �ڼ���
void InitSettingScene()
{
	if (bSettingSceneInit == 0)
	{
		_LoadSetting();
		bSettingSceneInit = 1;
	}
}

// ȭ�� ������Ʈ			- �ڽ���
void UpdateSettingScene()
{
	_updateSettingMenu();
}

// ����â ������			- �ڼ���
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




// SETTINGS ���� ���		- �ڼ���
void _printTitle()
{
	gotoxy(30, 6);  printf("  �����      �������    ��������  ��������  ��    ���        ��        �����        �����  \n");
	gotoxy(30, 7);  printf("��        ��    ��                    ��              ��        ��    ���        ��      ��        ��    ��        ��\n");
	gotoxy(30, 8);  printf("��        ��    ��                    ��              ��        ��    ���        ��    ��          ��    ��        ��\n");
	gotoxy(30, 9);  printf("��              ��                    ��              ��        ��    ��  ��      ��    ��                ��          \n");
	gotoxy(30, 10); printf("  ���          �������          ��              ��        ��    ��   ��     ��    ��    �����      ���      \n");
	gotoxy(30, 11); printf("      ���      ��                    ��              ��        ��    ��    ��    ��    ��          ��          ���  \n");
	gotoxy(30, 12); printf("          ��    ��                    ��              ��        ��    ��      ��  ��    ��          ��              ��\n");
	gotoxy(30, 13); printf("��        ��    ��                    ��              ��        ��    ��      ��  ��    ��          ��    ��        ��\n");
	gotoxy(30, 14); printf("��        ��    ��                    ��              ��        ��    ��        ���      ��      ���    ��        ��\n");
	gotoxy(30, 15); printf("  �����      �������          ��              ��        ��    ��        ���        ����  ��      �����  \n");

}

// ���� �޴� ���			 - �ڼ���
void _printSettingMenu()
{
	gotoxy(50, 28);
	if (_order == 0) printColoredText("���� ��¼ӵ�", RED);
	else printf("���� ��¼ӵ�");
	_printLevel(getUseTargetSetByValue(1), 28);

	gotoxy(50, 30);
	if (_order == 1) printColoredText("���� ����", RED);
	else printf("���� ����");
	_printLevel(getUseTargetSetByValue(2), 30);

	gotoxy(50, 32);
	if (_order == 2) printColoredText("�Ҹ� ũ��", RED);
	else printf("�Ҹ� ũ��");
	_printLevel(getUseTargetSetByValue(3), 32);

	gotoxy(50, 34);
	if (_order == 3) printColoredText("�ڷ� ����", RED);
	else printf("�ڷ� ����");
}

// (��� �ӵ�, �Ҹ� ũ���� �� �� ��) �Ǵ� (���� ������ ����, �ʷ�, �Ķ�)�� �����ϴ� �Լ�     - �ڼ���
void _printLevel(int value, int y)
{
	if (y == 28)
	{
		gotoxy(68, y);
		(value == 0) ? printColoredText("��", RED) : printf("��");

		gotoxy(76, y);
		(value == 1) ? printColoredText("��", RED) : printf("��");

		gotoxy(84, y);
		(value == 2) ? printColoredText("��", RED) : printf("��");
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
		(value == 0) ? printColoredText("���", RED) : printf("���");

		gotoxy(75, y);
		(value == 1) ? printColoredText("ȸ��", RED) : printf("ȸ��");

		gotoxy(83, y);
		(value == 2) ? printColoredText("û��", RED) : printf("û��");
	}
}

// ���� ȭ���� ������Ʈ				- �ڽ���
void _updateSettingMenu()
{
	_SettingInputKey();
}

// Ű���� ����Ű �Ǵ� ���͸� �޾ƿͼ� ó��			- �ڼ���
void _SettingInputKey()
{
	char cChar, DirKey;

	if (_kbhit())
	{
		cChar = _getch();
		switch (cChar)
		{
		case 13:			// ����Ű
			_SArrowEvent();

		case -32:
			DirKey = _getch();

			// ���� �� ����
			if (_bSpeed == 0 && _bColor == 0 && _bScale == 0)
			{
				switch (DirKey)
				{
				case 72:		// Ű���� �� ����Ű
					if (_order > 0)
					{
						_SRemoveArrow();
						_order -= 1;
						_printSettingMenu();
						_SRenderArrow();
					}
					break;

				case 80:		// Ű���� �Ʒ� ����Ű
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

			// �� ��
			else
			{
				switch (DirKey)
				{
				case 75:		// Ű���� ���� ����Ű
				{
					_SRemoveArrow2(getTargetSet());
					if (getUseTargetSet() > 0) {
						setTargetSet(-4);
						_printLevel(getUseTargetSetByValue(_order + 1), 28 + (_order * 2));
					}
					_SRenderArrow2(getTargetSet());
				}
				break;

				case 77:		// Ű���� ������ ����Ű
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

// ���� �޴��� �����ϴ� ȭ��ǥ(��)�� ǥ��		- �ڽ���
void _SRenderArrow()
{
	gotoxy(45, _arrowY + (_order * 2)); printf("��");
}

// ���� �޴��� �����ϴ� ȭ��ǥ(��)�� ����		- �ڽ���
void _SRemoveArrow()
{
	gotoxy(45, _arrowY + (_order * 2)); printf(" ");
}

// ���� �޴��� �������� �� �� �� �ϸ� �����ϴ� ȭ��ǥ(��)�� ǥ��		- �ڽ���
void _SRenderArrow2(int targetSet)
{
	if (_order == 1)
	{
		gotoxy(_arrowX2 + (targetSet * 2), _arrowY + 1); printf("��");
	}

	else if (_order == 2)
	{
		gotoxy(_arrowX2 + (targetSet * 2), _arrowY + 3); printf("��");
	}

	else
	{
		gotoxy(_arrowX2 + (targetSet * 2), _arrowY - 1); printf("��");
	}
}


// ���� �޴��� �������� �� �� �� �ϸ� �����ϴ� ȭ��ǥ(��)�� ����		- �ڽ���
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

// TargetSet ���� �޾ƿ��� �Լ�			- �ڽ���
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

// (��)ȭ��ǥ�� ��, �� �Ѱ踦 ���س��� �Լ�			- �ڼ���
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

// ���ϴ� ������ ���� ���� �޾ƿ��� �Լ�			- �ڽ���
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

// (��)ȭ��ǥ�� X��ǥ�� ���ϴ� ����ŭ �����̴� �Լ�			- �ڼ���
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

// ���� �޴��� ������ Enter�� ������ ��			- �ڼ���
void _SArrowEvent()
{
	// ����
	if (_bSpeed == 0 && _bColor == 0 && _bScale == 0)
	{
		switch (_order)
		{
		case 0:		// ���� ��¼ӵ�
			_bSpeed = 1;
			_SRenderArrow2(getTargetSet());
			break;

		case 1:		// ���� ����
			_bColor = 1;
			_SRenderArrow2(getTargetSet());
			break;

		case 2:		// �Ҹ� ũ��
			_bScale = 1;
			_SRenderArrow2(getTargetSet());
			break;

		case 3:		// �ڷ� ����
			system("cls");
			ChangeScene(MainScene);
			_SaveSetting();
			bSettingRender = 0;
			break;

		default:
			break;
		}
	}

	// �����ݴϴ�.
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

	// ���� ����( ���������� Settings.txt�� ����)
	FILE* fp = fopen("Settings.txt", "w");
	int i;

	if (fp == NULL) {
		printf("����\n");
		return;
	}

	// 1 ���ǵ�, 2 ����, 3 ����
	fprintf(fp, "%d %d %d", getUseTargetSetByValue(1), getUseTargetSetByValue(2), getUseTargetSetByValue(3));
	fclose(fp);
}