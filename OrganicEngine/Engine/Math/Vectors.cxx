#include "Vectors.hxx"
#include <cmath>

ID Engine::unique_ID::m_Counter = 0;

//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///
//																	//
//								fVec2								//
//																	//
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///
bool Engine::operator==(const Engine::fVec2& Left, const Engine::fVec2& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::fVec2::_SuffixNum; i++)
		ans &= Left.v[i] == Right.v[i];
	return ans;
}
bool Engine::operator!=(const Engine::fVec2& Left, const Engine::fVec2& Right)
{
	return !(Left == Right);
}
bool Engine::operator>(const Engine::fVec2& Left, const Engine::fVec2& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::fVec2::_SuffixNum; i++)
		ans &= Left.v[i] > Right.v[i];
	return ans;
}
bool Engine::operator<(const Engine::fVec2& Left, const Engine::fVec2& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::fVec2::_SuffixNum; i++)
		ans &= Left.v[i] < Right.v[i];
	return ans;
}
bool Engine::operator>=(const Engine::fVec2& Left, const Engine::fVec2& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::fVec2::_SuffixNum; i++)
		ans &= Left.v[i] >= Right.v[i];
	return ans;
}
bool Engine::operator<=(const Engine::fVec2& Left, const Engine::fVec2& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::fVec2::_SuffixNum; i++)
		ans &= Left.v[i] <= Right.v[i];
	return ans;
}
Engine::fVec2 Engine::operator+(const Engine::fVec2& Left, const Engine::fVec2& Right)
{
	Engine::fVec2 ans;
	for (int i = 0; i < Engine::fVec2::_SuffixNum; i++)
		ans.v[i] = Left.v[i] + Right.v[i];
	return ans;
}
Engine::fVec2 Engine::operator-(const Engine::fVec2& Left, const Engine::fVec2& Right)
{
	Engine::fVec2 ans;
	for (int i = 0; i < Engine::fVec2::_SuffixNum; i++)
		ans.v[i] = Left.v[i] - Right.v[i];
	return ans;
}
Engine::fVec2 Engine::operator*(const Engine::fVec2& Left, const Engine::fVec2& Right)
{
	Engine::fVec2 ans;
	for (int i = 0; i < Engine::fVec2::_SuffixNum; i++)
		ans.v[i] = Left.v[i] * Right.v[i];
	return ans;
}
Engine::fVec2 Engine::operator/(const Engine::fVec2& Left, const Engine::fVec2& Right)
{
	Engine::fVec2 ans;
	for (int i = 0; i < Engine::fVec2::_SuffixNum; i++)
	{
		if (Right.v[i] != 0.0f)
			ans.v[i] = Left.v[i] / Right.v[i];
		else
			ans.v[i] = 0.0f;
	}
	return ans;
}
Engine::fVec2 Engine::operator+(const Engine::fVec2& Left, const float Right)
{
	Engine::fVec2 ans;
	for (int i = 0; i < Engine::fVec2::_SuffixNum; i++)
		ans.v[i] = Left.v[i] + Right;
	return ans;
}
Engine::fVec2 Engine::operator-(const Engine::fVec2& Left, const float Right)
{
	Engine::fVec2 ans;
	for (int i = 0; i < Engine::fVec2::_SuffixNum; i++)
		ans.v[i] = Left.v[i] - Right;
	return ans;
}
Engine::fVec2 Engine::operator*(const Engine::fVec2& Left, const float Right)
{
	Engine::fVec2 ans;
	for (int i = 0; i < Engine::fVec2::_SuffixNum; i++)
		ans.v[i] = Left.v[i] * Right;
	return ans;
}
Engine::fVec2 Engine::operator/(const Engine::fVec2& Left, const float Right)
{
	Engine::fVec2 ans;
	for (int i = 0; i < Engine::fVec2::_SuffixNum; i++)
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
//								Engine::fVec3								//
//																	//
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///
bool Engine::operator==(const Engine::fVec3& Left, const Engine::fVec3& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::fVec3::_SuffixNum; i++)
		ans &= Left.v[i] == Right.v[i];
	return ans;
}
bool Engine::operator!=(const Engine::fVec3& Left, const Engine::fVec3& Right)
{
	return !(Left == Right);
}
bool Engine::operator>(const Engine::fVec3& Left, const Engine::fVec3& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::fVec3::_SuffixNum; i++)
		ans &= Left.v[i] > Right.v[i];
	return ans;
}
bool Engine::operator<(const Engine::fVec3& Left, const Engine::fVec3& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::fVec3::_SuffixNum; i++)
		ans &= Left.v[i] < Right.v[i];
	return ans;
}
bool Engine::operator>=(const Engine::fVec3& Left, const Engine::fVec3& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::fVec3::_SuffixNum; i++)
		ans &= Left.v[i] >= Right.v[i];
	return ans;
}
bool Engine::operator<=(const Engine::fVec3& Left, const Engine::fVec3& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::fVec3::_SuffixNum; i++)
		ans &= Left.v[i] <= Right.v[i];
	return ans;
}
Engine::fVec3 Engine::operator+(const Engine::fVec3& Left, const Engine::fVec3& Right)
{
	Engine::fVec3 ans;
	for (int i = 0; i < Engine::fVec3::_SuffixNum; i++)
		ans.v[i] = Left.v[i] + Right.v[i];
	return ans;
}
Engine::fVec3 Engine::operator-(const Engine::fVec3& Left, const Engine::fVec3& Right)
{
	Engine::fVec3 ans;
	for (int i = 0; i < Engine::fVec3::_SuffixNum; i++)
		ans.v[i] = Left.v[i] - Right.v[i];
	return ans;
}
Engine::fVec3 Engine::operator*(const Engine::fVec3& Left, const Engine::fVec3& Right)
{
	Engine::fVec3 ans;
	for (int i = 0; i < Engine::fVec3::_SuffixNum; i++)
		ans.v[i] = Left.v[i] * Right.v[i];
	return ans;
}
Engine::fVec3 Engine::operator/(const Engine::fVec3& Left, const Engine::fVec3& Right)
{
	Engine::fVec3 ans;
	for (int i = 0; i < Engine::fVec3::_SuffixNum; i++)
	{
		if (Right.v[i] != 0.0f)
			ans.v[i] = Left.v[i] / Right.v[i];
		else
			ans.v[i] = 0.0f;
	}
	return ans;
}
Engine::fVec3 Engine::operator+(const Engine::fVec3& Left, const float Right)
{
	Engine::fVec3 ans;
	for (int i = 0; i < Engine::fVec3::_SuffixNum; i++)
		ans.v[i] = Left.v[i] + Right;
	return ans;
}
Engine::fVec3 Engine::operator-(const Engine::fVec3& Left, const float Right)
{
	Engine::fVec3 ans;
	for (int i = 0; i < Engine::fVec3::_SuffixNum; i++)
		ans.v[i] = Left.v[i] - Right;
	return ans;
}
Engine::fVec3 Engine::operator*(const Engine::fVec3& Left, const float Right)
{
	Engine::fVec3 ans;
	for (int i = 0; i < Engine::fVec3::_SuffixNum; i++)
		ans.v[i] = Left.v[i] * Right;
	return ans;
}
Engine::fVec3 Engine::operator/(const Engine::fVec3& Left, const float Right)
{
	Engine::fVec3 ans;
	for (int i = 0; i < Engine::fVec3::_SuffixNum; i++)
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
//								Engine::fVec4								//
//																	//
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///
bool Engine::operator==(const Engine::fVec4& Left, const Engine::fVec4& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::fVec4::_SuffixNum; i++)
		ans &= Left.v[i] == Right.v[i];
	return ans;
}
bool Engine::operator!=(const Engine::fVec4& Left, const Engine::fVec4& Right)
{
	return !(Left == Right);
}
bool Engine::operator>(const Engine::fVec4& Left, const Engine::fVec4& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::fVec4::_SuffixNum; i++)
		ans &= Left.v[i] > Right.v[i];
	return ans;
}
bool Engine::operator<(const Engine::fVec4& Left, const Engine::fVec4& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::fVec4::_SuffixNum; i++)
		ans &= Left.v[i] < Right.v[i];
	return ans;
}
bool Engine::operator>=(const Engine::fVec4& Left, const Engine::fVec4& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::fVec4::_SuffixNum; i++)
		ans &= Left.v[i] >= Right.v[i];
	return ans;
}
bool Engine::operator<=(const Engine::fVec4& Left, const Engine::fVec4& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::fVec4::_SuffixNum; i++)
		ans &= Left.v[i] <= Right.v[i];
	return ans;
}
Engine::fVec4 Engine::operator+(const Engine::fVec4& Left, const Engine::fVec4& Right)
{
	Engine::fVec4 ans;
	for (int i = 0; i < Engine::fVec4::_SuffixNum; i++)
		ans.v[i] = Left.v[i] + Right.v[i];
	return ans;
}
Engine::fVec4 Engine::operator-(const Engine::fVec4& Left, const Engine::fVec4& Right)
{
	Engine::fVec4 ans;
	for (int i = 0; i < Engine::fVec4::_SuffixNum; i++)
		ans.v[i] = Left.v[i] - Right.v[i];
	return ans;
}
Engine::fVec4 Engine::operator*(const Engine::fVec4& Left, const Engine::fVec4& Right)
{
	Engine::fVec4 ans;
	for (int i = 0; i < Engine::fVec4::_SuffixNum; i++)
		ans.v[i] = Left.v[i] * Right.v[i];
	return ans;
}
Engine::fVec4 Engine::operator/(const Engine::fVec4& Left, const Engine::fVec4& Right)
{
	Engine::fVec4 ans;
	for (int i = 0; i < Engine::fVec4::_SuffixNum; i++)
	{
		if (Right.v[i] != 0.0f)
			ans.v[i] = Left.v[i] / Right.v[i];
		else
			ans.v[i] = 0.0f;
	}
	return ans;
}
Engine::fVec4 Engine::operator+(const Engine::fVec4& Left, const float Right)
{
	Engine::fVec4 ans;
	for (int i = 0; i < Engine::fVec4::_SuffixNum; i++)
		ans.v[i] = Left.v[i] + Right;
	return ans;
}
Engine::fVec4 Engine::operator-(const Engine::fVec4& Left, const float Right)
{
	Engine::fVec4 ans;
	for (int i = 0; i < Engine::fVec4::_SuffixNum; i++)
		ans.v[i] = Left.v[i] - Right;
	return ans;
}
Engine::fVec4 Engine::operator*(const Engine::fVec4& Left, const float Right)
{
	Engine::fVec4 ans;
	for (int i = 0; i < Engine::fVec4::_SuffixNum; i++)
		ans.v[i] = Left.v[i] * Right;
	return ans;
}
Engine::fVec4 Engine::operator/(const Engine::fVec4& Left, const float Right)
{
	Engine::fVec4 ans;
	for (int i = 0; i < Engine::fVec4::_SuffixNum; i++)
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
bool Engine::operator==(const Engine::nVec2& Left, const Engine::nVec2& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::nVec2::_SuffixNum; i++)
		ans &= Left.v[i] == Right.v[i];
	return ans;
}
bool Engine::operator!=(const Engine::nVec2& Left, const Engine::nVec2& Right)
{
	return !(Left == Right);
}
bool Engine::operator>(const Engine::nVec2& Left, const Engine::nVec2& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::nVec2::_SuffixNum; i++)
		ans &= Left.v[i] > Right.v[i];
	return ans;
}
bool Engine::operator<(const Engine::nVec2& Left, const Engine::nVec2& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::nVec2::_SuffixNum; i++)
		ans &= Left.v[i] < Right.v[i];
	return ans;
}
bool Engine::operator>=(const Engine::nVec2& Left, const Engine::nVec2& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::nVec2::_SuffixNum; i++)
		ans &= Left.v[i] >= Right.v[i];
	return ans;
}
bool Engine::operator<=(const Engine::nVec2& Left, const Engine::nVec2& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::nVec2::_SuffixNum; i++)
		ans &= Left.v[i] <= Right.v[i];
	return ans;
}
Engine::nVec2 Engine::operator+(const Engine::nVec2& Left, const Engine::nVec2& Right)
{
	Engine::nVec2 ans;
	for (int i = 0; i < Engine::nVec2::_SuffixNum; i++)
		ans.v[i] = Left.v[i] + Right.v[i];
	return ans;
}
Engine::nVec2 Engine::operator-(const Engine::nVec2& Left, const Engine::nVec2& Right)
{
	Engine::nVec2 ans;
	for (int i = 0; i < Engine::nVec2::_SuffixNum; i++)
		ans.v[i] = Left.v[i] - Right.v[i];
	return ans;
}
Engine::nVec2 Engine::operator*(const Engine::nVec2& Left, const Engine::nVec2& Right)
{
	Engine::nVec2 ans;
	for (int i = 0; i < Engine::nVec2::_SuffixNum; i++)
		ans.v[i] = Left.v[i] * Right.v[i];
	return ans;
}
Engine::nVec2 Engine::operator/(const Engine::nVec2& Left, const Engine::nVec2& Right)
{
	Engine::nVec2 ans;
	for (int i = 0; i < Engine::nVec2::_SuffixNum; i++)
	{
		if (Right.v[i] != 0)
			ans.v[i] = Left.v[i] / Right.v[i];
		else
			ans.v[i] = 0;
	}
	return ans;
}
Engine::nVec2 Engine::operator+(const Engine::nVec2& Left, const int Right)
{
	Engine::nVec2 ans;
	for (int i = 0; i < Engine::nVec2::_SuffixNum; i++)
		ans.v[i] = Left.v[i] + Right;
	return ans;
}
Engine::nVec2 Engine::operator-(const Engine::nVec2& Left, const int Right)
{
	Engine::nVec2 ans;
	for (int i = 0; i < Engine::nVec2::_SuffixNum; i++)
		ans.v[i] = Left.v[i] - Right;
	return ans;
}
Engine::nVec2 Engine::operator*(const Engine::nVec2& Left, const int Right)
{
	Engine::nVec2 ans;
	for (int i = 0; i < Engine::nVec2::_SuffixNum; i++)
		ans.v[i] = Left.v[i] * Right;
	return ans;
}
Engine::nVec2 Engine::operator/(const Engine::nVec2& Left, const int Right)
{
	Engine::nVec2 ans;
	for (int i = 0; i < Engine::nVec2::_SuffixNum; i++)
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
bool Engine::operator==(const Engine::nVec3& Left, const Engine::nVec3& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::nVec3::_SuffixNum; i++)
		ans &= Left.v[i] == Right.v[i];
	return ans;
}
bool Engine::operator!=(const Engine::nVec3& Left, const Engine::nVec3& Right)
{
	return !(Left == Right);
}
bool Engine::operator>(const Engine::nVec3& Left, const Engine::nVec3& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::nVec3::_SuffixNum; i++)
		ans &= Left.v[i] > Right.v[i];
	return ans;
}
bool Engine::operator<(const Engine::nVec3& Left, const Engine::nVec3& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::nVec3::_SuffixNum; i++)
		ans &= Left.v[i] < Right.v[i];
	return ans;
}
bool Engine::operator>=(const Engine::nVec3& Left, const Engine::nVec3& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::nVec3::_SuffixNum; i++)
		ans &= Left.v[i] >= Right.v[i];
	return ans;
}
bool Engine::operator<=(const Engine::nVec3& Left, const Engine::nVec3& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::nVec3::_SuffixNum; i++)
		ans &= Left.v[i] <= Right.v[i];
	return ans;
}
Engine::nVec3 Engine::operator+(const Engine::nVec3& Left, const Engine::nVec3& Right)
{
	Engine::nVec3 ans;
	for (int i = 0; i < Engine::nVec3::_SuffixNum; i++)
		ans.v[i] = Left.v[i] + Right.v[i];
	return ans;
}
Engine::nVec3 Engine::operator-(const Engine::nVec3& Left, const Engine::nVec3& Right)
{
	Engine::nVec3 ans;
	for (int i = 0; i < Engine::nVec3::_SuffixNum; i++)
		ans.v[i] = Left.v[i] - Right.v[i];
	return ans;
}
Engine::nVec3 Engine::operator*(const Engine::nVec3& Left, const Engine::nVec3& Right)
{
	Engine::nVec3 ans;
	for (int i = 0; i < Engine::nVec3::_SuffixNum; i++)
		ans.v[i] = Left.v[i] * Right.v[i];
	return ans;
}
Engine::nVec3 Engine::operator/(const Engine::nVec3& Left, const Engine::nVec3& Right)
{
	Engine::nVec3 ans;
	for (int i = 0; i < Engine::nVec3::_SuffixNum; i++)
	{
		if (Right.v[i] != 0)
			ans.v[i] = Left.v[i] / Right.v[i];
		else
			ans.v[i] = 0;
	}
	return ans;
}
Engine::nVec3 Engine::operator+(const Engine::nVec3& Left, const int Right)
{
	Engine::nVec3 ans;
	for (int i = 0; i < Engine::nVec3::_SuffixNum; i++)
		ans.v[i] = Left.v[i] + Right;
	return ans;
}
Engine::nVec3 Engine::operator-(const Engine::nVec3& Left, const int Right)
{
	Engine::nVec3 ans;
	for (int i = 0; i < Engine::nVec3::_SuffixNum; i++)
		ans.v[i] = Left.v[i] - Right;
	return ans;
}
Engine::nVec3 Engine::operator*(const Engine::nVec3& Left, const int Right)
{
	Engine::nVec3 ans;
	for (int i = 0; i < Engine::nVec3::_SuffixNum; i++)
		ans.v[i] = Left.v[i] * Right;
	return ans;
}
Engine::nVec3 Engine::operator/(const Engine::nVec3& Left, const int Right)
{
	Engine::nVec3 ans;
	for (int i = 0; i < Engine::nVec3::_SuffixNum; i++)
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
bool Engine::operator==(const Engine::nVec4& Left, const Engine::nVec4& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::nVec4::_SuffixNum; i++)
		ans &= Left.v[i] == Right.v[i];
	return ans;
}
bool Engine::operator!=(const Engine::nVec4& Left, const Engine::nVec4& Right)
{
	return !(Left == Right);
}
bool Engine::operator>(const Engine::nVec4& Left, const Engine::nVec4& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::nVec4::_SuffixNum; i++)
		ans &= Left.v[i] > Right.v[i];
	return ans;
}
bool Engine::operator<(const Engine::nVec4& Left, const Engine::nVec4& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::nVec4::_SuffixNum; i++)
		ans &= Left.v[i] < Right.v[i];
	return ans;
}
bool Engine::operator>=(const Engine::nVec4& Left, const Engine::nVec4& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::nVec4::_SuffixNum; i++)
		ans &= Left.v[i] >= Right.v[i];
	return ans;
}
bool Engine::operator<=(const Engine::nVec4& Left, const Engine::nVec4& Right)
{
	bool ans = true;
	for (int i = 0; i < Engine::nVec4::_SuffixNum; i++)
		ans &= Left.v[i] <= Right.v[i];
	return ans;
}
Engine::nVec4 Engine::operator+(const Engine::nVec4& Left, const Engine::nVec4& Right)
{
	Engine::nVec4 ans;
	for (int i = 0; i < Engine::nVec4::_SuffixNum; i++)
		ans.v[i] = Left.v[i] + Right.v[i];
	return ans;
}
Engine::nVec4 Engine::operator-(const Engine::nVec4& Left, const Engine::nVec4& Right)
{
	Engine::nVec4 ans;
	for (int i = 0; i < Engine::nVec4::_SuffixNum; i++)
		ans.v[i] = Left.v[i] - Right.v[i];
	return ans;
}
Engine::nVec4 Engine::operator*(const Engine::nVec4& Left, const Engine::nVec4& Right)
{
	Engine::nVec4 ans;
	for (int i = 0; i < Engine::nVec4::_SuffixNum; i++)
		ans.v[i] = Left.v[i] * Right.v[i];
	return ans;
}
Engine::nVec4 Engine::operator/(const Engine::nVec4& Left, const Engine::nVec4& Right)
{
	Engine::nVec4 ans;
	for (int i = 0; i < Engine::nVec4::_SuffixNum; i++)
	{
		if (Right.v[i] != 0)
			ans.v[i] = Left.v[i] / Right.v[i];
		else
			ans.v[i] = 0;
	}
	return ans;
}
Engine::nVec4 Engine::operator+(const Engine::nVec4& Left, const int Right)
{
	Engine::nVec4 ans;
	for (int i = 0; i < Engine::nVec4::_SuffixNum; i++)
		ans.v[i] = Left.v[i] + Right;
	return ans;
}
Engine::nVec4 Engine::operator-(const Engine::nVec4& Left, const int Right)
{
	Engine::nVec4 ans;
	for (int i = 0; i < Engine::nVec4::_SuffixNum; i++)
		ans.v[i] = Left.v[i] - Right;
	return ans;
}
Engine::nVec4 Engine::operator*(const Engine::nVec4& Left, const int Right)
{
	Engine::nVec4 ans;
	for (int i = 0; i < Engine::nVec4::_SuffixNum; i++)
		ans.v[i] = Left.v[i] * Right;
	return ans;
}
Engine::nVec4 Engine::operator/(const Engine::nVec4& Left, const int Right)
{
	Engine::nVec4 ans;
	for (int i = 0; i < Engine::nVec4::_SuffixNum; i++)
	{
		if (Right != 0)
			ans.v[i] = Left.v[i] / Right;
		else
			ans.v[i] = 0;
	}
	return ans;
}

float Engine::Vec::length(const Engine::fVec3& Vector)
{
	return powf(Vector.x * Vector.x + Vector.y * Vector.y + Vector.z * Vector.z, 0.5f);
}
Engine::fVec3 Engine::Vec::Nomalize(Engine::fVec3 Vector)
{
	return (Vector / length(Vector));
}
