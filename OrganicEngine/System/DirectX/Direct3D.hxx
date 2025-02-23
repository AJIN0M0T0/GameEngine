//	ファイル名	：Direct3D.hxx
//	  概  要	：
//	作	成	者	：daigo
//	 作成日時	：2025/02/23 21:02:51
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= インクルードガード部 =-=-=
#ifndef _____Direct3D_HXX_____
#define _____Direct3D_HXX_____

// =-=-= インクルード部 =-=-=
#include "../../Defines.hxx"
#include <d3d12.h>
#include <dxgi1_6.h>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

namespace dxp {
	class Device {};
	class DeviceContext {};
	class RasterizerState {};
	class BlendState {};
	class SamplerState {};

	D3D_FEATURE_LEVEL levels[] = {
#ifdef DIRECTX12_PRJ
		D3D_FEATURE_LEVEL_12_2,
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
#endif // DIRECTX12_PRJ
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
	};
}
/* @brief		DirectXの抽象クラス
 * @details		DirectX11とDirectX12の基底クラス。切り替えの単純化
 * @author		伊藤大悟
 * @bug			{解決できていないバグの説明}
 * @warning		{警告}
 * @remark		{注釈}
 * @note		{覚え書き}*/
class Direct3D
{
public:
	Direct3D();
	~Direct3D();

private:

};

#endif // !_____Direct3D_HXX_____
