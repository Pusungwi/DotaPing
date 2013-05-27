/* DotaPing - Dota 2 Server Ping Check Program For Windows
	Coded By Yi 'Pusungwi' Yeon Jae - 2013 */

#include "stdafx.h"
#include "DotaPing.h"
#include "DotaPingCore.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;								// 현재 인스턴스입니다.
TCHAR szTitle[MAX_LOADSTRING];					// 제목 표시줄 텍스트입니다.
TCHAR szWindowClass[MAX_LOADSTRING];			// 기본 창 클래스 이름입니다.

// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: 여기에 코드를 입력합니다.
	MSG msg;
	HACCEL hAccelTable;

	// 전역 문자열을 초기화합니다.
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_DOTAPING, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 응용 프로그램 초기화를 수행합니다.
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DOTAPING));

	// 기본 메시지 루프입니다.
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DOTAPING));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_DOTAPING);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   hWnd = CreateWindow(szWindowClass, szTitle, WS_BORDER,
      CW_USEDEFAULT, 0, 200, 250, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND	- 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT	- 주 창을 그립니다.
//  WM_DESTROY	- 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int sgnPing = PING_DEFAULT_VALUE;
	WCHAR sgnPingStr[7] = _T("");

	int uswPing = PING_DEFAULT_VALUE;
	WCHAR uswPingStr[7] = _T("");

	int usePing = PING_DEFAULT_VALUE;
	WCHAR usePingStr[7] = _T("");

	int shnPing = PING_DEFAULT_VALUE;
	WCHAR shnPingStr[7] = _T("");

	int luxPing = PING_DEFAULT_VALUE;
	WCHAR luxPingStr[7] = _T("");

	int ausPing = PING_DEFAULT_VALUE;
	WCHAR ausPingStr[7] = _T("");

	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_CREATE:
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 메뉴 선택을 구문 분석합니다.
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		TextOut(hdc, 40, 20, L"싱가폴 : ", 6);
		TextOut(hdc, 40, 40, L"미동부 : ", 6);
		TextOut(hdc, 40, 60, L"미서부 : ", 6);
		TextOut(hdc, 8, 80, L"룩셈부르크 : ", 8);
		TextOut(hdc, 40, 100, L"상하이 : ", 6);
		TextOut(hdc, 56, 120, L"호주 : ", 5);

		sgnPing = getPingValueFromSingapore();
		if (sgnPing == PING_ERROR_VALUE) {
			wcsstr(sgnPingStr, L"X");
		} else {
			_itow_s(sgnPing, sgnPingStr, 10);
			wcscat_s(sgnPingStr, L"ms");
		}
		TextOut(hdc, 100, 20, sgnPingStr, wcslen(sgnPingStr));

		usePing = getPingValueFromUSEast();
		if (usePing == PING_ERROR_VALUE) {
			wcsstr(usePingStr, L"X");
		} else {
			_itow_s(usePing, usePingStr, 10);
			wcscat_s(usePingStr, L"ms");	
		}
		TextOut(hdc, 100, 40, usePingStr, wcslen(usePingStr));

		uswPing = getPingValueFromUSWest();
		_itow_s(uswPing, uswPingStr, 10);
		wcscat_s(uswPingStr, L"ms");
		TextOut(hdc, 100, 60, uswPingStr, wcslen(uswPingStr));

		luxPing = getPingValueFromLuxemburg();
		_itow_s(luxPing, luxPingStr, 10);
		wcscat_s(luxPingStr, L"ms");
		TextOut(hdc, 100, 80, luxPingStr, wcslen(luxPingStr));

		shnPing = getPingValueFromShanghai();
		_itow_s(shnPing, shnPingStr, 10);	
		wcscat_s(shnPingStr, L"ms");
		TextOut(hdc, 100, 100, shnPingStr, wcslen(shnPingStr));

		ausPing = getPingValueFromAustrailia();
		_itow_s(ausPing, ausPingStr, 10);
		wcscat_s(ausPingStr, L"ms");
		TextOut(hdc, 100, 120, ausPingStr, wcslen(ausPingStr));

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
