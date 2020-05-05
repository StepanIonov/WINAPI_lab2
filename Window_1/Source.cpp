#include <windows.h>
#include <tchar.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd;
	TCHAR szClassName[] = _T("ClassWin");
	WNDCLASS wc;
	MSG msg;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = szClassName;
	wc.lpszMenuName = NULL;
	wc.style = CS_VREDRAW | CS_HREDRAW;

	if (!RegisterClass(&wc))
	{
		MessageBox(NULL, _T("����� ���� �� ���������������"), NULL, MB_OK);
		return 0;
	}

	hWnd = CreateWindow(szClassName, _T("������ ����"), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HWND hSecondWnd; //���������� ������� ����
	switch (msg)
	{
	case WM_LBUTTONDOWN:
		hSecondWnd = FindWindow(NULL, _T("������ ����")); //����� ������� ����
		if (hSecondWnd)
		{
			MessageBox(hWnd, _T("������ ���� �������. ���������� �������"), _T(""), MB_OK);
		}
		else
		{
			MessageBox(hWnd, _T("������ ���� �������. ������ ���� �����������"), _T(""), MB_OK);
			ShellExecute(NULL, NULL, _T("C:\\Users\\User\\Desktop\\4 ���\\���������������� Windows\\����\\��� ����\\lab2\\lab2\\Debug\\Window_2.exe"), NULL, NULL, SW_MINIMIZE);
			MessageBox(hWnd, _T("������ ���� �������. ���������� �������"), _T(""), MB_OK);
			hSecondWnd = FindWindow(NULL, _T("������ ����"));
		}
		SendMessage(hSecondWnd, WM_USER + 1, (WPARAM)hWnd, NULL); //�������� ����������� 
		break;
	
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}