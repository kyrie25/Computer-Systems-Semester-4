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
	wcex.hbrBackground = CreateSolidBrush(RGB(240, 240, 240));
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_KEYGEN);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	int windowWidth = 260;
	int windowHeight = 220;
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	int posX = (screenWidth - windowWidth) / 2;
	int posY = (screenHeight - windowHeight) / 2;

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		posX, posY, windowWidth, windowHeight, nullptr, nullptr, hInstance, nullptr);

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
//  PURPOSE: Processes messages for the main window.
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int selectedRadio = 1; // Variable to store selected radio button
	// Static array to hold matrix edit control handles for keygen 1.
	static HWND hMatrix[9] = { 0 };

	switch (message)
	{
	case WM_CREATE:
	{
		// Create radio buttons and default controls.
		CreateControlWithFont(L"STATIC", L"Keygen:",
			WS_CHILD | WS_VISIBLE,
			10, 10, 50, 20,
			hWnd, (HMENU)ID_STATIC_KEYGEN, hInst);
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

		CreateControlWithFont(L"STATIC", L"Serial:",
			WS_CHILD | WS_VISIBLE,
			10, 40, 50, 20,
			hWnd, (HMENU)ID_STATIC_SERIAL, hInst);

		// Initially, keygen 1 is selected so create the 3x3 matrix.
		int startX = 70; // Align with first radio button
		int startY = 40;
		int cellWidth = 40; // Wide enough for 4 numbers
		int cellHeight = 20;
		int gap = 5;
		for (int i = 0; i < 9; i++)
		{
			int col = i % 3;
			int row = i / 3;
			hMatrix[i] = CreateControlWithFont(L"EDIT", L"",
				WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY,
				startX + col * (cellWidth + gap), startY + row * (cellHeight + gap),
				cellWidth, cellHeight,
				hWnd, (HMENU)(5000 + i), hInst);
		}

		CreateControlWithFont(L"BUTTON", L"Generate",
			WS_CHILD | WS_VISIBLE,
			70, 120, 75, 25,
			hWnd, (HMENU)ID_BUTTON_GENERATE, hInst);

		// Resize window for the matrix layout.
		SetWindowPos(hWnd, nullptr, 0, 0, 260, 220, SWP_NOMOVE);
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

			if (selectedRadio == 1)
			{
				// Hide Name and Serial fields if they exist.
				if (GetDlgItem(hWnd, ID_STATIC_NAME))
				{
					ShowWindow(GetDlgItem(hWnd, ID_STATIC_NAME), SW_HIDE);
					ShowWindow(GetDlgItem(hWnd, ID_EDIT_NAME), SW_HIDE);
					ShowWindow(GetDlgItem(hWnd, ID_EDIT_SERIAL), SW_HIDE);
				}

				SetWindowPos(GetDlgItem(hWnd, ID_STATIC_SERIAL), nullptr, 10, 40, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
				SetWindowPos(GetDlgItem(hWnd, ID_BUTTON_GENERATE), nullptr, 70, 120, 0, 0, SWP_NOZORDER | SWP_NOSIZE);

				// Create 3x3 matrix if not existing.
				int startX = 70; // Align with first radio button
				int startY = 40;
				int cellWidth = 40;
				int cellHeight = 20;
				int gap = 5;
				for (int i = 0; i < 9; i++)
				{
					if (!hMatrix[i])
					{
						int col = i % 3;
						int row = i / 3;
						hMatrix[i] = CreateControlWithFont(L"EDIT", L"",
							WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY,
							startX + col * (cellWidth + gap), startY + row * (cellHeight + gap),
							cellWidth, cellHeight,
							hWnd, (HMENU)(5000 + i), hInst);
					}
				}
				// Resize window for matrix layout.
				SetWindowPos(hWnd, nullptr, 0, 0, 250, 220, SWP_NOMOVE);
			}
			else
			{
				// For keygens 2 and 3: add back Name and Serial fields if not already created.
				if (!GetDlgItem(hWnd, ID_STATIC_NAME))
				{
					CreateControlWithFont(L"STATIC", L"Name:",
						WS_CHILD | WS_VISIBLE,
						10, 40, 50, 20,
						hWnd, (HMENU)ID_STATIC_NAME, hInst);
					CreateControlWithFont(L"EDIT", L"",
						WS_CHILD | WS_VISIBLE | WS_BORDER,
						70, 40, 160, 20,
						hWnd, (HMENU)ID_EDIT_NAME, hInst);
					CreateControlWithFont(L"EDIT", L"",
						WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY,
						70, 70, 160, 20,
						hWnd, (HMENU)ID_EDIT_SERIAL, hInst);
				}
				else
				{
					// Show existing Name and Serial fields.
					ShowWindow(GetDlgItem(hWnd, ID_STATIC_NAME), SW_SHOW);
					ShowWindow(GetDlgItem(hWnd, ID_EDIT_NAME), SW_SHOW);
					ShowWindow(GetDlgItem(hWnd, ID_EDIT_SERIAL), SW_SHOW);
				}

				SetWindowPos(GetDlgItem(hWnd, ID_STATIC_SERIAL), nullptr, 10, 70, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
				SetWindowPos(GetDlgItem(hWnd, ID_BUTTON_GENERATE), nullptr, 70, 100, 0, 0, SWP_NOZORDER | SWP_NOSIZE);

				// Destroy matrix controls if they exist.
				for (int i = 0; i < 9; i++)
				{
					if (hMatrix[i])
					{
						DestroyWindow(hMatrix[i]);
						hMatrix[i] = nullptr;
					}
				}
				// Resize window back to original size.
				SetWindowPos(hWnd, nullptr, 0, 0, 275, 200, SWP_NOMOVE);
				// Clear the serial field.
				SetDlgItemText(hWnd, ID_EDIT_SERIAL, L"");
			}
		}
		// Handle Generate button click
		else if (wmId == ID_BUTTON_GENERATE)
		{
			std::string serial;
			std::string error;

			if (selectedRadio == 1)
			{
				// Generate key for keygen 1 with empty input.
				GenerateKey(selectedRadio, std::string(), serial, error);
				if (!error.empty())
				{
					std::wstring wError(error.begin(), error.end());
					MessageBox(hWnd, wError.c_str(), L"Error", MB_OK | MB_ICONERROR);
				}
				else
				{
					// Expected serial is a string with 9 numbers separated by spaces.
					// Split and distribute into 3x3 matrix edit boxes.
					std::istringstream iss(serial);
					std::string token;
					int index = 0;
					while (iss >> token && index < 9)
					{
						std::wstring wToken(token.begin(), token.end());
						if (hMatrix[index])
						{
							SetWindowText(hMatrix[index], wToken.c_str());
						}
						index++;
					}
				}
			}
			else
			{
				// For keygen 2 and 3, operate as before.
				// Enable the serial field for editing.
				SetDlgItemText(hWnd, ID_EDIT_SERIAL, L"");

				// Get the name from the edit control.
				WCHAR name[256];
				GetDlgItemText(hWnd, ID_EDIT_NAME, name, 256);

				// Convert WCHAR to std::string.
				std::wstring ws(name);
				std::string str(ws.begin(), ws.end());

				// Generate the key.
				GenerateKey(selectedRadio, str, serial, error);

				if (!error.empty())
				{
					std::wstring wError(error.begin(), error.end());
					MessageBox(hWnd, wError.c_str(), L"Error", MB_OK | MB_ICONERROR);
				}
				else
				{
					std::wstring wSerial(serial.begin(), serial.end());
					SetDlgItemText(hWnd, ID_EDIT_SERIAL, L"");
					SetDlgItemText(hWnd, ID_EDIT_SERIAL, wSerial.c_str());
				}
			}
		}
		else if (wmId == IDM_ABOUT)
		{
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
		}
		else if (wmId == IDM_EXIT)
		{
			DestroyWindow(hWnd);
		}
		else if (action == EN_SETFOCUS)
		{
			// Handle focus event for the edit control.
			HWND hwndEdit = (HWND)lParam;
			if (hwndEdit == GetDlgItem(hWnd, ID_EDIT_NAME))
			{
				SetClassLongPtr(hwndEdit, GCLP_HBRBACKGROUND, (LONG_PTR)CreateSolidBrush(RGB(255, 255, 255)));
				RedrawWindow(hwndEdit, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			}
			else if (hwndEdit == GetDlgItem(hWnd, ID_EDIT_SERIAL))
			{
				SetClassLongPtr(hwndEdit, GCLP_HBRBACKGROUND, (LONG_PTR)CreateSolidBrush(RGB(255, 255, 255)));
			}
		}
		else if (action == EN_KILLFOCUS)
		{
			// Handle kill focus event for the edit control.
			HWND hwndEdit = (HWND)lParam;
			if (hwndEdit == GetDlgItem(hWnd, ID_EDIT_NAME))
			{
				SetClassLongPtr(hwndEdit, GCLP_HBRBACKGROUND, (LONG_PTR)CreateSolidBrush(RGB(255, 255, 255)));
			}
			else if (hwndEdit == GetDlgItem(hWnd, ID_EDIT_SERIAL))
			{
				SetClassLongPtr(hwndEdit, GCLP_HBRBACKGROUND, (LONG_PTR)CreateSolidBrush(RGB(255, 255, 255)));
			}
		}
		else
			return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	case WM_CTLCOLORSTATIC:
	{
		HWND hwndCtrl = (HWND)lParam;
		WCHAR className[256];
		GetClassName(hwndCtrl, className, 256);
		// If the control is an Edit (typically a read-only edit), use white background.
		if (wcscmp(className, L"Edit") == 0)
		{
			SetBkMode((HDC)wParam, OPAQUE);
			SetBkColor((HDC)wParam, RGB(255, 255, 255));
			static HBRUSH hbrWhite = ::CreateSolidBrush(RGB(255, 255, 255));
			return (LRESULT)hbrWhite;
		}
		// Otherwise, use 240 background for static controls.
		SetBkMode((HDC)wParam, TRANSPARENT);
		static HBRUSH hbrBkgnd = ::CreateSolidBrush(RGB(240, 240, 240));
		return (LRESULT)hbrBkgnd;
	}
	case WM_CTLCOLOREDIT:
	{
		// For input fields, use white background (255,255,255)
		HDC hdcEdit = (HDC)wParam;
		HWND hwndEdit = (HWND)lParam;
		SetTextColor(hdcEdit, RGB(0, 0, 0)); // Black text
		SetBkColor(hdcEdit, RGB(255, 255, 255));
		static HBRUSH hbrWhite = ::CreateSolidBrush(RGB(255, 255, 255));
		return (INT_PTR)hbrWhite;
	}
	case WM_CTLCOLORBTN:
	{
		// For button controls, only radio buttons get white background; others use 240.
		HWND hwndBtn = (HWND)lParam;
		LONG style = GetWindowLong(hwndBtn, GWL_STYLE);
		HDC hdcBtn = (HDC)wParam;
		if (style & BS_AUTORADIOBUTTON)
		{
			SetBkColor(hdcBtn, RGB(255, 255, 255));
			static HBRUSH hbrWhite = CreateSolidBrush(RGB(255, 255, 255));
			return (INT_PTR)hbrWhite;
		}
		else
		{
			SetBkColor(hdcBtn, RGB(240, 240, 240));
			static HBRUSH hbrGray = CreateSolidBrush(RGB(240, 240, 240));
			return (INT_PTR)hbrGray;
		}
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
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
