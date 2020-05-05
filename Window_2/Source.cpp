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
		MessageBox(NULL, _T("Класс окна не зарегистрирован"), NULL, MB_OK);
		return 0;
	}

	hWnd = CreateWindow(szClassName, _T("Второе окно"), WS_OVERLAPPEDWINDOW,
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
	static HWND hFirstWnd = NULL; //дескриптор первого окна

	switch (msg)
	{
	case WM_USER + 1: //сообщение от первого окна
		hFirstWnd = (HWND)wParam; //получение дескриптора второго окна
		MessageBox(hWnd, _T("Дескриптор первого окна получен"), _T(""), MB_OK);
		break;

	case WM_RBUTTONDOWN:
		if (hFirstWnd)
		{
			MessageBox(NULL, _T("Первое окно закрывается"), _T(""), MB_OK);
			SendMessage(hFirstWnd, WM_CLOSE, 0, 0); //закрытие первого окна
			hFirstWnd = NULL;
		}
		else
			MessageBox(NULL, _T("Дескриптор первого окна не получен"), _T(""), MB_OK);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}