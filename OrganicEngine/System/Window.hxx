//	ファイル名	：Window.hxx
//	  概  要		：
//	作	成	者	：daigo
//	 作成日時	：2025/02/23 17:32:14
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= インクルードガード部 =-=-=
#ifndef _____Window_HXX_____
#define _____Window_HXX_____

// =-=-= インクルード部 =-=-=
#include <Windows.h>

class Window
{
public:
	Window();
	~Window();

	void SettingWindow(HINSTANCE hInstance, int nCmdShow);
	void ShowWindow();

	inline MSG GetMSG() { return m_message; }

	static LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

private:
	WNDCLASSEX m_wcex;
	HWND m_hWnd;
	MSG m_message;
	HINSTANCE m_hInstance;
	int m_nCmdShow;

	UINT SCREEN_WIDTH;
	UINT SCREEN_HEIGHT;
	const char* APP_TITLE = "Organic_Engine";

	bool m_bFullScreen;
};

#endif // !_____Window_HXX_____
