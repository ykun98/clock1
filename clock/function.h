#pragma once
#include"stdafx.h"
//function统一完成函数定义与实现

//函数原型定义
void Printscreen();
void Getclock();
void Setclock();
void Changeclock();
void Delateclock();
void Saveclock();
void Exit();
void Printclocktime();
void Comparebegin();

DWORD WINAPI Compareclock0(LPVOID lpparameter);
DWORD WINAPI Compareclock1(LPVOID lpparameter);
DWORD WINAPI Compareclock2(LPVOID lpparameter);
DWORD WINAPI Compareclock3(LPVOID lpparameter);
DWORD WINAPI Compareclock4(LPVOID lpparameter);



void Setxy(int x, int y);//设置光标位置
void Getxy(int* x, int* y);//获取光标位置