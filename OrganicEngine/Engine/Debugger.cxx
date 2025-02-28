#include "Debugger.hxx"


#ifndef SHIPPING
#include <iostream>	
class CNS_None {
public:	~CNS_None() {
#ifndef DEBUG
	rewind(stdin); (void)getchar(); 
#endif // !DEBUG
}
};

void _DebugStringOutput(const std::string& str)
{
	static bool bInit = true;
	static CNS_None none;
	if (bInit) {
		AllocConsole();
#pragma warning(push)
#pragma warning(disable: 4996)
		(void)freopen("CON", "r", stdin);     // 標準入力の割り当て
		(void)freopen("CON", "w", stdout);    // 標準出力の割り当て
#pragma warning(pop)
		bInit = false;
	}
	std::cout << str.c_str();
}
#endif // !SHIPPING

#ifdef DEBUG	

bool _falseCheckFunc(bool b)
{
	if (!b) {
		_DebugStringOutput("■◆■◆■ !-!-!-! ■◆■◆■ ：falseが返されました。\n");
		DebugBreak();
	}
	return b;
}

HRESULT _HResultCheckFunc(HRESULT hr)
{
	if (FAILED(hr)) {
		_DebugStringOutput("■◆■◆■ !-!-!-! ■◆■◆■ ：HRESULTが失敗しました。\n");
		DebugBreak();
	}
	return hr;
}


#endif // _DEBUG
