#include "testScene.hxx"
#include "../../Engine/System/Graphics/GraphicsAPI.hxx"

testScene::testScene()
{

}

testScene::~testScene()
{

}

bool testScene::Init()
{
	return true;
}

void testScene::Update()
{
}

void testScene::Draw(const Engine::Math::Matrix& world)
{
	Engine::Graphic::iRenderTarget* pRT = Engine::Graphic::TextureManager::GetInstance().RecordRenderTarget("default").get();
	Engine::Graphic::GraphicsFactory::GetInstance()->SetRenderTarget(1, &pRT, 
		Engine::Graphic::TextureManager::GetInstance().RecordDepstStencil("default").get());
}
