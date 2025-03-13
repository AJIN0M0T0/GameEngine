//	ファイル名	：defines.hxx
//	  概  要		：マクロ定義
//	作	成	者	：daigo
//	 作成日時	：2025/02/21 00:24:03
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#ifndef _____DEFINES_HXX_____
#define _____DEFINES_HXX_____

// 実行モード
#define __ENGINE__
#ifndef __ENGINE__
#define BULLET_INPORT_CHECK
#endif // !__ENGINE__


// ビルドモード
#ifdef _DEBUG
#define DEBUG
#else
//#define SHIPPING
#endif // !_DEBUG


// 描画API選択
#define _DIRECTXs_PRJ
#ifdef _DIRECTXs_PRJ
//#define DIRECTX12_PRJ
#define DIRECTX11_PRJ
#else // !_DIRECTXs_PRJ
#define VULKAN_PRJ
#endif // !_DIRECTXs_PRJ


// 追加処理
#define _THREADPOOL_


// その他
#define _CRTDBG_MAP_ALLOC // メモリリーク検出

#define public_Func public: // 関数アクセス修飾子
#define private_Func private: // 関数アクセス修飾子
#define protected_Func protected: // 関数アクセス修飾子
#define public_Var public: // 変数アクセス修飾子
#define private_Var private: // 変数アクセス修飾子
#define protected_Var protected: // 変数アクセス修飾子

#endif // !_____DEFINES_HXX_____
