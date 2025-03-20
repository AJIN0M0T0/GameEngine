//	ファイル名	：defines.hlsli
//	  概  要		：構造体の定義
//	作	成	者	：daigo
//	 作成日時	：2025/02/21 10:11:12
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

struct WVP
{
    float4x4 World;
    float4x4 View;
    float4x4 Projection;
};

struct VS_IN_01
{
    float3 pos : POSITION0;
	float3 normal : NORMAL0;
	float2 uv : TEXCOORD0;
};

struct PS_IN_01
{
    float4 pos : SV_POSITION0;
    float2 uv : TEXCOORD0;
	float3 normal : NORMAL0;
};
