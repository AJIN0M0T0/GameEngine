//	ファイル名	：Singleton.hxx
//	  概  要	：
//	作	成	者	：daigo
//	 作成日時	：2025/02/25 22:29:33
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= インクルードガード部 =-=-=
#ifndef _____Singleton_HXX_____
#define _____Singleton_HXX_____

// =-=-= インクルード部 =-=-=
#include <stack>
#include <mutex>

namespace Engine {
	namespace System {
		class Supervision;
	}

	/// @brief シングルトンの基底クラス
	class _SingletonBase
	{
	public:
		/// @brief 初期化処理 ※オーバーライドしてください
		virtual bool Init() { return true; }
		/// @brief 更新処理 ※オーバーライドしてください
		virtual void Update() {}

	protected:
		/// @brief コンストラクタ
		_SingletonBase() {}
		/// @brief デストラクタ
		virtual ~_SingletonBase() {}
	};

	/// @brief シングルトンのインスタンスを生成・保持するクラス
	template<typename Type>
	class Singleton :public _SingletonBase
	{
	public:
		/// @brief インスタンスを生成する
		/// @return インスタンス
		static inline Type& CreateInstance()
		{
			//初めて呼び出されたならインスタンスの生成
			std::call_once(initFlag, Create);
			return *instance;
		}

		/// @brief 既に生成されているインスタンスを取得する
		/// @return インスタンス
		static inline Type& GetInstance()
		{
			return *instance;
		}

	private:
		/// @brief インスタンスの生成関数
		static inline void Create()
		{
			instance = New(Type);
			System::Supervision::_addFinalizer(&Singleton<Type>::destroy);
		}

		/// @brief インスタンスを破棄する
		static inline void destroy()
		{
			DebugString_(typeid(Type).name() + std::string(" 終了処理開始   ===== 人人人 \n"))
				delete instance;
			instance = nullptr;
			DebugString_(typeid(Type).name() + std::string(" 終了処理終わり ===== ＹＹＹ \n"))
		}

		static std::once_flag initFlag;	//作ったかのフラグ(排他制御)
		static Type* instance;			//自らのインスタンス

	protected:

		/// @brief コンストラクタ
		Singleton() {}
		/// @brief デストラクタ
		virtual ~Singleton() = default;

		// コピー・代入禁止
		Singleton(const Singleton&) = delete;
		Singleton& operator=(const Singleton&) = delete;
	};
	// 静的メンバを定義
	template <typename Type> std::once_flag Singleton<Type>::initFlag;
	template <typename Type> Type* Singleton<Type>::instance = nullptr;
};

#endif // !_____SingletonsMng_HXX_____
