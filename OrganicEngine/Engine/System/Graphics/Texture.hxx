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
#include <unordered_map>

namespace Engine::Math {
	struct fVec4;
}

enum DXGI_FORMAT;

namespace Engine::Graphic {
	class GraphicsFactory;

	class iTexture
	{
	public:
		virtual ~iTexture() = default;

		virtual void Load(const std::string& Path) = 0;
		virtual void Bind() = 0;
	};

	class DirectX11Texture 
		: public iTexture
	{
	public:
		void Load(const std::string& Path) override final;
		void Bind() override ;
	private:
	};

	class DirectX12Texture 
		: public iTexture
	{
	public:
		void Load(const std::string& Path) override final;
		void Bind() override ;
	private:
	};


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
	};

	class DirectX11RenderTarget
		: public iRenderTarget
		, public DirectX11Texture
	{
	};

	class DirectX12RenderTarget
		: public iRenderTarget
		, public DirectX12Texture
	{
	};



	//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///
	//																	//
	//								factory								//
	//																	//
	//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__///

	class iTextureFactory
	{
	public:
		virtual iTexture* Create() = 0;
		virtual ~iTextureFactory() = default;
	};

	class DirectX11TextureFactory 
		: public iTextureFactory
	{
	public:
		inline iTexture* Create() override
		{
			return new DirectX11Texture();
		}
	};

	class DirectX12TextureFactory 
		: public iTextureFactory
	{
	public:
		inline iTexture* Create() override
		{
			return new DirectX12Texture();
		}
	};


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
		iTexture* LoadTexture(const std::string& Path);

	private:
		~TextureManager();

		std::unordered_map<std::string, iTexture*> m_textures;
		iTextureFactory* m_factory;
	};
}

#endif // !_____Texture_HXX_____
