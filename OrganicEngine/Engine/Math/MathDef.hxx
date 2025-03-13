//	ファイル名	：MathDef.hxx
//	  概  要		：変数型定義
//	作	成	者	：daigo
//	 作成日時	：2025/02/25 00:24:03
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#ifndef _____MathDef_HXX_____
#define _____MathDef_HXX_____
#include <string>

using uint16 = unsigned short;
using uint32 = unsigned long;
using uint64 = unsigned long long;
using int16 = short;
using int32 = long;
using int64 = long long;

using count = unsigned short;
using ID = unsigned long;
using Tag = unsigned short;
using Name = std::string;

namespace Engine {

	/**	@brief		ユニークIDを作成・保持するクラス
		@details	生成時固有のIDを保持する
		@author		伊藤大悟*/
	class unique_ID {
	private: static ID m_Counter; ID m_ID;
	public:	inline unique_ID() { m_ID = ++m_Counter; }
		  inline explicit operator ID() { return m_ID; }
	};


	//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///
	//																	//
	//						　定数・メタ関数定義							//
	//																	//
	//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///
	constexpr float PI = 3.1415926535f; // 円周率

	/// @brief メタ関数
	namespace Meta {
		// 掛け算のメタ関数
		template <float a, float b > 
		inline constexpr float Multiply() { return a * b; }
		template <uint32 a, uint32 b> 
		inline constexpr float Multiply() { return a * b; }

		// 割り算のメタ関数
		template <float a, float b > 
		inline constexpr float Division() { return a / b; }
		template <uint32 a, uint32 b> 
		inline constexpr float Division() { return a / b; }

		// 階乗のメタ関数
		template <uint32 N> 
		inline constexpr uint32 Factorial() { return N * Factorial<N - 1>(); }
		template <> 
		inline constexpr uint32 Factorial<0>() { return 1; }
	}

	/// @brief 角度をラジアン角に変換
	/// @param Angle 角度
	/// @return ラジアン角 
	inline float toRadian(float Angle) { return Angle * Meta::Division<Engine::PI, 180.0f>(); }

	/// @brief ラジアン角を角度に変換
	/// @param Radian ラジアン角
	/// @return 角度
	inline float toAngle(float Radian) { return Radian * Meta::Division<180.0f, Engine::PI>(); }

};

#endif // !_____MathDef_HXX_____
