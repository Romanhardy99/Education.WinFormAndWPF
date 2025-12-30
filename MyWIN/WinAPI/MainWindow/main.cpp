#undef UNICODE
#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<stdio.h>

CONST CHAR g_sz_CLASS_NAME[] = "Main Window PV_522";  //Имя класса окна

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	WNDCLASSEX wClass;                   //Создаем структуру класса окна
	ZeroMemory(&wClass, sizeof(wClass));        //Обнуляем память структуры
	wClass.style = NULL;                //Стиль окна
	wClass.cbSize = sizeof(wClass);            //Размер структуры
	wClass.cbClsExtra = 0;                //cb - Count Bytes
	wClass.cbWndExtra = 0;

	wClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);    //Иконка окна
	wClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);  //Маленькая иконка окна
	wClass.hCursor = LoadCursor(NULL, IDC_ARROW);    //Курсор окна
	wClass.hbrBackground = (HBRUSH)COLOR_WINDOW;    //Цвет фона окна

	wClass.hInstance = hInstance;            //Дескриптор экземпляра приложения
	wClass.lpszMenuName = NULL;             //Имя меню  
	wClass.lpszClassName = g_sz_CLASS_NAME;        //Имя класса окна
	wClass.lpfnWndProc = WndProc;

	//wClass.lpfnWndProc = DefWindowProc;        //Указатель на оконную процедуру

	//1.3) Зарегистрировать этот класс в ОС;
	if (!RegisterClassEx(&wClass))
	{
		MessageBox(NULL, "Class registration failed", NULL, MB_OK | MB_ICONERROR);
	}
	//2) Создание окна:

	INT screen_width = GetSystemMetrics(SM_CXSCREEN); // узнаем размер экрана
	INT screen_height = GetSystemMetrics(SM_CYSCREEN);
	INT window_width = screen_width * 3 / 4;
	INT window_height = screen_height * 3 / 4;
	INT window_start_x = screen_width / 8;
	INT window_start_y = screen_height / 8;
	HWND hwnd = CreateWindowEx
	(
		NULL, //exStyles
		g_sz_CLASS_NAME, //ClassName
		g_sz_CLASS_NAME, //window title
		WS_OVERLAPPEDWINDOW, //Cтиль окна. Набор стилей всегда зависит от класса окна. 
		//Стиль главного окна всегда WS_OVERLAPPEDWINDOW
		window_start_x, window_start_y, //Начальная позиция окна (при запуске)
		window_width, window_height, //Размер окна
		NULL,		//Parent window
		NULL,		//hMenu. Для главного окна этот параметр определяет главное меню.
		//Для дочернего окна (Control) этот параметр содержит ResourceID дочернего окна.
		//Благодаря hMenu, дочернее окно всегда можно найти при помощи функции GetDlgItem()
		hInstance,
		NULL
	);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failed", NULL, MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);
	//3) Запуск цикла сообщений

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
		HWND hStatic = CreateWindowEx
		(
			NULL, //exStyle
			"Static", //Window class
			"Этот текст создан функцией CreateWindowEx()", //Window title SendMessage(hwnd, WM_SETTEXT,...)
			WS_CHILD | WS_VISIBLE, //Window styles
			10, 10, //Position 
			500, 25, //Size
			hwnd, //Parent Window
			(HMENU)1000, //ResourceID
			GetModuleHandle(NULL),
			NULL
		);

		HWND hEdit = CreateWindowEx
		(
			NULL,
			"Edit",
			"",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			10, 40,
			500, 22,
			hwnd,
			(HMENU)1001,
			GetModuleHandle(NULL),
			NULL
		);
		//100 ...999 - Окна, значки
		//1000 ... 40000 - элементы управления окна
		CreateWindowEx
		(
			NULL,
			"Button",
			"Применить",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			410, 70,
			100, 25,
			hwnd,
			(HMENU)1002,
			GetModuleHandle(NULL),
			NULL
		);
	}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case 1002:
		{
			CHAR sz_buffer[MAX_PATH] = {};
			HWND hStatic = GetDlgItem(hwnd, 1000);
			HWND hEdit = GetDlgItem(hwnd, 1001);
			SendMessage(hEdit, WM_GETTEXT, MAX_PATH, (LPARAM)sz_buffer);
			SendMessage(hStatic, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
			break;
		}
		
	case WM_SIZE:
	case WM_MOVE:
	{
		RECT rect;
		GetWindowRect(hwnd, &rect);
		CHAR sz_title[MAX_PATH]{};
		sprintf(sz_title, "%s - Position: %ix%i, Size: %ix%i",
			g_sz_CLASS_NAME, rect.left, rect.top,
			rect.right - rect.left, rect.bottom - rect.top);
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_title);
	}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return FALSE;
}