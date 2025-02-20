//	ファイル名	：defines.hxx
//	  概  要		：マクロ定義
//	作	成	者	：daigo
//	 作成日時	：2025/02/21 00:24:03
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#ifndef _____DEFINES_HXX_____
#define _____DEFINES_HXX_____

// ビルドモード
#ifdef _DEBUG
#define DEBUG
#else
//#define SHIPPING
#endif // !_DEBUG

// 描画API選択
#define DIRECTX11_PRJ
//#define DIRECTX12_PRJ

// 追加処理
#define _THREADPOOL_

#endif // !_____DEFINES_HXX_____