//	ファイル名	：Shader.hxx
//	  概  要	：
//	作	成	者	：daigo
//	 作成日時	：2025/02/28 23:02:10
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= インクルードガード部 =-=-=
#ifndef _____Shader_HXX_____
#define _____Shader_HXX_____

// =-=-= インクルード部 =-=-=

namespace Engine {
	namespace Graphic {

		class iShader
		{
		public:
			virtual ~iShader() = default;

			virtual void Load(const std::string& Path) = 0;
			virtual void Bind() = 0;
		};



	}
}

#endif // !_____Shader_HXX_____
