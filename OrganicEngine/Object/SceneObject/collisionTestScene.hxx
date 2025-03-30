/**
 * @file collisionTestScene.hxx
 * @author yuki57-46
 * @brief 
 * @date 2025/03/30
 */

 // =-=-= インクルードガード部 =-=-=
#ifndef ____COLLISIONTESTSCENE_HXX____
#define ____COLLISIONTESTSCENE_HXX____

// =-=-= インクルード部 =-=-=
#include "../SceneBase.hxx"

namespace Engine::Graphic {
	class Model;
};

class collisionTestScene
	: public iScene
{
public:
	collisionTestScene();
	~collisionTestScene();

	bool Init()override;
	void Update()override;
	void Draw(const Engine::Math::Matrix& world)override;

private:

	GameObject* m_pObject1;
	GameObject* m_pObject2;

	Engine::Graphic::Model* m_pModel1;
	Engine::Graphic::Model* m_pModel2;

};

#endif // !____COLLISIONTESTSCENE_HXX____
