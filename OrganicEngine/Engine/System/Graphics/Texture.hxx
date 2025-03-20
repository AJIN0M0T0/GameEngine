//	ファイル名	：Texture.hxx
//	  概  要	：
//	作	成	者	：daigo
//	 作成日時	：2025/02/28 17:15:42
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= インクルードガード部 =-=-=
#ifndef _____Texture_HXX_____
#define _____Texture_HXX_____

// =-=-= インクルード部 =-=-=
#include "../Singleton.hxx"
#include "../../Math/Vectors.hxx"
#include <unordered_map>

#ifdef SHIPPING
#include <Windows.h>
#endif // SHIPPING

enum DXGI_FORMAT;
struct ID3D11ShaderResourceView;
struct ID3D11Texture2D;
struct D3D11_TEXTURE2D_DESC;
struct ID3D11RenderTargetView;
struct ID3D11DepthStencilView;

struct ID3D12ShaderResourceView;
struct ID3D12Texture2D;
struct D3D12_TEXTURE2D_DESC;
struct ID3D12RenderTargetView;
struct ID3D12DepthStencilView;

union convShaderResourceView {
	ID3D11ShaderResourceView* p11SRV;
	ID3D12ShaderResourceView* p12SRV;
};

union convRenderTargetView {
	ID3D11RenderTargetView* p11RTV;
	ID3D12RenderTargetView* p12RTV;
};

union convDepthStencilView {
	ID3D11DepthStencilView* p11DSV;
	ID3D12DepthStencilView* p12DSV;
};

namespace Engine::Graphic {
	class GraphicsManager;

	using SRV_data = std::pair<convShaderResourceView, Math::nVec2>;

	class iTexture
	{
	public:
		iTexture();
		virtual ~iTexture() = default;

		inline uint16 GetWidth()const { return m_width; }
		inline uint16 GetHeight()const { return m_height; }

		virtual HRESULT Create(const char* fileName) = 0;
		virtual HRESULT Create(DXGI_FORMAT format, uint16 width, uint16 height, const void* pData = nullptr) = 0;
		virtual convShaderResourceView GetResource()const = 0;

	protected:
		uint16 m_width;
		uint16 m_height;
	};

	class DirectX11Texture 
		: virtual public iTexture
	{
	public:
		DirectX11Texture();
		virtual ~DirectX11Texture();

		HRESULT Create(const char* fileName) override;
		HRESULT Create(DXGI_FORMAT format, uint16 width, uint16 height, const void* pData = nullptr) override;
		inline convShaderResourceView GetResource()const override { return m_pSRV.get()->first; };

	protected:
		D3D11_TEXTURE2D_DESC MakeTexDesc(DXGI_FORMAT format, uint16 width, uint16 height);
		virtual HRESULT CreateResource(D3D11_TEXTURE2D_DESC& desc, const void* pData);

	protected:
		std::shared_ptr<SRV_data> m_pSRV;
		ID3D11Texture2D* m_pTex;
	};

	//class DirectX12Texture 
	//	: virtual public iTexture
	//{
	//public:
	//private:
	//};


	//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///
	//																	//
	//							RenderTarget							//
	//																	//
	//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///

	class iRenderTarget 
		: virtual public iTexture
	{
	public:
		iRenderTarget() = default;
		virtual ~iRenderTarget() = default;

		virtual void Clear() = 0;
		virtual void Clear(const Engine::Math::fVec4& color) = 0;

		virtual HRESULT Create(DXGI_FORMAT format, uint16 width, uint16 height) = 0;
		virtual HRESULT CreateFormScreen() = 0;

		virtual convRenderTargetView GetView()const = 0;
	};

	class DirectX11RenderTarget
		: public DirectX11Texture 
		, public iRenderTarget
	{
	public:
		DirectX11RenderTarget();
		~DirectX11RenderTarget();

		void Clear()override;
		void Clear(const Engine::Math::fVec4& color)override;

		HRESULT Create(DXGI_FORMAT format, uint16 width, uint16 height)override;
		HRESULT CreateFormScreen()override;
		inline convRenderTargetView GetView()const override { return { m_pRTV }; }

		inline convShaderResourceView GetResource()const override { return m_pSRV.get()->first; };
		inline HRESULT Create(const char* fileName) { return DirectX11Texture::Create(fileName); }
		inline HRESULT Create(DXGI_FORMAT format, uint16 width, uint16 height, const void* pData = nullptr) { return DirectX11Texture::Create(format, width, height, pData); }

	protected:
		virtual HRESULT CreateResource(D3D11_TEXTURE2D_DESC& desc, const void* pData = nullptr);

	private:
		ID3D11RenderTargetView* m_pRTV;
	};

	//class DirectX12RenderTarget
	//	: public iRenderTarget
	//	, public DirectX12Texture
	//{
	//public:
	//	DirectX12RenderTarget();
	//	~DirectX12RenderTarget();
	//
	//	void Clear()override;
	//	void Clear(const Engine::Math::fVec4& color)override;
	//
	//	HRESULT Create(DXGI_FORMAT format, uint16 width, uint16 height)override;
	//	HRESULT CreateFormScreen()override;
	//
	//private:
	//
	//};



	//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///
	//																	//
	//							DepthStencil							//
	//																	//
	//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///
	class iDepstStencil
		: virtual public iTexture
	{
	public:
		iDepstStencil() = default;
		virtual ~iDepstStencil() = default;

		virtual void Clear() = 0;
		virtual HRESULT Create(uint16 width, uint16 height, bool useStencil) = 0;
		virtual convDepthStencilView GetView()const = 0;
	};

	class DirectX11DepstStencil
		: public DirectX11Texture
		, public iDepstStencil
	{
	public:
		DirectX11DepstStencil();
		~DirectX11DepstStencil();

		void Clear() override;
		HRESULT Create(uint16 width, uint16 height, bool useStencil) override;
		inline convDepthStencilView GetView()const override { return { m_pDSV }; }

		convShaderResourceView GetResource()const override { return m_pSRV.get()->first; };
		inline HRESULT Create(const char* fileName) { return DirectX11Texture::Create(fileName); }
		inline HRESULT Create(DXGI_FORMAT format, uint16 width, uint16 height, const void* pData = nullptr) { return DirectX11Texture::Create(format, width, height, pData); }

	protected:
		virtual HRESULT CreateResource(D3D11_TEXTURE2D_DESC& desc, const void* pData = nullptr);

	private:
		ID3D11DepthStencilView* m_pDSV;
	};


	//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///
	//																	//
	//								factory								//
	//																	//
	//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///

	class iTextureFactory
	{
	public:
		virtual SRV_data* CreateSRV(const std::string& path) = 0;
		virtual iTexture* CreateTexture() = 0;
		virtual iRenderTarget* CreateRenderTarget() = 0;
		virtual iDepstStencil* CreateDepstStencil() = 0;

		virtual ~iTextureFactory() = default;
	};

	class DirectX11TextureFactory 
		: public iTextureFactory
	{
	public:
		SRV_data* CreateSRV(const std::string& path) override;
		iTexture* CreateTexture()override;
		inline iRenderTarget* CreateRenderTarget() override
		{
			return New(DirectX11RenderTarget());
		}
		inline iDepstStencil* CreateDepstStencil() override
		{
			return New(DirectX11DepstStencil());
		}
	};

	//class DirectX12TextureFactory 
	//	: public iTextureFactory
	//{
	//public:
	//	inline iTexture* CreateTexture() override
	//	{
	//		return New(DirectX12Texture());
	//	}
	//	inline iRenderTarget* CreateRenderTarget()
	//	{
	//		return New(DirectX12RenderTarget());
	//	}
	//};



	//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///
	//																	//
	//								Manager								//
	//																	//
	//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///
	class TextureManager final
		: public System::Singleton<TextureManager>
	{
		friend class System::Singleton<TextureManager>;
	public:
		void SetFactory(iTextureFactory* Factory);
		std::shared_ptr<SRV_data> LoadTexture(const std::string& Path);
		std::shared_ptr<iTexture> CreateTexture();
		std::shared_ptr<iTexture> CreateTexture(const std::string& path);
		std::shared_ptr<iRenderTarget> RecordRenderTarget(const std::string& RecordName);
		std::shared_ptr<iDepstStencil> RecordDepstStencil(const std::string& RecordName);

	private:
		TextureManager();
		~TextureManager();

		std::unordered_map<std::string, std::weak_ptr<SRV_data>> m_srv;
		std::unordered_map<std::string, std::weak_ptr<iTexture>> m_Textures;
		std::unordered_map<std::string, std::weak_ptr<iRenderTarget>> m_RenderTargets;
		std::unordered_map<std::string, std::weak_ptr<iDepstStencil>> m_DepstStencils;
		std::shared_ptr<iRenderTarget> m_defaultRTV;
		std::shared_ptr<iDepstStencil> m_defaultDSV;

		iTextureFactory* m_factory;
	};
}

#endif // !_____Texture_HXX_____
