// clock.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"function.h"

 SYSTEMTIME clocktime[5];
  short count = 0;
  short point = 0;

CRITICAL_SECTION section1;


int main()
{
	//DeleteMenu(GetSystemMenu(GetConsoleWindow(), FALSE), SC_CLOSE, MF_BYCOMMAND);
	//DrawMenuBar(GetConsoleWindow());                                              //使得关闭按钮不可用（取消功能）
	system("color 0A");                                                           //设置窗口背景色及字体颜色
	system("mode con cols=160 lines=40");                                       //设置窗口大小
	InitializeCriticalSection(&section1);                                  //初始化临界区
	bool flag = true;
	int choose;
	
	do {
		system("cls");
		EnterCriticalSection(&section1);
		 Printscreen();
		LeaveCriticalSection(&section1);
		 
		 int X=50,Y=12;
		 Getxy(&X, &Y);
	     Y += 2;
	     X = 50;
		 Setxy(X,Y);
		 printf( "请选择菜单：");
		 scanf_s("%d",&choose);
		 switch (choose)
		 {
		 case 1:EnterCriticalSection(&section1); 
			    Setclock(); 
				LeaveCriticalSection(&section1);
				break;
		 case 2:EnterCriticalSection(&section1);
			    Changeclock();
				LeaveCriticalSection(&section1);
				break;
		 case 3:EnterCriticalSection(&section1);
			    Delateclock();
			    LeaveCriticalSection(&section1);
				break;
		 case 4:Comparebegin();
			   
			    break;
		 case 5:Exit(); break;
		 default:
			printf("请选择正确的菜单项！\n");
			 break;
		 }

		
	} while (flag);
	return 0;
}

		
