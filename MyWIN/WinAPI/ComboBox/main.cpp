#include<windows.h>
#include"resource.h"

CONST CHAR* g_sz_VALUES[] = { "This", "is", "my", "first", "Combo", "Box" };

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND hCombo = GetDlgItem(hwnd, IDC_COMBO);
		for (int i = 0; i < sizeof(g_sz_VALUES) / sizeof(g_sz_VALUES[0]); i++)
		{
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)g_sz_VALUES[i]);
		}
		return TRUE;
	}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
			case IDCANCEL:
				{
					EndDialog(hwnd, 0);
					break;
				}
			case IDOK:
			{
				HWND hCombo = GetDlgItem(hwnd, IDC_COMBO); 
				int index = (int)SendMessage(hCombo, CB_GETCURSEL, 0, 0);
				if (index == CB_ERR)
				{
					MessageBox(hwnd, "Ничего не выбрано", "info", MB_OK | MB_ICONWARNING);
					break;
				}

				char buffer[256] = {};
				SendMessage(hCombo, CB_GETLBTEXT, index, (LPARAM)buffer);

				MessageBox(hwnd, buffer, "В поле выбрано: ", MB_OK | MB_ICONINFORMATION);
				break;
			}
		}

		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
		break;
	}
	return FALSE;
}