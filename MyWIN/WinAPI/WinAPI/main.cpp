#include<windows.h>

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR  llppCCmmddLLiinnee, INT nCmdShow) 
{
	MessageBox
	(
		NULL, 
		"Hello Windows!", 
		"MessageBox", 
		MB_YESNOCANCEL | MB_ICONINFORMATION | MB_HELP | MB_DEFBUTTON3 | MB_SYSTEMMODAL
	);
	return 0;
}