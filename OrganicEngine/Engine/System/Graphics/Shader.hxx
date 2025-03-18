//	ファイル名	：Shader.hxx
//	  概  要	：
//	作	成	者	：daigo
//	 作成日時	：2025/02/28 23:02:10
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= インクルードガード部 =-=-=
#ifndef _____Shader_HXX_____
#define _____Shader_HXX_____

// =-=-= インクルード部 =-=-=
#include "Texture.hxx"
#include <d3d11.h>

namespace Engine::Graphic {
	class iShader
	{
	protected: 
		enum class ShaderType
		{
			Vertex,
			Geometry,
			Hull,
			Domain,
			Pixel,
			Compute
		};

	protected:
		inline iShader(ShaderType kind) :m_kind(kind) {}

	public:
		virtual ~iShader() = default;

		virtual HRESULT Load(const std::string& Path) = 0;
		virtual HRESULT Compile(const std::string& code) = 0;

		virtual void WriteBuffer(uint16 slot, void* pData) = 0;
		virtual void SetTexture(uint16 slot, iTexture* pTexture) = 0;

		virtual void Bind() = 0;

	protected:
		virtual HRESULT MakeShader(void* pData, uint16 size) = 0;

	protected :
		ShaderType m_kind;
	};

	class DirectX11Shader
		: public iShader
	{
	protected:
		inline DirectX11Shader(ShaderType kind) :iShader(kind) {}

	public:
		virtual ~DirectX11Shader() = default;

		// シェーダーファイル(*.cso)を読み込む処理
		HRESULT Load(const std::string& Path) override;
		// 文字列からシェーダをコンパイル
		HRESULT Compile(const std::string& code) override;

		void WriteBuffer(uint16 slot, void* pData) override;
		void SetTexture(uint16 slot, iTexture* pTexture) override;

	private:
		HRESULT Make(void* pData, uint16 size);

	private:
		std::vector<ID3D11Buffer*> m_pBuffers;
		std::vector<ID3D11ShaderResourceView*> m_pTexture;
	};

	class iVertexShader
		: public iShader
	{
	};

	class iPixelShader
		: public iShader
	{
	};

	class iHullShader
		: public iShader
	{
	};

	class iDomainShader
		: public iShader
	{
	};

	class iGeometryShader
		: public iShader
	{
	};

	class iComputeShader
		: public iShader
	{
	};
}

#endif // !_____Shader_HXX_____
