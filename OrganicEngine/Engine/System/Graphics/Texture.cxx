#include "Texture.hxx"

using namespace Engine::Graphic;

void DirectX11Texture::Load(const std::string& Path)
{
}

void DirectX11Texture::Bind()
{
}

void DirectX12Texture::Load(const std::string& Path)
{
}

void DirectX12Texture::Bind()
{
}

void TextureManager::SetFactory(iTextureFactory* Factory)
{
	m_factory = Factory;
}
