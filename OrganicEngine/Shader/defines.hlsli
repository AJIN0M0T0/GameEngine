//	�t�@�C����	�Fdefines.hlsli
//	  �T  �v		�F�\���̂̒�`
//	��	��	��	�Fdaigo
//	 �쐬����	�F2025/02/21 10:11:12
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