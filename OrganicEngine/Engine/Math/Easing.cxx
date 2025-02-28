// ----------インクルード部----------
#include "Easing.hxx"
#include "Vectors.hxx"
#include <cmath>

// ----------定数定義部----------
namespace
{
	constexpr float c1 = 1.70158f;
	constexpr float c2 = c1 * 1.525f;
	constexpr float c3 = c1 + 1;
	constexpr float c4 = (2 * Engine::PI) / 3;
	constexpr float c5 = (2 * Engine::PI) / 4.5f;
	constexpr float n1 = 7.5625f;
	constexpr float d1 = 2.75f;

	//入力値の補正
	void Revision(float* num)
	{
		if (*num < 0.0f)
			*num = 0.0f;
		else if (*num > 1.0f)
			*num = 1.0f;
		return;
	}

}

namespace Engine {
	// ネームスペース「 eas 」
	namespace eas
	{
		float InSine(float num)
		{
			Revision(&num);
			return (1 - cosf((num * PI) * 0.5f));
		}

		float OutSine(float num)
		{
			Revision(&num);
			return (sinf((num * PI) * 0.5f));
		}

		float InOutSine(float num)
		{
			Revision(&num);
			return (-(cosf(PI * num) - 1) * 0.5f);
		}

		float InQuad(float num)
		{
			Revision(&num);
			return (powf(num, 2));
		}

		float OutQuad(float num)
		{
			Revision(&num);
			return (1 - powf(1 - num, 2));
		}

		float InOutQuad(float num)
		{
			Revision(&num);
			return
				(
					(num < 0.5f)
					?
					(
						2 * powf(num, 2)
						)
					:
					(
						1 - powf(-2 * num + 2, 2) * 0.5f
						)
					);
		}

		float InCubic(float num)
		{
			Revision(&num);
			return (powf(num, 3));
		}

		float OutCubic(float num)
		{
			Revision(&num);
			return (1 - powf(1 - num, 3));
		}

		float InOutCubic(float num)
		{
			Revision(&num);
			return
				(
					(num < 0.5f)
					?
					(
						4 * powf(num, 3)
						)
					:
					(
						1 - powf(-2 * num + 2, 3) * 0.5f
						)
					);
		}

		float InQuart(float num)
		{
			Revision(&num);
			return (powf(num, 4));
		}

		float OutQuart(float num)
		{
			Revision(&num);
			return (1 - powf(1 - num, 4));
		}

		float InOutQuart(float num)
		{
			Revision(&num);
			return
				(
					(num < 0.5f)
					?
					(
						8 * powf(num, 4)
						)
					:
					(
						1 - powf(-2 * num + 2, 4) * 0.5f
						)
					);
		}

		float InQuint(float num)
		{
			Revision(&num);
			return (powf(num, 5));
		}

		float OutQuint(float num)
		{
			Revision(&num);
			return (1 - powf(1 - num, 5));
		}

		float InOutQuint(float num)
		{
			Revision(&num);
			return
				(
					(num < 0.5f)
					?
					(
						16 * powf(num, 5)
						)
					:
					(
						1 - powf(-2 * num + 2, 5) * 0.5f
						)
					);
		}

		float InExpo(float num)
		{
			Revision(&num);
			return
				(
					(num == 0.0f)
					?
					(0.0f)
					:
					(
						powf(2, 10 * num - 10)
						)
					);
		}

		float OutExpo(float num)
		{
			Revision(&num);
			return
				(
					(num == 1.0f)
					?
					(1.0f)
					:
					(
						1 - powf(2, -10 * num)
						)
					);
		}

		float InOutExpo(float num)
		{
			Revision(&num);
			return
				(
					(num == 0.0f)
					?
					(0.0f)
					:
					(
						(num == 1.0f)
						?
						(1.0f)
						:
						(
							(num < 0.5f)
							?
							(
								powf(2, 20 * num - 10) * 0.5f
								)
							:
							(
								(2 - powf(2, -20 * num + 10)) * 0.5f
								)
							)
						)
					);
		}

		float InCirc(float num)
		{
			Revision(&num);
			return (1 - sqrtf(1 - powf(num, 2)));
		}

		float OutCirc(float num)
		{
			Revision(&num);
			return (sqrtf(1 - powf(num - 1, 2)));
		}

		float InOutCirc(float num)
		{
			Revision(&num);
			return
				(
					(num < 0.5f)
					?
					(
						(1 - sqrtf(1 - powf(2 * num, 2))) * 0.5f
						)
					:
					(
						(sqrtf(1 - powf(-2 * num + 2, 2)) + 1) * 0.5f
						)
					);
		}

		float InBack(float num)
		{
			Revision(&num);
			return (c3 * powf(num, 3) - c1 * powf(num, 2));
		}

		float OutBack(float num)
		{
			Revision(&num);
			return (1 + c3 * powf(num - 1, 3) + c1 * powf(num - 1, 2));
		}

		float InOutBack(float num)
		{
			Revision(&num);
			return
				(
					(num < 0.5f)
					?
					(
						(powf(2 * num, 2) * ((c2 + 1) * 2 * num - c2)) * 0.5f
						)
					:
					(
						(powf(2 * num - 2, 2) * ((c2 + 1) * (num * 2 - 2) + c2) + 2) * 0.5f
						)
					);
		}

		float InElastic(float num)
		{
			Revision(&num);
			return
				(
					(num == 0.0f)
					?
					(0.0f)
					:
					(
						(num == 1.0f)
						?
						(1.0f)
						:
						(
							-powf(2, 10 * num - 10) * sinf((num * 10 - 10.75f) * c4)
							)
						)
					);
		}

		float OutElastic(float num)
		{
			Revision(&num);
			return
				(
					(num == 0.0f)
					?
					(0.0f)
					:
					(
						(num == 1.0f)
						?
						(1.0f)
						:
						(
							powf(2, -10 * num) * sinf((num * 10 - 0.75f) * c4) + 1
							)
						)
					);
		}

		float InOutElastic(float num)
		{
			Revision(&num);
			return
				(
					(num == 0.0f)
					?
					(0.0f)
					:
					(
						(num == 1.0f)
						?
						(1.0f)
						:
						(
							(num < 0.5f)
							?
							(
								-(powf(2, 20 * num - 10) * sinf((20 * num - 11.125f) * c5)) * 0.5f
								)
							:
							(
								(powf(2, -20 * num + 10) * sinf((20 * num - 11.125f) * c5)) * 0.5f + 1
								)
							)
						)
					);
		}

		float OutBounce(float num)
		{
			Revision(&num);
			if (num < 1 / d1)
			{
				return (n1 * powf(num, 2));
			}
			else if (num < 2 / d1)
			{
				return (n1 * (num -= 1.5f / d1) * num + 0.75f);
			}
			else if (num < 2.5f / d1)
			{
				return (n1 * (num -= 2.25f / d1) * num + 0.9375f);
			}
			else
			{
				return (n1 * (num -= 2.625f / d1) * num + 0.984375f);
			}
		}

		float InBounce(float num)
		{
			Revision(&num);
			return (1 - OutBounce(1 - num));
		}

		float InOutBounce(float num)
		{
			Revision(&num);
			return
				(
					(num < 0.5f)
					?
					((1 - OutBounce(1 - 2 * num)) * 0.5f)
					:
					((1 + OutBounce(2 * num - 1)) * 0.5f)
					);
		}
	};
};
