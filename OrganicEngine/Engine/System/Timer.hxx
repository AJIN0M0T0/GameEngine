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
		void TimerInit();
		float DeltaSeconds();
		float GetFPS();
		void TimerUpdate();
	}
}

#endif // !_____Time_HXX_____
