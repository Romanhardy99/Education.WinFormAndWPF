#include<Windows.h>
#include"resource.h"

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR  lpCmdLine, INT nCmdShow) 
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_INITDIALOG: //инициализация окна диалога. Эта секция отрабатывает 1 раз - при запуске окна.
			break;
		case WM_COMMAND: //В этой секции обрабатываются нажатия кнопок, клавишь и другие события.
			switch (LOWORD(wParam))
			{
			case IDOK: MessageBox(hwnd, "Была нажата кнопка ОК", "Info", MB_OK | MB_ICONINFORMATION);
				break;
			case IDCANCEL: EndDialog(hwnd, 0);
				break;
			}
			break;
		case WM_CLOSE: //Отрабатывает 1 раз при закрытии окна.
			EndDialog(hwnd, 0);
	}
	return FALSE;
}