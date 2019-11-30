/* ****************************************************************
* ���α׷��� : Util.h
* �ۼ��� : �ں���, 1�� �ù�(�ڽ���, �ڰ��, �ڼ���, �ڼ���)
* �ۼ��� : 2017.05.31
* ���α׷� ���� : ���α׷��� ���������� ���Ǵ� �Լ����� �����Դϴ�.
**************************************************************** */

#pragma once

#include "SceneManager.h"
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <mmsystem.h>

#pragma comment(lib,"winmm.lib")

// ȭ�鿡 ����ϴ� ������ �����մϴ�.    - �ڼ���
#define BLACK 0
#define DARK_BLUE 1
#define DARK_GREEN 2
#define DARK_CYAN 3
#define DARK_RED 4
#define DARK_PURPLE 5
#define DARK_YELLOW 6
#define GRAY 7
#define DARK_GRAY 8
#define BLUE 9
#define GREEN 10
#define CYAN 11
#define RED 12
#define PURPLE 13
#define YELLOW 14
#define WHITE 15


/************************�� �����δ� �Լ�******************************/

void fullscreen();		//	��üȭ��.

void gotoxy(int x, int y);
void changeTextColor(int colorID);
void printColoredText(char* str, int colorID);
void PrintTextFile(char * fileName);
void PrintTextFileP(char name[], char order[], char format[]);
void DrawBox(int x, int y, int width, int height);

// �����δ� ����â
void setSpeedSelected(int select);
void setSoundSelected(int select);
void setColorSelected(int select);

char * getTextFileName(char * name, int i);
void printBlank();

int getSpeed();
int getSpeedOrder();
int getSound();
int getSoundOrder();
int getColor();
int getColorOrder();


void  ESC();
void StartBGMusic();
void StartGameBGMusic();
void StartClearMusic();
void StartFailMusic();
void EndMusic();
void _loadSetting();

int _loadGame();

int _saveGame(int n);
