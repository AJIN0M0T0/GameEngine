#include "Vectors.hxx"
#include <cmath>

ID Engine::unique_ID::m_Counter = 0;

//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///
//																	//
//								fVec2								//
//																	//
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///
bool Engine::Math::operator==(const Engine::Math::fVec2& Left, const Engine::Math::fVec2& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::Math::fVec2::_SuffixNum; i++)
		ans &= Left.v[i] == Right.v[i];
	return ans;
}
bool Engine::Math::operator!=(const Engine::Math::fVec2& Left, const Engine::Math::fVec2& Right)
{
	return !(Left == Right);
}
bool Engine::Math::operator>(const Engine::Math::fVec2& Left, const Engine::Math::fVec2& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::Math::fVec2::_SuffixNum; i++)
		ans &= Left.v[i] > Right.v[i];
	return ans;
}
bool Engine::Math::operator<(const Engine::Math::fVec2& Left, const Engine::Math::fVec2& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::Math::fVec2::_SuffixNum; i++)
		ans &= Left.v[i] < Right.v[i];
	return ans;
}
bool Engine::Math::operator>=(const Engine::Math::fVec2& Left, const Engine::Math::fVec2& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::Math::fVec2::_SuffixNum; i++)
		ans &= Left.v[i] >= Right.v[i];
	return ans;
}
bool Engine::Math::operator<=(const Engine::Math::fVec2& Left, const Engine::Math::fVec2& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::Math::fVec2::_SuffixNum; i++)
		ans &= Left.v[i] <= Right.v[i];
	return ans;
}
Engine::Math::fVec2 Engine::Math::operator+(const Engine::Math::fVec2& Left, const Engine::Math::fVec2& Right)
{
	Engine::Math::fVec2 ans;
	for (int i = 0; i < Engine::Math::fVec2::_SuffixNum; i++)
		ans.v[i] = Left.v[i] + Right.v[i];
	return ans;
}
Engine::Math::fVec2 Engine::Math::operator-(const Engine::Math::fVec2& Left, const Engine::Math::fVec2& Right)
{
	Engine::Math::fVec2 ans;
	for (int i = 0; i < Engine::Math::fVec2::_SuffixNum; i++)
		ans.v[i] = Left.v[i] - Right.v[i];
	return ans;
}
Engine::Math::fVec2 Engine::Math::operator*(const Engine::Math::fVec2& Left, const Engine::Math::fVec2& Right)
{
	Engine::Math::fVec2 ans;
	for (int i = 0; i < Engine::Math::fVec2::_SuffixNum; i++)
		ans.v[i] = Left.v[i] * Right.v[i];
	return ans;
}
Engine::Math::fVec2 Engine::Math::operator/(const Engine::Math::fVec2& Left, const Engine::Math::fVec2& Right)
{
	Engine::Math::fVec2 ans;
	for (int i = 0; i < Engine::Math::fVec2::_SuffixNum; i++)
	{
		if (Right.v[i] != 0.0f)
			ans.v[i] = Left.v[i] / Right.v[i];
		else
			ans.v[i] = 0.0f;
	}
	return ans;
}
Engine::Math::fVec2 Engine::Math::operator+(const Engine::Math::fVec2& Left, const float Right)
{
	Engine::Math::fVec2 ans;
	for (int i = 0; i < Engine::Math::fVec2::_SuffixNum; i++)
		ans.v[i] = Left.v[i] + Right;
	return ans;
}
Engine::Math::fVec2 Engine::Math::operator-(const Engine::Math::fVec2& Left, const float Right)
{
	Engine::Math::fVec2 ans;
	for (int i = 0; i < Engine::Math::fVec2::_SuffixNum; i++)
		ans.v[i] = Left.v[i] - Right;
	return ans;
}
Engine::Math::fVec2 Engine::Math::operator*(const Engine::Math::fVec2& Left, const float Right)
{
	Engine::Math::fVec2 ans;
	for (int i = 0; i < Engine::Math::fVec2::_SuffixNum; i++)
		ans.v[i] = Left.v[i] * Right;
	return ans;
}
Engine::Math::fVec2 Engine::Math::operator/(const Engine::Math::fVec2& Left, const float Right)
{
	Engine::Math::fVec2 ans;
	for (int i = 0; i < Engine::Math::fVec2::_SuffixNum; i++)
	{
		if (Right != 0.0f)
			ans.v[i] = Left.v[i] / Right;
		else
			ans.v[i] = 0.0f;
	}
	return ans;
}

//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///
//																	//
//								Engine::Math::fVec3								//
//																	//
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///
bool Engine::Math::operator==(const Engine::Math::fVec3& Left, const Engine::Math::fVec3& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::Math::fVec3::_SuffixNum; i++)
		ans &= Left.v[i] == Right.v[i];
	return ans;
}
bool Engine::Math::operator!=(const Engine::Math::fVec3& Left, const Engine::Math::fVec3& Right)
{
	return !(Left == Right);
}
bool Engine::Math::operator>(const Engine::Math::fVec3& Left, const Engine::Math::fVec3& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::Math::fVec3::_SuffixNum; i++)
		ans &= Left.v[i] > Right.v[i];
	return ans;
}
bool Engine::Math::operator<(const Engine::Math::fVec3& Left, const Engine::Math::fVec3& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::Math::fVec3::_SuffixNum; i++)
		ans &= Left.v[i] < Right.v[i];
	return ans;
}
bool Engine::Math::operator>=(const Engine::Math::fVec3& Left, const Engine::Math::fVec3& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::Math::fVec3::_SuffixNum; i++)
		ans &= Left.v[i] >= Right.v[i];
	return ans;
}
bool Engine::Math::operator<=(const Engine::Math::fVec3& Left, const Engine::Math::fVec3& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::Math::fVec3::_SuffixNum; i++)
		ans &= Left.v[i] <= Right.v[i];
	return ans;
}
Engine::Math::fVec3 Engine::Math::operator+(const Engine::Math::fVec3& Left, const Engine::Math::fVec3& Right)
{
	Engine::Math::fVec3 ans;
	for (int i = 0; i < Engine::Math::fVec3::_SuffixNum; i++)
		ans.v[i] = Left.v[i] + Right.v[i];
	return ans;
}
Engine::Math::fVec3 Engine::Math::operator-(const Engine::Math::fVec3& Left, const Engine::Math::fVec3& Right)
{
	Engine::Math::fVec3 ans;
	for (int i = 0; i < Engine::Math::fVec3::_SuffixNum; i++)
		ans.v[i] = Left.v[i] - Right.v[i];
	return ans;
}
Engine::Math::fVec3 Engine::Math::operator*(const Engine::Math::fVec3& Left, const Engine::Math::fVec3& Right)
{
	Engine::Math::fVec3 ans;
	for (int i = 0; i < Engine::Math::fVec3::_SuffixNum; i++)
		ans.v[i] = Left.v[i] * Right.v[i];
	return ans;
}
Engine::Math::fVec3 Engine::Math::operator/(const Engine::Math::fVec3& Left, const Engine::Math::fVec3& Right)
{
	Engine::Math::fVec3 ans;
	for (int i = 0; i < Engine::Math::fVec3::_SuffixNum; i++)
	{
		if (Right.v[i] != 0.0f)
			ans.v[i] = Left.v[i] / Right.v[i];
		else
			ans.v[i] = 0.0f;
	}
	return ans;
}
Engine::Math::fVec3 Engine::Math::operator+(const Engine::Math::fVec3& Left, const float Right)
{
	Engine::Math::fVec3 ans;
	for (int i = 0; i < Engine::Math::fVec3::_SuffixNum; i++)
		ans.v[i] = Left.v[i] + Right;
	return ans;
}
Engine::Math::fVec3 Engine::Math::operator-(const Engine::Math::fVec3& Left, const float Right)
{
	Engine::Math::fVec3 ans;
	for (int i = 0; i < Engine::Math::fVec3::_SuffixNum; i++)
		ans.v[i] = Left.v[i] - Right;
	return ans;
}
Engine::Math::fVec3 Engine::Math::operator*(const Engine::Math::fVec3& Left, const float Right)
{
	Engine::Math::fVec3 ans;
	for (int i = 0; i < Engine::Math::fVec3::_SuffixNum; i++)
		ans.v[i] = Left.v[i] * Right;
	return ans;
}
Engine::Math::fVec3 Engine::Math::operator/(const Engine::Math::fVec3& Left, const float Right)
{
	Engine::Math::fVec3 ans;
	for (int i = 0; i < Engine::Math::fVec3::_SuffixNum; i++)
	{
		if (Right != 0.0f)
			ans.v[i] = Left.v[i] / Right;
		else
			ans.v[i] = 0.0f;
	}
	return ans;
}

//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///
//																	//
//								Engine::Math::fVec4								//
//																	//
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///
bool Engine::Math::operator==(const Engine::Math::fVec4& Left, const Engine::Math::fVec4& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::Math::fVec4::_SuffixNum; i++)
		ans &= Left.v[i] == Right.v[i];
	return ans;
}
bool Engine::Math::operator!=(const Engine::Math::fVec4& Left, const Engine::Math::fVec4& Right)
{
	return !(Left == Right);
}
bool Engine::Math::operator>(const Engine::Math::fVec4& Left, const Engine::Math::fVec4& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::Math::fVec4::_SuffixNum; i++)
		ans &= Left.v[i] > Right.v[i];
	return ans;
}
bool Engine::Math::operator<(const Engine::Math::fVec4& Left, const Engine::Math::fVec4& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::Math::fVec4::_SuffixNum; i++)
		ans &= Left.v[i] < Right.v[i];
	return ans;
}
bool Engine::Math::operator>=(const Engine::Math::fVec4& Left, const Engine::Math::fVec4& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::Math::fVec4::_SuffixNum; i++)
		ans &= Left.v[i] >= Right.v[i];
	return ans;
}
bool Engine::Math::operator<=(const Engine::Math::fVec4& Left, const Engine::Math::fVec4& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::Math::fVec4::_SuffixNum; i++)
		ans &= Left.v[i] <= Right.v[i];
	return ans;
}
Engine::Math::fVec4 Engine::Math::operator+(const Engine::Math::fVec4& Left, const Engine::Math::fVec4& Right)
{
	Engine::Math::fVec4 ans;
	for (int i = 0; i < Engine::Math::fVec4::_SuffixNum; i++)
		ans.v[i] = Left.v[i] + Right.v[i];
	return ans;
}
Engine::Math::fVec4 Engine::Math::operator-(const Engine::Math::fVec4& Left, const Engine::Math::fVec4& Right)
{
	Engine::Math::fVec4 ans;
	for (int i = 0; i < Engine::Math::fVec4::_SuffixNum; i++)
		ans.v[i] = Left.v[i] - Right.v[i];
	return ans;
}
Engine::Math::fVec4 Engine::Math::operator*(const Engine::Math::fVec4& Left, const Engine::Math::fVec4& Right)
{
	Engine::Math::fVec4 ans;
	for (int i = 0; i < Engine::Math::fVec4::_SuffixNum; i++)
		ans.v[i] = Left.v[i] * Right.v[i];
	return ans;
}
Engine::Math::fVec4 Engine::Math::operator/(const Engine::Math::fVec4& Left, const Engine::Math::fVec4& Right)
{
	Engine::Math::fVec4 ans;
	for (int i = 0; i < Engine::Math::fVec4::_SuffixNum; i++)
	{
		if (Right.v[i] != 0.0f)
			ans.v[i] = Left.v[i] / Right.v[i];
		else
			ans.v[i] = 0.0f;
	}
	return ans;
}
Engine::Math::fVec4 Engine::Math::operator+(const Engine::Math::fVec4& Left, const float Right)
{
	Engine::Math::fVec4 ans;
	for (int i = 0; i < Engine::Math::fVec4::_SuffixNum; i++)
		ans.v[i] = Left.v[i] + Right;
	return ans;
}
Engine::Math::fVec4 Engine::Math::operator-(const Engine::Math::fVec4& Left, const float Right)
{
	Engine::Math::fVec4 ans;
	for (int i = 0; i < Engine::Math::fVec4::_SuffixNum; i++)
		ans.v[i] = Left.v[i] - Right;
	return ans;
}
Engine::Math::fVec4 Engine::Math::operator*(const Engine::Math::fVec4& Left, const float Right)
{
	Engine::Math::fVec4 ans;
	for (int i = 0; i < Engine::Math::fVec4::_SuffixNum; i++)
		ans.v[i] = Left.v[i] * Right;
	return ans;
}
Engine::Math::fVec4 Engine::Math::operator/(const Engine::Math::fVec4& Left, const float Right)
{
	Engine::Math::fVec4 ans;
	for (int i = 0; i < Engine::Math::fVec4::_SuffixNum; i++)
	{
		if (Right != 0.0f)
			ans.v[i] = Left.v[i] / Right;
		else
			ans.v[i] = 0.0f;
	}
	return ans;
}

//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///
//																	//
//								nVec2								//
//																	//
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///
bool Engine::Math::operator==(const Engine::Math::nVec2& Left, const Engine::Math::nVec2& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::Math::nVec2::_SuffixNum; i++)
		ans &= Left.v[i] == Right.v[i];
	return ans;
}
bool Engine::Math::operator!=(const Engine::Math::nVec2& Left, const Engine::Math::nVec2& Right)
{
	return !(Left == Right);
}
bool Engine::Math::operator>(const Engine::Math::nVec2& Left, const Engine::Math::nVec2& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::Math::nVec2::_SuffixNum; i++)
		ans &= Left.v[i] > Right.v[i];
	return ans;
}
bool Engine::Math::operator<(const Engine::Math::nVec2& Left, const Engine::Math::nVec2& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::Math::nVec2::_SuffixNum; i++)
		ans &= Left.v[i] < Right.v[i];
	return ans;
}
bool Engine::Math::operator>=(const Engine::Math::nVec2& Left, const Engine::Math::nVec2& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::Math::nVec2::_SuffixNum; i++)
		ans &= Left.v[i] >= Right.v[i];
	return ans;
}
bool Engine::Math::operator<=(const Engine::Math::nVec2& Left, const Engine::Math::nVec2& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::Math::nVec2::_SuffixNum; i++)
		ans &= Left.v[i] <= Right.v[i];
	return ans;
}
Engine::Math::nVec2 Engine::Math::operator+(const Engine::Math::nVec2& Left, const Engine::Math::nVec2& Right)
{
	Engine::Math::nVec2 ans;
	for (int i = 0; i < Engine::Math::nVec2::_SuffixNum; i++)
		ans.v[i] = Left.v[i] + Right.v[i];
	return ans;
}
Engine::Math::nVec2 Engine::Math::operator-(const Engine::Math::nVec2& Left, const Engine::Math::nVec2& Right)
{
	Engine::Math::nVec2 ans;
	for (int i = 0; i < Engine::Math::nVec2::_SuffixNum; i++)
		ans.v[i] = Left.v[i] - Right.v[i];
	return ans;
}
Engine::Math::nVec2 Engine::Math::operator*(const Engine::Math::nVec2& Left, const Engine::Math::nVec2& Right)
{
	Engine::Math::nVec2 ans;
	for (int i = 0; i < Engine::Math::nVec2::_SuffixNum; i++)
		ans.v[i] = Left.v[i] * Right.v[i];
	return ans;
}
Engine::Math::nVec2 Engine::Math::operator/(const Engine::Math::nVec2& Left, const Engine::Math::nVec2& Right)
{
	Engine::Math::nVec2 ans;
	for (int i = 0; i < Engine::Math::nVec2::_SuffixNum; i++)
	{
		if (Right.v[i] != 0)
			ans.v[i] = Left.v[i] / Right.v[i];
		else
			ans.v[i] = 0;
	}
	return ans;
}
Engine::Math::nVec2 Engine::Math::operator+(const Engine::Math::nVec2& Left, const int Right)
{
	Engine::Math::nVec2 ans;
	for (int i = 0; i < Engine::Math::nVec2::_SuffixNum; i++)
		ans.v[i] = Left.v[i] + Right;
	return ans;
}
Engine::Math::nVec2 Engine::Math::operator-(const Engine::Math::nVec2& Left, const int Right)
{
	Engine::Math::nVec2 ans;
	for (int i = 0; i < Engine::Math::nVec2::_SuffixNum; i++)
		ans.v[i] = Left.v[i] - Right;
	return ans;
}
Engine::Math::nVec2 Engine::Math::operator*(const Engine::Math::nVec2& Left, const int Right)
{
	Engine::Math::nVec2 ans;
	for (int i = 0; i < Engine::Math::nVec2::_SuffixNum; i++)
		ans.v[i] = Left.v[i] * Right;
	return ans;
}
Engine::Math::nVec2 Engine::Math::operator/(const Engine::Math::nVec2& Left, const int Right)
{
	Engine::Math::nVec2 ans;
	for (int i = 0; i < Engine::Math::nVec2::_SuffixNum; i++)
	{
		if (Right != 0)
			ans.v[i] = Left.v[i] / Right;
		else
			ans.v[i] = 0;
	}
	return ans;
}

//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///
//																	//
//								nVec3								//
//																	//
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///
bool Engine::Math::operator==(const Engine::Math::nVec3& Left, const Engine::Math::nVec3& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::Math::nVec3::_SuffixNum; i++)
		ans &= Left.v[i] == Right.v[i];
	return ans;
}
bool Engine::Math::operator!=(const Engine::Math::nVec3& Left, const Engine::Math::nVec3& Right)
{
	return !(Left == Right);
}
bool Engine::Math::operator>(const Engine::Math::nVec3& Left, const Engine::Math::nVec3& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::Math::nVec3::_SuffixNum; i++)
		ans &= Left.v[i] > Right.v[i];
	return ans;
}
bool Engine::Math::operator<(const Engine::Math::nVec3& Left, const Engine::Math::nVec3& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::Math::nVec3::_SuffixNum; i++)
		ans &= Left.v[i] < Right.v[i];
	return ans;
}
bool Engine::Math::operator>=(const Engine::Math::nVec3& Left, const Engine::Math::nVec3& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::Math::nVec3::_SuffixNum; i++)
		ans &= Left.v[i] >= Right.v[i];
	return ans;
}
bool Engine::Math::operator<=(const Engine::Math::nVec3& Left, const Engine::Math::nVec3& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::Math::nVec3::_SuffixNum; i++)
		ans &= Left.v[i] <= Right.v[i];
	return ans;
}
Engine::Math::nVec3 Engine::Math::operator+(const Engine::Math::nVec3& Left, const Engine::Math::nVec3& Right)
{
	Engine::Math::nVec3 ans;
	for (int i = 0; i < Engine::Math::nVec3::_SuffixNum; i++)
		ans.v[i] = Left.v[i] + Right.v[i];
	return ans;
}
Engine::Math::nVec3 Engine::Math::operator-(const Engine::Math::nVec3& Left, const Engine::Math::nVec3& Right)
{
	Engine::Math::nVec3 ans;
	for (int i = 0; i < Engine::Math::nVec3::_SuffixNum; i++)
		ans.v[i] = Left.v[i] - Right.v[i];
	return ans;
}
Engine::Math::nVec3 Engine::Math::operator*(const Engine::Math::nVec3& Left, const Engine::Math::nVec3& Right)
{
	Engine::Math::nVec3 ans;
	for (int i = 0; i < Engine::Math::nVec3::_SuffixNum; i++)
		ans.v[i] = Left.v[i] * Right.v[i];
	return ans;
}
Engine::Math::nVec3 Engine::Math::operator/(const Engine::Math::nVec3& Left, const Engine::Math::nVec3& Right)
{
	Engine::Math::nVec3 ans;
	for (int i = 0; i < Engine::Math::nVec3::_SuffixNum; i++)
	{
		if (Right.v[i] != 0)
			ans.v[i] = Left.v[i] / Right.v[i];
		else
			ans.v[i] = 0;
	}
	return ans;
}
Engine::Math::nVec3 Engine::Math::operator+(const Engine::Math::nVec3& Left, const int Right)
{
	Engine::Math::nVec3 ans;
	for (int i = 0; i < Engine::Math::nVec3::_SuffixNum; i++)
		ans.v[i] = Left.v[i] + Right;
	return ans;
}
Engine::Math::nVec3 Engine::Math::operator-(const Engine::Math::nVec3& Left, const int Right)
{
	Engine::Math::nVec3 ans;
	for (int i = 0; i < Engine::Math::nVec3::_SuffixNum; i++)
		ans.v[i] = Left.v[i] - Right;
	return ans;
}
Engine::Math::nVec3 Engine::Math::operator*(const Engine::Math::nVec3& Left, const int Right)
{
	Engine::Math::nVec3 ans;
	for (int i = 0; i < Engine::Math::nVec3::_SuffixNum; i++)
		ans.v[i] = Left.v[i] * Right;
	return ans;
}
Engine::Math::nVec3 Engine::Math::operator/(const Engine::Math::nVec3& Left, const int Right)
{
	Engine::Math::nVec3 ans;
	for (int i = 0; i < Engine::Math::nVec3::_SuffixNum; i++)
	{
		if (Right != 0)
			ans.v[i] = Left.v[i] / Right;
		else
			ans.v[i] = 0;
	}
	return ans;
}

//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///
//																	//
//								nVec4								//
//																	//
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///
bool Engine::Math::operator==(const Engine::Math::nVec4& Left, const Engine::Math::nVec4& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::Math::nVec4::_SuffixNum; i++)
		ans &= Left.v[i] == Right.v[i];
	return ans;
}
bool Engine::Math::operator!=(const Engine::Math::nVec4& Left, const Engine::Math::nVec4& Right)
{
	return !(Left == Right);
}
bool Engine::Math::operator>(const Engine::Math::nVec4& Left, const Engine::Math::nVec4& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::Math::nVec4::_SuffixNum; i++)
		ans &= Left.v[i] > Right.v[i];
	return ans;
}
bool Engine::Math::operator<(const Engine::Math::nVec4& Left, const Engine::Math::nVec4& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::Math::nVec4::_SuffixNum; i++)
		ans &= Left.v[i] < Right.v[i];
	return ans;
}
bool Engine::Math::operator>=(const Engine::Math::nVec4& Left, const Engine::Math::nVec4& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::Math::nVec4::_SuffixNum; i++)
		ans &= Left.v[i] >= Right.v[i];
	return ans;
}
bool Engine::Math::operator<=(const Engine::Math::nVec4& Left, const Engine::Math::nVec4& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::Math::nVec4::_SuffixNum; i++)
		ans &= Left.v[i] <= Right.v[i];
	return ans;
}
Engine::Math::nVec4 Engine::Math::operator+(const Engine::Math::nVec4& Left, const Engine::Math::nVec4& Right)
{
	Engine::Math::nVec4 ans;
	for (int i = 0; i < Engine::Math::nVec4::_SuffixNum; i++)
		ans.v[i] = Left.v[i] + Right.v[i];
	return ans;
}
Engine::Math::nVec4 Engine::Math::operator-(const Engine::Math::nVec4& Left, const Engine::Math::nVec4& Right)
{
	Engine::Math::nVec4 ans;
	for (int i = 0; i < Engine::Math::nVec4::_SuffixNum; i++)
		ans.v[i] = Left.v[i] - Right.v[i];
	return ans;
}
Engine::Math::nVec4 Engine::Math::operator*(const Engine::Math::nVec4& Left, const Engine::Math::nVec4& Right)
{
	Engine::Math::nVec4 ans;
	for (int i = 0; i < Engine::Math::nVec4::_SuffixNum; i++)
		ans.v[i] = Left.v[i] * Right.v[i];
	return ans;
}
Engine::Math::nVec4 Engine::Math::operator/(const Engine::Math::nVec4& Left, const Engine::Math::nVec4& Right)
{
	Engine::Math::nVec4 ans;
	for (int i = 0; i < Engine::Math::nVec4::_SuffixNum; i++)
	{
		if (Right.v[i] != 0)
			ans.v[i] = Left.v[i] / Right.v[i];
		else
			ans.v[i] = 0;
	}
	return ans;
}
Engine::Math::nVec4 Engine::Math::operator+(const Engine::Math::nVec4& Left, const int Right)
{
	Engine::Math::nVec4 ans;
	for (int i = 0; i < Engine::Math::nVec4::_SuffixNum; i++)
		ans.v[i] = Left.v[i] + Right;
	return ans;
}
Engine::Math::nVec4 Engine::Math::operator-(const Engine::Math::nVec4& Left, const int Right)
{
	Engine::Math::nVec4 ans;
	for (int i = 0; i < Engine::Math::nVec4::_SuffixNum; i++)
		ans.v[i] = Left.v[i] - Right;
	return ans;
}
Engine::Math::nVec4 Engine::Math::operator*(const Engine::Math::nVec4& Left, const int Right)
{
	Engine::Math::nVec4 ans;
	for (int i = 0; i < Engine::Math::nVec4::_SuffixNum; i++)
		ans.v[i] = Left.v[i] * Right;
	return ans;
}
Engine::Math::nVec4 Engine::Math::operator/(const Engine::Math::nVec4& Left, const int Right)
{
	Engine::Math::nVec4 ans;
	for (int i = 0; i < Engine::Math::nVec4::_SuffixNum; i++)
	{
		if (Right != 0)
			ans.v[i] = Left.v[i] / Right;
		else
			ans.v[i] = 0;
	}
	return ans;
}

float Engine::Math::Vec::length(const Engine::Math::fVec3& Vector)
{
	return powf(Vector.x * Vector.x + Vector.y * Vector.y + Vector.z * Vector.z, 0.5f);
}
Engine::Math::fVec3 Engine::Math::Vec::Nomalize(Engine::Math::fVec3 Vector)
{
	return (Vector / length(Vector));
}
