//	ファイル名	：testScene.hxx
//	  概  要	：
//	作	成	者	：daigo
//	 作成日時	：2025/03/17 4:34:44
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= インクルードガード部 =-=-=
#ifndef _____testScene_HXX_____
#define _____testScene_HXX_____

// =-=-= インクルード部 =-=-=
#include "../SceneBase.hxx"

class testScene
	: public iScene
{
public:
	testScene();
	~testScene();

	bool Init()override;
	void Update()override;
	void Draw(const Engine::Math::Matrix& world)override;

private:

};

#endif // !_____testScene_HXX_____
