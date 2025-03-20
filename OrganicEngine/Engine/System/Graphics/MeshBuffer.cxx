#include "MeshBuffer.hxx"
#include "GraphicsAPI.hxx"
#include "Shader.hxx"

using namespace Engine::Graphic;

iMeshBuffer::iMeshBuffer(const Description& desc)
	:m_desc{}
{
	
}
iMeshBuffer::~iMeshBuffer()
{
	if (m_desc.pVtx) { delete[] m_desc.pVtx; }
	if (m_desc.pIdx) { delete[] m_desc.pIdx; }
}


DirectX11MeshBuffer::DirectX11MeshBuffer(const Description& desc)
	: iMeshBuffer(desc)
	, m_pIdxBuffer(nullptr)
	, m_pVtxBuffer(nullptr)
{
	HRESULT hr = E_FAIL;
	hr = CreateVertexBuffer(desc.pVtx, desc.vtxSize, desc.vtxCount, desc.isWrite);
	if (desc.pIdx)
	{
		hr = CreateIndexBuffer(desc.pIdx, desc.idxSize, desc.idxCount);
	}
	m_desc = desc;

	rsize_t vtxMemSize = desc.vtxSize * desc.vtxCount;
	void* pVtx = new char[vtxMemSize];
	memcpy_s(pVtx, vtxMemSize, desc.pVtx, vtxMemSize);
	m_desc.pVtx = pVtx;
	rsize_t idxMemSize = desc.idxSize * desc.idxCount;
	void* pIdx = new char[idxMemSize];
	memcpy_s(pIdx, idxMemSize, desc.pIdx, idxMemSize);
	m_desc.pIdx = pIdx;
}
DirectX11MeshBuffer::~DirectX11MeshBuffer()
{
	if (m_pIdxBuffer) { delete m_pIdxBuffer; m_pIdxBuffer = nullptr; }
	if (m_pVtxBuffer) { delete m_pVtxBuffer; m_pVtxBuffer = nullptr; }
}
void DirectX11MeshBuffer::Draw(int count)
{
	ID3D11DeviceContext* pContext = GraphicsManager::GetInstance()->GetDeviceContext().p11DC;
	UINT stride = m_desc.vtxSize;
	UINT offset = 0;

	// トポロジの設定
	ID3D11HullShader* hullShader;
	pContext->HSGetShader(&hullShader, nullptr, nullptr);
	if (hullShader)
		hullShader->Release();
	else
		pContext->IASetPrimitiveTopology(m_desc.topology);

	// 頂点バッファ設定
	pContext->IASetVertexBuffers(0, 1, &m_pVtxBuffer, &stride, &offset);

	// 描画
	if (m_desc.idxCount > 0)
	{
		DXGI_FORMAT format;
		switch (m_desc.idxSize)
		{
		case 4: format = DXGI_FORMAT_R32_UINT; break;
		case 2: format = DXGI_FORMAT_R16_UINT; break;
		}
		pContext->IASetIndexBuffer(m_pIdxBuffer, format, 0);
		pContext->DrawIndexed(count ? count : m_desc.idxCount, 0, 0);
	}
	else
	{
		// 頂点バッファのみで描画
		pContext->Draw(count ? count : m_desc.vtxCount, 0);
	}
}
HRESULT DirectX11MeshBuffer::Write(void* pVtx)
{
	if (!m_desc.isWrite) { return E_FAIL; }

	HRESULT hr;
	GraphicsManager& gr = GraphicsManager::GetInstance();
	ID3D11Device* pDevice = gr->GetDevice().p11D;
	ID3D11DeviceContext* pContext = gr->GetDeviceContext().p11DC;
	D3D11_MAPPED_SUBRESOURCE mapResource;

	// データコピー
	hr = pContext->Map(m_pVtxBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapResource);
	if (SUCCEEDED(hr))
	{
		rsize_t size = m_desc.vtxCount * m_desc.vtxSize;
		memcpy_s(mapResource.pData, size, pVtx, size);
		pContext->Unmap(m_pVtxBuffer, 0);
	}
	return hr;
}
HRESULT DirectX11MeshBuffer::CreateVertexBuffer(const void* pVtx, uint32 size, uint32 count, bool isWrite)
{
	//--- 作成するバッファの情報
	D3D11_BUFFER_DESC bufDesc = {};
	bufDesc.ByteWidth = size * count;
	bufDesc.Usage = D3D11_USAGE_DEFAULT;
	bufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	if (isWrite)
	{
		bufDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}

	//--- バッファの初期値を設定
	D3D11_SUBRESOURCE_DATA subResource = {};
	subResource.pSysMem = pVtx;

	//--- 頂点バッファの作成
	HRESULT hr;
	ID3D11Device* pDevice = GraphicsManager::GetInstance()->GetDevice().p11D;
	hr = pDevice->CreateBuffer(&bufDesc, &subResource, &m_pVtxBuffer);

	return hr;
}
HRESULT DirectX11MeshBuffer::CreateIndexBuffer(const void* pIdx, uint32 size, uint32 count)
{
	// インデックスサイズの確認
	switch (size)
	{
	default:
		return E_FAIL;
	case 2:
	case 4:
		break;
	}

	// バッファの情報を設定
	D3D11_BUFFER_DESC bufDesc = {};
	bufDesc.ByteWidth = size * count;
	bufDesc.Usage = D3D11_USAGE_DEFAULT;
	bufDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	// バッファの初期データ
	D3D11_SUBRESOURCE_DATA subResource = {};
	subResource.pSysMem = pIdx;

	// インデックスバッファ生成
	ID3D11Device* pDevice = GraphicsManager::GetInstance()->GetDevice().p11D;
	HRESULT hr;
	hr = pDevice->CreateBuffer(&bufDesc, &subResource, &m_pIdxBuffer);

	return hr;
}
