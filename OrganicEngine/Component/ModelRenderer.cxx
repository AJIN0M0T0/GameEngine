#include "ModelRenderer.hxx"
#include "../Object/Object.hxx"

ModelRenderer::ModelRenderer()
	: m_pModel(nullptr)
	, m_scale(1.0f)
{

}

ModelRenderer::~ModelRenderer()
{

}

bool ModelRenderer::Init()
{
	return true;
}

void ModelRenderer::Update()
{
}

void ModelRenderer::Execute(const std::string& path)
{
	if (m_pModel)return;
	m_modelName = path;
	m_pModel = New(Engine::Graphic::Model);
	m_pModel->SetTransform(&m_pObject->GetTransform());
	m_pModel->Load(m_modelName.c_str(), m_scale);
}
