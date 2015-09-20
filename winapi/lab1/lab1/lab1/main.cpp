#include <Windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <shobjidl.h> 

enum ids{
	ID_SOURCE_BUTTON = 100,
	ID_OVERLAY_BUTTON
};

static TCHAR szWindowClass[] = _T("lab1_main");
static TCHAR szTitle[] = _T("Lab 1 Application");

HINSTANCE hInst;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
PWSTR getFilePath();

struct paths_t{
	PWSTR source;
	PWSTR overlay;
} paths;

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szWindowClass;
	wc.hIconSm = LoadIcon(wc.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, 
			_T("Call to RegisterClassEx failed!"),
			_T("Win32 Guided Tour"), // ??
			NULL);
		return 1;
	}

	hInst = hInstance;

	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		500, 500,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Win32 Guided Tour"),
			NULL);
		return 1;
	}

	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR sourceStr[] = _T("Выберите исходное изображение");
	TCHAR overlayStr[] = _T("Выберите накладываемое изображение");

	switch (msg)
	{
	case WM_CREATE:
		HWND hButtonSource;
		hButtonSource = CreateWindow(L"BUTTON", L"Label",
			WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
			250, 5,
			50, 20,
			hWnd, 
			(HMENU)ID_SOURCE_BUTTON,
			hInst, // ((LPCREATESTRUCT) lParam) -> hInstance
			NULL);

		HWND hButtonOverlay;
		hButtonOverlay = CreateWindow(L"BUTTON", L"Label",
			WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
			250, 40,
			50, 20,
			hWnd,
			(HMENU)ID_OVERLAY_BUTTON,
			hInst, // ((LPCREATESTRUCT) lParam) -> hInstance
			NULL);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		TextOut(hdc,
			5, 5,
			sourceStr, _tcslen(sourceStr));

		TextOut(hdc,
			5, 40,
			overlayStr, _tcslen(overlayStr));

		EndPaint(hWnd, &ps);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_SOURCE_BUTTON:
			paths.source = getFilePath();
			return 0;
		case ID_OVERLAY_BUTTON:
			paths.overlay = getFilePath();
			return 0;
		}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

PWSTR getFilePath()
{
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
		COINIT_DISABLE_OLE1DDE);
	if (SUCCEEDED(hr))
	{
		IFileOpenDialog *pFileOpen;

		// Create the FileOpenDialog object.
		hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
			IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

		if (SUCCEEDED(hr))
		{
			// Show the Open dialog box.
			hr = pFileOpen->Show(NULL);

			// Get the file name from the dialog box.
			if (SUCCEEDED(hr))
			{
				IShellItem *pItem;
				hr = pFileOpen->GetResult(&pItem);
				if (SUCCEEDED(hr))
				{
					PWSTR pszFilePath;
					hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

					// Display the file name to the user.
					if (SUCCEEDED(hr))
					{
						//MessageBox(NULL, pszFilePath, L"File Path", MB_OK);
						//CoTaskMemFree(pszFilePath);
						return pszFilePath;
					}
					pItem->Release();
				}
			}
			pFileOpen->Release();
		}
		CoUninitialize();
	}
	return NULL;
}