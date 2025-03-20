//	ファイル名	：Shader.hxx
//	  概  要	：
//	作	成	者	：daigo
//	 作成日時	：2025/02/28 23:02:10
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= インクルードガード部 =-=-=
#ifndef _____Shader_HXX_____
#define _____Shader_HXX_____

// =-=-= インクルード部 =-=-=
#include <d3d11.h>
#include <d3d12.h>
#include "../Singleton.hxx"
#include "Texture.hxx"

union convUnorderedAccessView {
	ID3D11UnorderedAccessView* p11UAV;
};

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
			Compute,
		};

	protected:
		inline iShader(ShaderType kind) :m_kind(kind), m_isComplete(false) {}
		inline iShader() :m_kind(), m_isComplete(false) {};

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
		bool m_isComplete;
		ShaderType m_kind;
	};

	class iUnorderedAccessView
	{
	public:
		virtual ~iUnorderedAccessView() = default;
		virtual HRESULT Create(uint32 stride, uint16 num, void* pData = nullptr) = 0;
		virtual convUnorderedAccessView GetUAV() = 0;

		virtual void copy() = 0;
	};


//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

//					DirectX11基底シェーダーの定義・実装

//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

	class DirectX11Shader
		: virtual public iShader
	{
	protected:
		inline DirectX11Shader() {}

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

	protected:
		std::vector<ID3D11Buffer*> m_pBuffers;
		std::vector<ID3D11ShaderResourceView*> m_pTextures;
	};


//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

//						各シェーダーの定義

//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

	class iVertexShader
		: virtual public iShader
	{
	public:
		iVertexShader() :iShader(ShaderType::Vertex) {}
		virtual void Bind() = 0;
	};

	class iPixelShader
		: virtual public iShader
	{
	public:
		iPixelShader() :iShader(ShaderType::Pixel) {}
		virtual void Bind() = 0;
	};

	class iHullShader
		: virtual public iShader
	{
	public:
		iHullShader() :iShader(ShaderType::Hull) {}
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
	};

	class iDomainShader
		: virtual public iShader
	{
	public:
		iDomainShader() :iShader(ShaderType::Domain) {}
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
	};

	class iGeometryShader
		: virtual public iShader
	{
	public:
		iGeometryShader() :iShader(ShaderType::Geometry) {}
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
	};

	class iComputeShader
		: virtual public iShader
	{
	public:
		iComputeShader() : iShader(ShaderType::Compute) {}
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void Dispatch(uint32 num, iUnorderedAccessView** ppUAV, uint32 thread) = 0;
	};


//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

//					DirectX11の各シェーダーの実装

//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

	class DirectX11VertexShader
		: public DirectX11Shader
		, public iVertexShader
	{
	public:
		DirectX11VertexShader();
		~DirectX11VertexShader();
		void Bind()override;

	protected:
		HRESULT MakeShader(void* pData, uint16 size) override;

	private:
		ID3D11VertexShader* m_pVS;
		ID3D11InputLayout* m_pInputLayout;
	};

	class DirectX11PixelShader
		: public DirectX11Shader
		, public iPixelShader
	{
	public:
		DirectX11PixelShader();
		~DirectX11PixelShader();
		void Bind()override;

	protected:
		HRESULT MakeShader(void* pData, uint16 size) override;

	private:
		ID3D11PixelShader* m_pPS;
	};

	class DirectX11HullShader
		: public DirectX11Shader
		, public iHullShader
	{
	public:
		DirectX11HullShader();
		~DirectX11HullShader();
		void Bind()override;
		void Unbind()override;

	protected:
		HRESULT MakeShader(void* pData, uint16 size) override;

	private:
		ID3D11HullShader* m_pHS;
	};

	class DirectX11DomainShader
		: public DirectX11Shader
		, public iDomainShader
	{
	public:
		DirectX11DomainShader();
		~DirectX11DomainShader();
		void Bind()override;
		void Unbind()override;

	protected:
		HRESULT MakeShader(void* pData, uint16 size) override;

	private:
		ID3D11DomainShader* m_pDS;
	};

	class DirectX11GeometryShader
		: public DirectX11Shader
		, public iGeometryShader
	{
	public:
		DirectX11GeometryShader();
		~DirectX11GeometryShader();
		void Bind()override;
		void Unbind()override;

	protected:
		HRESULT MakeShader(void* pData, uint16 size) override;

	private:
		ID3D11GeometryShader* m_pGS;
	};

	class DirectX11ComputeShader
		: public DirectX11Shader
		, public iComputeShader
	{
	public:
		DirectX11ComputeShader();
		~DirectX11ComputeShader();
		void Bind()override;
		void Unbind()override;
		void Dispatch(uint32 num, iUnorderedAccessView** ppUAV, uint32 thread) override;

	protected:
		HRESULT MakeShader(void* pData, uint16 size) override;

	private:
		ID3D11ComputeShader* m_pCS;
	};


//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

//					DirectX12の各シェーダーの実装

//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

//					シェーダーファクトリークラス

//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

	class iShaderFactory
	{
	public:
		virtual ~iShaderFactory() = default;
		virtual iVertexShader* CreateVertexShader() = 0;
		virtual iPixelShader* CreatePixelShader() = 0;
		virtual iHullShader* CreateHullShader() = 0;
		virtual iDomainShader* CreateDomainShader() = 0;
		virtual iGeometryShader* CreateGeometryShader() = 0;
		virtual iComputeShader* CreateComputeShader() = 0;
	};
	class DirectX11ShaderFactory
		: public iShaderFactory
	{
	public:
		DirectX11ShaderFactory() = default;
		~DirectX11ShaderFactory() = default;
		iVertexShader* CreateVertexShader() override;
		iPixelShader* CreatePixelShader() override;
		iHullShader* CreateHullShader() override;
		iDomainShader* CreateDomainShader() override;
		iGeometryShader* CreateGeometryShader() override;
		iComputeShader* CreateComputeShader() override;
	};
	//class DirectX12ShaderFactory
	//	: public iShaderFactory
	//{
	//public:
	//	DirectX12ShaderFactory();
	//	~DirectX12ShaderFactory();
	//	iVertexShader* CreateVertexShader() override;
	//	iPixelShader* CreatePixelShader() override;
	//	iHullShader* CreateHullShader() override;
	//	iDomainShader* CreateDomainShader() override;
	//	iGeometryShader* CreateGeometryShader() override;
	//	iComputeShader* CreateComputeShader() override;
	//};

	class ShaderManager final
		: public System::Singleton<ShaderManager>
	{
		friend class System::Singleton<ShaderManager>;

	public:
		void SetFactory(iShaderFactory* Factory);

		std::shared_ptr<iVertexShader> LoadVertexShader		(const std::string& Tag);
		std::shared_ptr<iPixelShader> LoadPixelShader		(const std::string& Tag);
		std::shared_ptr<iHullShader> LoadHullShader			(const std::string& Tag);
		std::shared_ptr<iDomainShader> LoadDomainShader		(const std::string& Tag);
		std::shared_ptr<iGeometryShader> LoadGeometryShader	(const std::string& Tag);
		std::shared_ptr<iComputeShader> LoadComputeShader	(const std::string& Tag);

	private:
		ShaderManager();
		~ShaderManager();

	private:
		std::unordered_map<std::string, std::weak_ptr<iShader>> m_shaders;
		iShaderFactory* m_pFactory;
	};
}

#endif // !_____Shader_HXX_____
