#include<Windows.h>
#include"resource.h"
bool showLogin = true;
CONST CHAR g_sz_INVITE[] = "Введите имя пользователя";

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
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);
		
		HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
		SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)g_sz_INVITE);

		showLogin = true;
		return TRUE;
	}
	break;
	case WM_COMMAND: //В этой секции обрабатываются нажатия кнопок, клавишь и другие события.
		if (LOWORD(wParam) == IDC_EDIT_LOGIN &&
			HIWORD(wParam) == EN_SETFOCUS)
		{
			if (showLogin)
			{
				SetDlgItemText(hwnd, IDC_EDIT_LOGIN, "");
				showLogin = false;
			}
		}
		switch (LOWORD(wParam))
		{
		case IDC_EDIT_LOGIN:
			{
				CONST INT SIZE = 256;
				CHAR sz_buffer[SIZE] = {};
				//HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN); //hwnd - родительское окно; IDC_EDIT_LOGIN - ResourceID элемента, дескриптор которого мы хотим получить
				SendMessage((HWND)lParam, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);

				if (HIWORD(wParam) == EN_SETFOCUS && strcmp(sz_buffer, g_sz_INVITE) == 0)
						SendMessage((HWND)lParam, WM_GETTEXT, 0, (LPARAM)"");
				
				if (HIWORD(wParam) == EN_KILLFOCUS  && strcmp(sz_buffer, "") == 0)
						SendMessage((HWND)lParam, WM_SETTEXT, 0, (LPARAM)g_sz_INVITE);
				
			}
			break;
		case IDC_BUTTON_COPY:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
			HWND hEditPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);

			//WM_WindowsMessage (такое сообщение можно отправить любому окну)
			SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			SendMessage(hEditPassword, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
		break;
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