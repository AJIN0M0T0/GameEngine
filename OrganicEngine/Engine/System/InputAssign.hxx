//	ファイル名	：InputAssign.hxx
//	  概  要		：UnrealEngineのインプットシステムを参考にしました。使用方法は一緒です。
//	作	成	者	：daigo
//	 作成日時	：2025/03/29 23:46:59
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= インクルードガード部 =-=-=
#ifndef _____InputAssign_HXX_____
#define _____InputAssign_HXX_____

// =-=-= インクルード部 =-=-=

namespace Engine::System {
	
	class iInputAction {
	public:

	};

	class ActionController {
	public:
		virtual void Update() = 0;
	private:

	};

}

#endif // !_____InputAssign_HXX_____
