#include "GGApplication.h"

GGApplication::GGApplication(HINSTANCE hInstance, const std::wstring& title)
	:
	m_width(1280),
	m_height(720),
	m_hwnd(MakeWindow(hInstance, title, m_width, m_height)),
	m_graphics(m_input, m_hwnd, m_width, m_height)
{}

void GGApplication::Run(int nCmdShow)
{
	ShowWindow(m_hwnd, nCmdShow);

	MSG msg{nullptr};
	while (true)
	{
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				return;
			}

			DispatchMessage(&msg);

			m_input.ProcessMessage(&msg);
		}

		Update();
	}
}

void GGApplication::Update()
{
	m_graphics.Update(m_input);
}

HWND GGApplication::MakeWindow(HINSTANCE hInstance, const std::wstring& title, int width, int height)
{
	WNDCLASS wc{};

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = title.c_str();

	RegisterClass(&wc);

	DWORD dwStyle = WS_OVERLAPPEDWINDOW;

	RECT area{0 , 0, width, height};
	AdjustWindowRect(&area, dwStyle, FALSE);
	width = area.right - area.left;
	height = area.bottom - area.top;

	const auto hWnd = CreateWindowW(
		title.c_str(), title.c_str(),
		dwStyle,
		CW_USEDEFAULT, CW_USEDEFAULT, width, height,
		NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		throw std::exception();
	}

	return hWnd;
}

LRESULT GGApplication::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);

		return 0;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}
