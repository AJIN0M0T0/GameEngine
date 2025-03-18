//	ファイル名	：Time.hxx
//	  概  要	：
//	作	成	者	：daigo
//	 作成日時	：2025/02/25 23:03:50
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= インクルードガード部 =-=-=
#ifndef _____Time_HXX_____
#define _____Time_HXX_____

// =-=-= インクルード部 =-=-=

namespace Engine {
	namespace Time
	{
		/// @brief タイマーの初期化
		void TimerInit();

		/// @brief フレーム間の時間を取得
		/// @return フレーム間の時間(秒)
		float DeltaSeconds();

		/// @brief FPSを取得
		/// @return FPS
		float GetFPS();

		/// @brief タイマーのアップデート
		void TimerUpdate();
	}
}

#endif // !_____Time_HXX_____
