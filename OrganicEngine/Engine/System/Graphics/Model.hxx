//	ファイル名	：Model.hxx
//	  概  要	：
//	作	成	者	：daigo
//	 作成日時	：2025/03/20 0:40:06
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// =-=-= インクルードガード部 =-=-=
#ifndef _____Model_HXX_____
#define _____Model_HXX_____

// =-=-= インクルード部 =-=-=
#include <functional>
#include "Shader.hxx"
#include "Texture.hxx"
#include "MeshBuffer.hxx"

namespace Engine::Math {
	class Transform;
}

namespace Engine::Graphic {
	class Model
	{
	public:
		struct Vertex
		{
			DirectX::XMFLOAT3 pos;
			DirectX::XMFLOAT3 normal;
			DirectX::XMFLOAT2 uv;
		};
		struct Material
		{
			DirectX::XMFLOAT4 diffuse;
			DirectX::XMFLOAT4 ambient;
			DirectX::XMFLOAT4 specular;
			std::shared_ptr<iTexture> texture;
		};
		using Materials = std::vector<Material>;
		struct Mesh
		{
			std::shared_ptr<iMeshBuffer> mesh;
			unsigned int materialID;
		};
		using Meshes = std::vector<Mesh>;

		struct RemakeInfo
		{
			uint32 vtxNum;
			void* dest;
			const void* source;
			uint32 idxNum;
			const void* idx;
		};

	public:
		Model();
		~Model();
		void SetVertexShader(const std::string& Tag);
		void SetPixelShader(const std::string& Tag);
		const Mesh* GetMesh(unsigned int index);
		unsigned int GetMeshNum();
		
		void SetTransform(Engine::Math::Transform* tf);
		Math::fVec4x4 GetWorldMatrix();

	public:
		bool Load(const char* file, float scale = 1.0f, bool flip = false);
		void Draw(int texSlot = 0);

		void RemakeVertex(int vtxSize, std::function<void(RemakeInfo& data)> func);

	private:
		void MakeDefaultShader();

	private:
		static std::shared_ptr<iVertexShader> m_defVS;
		static std::shared_ptr<iPixelShader> m_defPS;
	private:
		Meshes m_meshes;
		Materials m_materials;
		Engine::Math::Transform* m_transform;
		std::shared_ptr<iVertexShader> m_pVS;
		std::shared_ptr<iPixelShader> m_pPS;
	};
}

#endif // !_____Model_HXX_____
