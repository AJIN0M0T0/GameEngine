//	ファイル名	：MeshBuffer.hxx
//	  概  要	：
//	作	成	者	：daigo
//	 作成日時	：2025/03/20 0:42:47
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= インクルードガード部 =-=-=
#ifndef _____MeshBuffer_HXX_____
#define _____MeshBuffer_HXX_____

// =-=-= インクルード部 =-=-=

// =-=-= 前方定義 =-=-=
enum D3D_PRIMITIVE_TOPOLOGY;
struct ID3D11Buffer;

namespace Engine::Graphic {
	struct Description
	{
		const void* pVtx;
		UINT vtxSize;
		UINT vtxCount;
		bool isWrite;
		const void* pIdx;
		UINT idxSize;
		UINT idxCount;
		D3D_PRIMITIVE_TOPOLOGY topology;
	};

	class iMeshBuffer
	{
	public:
		iMeshBuffer(const Description& desc);
		virtual ~iMeshBuffer();

		virtual void Draw(int count = 0) = 0;
		virtual HRESULT Write(void* pVtx) = 0;

		inline Description GetDesc()const { return m_desc; };

	private:
		virtual HRESULT CreateVertexBuffer(const void* pIdx, uint32 size, uint32 count, bool isWrite) = 0;
		virtual HRESULT CreateIndexBuffer(const void* pVtx, uint32 size, uint32 count) = 0;

	protected:
		Description m_desc;
	};

	class DirectX11MeshBuffer
		: public iMeshBuffer
	{
	public:
		DirectX11MeshBuffer(const Description& desc);
		~DirectX11MeshBuffer();

		void Draw(int count = 0) override;
		HRESULT Write(void* pVtx) override;

	private:
		HRESULT CreateVertexBuffer(const void* pIdx, uint32 size, uint32 count, bool isWrite)override;
		HRESULT CreateIndexBuffer(const void* pVtx, uint32 size, uint32 count)override;

	private:
		ID3D11Buffer* m_pVtxBuffer;
		ID3D11Buffer* m_pIdxBuffer;
	};

	inline std::shared_ptr<iMeshBuffer> CreateMeshBuffer(const Description& desc)
	{
#ifdef DIRECTX11_PRJ
		return std::shared_ptr<DirectX11MeshBuffer>(New(DirectX11MeshBuffer)(desc));
#else
		return std::shared_ptr<DirectX12MeshBuffer>(New(DirectX12MeshBuffer)(desc));
#endif // DIRECTX11_PRJ

	}
}

#endif // !_____MeshBuffer_HXX_____
