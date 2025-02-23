#include "Window.hxx"

Window::Window()
	: SCREEN_WIDTH(1280)
	, SCREEN_HEIGHT(720)
	, m_bFullScreen(false)
{

}

Window::~Window()
{
	UnregisterClass(m_wcex.lpszClassName, m_wcex.hInstance);
}

LRESULT Window::WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

void Window::SettingWindow(HINSTANCE hInstance, int nCmdShow)
{
	m_hInstance = hInstance;
	m_nCmdShow = nCmdShow;

	// ウィンドクラス情報の設定
	ZeroMemory(&m_wcex, sizeof(m_wcex));
	m_wcex.hInstance = m_hInstance;
	m_wcex.lpszClassName = "Class Name";
	m_wcex.lpfnWndProc = Window::WindowProcedure;
	m_wcex.style = CS_CLASSDC | CS_DBLCLKS;
	m_wcex.cbSize = sizeof(WNDCLASSEX);
	m_wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	m_wcex.hIconSm = m_wcex.hIcon;
	m_wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	m_wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

	// ウィンドウクラス情報の登録
	if (!RegisterClassEx(&m_wcex))
	{
		MessageBox(NULL, "Failed to RegisterClassEx", "Error", MB_OK);
		return ;
	}
}

void Window::ShowWindow()
{
	// ウィンドウの作成
	RECT rect = { 0, 0, (long)SCREEN_WIDTH, (long)SCREEN_HEIGHT };
	DWORD style = WS_CAPTION | WS_SYSMENU;
	DWORD exStyle = WS_EX_OVERLAPPEDWINDOW;
	AdjustWindowRectEx(&rect, style, false, exStyle);
	m_hWnd = CreateWindowEx(
		exStyle, m_wcex.lpszClassName,
		APP_TITLE, style,
		CW_USEDEFAULT, CW_USEDEFAULT,
		rect.right - rect.left, rect.bottom - rect.top,
		HWND_DESKTOP,
		NULL, m_hInstance, NULL
	);

	// ウィンドウの表示
	::ShowWindow(m_hWnd, m_nCmdShow);
	UpdateWindow(m_hWnd);
}
