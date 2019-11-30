/* ****************************************************************
* 프로그램명 : Util.h
* 작성자 : 박병직, 1조 올박(박신형, 박경덕, 박성진, 박수현)
* 작성일 : 2017.05.31
* 프로그램 설명 : 프로그램에 전반적으로 사용되는 함수들의 집합입니다.
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

// 화면에 출력하는 색깔을 설정합니다.    - 박성진
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


/************************이 밑으로는 함수******************************/

void fullscreen();		//	전체화면.

void gotoxy(int x, int y);
void changeTextColor(int colorID);
void printColoredText(char* str, int colorID);
void PrintTextFile(char * fileName);
void PrintTextFileP(char name[], char order[], char format[]);
void DrawBox(int x, int y, int width, int height);

// 밑으로는 세팅창
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
