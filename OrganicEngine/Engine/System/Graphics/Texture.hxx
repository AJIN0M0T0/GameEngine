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

namespace Engine {
	namespace Graphic {

		class iTexture
		{
		public:
			virtual ~iTexture() = default;

			virtual void Load(const std::string& Path) = 0;
			virtual void Bind() = 0;
		};

		class DirectX11Texture : public iTexture
		{
		public:
			void Load(const std::string& Path) override;
			void Bind() override;
		private:
		};

		class DirectX12Texture : public iTexture
		{
		public:
			void Load(const std::string& Path) override;
			void Bind() override;
		private:
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

		class DirectX11TextureFactory : public iTextureFactory
		{
		public:
			inline iTexture* Create() override
			{
				return new DirectX11Texture();
			}
		};

		class DirectX12TextureFactory : public iTextureFactory
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

			std::unordered_map<std::string, iTexture*> textures;
			iTextureFactory* factory;
		};
	}
}

#endif // !_____Texture_HXX_____
