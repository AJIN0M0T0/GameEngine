//	ファイル名	：Device.hxx
//	  概  要	：
//	作	成	者	：daigo
//	 作成日時	：2025/02/28 21:22:16
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= インクルードガード部 =-=-=
#ifndef _____Device_HXX_____
#define _____Device_HXX_____

// =-=-= インクルード部 =-=-=

namespace Engine {
	namespace Graphic {
		class iDevice
		{
		public:
			virtual ~iDevice() = default;

			virtual bool Initialize() = 0;
			virtual void CreateRenderTarget() = 0;
			//HRESULT virtual CreateBuffer(const void* bufferDesc, const void* SubresourceData, void** ppBuffer) = 0;
		};

		// 前方定義
		class ID3D11Device;
		class ID3D11DeviceContext;

		class DirectX11Device 
			: public iDevice
		{
		public:
			bool Initialize() override;
			void CreateRenderTarget() override;

		private:
			std::unique_ptr<ID3D11Device> m_Device;
			std::unique_ptr<ID3D11DeviceContext> m_DeviceContext;
		};

		// 前方定義
		class ID3D12Device;

		class DirectX12Device 
			: public iDevice
		{
		public:
			bool Initialize() override;
			void CreateRenderTarget() override;
		private:
			std::unique_ptr<ID3D12Device> m_Device;
		};
	}
}

#endif // !_____Device_HXX_____
