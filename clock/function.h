#pragma once
#include"stdafx.h"
//functionͳһ��ɺ���������ʵ��

//����ԭ�Ͷ���
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



void Setxy(int x, int y);//���ù��λ��
void Getxy(int* x, int* y);//��ȡ���λ��