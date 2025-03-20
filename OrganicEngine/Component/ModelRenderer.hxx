//	ファイル名	：ModelRenderer.hxx
//	  概  要	：
//	作	成	者	：daigo
//	 作成日時	：2025/03/20 3:04:53
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= インクルードガード部 =-=-=
#ifndef _____ModelRenderer_HXX_____
#define _____ModelRenderer_HXX_____

// =-=-= インクルード部 =-=-=
#include "Component.hxx"
#include "../Engine/System/Graphics/Model.hxx"

class ModelRenderer
	: public iComponent
{
public:
	ModelRenderer();
	~ModelRenderer();
	void Execute(const std::string& path);

	bool Init() override;
	void Update() override;

	Engine::Graphic::Model* GetModel() { return m_pModel; }
private:
	std::string m_modelName;
	Engine::Graphic::Model* m_pModel;
	float m_scale;
};

#endif // !_____ModelRenderer_HXX_____
