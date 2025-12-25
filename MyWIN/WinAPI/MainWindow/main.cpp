#undef UNICODE
#include<Windows.h>

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
	HWND hwnd = CreateWindowEx
	(
		NULL, //exStyles
		g_sz_CLASS_NAME, //ClassName
		g_sz_CLASS_NAME, //window title
		WS_OVERLAPPEDWINDOW, //Cтиль окна. Набор стилей всегда зависит от класса окна. 
		//Стиль главного окна всегда WS_OVERLAPPEDWINDOW
		CW_USEDEFAULT, CW_USEDEFAULT, //Начальная позиция окна (при запуске)
		CW_USEDEFAULT, CW_USEDEFAULT, //Размер окна
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
		break;
	case WM_COMMAND:
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