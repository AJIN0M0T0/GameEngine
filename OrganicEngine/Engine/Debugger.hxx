//	ファイル名	：debugger.hxx
//	  概  要		：デバッグの際に使用する処理です。
//	作	成	者	：daigo
//	 作成日時	：2025/02/23 21:46:38
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


// !-!-! = 関数を直接参照せず、マクロを使用してください！ = !-!-!


// =-=-= インクルードガード部 =-=-=
#ifndef _____debugger_HXX_____
#define _____debugger_HXX_____

namespace Engine {
	/// @brief エラーの種類
	enum class ErrorType {
		isFalse_Bool, // Falseなら停止します
		isFailure_HResult, // HResultが失敗していたら停止
		isNullptr_pointer, // ポインタのNullチェック
		Singleton_Instance_nullptr, // シングルトンのインスタンスがnullptr
		Unsetting_Factory, // ファクトリーが設定されていません
	};
};

#ifndef SHIPPING
	// DEBUGとRELEASEの場合の共通処理
#include <windows.h>
#include <string>
// デバッグ用文字列の出力　※セミコロン付き
#define DebugString_(str) _DebugStringOutput(str);
// デバッグ用文字列の出力 cout版 ※セミコロン付き
#define DebugCOUT_(str) std::cout << str;

void _DebugStringOutput(const std::string& str);

#ifdef DEBUG
	// DEBUGの場合のみの処理

	// ポインタのNullチェック
#define NullptrCheck(ptr) _NullptrCheckFunc(ptr)
// ポインタのNullチェック　※セミコロン付き
#define NullptrCheck_(ptr) _NullptrCheckFunc(ptr);
// Falseなら停止します
#define FalseCheck(b) _falseCheckFunc(b)
// HResultが失敗していたら停止
#define HResultCheck(hr) _HResultCheckFunc(hr)
// ここにたどり着いたら停止　※セミコロン付き
#define DebugBreakPoint_ DebugBreak();

	template<typename Type>
	Type* _NullptrCheckFunc(Type* ptr)
	{
		std::string stri;
		stri += "■◆■◆■ !-!-!-! ■◆■◆■ ：";
		stri += typeid(Type).name();
		stri += " の [ nullptr ]が発生しました。参照・依存関係を見直してください。\n";
		if (!ptr) {
			_DebugStringOutput(stri);
			DebugBreak();
		}
		return ptr;
	}
	bool _falseCheckFunc(bool b);
	HRESULT _HResultCheckFunc(HRESULT hr);

#else // !DEBUG
	// RELEASEでありSHIPPINGでもDEBUGでもない場合の処理

#endif // DEBUG
#else // SHIPPING
	// SHIPPINGの場合のみの処理

#define DebugString_(str);
#define DebugCOUT_(str);

#endif // !SHIPPING
#ifndef DEBUG
// RELEASEとSHIPPINGの場合の共通処理

#define NullptrCheck(ptr) ptr
#define NullptrCheck_(ptr) 
#define FalseCheck(b) b
#define HResultCheck(hr) hr
#define DebugBreakPoint_ 

#endif // !DEBUG


#endif // !_____debugger_HXX_____
