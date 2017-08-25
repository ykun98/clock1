#include"function.h"
#include"stdafx.h"

using namespace std;

extern SYSTEMTIME clocktime[5];
extern short count;
extern short point;

extern CRITICAL_SECTION section1;

void Setxy(int x, int y)
{
	COORD coord1 = { (short)x, (short)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord1);
}

void  Getxy(int* x, int* y)

{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coordScreen = { 0, 0 };
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(hConsole, &csbi))
	{
		*x = csbi.dwCursorPosition.X;
		*y = csbi.dwCursorPosition.Y;
	}
}
void Getclock()
{
	FILE *getclocktime;
	if (!fopen_s(&getclocktime, "clocktime.dat", "r"))
	{
		for (int i = 0; i < 5; i++)
		{
			fscanf(getclocktime, "%hd", &clocktime[i].wYear);
			fscanf(getclocktime, "%d", &clocktime[i].wMonth);
			fscanf(getclocktime, "%d", &clocktime[i].wDay);
			fscanf(getclocktime, "%d", &clocktime[i].wHour);
			fscanf(getclocktime, "%d", &clocktime[i].wMinute);

		}
	}
	else
	{
		return;
	}
	fclose(getclocktime);
}
void Printclocktime()
{
	Getclock();
	int x, y;
	if (clocktime[0].wYear == 0)
		return;
	for (int i = 0; i < 5; i++)
		if (clocktime[i].wYear != 2017)
		{
			count = i;
			break;
		}
	if (clocktime[4].wYear == 2017)
		count = 5;
	
	Getxy(&x, &y);
	x = 50;
	y += 2;
	Setxy(x, y);
	printf("***********************当前已设闹钟***********************\n");
	
	for (int i = 0; i < count; i++)
	{
		Getxy(&x, &y);
		x = 50;
		y += 2;
		Setxy(x, y);
		printf("%x :  %hd 年  %d 月  %d 日 %d : %d \n", i,clocktime[i].wYear, clocktime[i].wMonth, clocktime[i].wDay, clocktime[i].wHour, clocktime[i].wMinute);
	}
}
void Saveclock()
{
	FILE *clocksave;
	
		
	clocksave=fopen("clocktime.dat","w");
	for (int i = 0; i < 5; i++)
	{
		short year = clocktime[i].wYear;
		fprintf(clocksave, "%d\n%d\n%d\n%d\n%d\n",year, clocktime[i].wMonth, clocktime[i].wDay, clocktime[i].wHour, clocktime[i].wMinute);	
	}
	fclose(clocksave);
}
void Setclock()
{
	int i;
	for (int i = 0; i < 5; i++)                          //得到第一个空白的闹钟编号
		if (clocktime[i].wYear == 0)
		{
			count = i;
			break;
		}
		else
			count = 5;
	if (count == 5)
	{
		printf("闹钟数已满！请先删除一个闹钟！");
		Sleep(2000);
		return;
	}
	for ( i = 0; i < 5; i++)
	{
		if (clocktime[i].wYear == 0)
		{
			count = i;
			break;
		}
	}
	
	clocktime[count].wYear = 2017;       //年份用来判断该闹钟是否存在作为flag
	while (1)
	{
		printf("请依次输入月份 日期  时间 （输入0为所有月或日，格式如：2 3 17 20）\n");
		scanf("%d %d %d %d", &clocktime[count].wMonth, &clocktime[count].wDay, &clocktime[count].wHour, &clocktime[count].wMinute);
		if ((clocktime[count].wMonth > 12 || clocktime[count].wMonth < 0 )|| (clocktime[count].wDay > 31 || clocktime[count].wDay < 0)|| (clocktime[count].wHour > 23 || clocktime[count].wHour < 0) || (clocktime[count].wMinute >59 || clocktime[count].wMinute < 0))
		    printf("输入数据错误，请输入正确数据（如：小时不能超过23且不能为负1）！！！\n");
		else
		{
			Saveclock();
			break;
			
		}	
	}
	
}

void Changeclock()                                 //修改闹钟
{
	system("cls");
	Printclocktime();
	printf("请选择要修改的闹铃：");
	scanf_s("%hx", &count);
	SYSTEMTIME TIMEN;
	GetSystemTime(&TIMEN);
	clocktime[count].wYear = TIMEN.wYear;
	while (1)
	{
		printf("请依次输入月份 日期  时间 （输入0为所有月或日，格式如：2 3 17 20）\n");
		scanf("%d %d %d %d", &clocktime[count].wMonth, &clocktime[count].wDay, &clocktime[count].wHour, &clocktime[count].wMinute);
		if ((clocktime[count].wMonth > 12 || clocktime[count].wMonth < 0) || (clocktime[count].wDay > 31 || clocktime[count].wDay < 0) || (clocktime[count].wHour > 23 || clocktime[count].wHour < 0) || (clocktime[count].wMinute >59 || clocktime[count].wMinute < 0))
			printf("输入数据错误，请输入正确数据（如：小时不能超过23且不能为负1）！！！\n");
		else
		{
			Saveclock();
			break;

		}
			
	}
	

}
void Delateclock()
{
	system("cls");
	Printclocktime();
	for (int i = 0; i < 5; i++)                          //得到第一个空白的闹钟编号
		if (clocktime[i].wYear == 0)
		{
			count = i;
			break;
		}
		else
			count = 5;
	if (count == 0 && clocktime[0].wYear == 0)
	{
		printf("未设置任何闹钟！！");
		return;
	}
	if (clocktime[4].wYear == 2017)
	{

	}
	printf("请选择要删除的闹铃：");
	int c;
	scanf_s("%d", &c);
	if (c > 4)
	{
		printf("不存在的闹钟！");
		return;
	}
	
	for (int j = c; j < count; j++)
	{
		if (j == 4)
			break;
		clocktime[j] = clocktime[j + 1];
	}
	clocktime[4].wYear = 0;
	clocktime[4].wMonth = 0;
	clocktime[4].wDay = 0;
	clocktime[4].wHour = 0;
	clocktime[4].wMinute = 0;


	Saveclock();


}
void Printscreen()
{
	/*SYSTEMTIME prtime;
	GetLocalTime(&prtime);
	printf("%hx 月 %hx 日   %d:%d", prtime.wMonth, prtime.wDay, prtime.wHour, prtime.wMinute);
	*/

	Setxy(50,1);
	printf("**********************请选择闹钟菜单**********************\n");
	Setxy(50, 3);
	printf("*                      一 新增闹钟                       *\n");
	Setxy(50, 5); 
	printf("*                      二 修改闹钟                       *\n");
	Setxy(50, 7); 
	printf("*                      三 删除闹钟                       *\n");
	Setxy(50, 9); 
	printf("*                      四 开始闹钟                       *\n");
	Setxy(50, 11);
	printf("*                      五 退出程序                       *\n");
	Setxy(50, 13);
	printf("**********************************************************\n");
	Printclocktime();
}

void Exit()
{
	while (10)
	{
		printf("退出程序后闹钟将不会响铃，是否退出？1，退出  2，取消 \n");
		int flag;
		scanf_s("%d", &flag);
		if (flag == 1)
			exit(1);
		if (flag == 2)
			return;
		else
			printf("请输入1或2");
	}
}

/*DWORD WINAPI Changeinf(LPVOID lpparameter)
{
	Sleep(50);
	for (int i = 0; i <= 19; i++)
		printf("\b");
	printf("请按任意键停止. . . ");
	return 3;
}
DWORD WINAPI Ring(LPVOID lpparameter)
{
	HANDLE h2;
	int x, y;
	mciSendString(TEXT("open E:\\a.wav alias ring"), NULL, 0, NULL);
	mciSendString(TEXT("play ring"), NULL, 0, NULL);
	Getxy(&x, &y);
	x = 50;
	y = y + 2;
	h2 = CreateThread(NULL, 0, Changeinf, NULL, 0, NULL);
	system("pause");
	mciSendString(TEXT("stop ring"), NULL, 0, NULL);
	mciSendString(TEXT("close ring"), NULL, 0, NULL);
	return 2;
}*/
DWORD WINAPI Compareclock0(LPVOID lpparameter)                              //进行时间比对并响铃
{
	SYSTEMTIME comtime, localtime;


	EnterCriticalSection(&section1);                                           //获取参数point指向的闹钟
	comtime = clocktime[0];
	LeaveCriticalSection(&section1);

	

	GetLocalTime(&localtime);

	if ((comtime.wHour < localtime.wHour) || (comtime.wHour == comtime.wHour && comtime.wMinute < localtime.wMinute))
		return 0;

	if ((comtime.wMonth == localtime.wMonth && comtime.wDay == localtime.wDay) || (comtime.wMonth == 0 && comtime.wDay == localtime.wDay) || (comtime.wMonth == localtime.wMonth && comtime.wDay == 0) || (comtime.wMonth == 0 && comtime.wDay == 0))
	{
		while (1)
		{
			GetLocalTime(&localtime);
			if (comtime.wHour == localtime.wHour && comtime.wMinute == localtime.wMinute)
			{
				int x, y;
				mciSendString(TEXT("open  E:\\a.wav alias ring"), NULL, 0, NULL);      //open E:\\a.wav alias ring
				mciSendString(TEXT("play ring"), NULL, 0, NULL);
				printf("%d : %d 到了! \n ", comtime.wHour, comtime.wMinute);
				system("pause");
				mciSendString(TEXT("stop ring"), NULL, 0, NULL);
				mciSendString(TEXT("close ring"), NULL, 0, NULL);                                                                        //ring1 = CreateThread(NULL, 0, Ring, NULL, 0, NULL);
																																		 //WaitForSingleObject(ring1, INFINITE);
				return 1;
			}
			
		}
	}

}
DWORD WINAPI Compareclock1(LPVOID lpparameter)
{
	SYSTEMTIME comtime, localtime;


	EnterCriticalSection(&section1);                                           //获取参数point指向的闹钟
	comtime = clocktime[1];
	LeaveCriticalSection(&section1);



	GetLocalTime(&localtime);
	if ((comtime.wHour < localtime.wHour) || (comtime.wHour == comtime.wHour && comtime.wMinute < localtime.wMinute))
		return 1;

	if ((comtime.wMonth == localtime.wMonth && comtime.wDay == localtime.wDay) || (comtime.wMonth == 0 && comtime.wDay == localtime.wDay) || (comtime.wMonth == localtime.wMonth && comtime.wDay == 0) || (comtime.wMonth == 0 && comtime.wDay == 0))
	{
		while (1)
		{
			GetLocalTime(&localtime);
			if (comtime.wHour == localtime.wHour && comtime.wMinute == localtime.wMinute)
			{
				int x, y;
				mciSendString(TEXT("open  E:\\a.wav alias ring"), NULL, 0, NULL);              //open E:\\a.wav alias ring
				mciSendString(TEXT("play ring"), NULL, 0, NULL);
				printf("%d : %d 到了! \n ", comtime.wHour, comtime.wMinute);
				system("pause");
				mciSendString(TEXT("stop ring"), NULL, 0, NULL);
				mciSendString(TEXT("close ring"), NULL, 0, NULL);                                                                        //ring1 = CreateThread(NULL, 0, Ring, NULL, 0, NULL);
																																		 //WaitForSingleObject(ring1, INFINITE);
				return 1;
			}
			
		}
	}

}
DWORD WINAPI Compareclock2(LPVOID lpparameter)
{
	SYSTEMTIME comtime, localtime;


	EnterCriticalSection(&section1);                                           //获取参数point指向的闹钟
	comtime = clocktime[2];
	LeaveCriticalSection(&section1);



	GetLocalTime(&localtime);
	if ((comtime.wHour < localtime.wHour) || (comtime.wHour == comtime.wHour && comtime.wMinute < localtime.wMinute))
		return 2;

	if ((comtime.wMonth == localtime.wMonth && comtime.wDay == localtime.wDay) || (comtime.wMonth == 0 && comtime.wDay == localtime.wDay) || (comtime.wMonth == localtime.wMonth && comtime.wDay == 0) || (comtime.wMonth == 0 && comtime.wDay == 0))
	{
		while (1)
		{
			GetLocalTime(&localtime);
			if (comtime.wHour == localtime.wHour && comtime.wMinute == localtime.wMinute)
			{
				
				mciSendString(TEXT("open  E:\\a.wav alias ring"), NULL, 0, NULL);                //open E:\\a.wav alias ring
				mciSendString(TEXT("play ring"), NULL, 0, NULL);
				printf("%d : %d 到了! \n ", comtime.wHour, comtime.wMinute);
				system("pause");
				mciSendString(TEXT("stop ring"), NULL, 0, NULL);
				mciSendString(TEXT("close ring"), NULL, 0, NULL);                                                                        //ring1 = CreateThread(NULL, 0, Ring, NULL, 0, NULL);
																																		 //WaitForSingleObject(ring1, INFINITE);
				return 1;
			}
			
		}
	}

}
DWORD WINAPI Compareclock3(LPVOID lpparameter)
{
	SYSTEMTIME comtime, localtime;


	EnterCriticalSection(&section1);                                           //获取参数point指向的闹钟
	comtime = clocktime[3];
	LeaveCriticalSection(&section1);



	GetLocalTime(&localtime);
	if ((comtime.wHour < localtime.wHour) || (comtime.wHour == comtime.wHour && comtime.wMinute < localtime.wMinute))
		return 3;

	if ((comtime.wMonth == localtime.wMonth && comtime.wDay == localtime.wDay) || (comtime.wMonth == 0 && comtime.wDay == localtime.wDay) || (comtime.wMonth == localtime.wMonth && comtime.wDay == 0) || (comtime.wMonth == 0 && comtime.wDay == 0))
	{
		while (1)
		{
			GetLocalTime(&localtime);
			if (comtime.wHour == localtime.wHour && comtime.wMinute == localtime.wMinute)
			{
				int x, y;
				mciSendString(TEXT("open  E:\\a.wav alias ring"), NULL, 0, NULL);            //open E:\\a.wav alias ring
				mciSendString(TEXT("play ring"), NULL, 0, NULL);
				printf("%d : %d 到了! \n ", comtime.wHour, comtime.wMinute);
				system("pause");
				mciSendString(TEXT("stop ring"), NULL, 0, NULL);
				mciSendString(TEXT("close ring"), NULL, 0, NULL);                                                                        //ring1 = CreateThread(NULL, 0, Ring, NULL, 0, NULL);
																																		 //WaitForSingleObject(ring1, INFINITE);
				return 1;
			}
			
		}
	}

}
DWORD WINAPI Compareclock4(LPVOID lpparameter)                                      //由于只有一个函数时多次创建新线程会导致某些错误，目前没有找到解决办法
{                                                                                   //于是只能每个闹铃对应一个函数，创建线程时使用相应函数避免错误。
	SYSTEMTIME comtime, localtime;


	EnterCriticalSection(&section1);                                           //获取参数point指向的闹钟
	comtime = clocktime[4];
	LeaveCriticalSection(&section1);



	GetLocalTime(&localtime);
	if ((comtime.wHour < localtime.wHour) || (comtime.wHour == comtime.wHour && comtime.wMinute < localtime.wMinute))
		return 4;

	if ((comtime.wMonth == localtime.wMonth && comtime.wDay == localtime.wDay) || (comtime.wMonth == 0 && comtime.wDay == localtime.wDay) || (comtime.wMonth == localtime.wMonth && comtime.wDay == 0) || (comtime.wMonth == 0 && comtime.wDay == 0))
	{
		while (1)
		{
			GetLocalTime(&localtime);
			if (comtime.wHour == localtime.wHour && comtime.wMinute == localtime.wMinute)
			{
				int x, y;
				mciSendString(TEXT("open  E:\\a.wav alias ring"), NULL, 0, NULL);              //open E:\\a.wav alias ring
				mciSendString(TEXT("play ring"), NULL, 0, NULL);
				printf("%d : %d 到了! \n ",comtime.wHour,comtime.wMinute);
				system("pause");
				mciSendString(TEXT("stop ring"), NULL, 0, NULL);
				mciSendString(TEXT("close ring"), NULL, 0, NULL);                                                                        //ring1 = CreateThread(NULL, 0, Ring, NULL, 0, NULL);
																																		 //WaitForSingleObject(ring1, INFINITE);
				return 1;
			}
			
		}
	}
	
}

void Comparebegin()
{
	HANDLE compare[5];
	int count1,i=0;
	EnterCriticalSection(&section1);
	for (int i = 0; i < 5; i++)                          //得到第一个空白的闹钟编号
		if (clocktime[i].wYear == 0)
		{
			count = i ;
			break;
		}
		else
			count = 5;
	count1 = count;

	LeaveCriticalSection(&section1);

	printf("开始闹钟后将不再接受菜单选择！！ 1 开始   2 取消 :");
	int flag1;
	scanf("%d", &flag1);
	if (flag1 == 2)
		return;
	if (flag1 == 1)
	    printf("闹钟已开始！\n");
	else
		return;
	switch (count1)                                                     //分支语句对应有几个闹钟就创建几个线程并且只会使用相应的函数创建相应的线程
	{
	case 1:
		compare[0]=CreateThread(NULL, 0, Compareclock0, NULL, 0, NULL);

		WaitForSingleObject(compare[0], INFINITE);                     //创建线程后等待线程结束
		break;
	case 2:
		compare[0] = CreateThread(NULL, 0, Compareclock0, NULL, 0, NULL);
		
		compare[1] = CreateThread(NULL, 0, Compareclock1, NULL, 0, NULL);

		WaitForSingleObject(compare[0], INFINITE);                    //创建多个线程时等待所有线程结束
		WaitForSingleObject(compare[1], INFINITE);
	
		break;
	case 3:
		
		compare[0] = CreateThread(NULL, 0, Compareclock0, NULL, 0, NULL);
		

		
		compare[1] = CreateThread(NULL, 0, Compareclock1, NULL, 0, NULL);
		

		
		compare[2] = CreateThread(NULL, 0, Compareclock2, NULL, 0, NULL);

		WaitForSingleObject(compare[0], INFINITE);
		WaitForSingleObject(compare[1], INFINITE);
		WaitForSingleObject(compare[2], INFINITE);
		
		break;
	case 4:
		
		compare[0] = CreateThread(NULL, 0, Compareclock0, NULL, 0, NULL);
	

		
		compare[1] = CreateThread(NULL, 0, Compareclock1, NULL, 0, NULL);
	

	
		compare[2] = CreateThread(NULL, 0, Compareclock2, NULL, 0, NULL);
	

	
		compare[3] = CreateThread(NULL, 0, Compareclock3, NULL, 0, NULL);

		WaitForSingleObject(compare[0], INFINITE);
		WaitForSingleObject(compare[1], INFINITE);
		WaitForSingleObject(compare[2], INFINITE);
		WaitForSingleObject(compare[3], INFINITE);
	
		break;
	case 5:
	
		compare[0] = CreateThread(NULL, 0, Compareclock0, NULL, 0, NULL);
	

	
		compare[1] = CreateThread(NULL, 0, Compareclock1, NULL, 0, NULL);
	

		
		compare[2] = compare[5] = CreateThread(NULL, 0, Compareclock2, NULL, 0, NULL);
	

	
		compare[3] = CreateThread(NULL, 0, Compareclock3, NULL, 0, NULL);
	

	
		compare[4] = CreateThread(NULL, 0, Compareclock4, NULL, 0, NULL);

		WaitForSingleObject(compare[0], INFINITE);
		WaitForSingleObject(compare[1], INFINITE);
		WaitForSingleObject(compare[2], INFINITE);
		WaitForSingleObject(compare[3], INFINITE);
		WaitForSingleObject(compare[4], INFINITE);
		
		break;
		
	default:
		break;
	}

	/*for (i = 0; i < count1; i++)
	{
		WaitForSingleObject(compare[i], INFINITE);
	}*/

	/*int x1, y1;
	Getxy(&x1, &y1);
	x1 = 50;
	y1 += 1;
	while (1)     打印出当前时间
	{
		Setxy(x1, y1);
		GetLocalTime(&prtime);
		printf("%hx 月 %hx 日   %hx:%hx", prtime.wMonth, prtime.wDay, prtime.wHour, prtime.wMinute);


	}*/
}

