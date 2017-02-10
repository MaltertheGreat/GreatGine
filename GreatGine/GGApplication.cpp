#include "GGApplication.h"

GGApplication::GGApplication(HINSTANCE hInstance, const std::wstring& title)
{
	int width = 1280;
	int height = 720;

	MakeWindow(hInstance, title, width, height);
}

void GGApplication::Run(int nCmdShow)
{
	ShowWindow(m_hwnd, nCmdShow);

	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Update();
		}
	}
}

void GGApplication::MakeWindow(HINSTANCE hInstance, const std::wstring& title, int width, int height)
{
	WNDCLASS wc = {};

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = title.c_str();

	RegisterClass(&wc);

	DWORD  dwStyle = WS_OVERLAPPEDWINDOW;
	RECT area = {0 , 0, width, height};

	AdjustWindowRect(&area, dwStyle, FALSE);
	width = area.right - area.left;
	height = area.bottom - area.top;

	m_hwnd = CreateWindow(
		title.c_str(), title.c_str(),
		dwStyle,
		CW_USEDEFAULT, CW_USEDEFAULT, width, height,
		NULL, NULL, hInstance, NULL);

	if (m_hwnd == NULL)
	{
		throw std::exception();
	}
}

void GGApplication::Update()
{
}

LRESULT GGApplication::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);

		return 0;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
