//#include "Shader.hxx"
//#include <d3dcompiler.h>
//#include "GraphicsAPI.hxx"
//
//#pragma comment(lib, "d3dcompiler.lib")
//
//using namespace Engine::Graphic;
//
//DirectX11Shader::DirectX11Shader(ShaderType kind)
//	: iShader(kind)
//{
//
//}
//
//HRESULT DirectX11Shader::Load(const std::string& Path)
//{
//	HRESULT hr = E_FAIL;
//
//	// ファイルを読み込む
//	FILE* fp;
//	fopen_s(&fp, Path.c_str(), "rb");
//	if (!fp) { return hr; }
//
//	// ファイルのサイズを調べる
//	int fileSize = 0;
//	fseek(fp, 0, SEEK_END);
//	fileSize = ftell(fp);
//
//	// メモリに読み込み
//	fseek(fp, 0, SEEK_SET);
//	char* pData = new char[fileSize];
//	fread(pData, fileSize, 1, fp);
//	fclose(fp);
//
//	// シェーダー作成
//	hr = Make(pData, fileSize);
//
//	// 終了処理
//	if (pData) { delete[] pData; }
//	return hr;
//}
//HRESULT DirectX11Shader::Compile(const std::string& code)
//{
//	static const char* pTargetList[] =
//	{
//		"vs_5_0",
//		"gs_5_0",
//		"hs_5_0",
//		"ds_5_0",
//		"ps_5_0"
//	};
//
//	HRESULT hr;
//	ID3DBlob* pBlob;
//	ID3DBlob* error;
//	UINT compileFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
//	hr = D3DCompile(code.c_str(), code.length(), nullptr, nullptr, nullptr,
//		"main", pTargetList[(int)m_kind], compileFlag, 0, &pBlob, &error);
//	if (FAILED(hr)) { return hr; }
//
//	// シェーダ作成
//	hr = Make(pBlob->GetBufferPointer(), (UINT)pBlob->GetBufferSize());
//	delete pBlob;
//	pBlob = nullptr;
//	delete error;
//	error = nullptr;
//	return hr;
//}
//void DirectX11Shader::WriteBuffer(uint16 slot, void* pData)
//{
//	if (slot < m_pBuffers.size())
//		static_cast<ID3D11DeviceContext*>(GraphicsFactory::GetInstance()->GetiDevice()->GetDeviceContext())
//			->UpdateSubresource(m_pBuffers[slot], 0, nullptr, pData, 0, 0);
//}
//void DirectX11Shader::SetTexture(uint16 slot, iTexture* pTexture)
//{
//	if (slot >= m_pTexture.size()) { return; }
//	ID3D11ShaderResourceView* pTex = pTexture ? static_cast<ID3D11ShaderResourceView*>(pTexture->GetResource()) : nullptr;
//	m_pTexture[slot] = pTex;
//	ID3D11DeviceContext* pContext = static_cast<ID3D11DeviceContext*>(GraphicsFactory::GetInstance()->GetiDevice()->GetDeviceContext());
//	switch (m_kind)
//	{
//	case Engine::Graphic::iShader::ShaderType::Vertex:
//		pContext->VSSetShaderResources(slot, 1, &pTex); break;
//	case Engine::Graphic::iShader::ShaderType::Hull:
//		pContext->HSSetShaderResources(slot, 1, &pTex); break;
//	case Engine::Graphic::iShader::ShaderType::Domain:
//		pContext->DSSetShaderResources(slot, 1, &pTex); break;
//	case Engine::Graphic::iShader::ShaderType::Pixel:
//		pContext->PSSetShaderResources(slot, 1, &pTex); break;
//	}
//}
//HRESULT DirectX11Shader::Make(void* pData, uint16 size)
//{
//	HRESULT hr;
//	ID3D11Device* pDevice = static_cast<ID3D11Device*>(GraphicsFactory::GetInstance()->GetiDevice()->GetDevice());
//
//	// 解析用のリフレクション作成
//	ID3D11ShaderReflection* pReflection;
//	hr = D3DReflect(pData, size, IID_PPV_ARGS(&pReflection));
//	if (FAILED(hr)) { return hr; }
//
//	// 定数バッファ作成
//	D3D11_SHADER_DESC shaderDesc;
//	pReflection->GetDesc(&shaderDesc);
//	m_pBuffers.resize(shaderDesc.ConstantBuffers, nullptr);
//	for (UINT i = 0; i < shaderDesc.ConstantBuffers; ++i)
//	{
//		// シェーダーの定数バッファの情報を取得
//		D3D11_SHADER_BUFFER_DESC shaderBufDesc;
//		ID3D11ShaderReflectionConstantBuffer* cbuf = pReflection->GetConstantBufferByIndex(i);
//		cbuf->GetDesc(&shaderBufDesc);
//
//		// 作成するバッファの情報
//		D3D11_BUFFER_DESC bufDesc = {};
//		bufDesc.ByteWidth = shaderBufDesc.Size;
//		bufDesc.Usage = D3D11_USAGE_DEFAULT;
//		bufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
//
//		// バッファの作成
//		hr = pDevice->CreateBuffer(&bufDesc, nullptr, &m_pBuffers[i]);
//		if (FAILED(hr)) { return hr; }
//	}
//	// テクスチャ領域作成
//	m_pTexture.resize(shaderDesc.BoundResources, nullptr);
//
//	return MakeShader(pData, size);
//}
