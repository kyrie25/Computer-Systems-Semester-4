// Keygen.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Utils.h"

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_KEYGEN, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_KEYGEN));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_KEYGEN));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_KEYGEN);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT, 0, 300, 200, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

HWND CreateControlWithFont(
	LPCWSTR lpClassName,
	LPCWSTR lpWindowName,
	DWORD dwStyle,
	int x, int y, int width, int height,
	HWND hWndParent,
	HMENU hMenu,
	HINSTANCE hInst
) {
	HWND hWndCtrl = CreateWindowW(lpClassName, lpWindowName,
		dwStyle | WS_CHILD | WS_VISIBLE,
		x, y, width, height,
		hWndParent, hMenu, hInst, nullptr);
	if (hWndCtrl) {
		SendMessage(hWndCtrl, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE);
	}
	return hWndCtrl;
}


//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int selectedRadio = 1; // Variable to store selected radio button

	switch (message)
	{
	case WM_CREATE:
	{
		CreateControlWithFont(L"STATIC", L"Keygen:",
			WS_CHILD | WS_VISIBLE,
			10, 10, 50, 20,
			hWnd, (HMENU)ID_STATIC_NAME, hInst);
		HWND hRadio1 = CreateControlWithFont(L"BUTTON", L"1",
			WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			70, 10, 50, 20,
			hWnd, (HMENU)ID_BUTTON_KEYGEN1, hInst);
		HWND hRadio2 = CreateControlWithFont(L"BUTTON", L"2",
			WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			120, 10, 50, 20,
			hWnd, (HMENU)ID_BUTTON_KEYGEN2, hInst);
		HWND hRadio3 = CreateControlWithFont(L"BUTTON", L"3",
			WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			170, 10, 50, 20,
			hWnd, (HMENU)ID_BUTTON_KEYGEN3, hInst);

		// Select the first radio button by default
		SendMessage(hRadio1, BM_SETCHECK, BST_CHECKED, 0);

		CreateControlWithFont(L"STATIC", L"Name:",
			WS_CHILD | WS_VISIBLE,
			10, 40, 50, 20,
			hWnd, (HMENU)ID_STATIC_NAME, hInst);
		CreateControlWithFont(L"EDIT", L"",
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			70, 40, 175, 20,
			hWnd, (HMENU)ID_EDIT_NAME, hInst);

		CreateControlWithFont(L"STATIC", L"Serial:",
			WS_CHILD | WS_VISIBLE,
			10, 70, 50, 20,
			hWnd, (HMENU)ID_STATIC_SERIAL, hInst);
		CreateControlWithFont(L"EDIT", L"",
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY,
			70, 70, 175, 20,
			hWnd, (HMENU)ID_EDIT_SERIAL, hInst);

		CreateControlWithFont(L"BUTTON", L"Generate",
			WS_CHILD | WS_VISIBLE,
			10, 100, 75, 25,
			hWnd, (HMENU)ID_BUTTON_GENERATE, hInst);

		break;
	}
	case WM_COMMAND:
	{
		int action = HIWORD(wParam);
		int wmId = LOWORD(wParam);
		// Handle radio button selection
		if (wmId == ID_BUTTON_KEYGEN1 || wmId == ID_BUTTON_KEYGEN2 || wmId == ID_BUTTON_KEYGEN3)
		{
			selectedRadio = wmId - ID_BUTTON_KEYGEN1 + 1; // Update selected radio button
			// Clear the serial field when a radio button is selected
			//SetDlgItemText(hWnd, ID_EDIT_SERIAL, L"");
		}
		// Handle Generate button click
		else if (wmId == ID_BUTTON_GENERATE)
		{
			// Enable the serial field for editing
			SetDlgItemText(hWnd, ID_EDIT_SERIAL, L"");

			// Get the name from the edit control
			WCHAR name[256];
			GetDlgItemText(hWnd, ID_EDIT_NAME, name, 256);
			std::string serial;
			std::string error;

			// Convert WCHAR to std::string
			std::wstring ws(name);
			std::string str(ws.begin(), ws.end());

			// Generate the key
			GenerateKey(selectedRadio, str, serial, error);

			if (error.length())
			{
				// In case of error, clear the serial field and show the error message.
				std::wstring wError(error.begin(), error.end());
				MessageBox(hWnd, wError.c_str(), L"Error", MB_OK | MB_ICONERROR);
			}
			else
			{
				// Convert std::string to WCHAR and update the serial field.
				std::wstring wSerial(serial.begin(), serial.end());
				SetDlgItemText(hWnd, ID_EDIT_SERIAL, L"");
				SetDlgItemText(hWnd, ID_EDIT_SERIAL, wSerial.c_str());
			}
		}
		else if (wmId == IDM_ABOUT)
			// Modify the About dialog procedure to include more details

			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
		else if (wmId == IDM_EXIT)
			DestroyWindow(hWnd);
		else if (action == EN_SETFOCUS) {
			// Handle focus event for the edit control
			HWND hwndEdit = (HWND)lParam;

			if (hwndEdit == GetDlgItem(hWnd, ID_EDIT_NAME))
			{
				// Set the background color to white
				SetClassLongPtr(hwndEdit, GCLP_HBRBACKGROUND, (LONG_PTR)CreateSolidBrush(RGB(255, 255, 255)));
				RedrawWindow(hwndEdit, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			}
			else if (hwndEdit == GetDlgItem(hWnd, ID_EDIT_SERIAL))
			{
				//MessageBox(hWnd, L"Test", L"Error", MB_OK | MB_ICONERROR);
				// Set the background color to white
				SetClassLongPtr(hwndEdit, GCLP_HBRBACKGROUND, (LONG_PTR)CreateSolidBrush(RGB(255, 255, 255)));
			}
		}
		else if (action == EN_KILLFOCUS) {
			// Handle focus event for the edit control
			HWND hwndEdit = (HWND)lParam;
			if (hwndEdit == GetDlgItem(hWnd, ID_EDIT_NAME))
			{
				// Set the background color to white
				SetClassLongPtr(hwndEdit, GCLP_HBRBACKGROUND, (LONG_PTR)CreateSolidBrush(RGB(255, 255, 255)));
			}
			else if (hwndEdit == GetDlgItem(hWnd, ID_EDIT_SERIAL))
			{
				// Set the background color to white
				SetClassLongPtr(hwndEdit, GCLP_HBRBACKGROUND, (LONG_PTR)CreateSolidBrush(RGB(255, 255, 255)));
			}
		}
		else
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	case WM_CTLCOLORSTATIC:
	{
		SetBkMode((HDC)wParam, TRANSPARENT);
		static HBRUSH hbrBkgnd = ::CreateSolidBrush(RGB(255, 255, 255));
		return (LRESULT)hbrBkgnd;
	}
	case WM_CTLCOLOREDIT:
	{
		HDC hdcEdit = (HDC)wParam;
		HWND hwndEdit = (HWND)lParam;

		// Set text color if needed
		SetTextColor(hdcEdit, RGB(0, 0, 0)); // Black text

		// Set background color
		SetBkColor(hdcEdit, RGB(255, 255, 255));

		// Create and return a white brush
		static HBRUSH hbrWhite = CreateSolidBrush(RGB(255, 255, 255));
		return (INT_PTR)hbrWhite;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		SetDlgItemText(hDlg, IDD_KEYGEN_DIALOG, L"Your new text here");
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
