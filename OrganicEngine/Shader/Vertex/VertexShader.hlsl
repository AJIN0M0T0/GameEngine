#include "../defines.hlsli"

cbuffer WVP : register(b0)
{
	WVP wvp;
};

PS_IN_01 main( VS_IN_01 vin)
{
	PS_IN_01 vout;
	
	// ローカル座標をスクリーン座標へ変換
	vout.pos = float4(vin.pos, 1.0f); // ローカル座標
	vout.pos = mul(vout.pos, wvp.World); // ワールド座標
	vout.pos = mul(vout.pos, wvp.View); // ビュー座標
	vout.pos = mul(vout.pos, wvp.Projection); // プロジェクション座標

	// ピクセルシェーダーで利用するUV座標を渡す
	vout.uv = vin.uv;

	// ピクセルシェーダーで利用する法線を渡す
	// 法線はオブジェクトの回転に併せて回転させないとおかしな見た目になる。
	// ワールド行列には移動成分も含まれるが、移動を法線に適用してもおかしく
	// なるので、回転成分のみの行列となるように縮小して計算する。
	vout.normal = mul(vin.normal, (float3x3) wvp.World);

	return vout;
}
