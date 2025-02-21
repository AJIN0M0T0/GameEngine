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
    float3 Pos : POSITION;
    float4 Color : COLOR;
};

struct PS_IN_01
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR;
};