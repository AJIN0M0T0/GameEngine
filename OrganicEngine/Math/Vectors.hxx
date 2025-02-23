//	ファイル名	：Vectors.hxx
//	  概  要		：構造体等の定義
//	作	成	者	：daigo
//	 作成日時	：2025/02/23 22:23:45
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= インクルードガード部 =-=-=
#ifndef _____Vectors_HXX_____
#define _____Vectors_HXX_____

// =-=-= インクルード部 =-=-=
#include "../Defines.hxx"
#include <string>

//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///
//																	//
//							　変数型定義								//
//																	//
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///
#ifdef _DIRECTXs_PRJ
#include <DirectXMath.h>
using fVec4x4 = DirectX::XMFLOAT4X4;
using Matrix = DirectX::XMMATRIX;
#endif

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
/**	@brief		ユニークIDを作成・保持するクラス
	@details	生成時固有のIDを保持する
	@author		伊藤大悟*/
class unique_ID { 
private: static ID m_Counter; ID m_ID;
public:	inline unique_ID() { m_ID = ++m_Counter; }
		inline explicit operator ID() { return m_ID; }};



//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///
//																	//
//						　定数・メタ関数定義							//
//																	//
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///
constexpr float PI = 3.1415926535f; // 円周率

namespace meta{
	// 掛け算のメタ関数
	template <float a , float b > inline constexpr float Multiply() { return a * b; }
	template <uint32 a, uint32 b> inline constexpr float Multiply() { return a * b; }
	
	// 割り算のメタ関数
	template <float a , float b > inline constexpr float Division() { return a / b; }
	template <uint32 a, uint32 b> inline constexpr float Division() { return a / b; }
	
	// 階乗のメタ関数
	template <uint32 N> inline constexpr uint32 Factorial() { return N * Factorial<N - 1>(); }
	template <> inline constexpr uint32 Factorial<0>() { return 1; }
}

/// @brief 角度をラジアン角に変換
/// @param Angle 角度
/// @return ラジアン角 
inline float toRadian(float Angle) { return Angle * meta::Division<PI,180.0f>();}

/// @brief ラジアン角を角度に変換
/// @param Radian ラジアン角
/// @return 角度
inline float toAngle(float Radian) { return Radian * meta::Division<180.0f,PI>();}


//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///
//																	//
//								fVec2								//
//																	//
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///
struct fVec2
{
	static const int _SuffixNum = 2;
	union
	{
		struct
		{
			float x, y;
		};
		float v[_SuffixNum] = { 0.0f,0.0f };
	};
};
bool operator==(const fVec2& Left, const fVec2& Right);
bool operator!=(const fVec2& Left, const fVec2& Right);
bool operator>(const fVec2& Left, const fVec2& Right);
bool operator<(const fVec2& Left, const fVec2& Right);
bool operator>=(const fVec2& Left, const fVec2& Right);
bool operator<=(const fVec2& Left, const fVec2& Right);
fVec2 operator+(const fVec2& Left, const fVec2& Right);
fVec2 operator-(const fVec2& Left, const fVec2& Right);
fVec2 operator*(const fVec2& Left, const fVec2& Right);
fVec2 operator/(const fVec2& Left, const fVec2& Right);
fVec2 operator+(const fVec2& Left, const float Right);
fVec2 operator-(const fVec2& Left, const float Right);
fVec2 operator*(const fVec2& Left, const float Right);
fVec2 operator/(const fVec2& Left, const float Right);

//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///
//																	//
//								fVec3								//
//																	//
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///
struct fVec3
{
	static const int _SuffixNum = 3;
	union
	{
		struct
		{
			float x, y, z;
		};
		float v[_SuffixNum] = { 0.0f,0.0f,0.0f };
	};
};
bool operator==(const fVec3& Left, const fVec3& Right);
bool operator!=(const fVec3& Left, const fVec3& Right);
bool operator>(const fVec3& Left, const fVec3& Right);
bool operator<(const fVec3& Left, const fVec3& Right);
bool operator>=(const fVec3& Left, const fVec3& Right);
bool operator<=(const fVec3& Left, const fVec3& Right);
fVec3 operator+(const fVec3& Left, const fVec3& Right);
fVec3 operator-(const fVec3& Left, const fVec3& Right);
fVec3 operator*(const fVec3& Left, const fVec3& Right);
fVec3 operator/(const fVec3& Left, const fVec3& Right);
fVec3 operator+(const fVec3& Left, const float Right);
fVec3 operator-(const fVec3& Left, const float Right);
fVec3 operator*(const fVec3& Left, const float Right);
fVec3 operator/(const fVec3& Left, const float Right);

//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///
//																	//
//								fVec4								//
//																	//
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///
struct fVec4
{
	static const int _SuffixNum = 4;
	union
	{
		struct
		{
			float x, y, z, w;
		};
		float v[_SuffixNum] = { 0.0f,0.0f,0.0f,0.0f };
	};
};
bool operator==(const fVec4& Left, const fVec4& Right);
bool operator!=(const fVec4& Left, const fVec4& Right);
bool operator> (const fVec4& Left, const fVec4& Right);
bool operator< (const fVec4& Left, const fVec4& Right);
bool operator>=(const fVec4& Left, const fVec4& Right);
bool operator<=(const fVec4& Left, const fVec4& Right);
fVec4 operator+(const fVec4& Left, const fVec4& Right);
fVec4 operator-(const fVec4& Left, const fVec4& Right);
fVec4 operator*(const fVec4& Left, const fVec4& Right);
fVec4 operator/(const fVec4& Left, const fVec4& Right);
fVec4 operator+(const fVec4& Left, const float Right);
fVec4 operator-(const fVec4& Left, const float Right);
fVec4 operator*(const fVec4& Left, const float Right);
fVec4 operator/(const fVec4& Left, const float Right);

//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///
//																	//
//								nVec2								//
//																	//
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///
struct nVec2
{
	static const int _SuffixNum = 2;
	union
	{
		struct
		{
			int x, y;
		};
		int v[_SuffixNum] = { 0,0 };
	};
};
bool operator==(const nVec2& Left, const nVec2& Right);
bool operator!=(const nVec2& Left, const nVec2& Right);
bool operator>(const nVec2& Left, const nVec2& Right);
bool operator<(const nVec2& Left, const nVec2& Right);
bool operator>=(const nVec2& Left, const nVec2& Right);
bool operator<=(const nVec2& Left, const nVec2& Right);
nVec2 operator+(const nVec2& Left, const nVec2& Right);
nVec2 operator-(const nVec2& Left, const nVec2& Right);
nVec2 operator*(const nVec2& Left, const nVec2& Right);
nVec2 operator/(const nVec2& Left, const nVec2& Right);
nVec2 operator+(const nVec2& Left, const int Right);
nVec2 operator-(const nVec2& Left, const int Right);
nVec2 operator*(const nVec2& Left, const int Right);
nVec2 operator/(const nVec2& Left, const int Right);

//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///
//																	//
//								nVec3								//
//																	//
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///
struct nVec3
{
	static const int _SuffixNum = 3;
	union
	{
		struct
		{
			int x, y, z;
		};
		int v[_SuffixNum] = { 0,0,0 };
	};
};
bool operator==(const nVec3& Left, const nVec3& Right);
bool operator!=(const nVec3& Left, const nVec3& Right);
bool operator>(const nVec3& Left, const nVec3& Right);
bool operator<(const nVec3& Left, const nVec3& Right);
bool operator>=(const nVec3& Left, const nVec3& Right);
bool operator<=(const nVec3& Left, const nVec3& Right);
nVec3 operator+(const nVec3& Left, const nVec3& Right);
nVec3 operator-(const nVec3& Left, const nVec3& Right);
nVec3 operator*(const nVec3& Left, const nVec3& Right);
nVec3 operator/(const nVec3& Left, const nVec3& Right);
nVec3 operator+(const nVec3& Left, const int Right);
nVec3 operator-(const nVec3& Left, const int Right);
nVec3 operator*(const nVec3& Left, const int Right);
nVec3 operator/(const nVec3& Left, const int Right);

//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///
//																	//
//								nVec4								//
//																	//
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///
struct nVec4
{
	static const int _SuffixNum = 4;
	union
	{
		struct
		{
			int x, y, z, w;
		};
		int v[_SuffixNum] = { 0,0,0,0 };
	};
};
bool operator==(const nVec4& Left, const nVec4& Right);
bool operator!=(const nVec4& Left, const nVec4& Right);
bool operator>(const nVec4& Left, const nVec4& Right);
bool operator<(const nVec4& Left, const nVec4& Right);
bool operator>=(const nVec4& Left, const nVec4& Right);
bool operator<=(const nVec4& Left, const nVec4& Right);
nVec4 operator+(const nVec4& Left, const nVec4& Right);
nVec4 operator-(const nVec4& Left, const nVec4& Right);
nVec4 operator*(const nVec4& Left, const nVec4& Right);
nVec4 operator/(const nVec4& Left, const nVec4& Right);
nVec4 operator+(const nVec4& Left, const int Right);
nVec4 operator-(const nVec4& Left, const int Right);
nVec4 operator*(const nVec4& Left, const int Right);
nVec4 operator/(const nVec4& Left, const int Right);


namespace Vec {
	/// @brief ベクトルの長さを求める
	/// @param Vector 求めるベクトル
	/// @return ベクトルの長さ
	float length(const fVec3& Vector);

	/// @brief ベクトルを正規化する
	/// @param Vector 正規化するベクトル
	/// @return 正規化されたベクトル
	fVec3 Nomalize(fVec3 Vector);

#ifdef DIRECTX11_PRJ
	DirectX::XMFLOAT3 ToXMFLOAT3(const fVec3& Vector);
#endif // DIRECTX11_PRJ
}


#endif // !_____Vectors_HXX_____
