#include "../defines.hlsli"

Texture2D tex : register(t0);
SamplerState samp : register(s0);

float4 main(PS_IN_01 pin) : SV_TARGET
{
	float4 color = tex.Sample(samp, pin.uv);
	return color;
}
