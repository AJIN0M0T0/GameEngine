# OrganicEngine

<t>基本設計 : Unity,SP31,UnrealEngineを参考に組み上げたエンジンです
描画回はSP31を、オブジェクトはUnityを、その他システムはUnrealEngineをベースに組み上げています。\
namespace毎に各機能を紹介していきます。</t>

## 実装関連クラス
ゲームの実装にあたり必要なクラス。ObjectやComponentを実装例と共に。

<details><summary>class iComponent</summary>
各オブジェクトにつけるコンポーネント

```cpp
class iComponent
{
public:
	iComponent() :m_pObject(nullptr) {};
	virtual ~iComponent() = default;

	virtual bool Init() = 0;
	virtual void Update() = 0;

	/// @brief GameObjectを取得する
	/// @brief 注意※SceneComponentの場合エラー
	/// @return 所属ゲームオブジェクト
	iObject* GetGameObject();

protected:
	iObject* m_pObject;
};
```

<details><summary><code>使用例</code></summary>
モデルコンポーネントの使用

```cpp
bool tekitouScene::Init()
{
	GameObject& pObject = thisCreateObject<GameObject>();
    
    // ゲームオブジェクトへコンポーネントを追加
	ModelRenderer* pModelRenderer = pObject.AddComponent<ModelRenderer>();
	pModelRenderer->Execute("Assets/Model/spot/spot.fbx");// コンポーネント内関数参照
	m_pModel = pModelRenderer->GetModel();

    // シェーダーマネージャーのインスタンス取得
	Engine::Graphic::ShaderManager& sm = Engine::Graphic::ShaderManager::GetInstance();

    // シェーダーをタグ毎に作成
	m_pModel->SetVertexShader("defaultVS");
	m_pModel->SetPixelShader("defaultPS");

    // csoファイルの読み込み
	sm.LoadVertexShader("defaultVS")->Load("defaultVertexShader");
	sm.LoadPixelShader("defaultPS")->Load("defaultPixelShader");
```

</details>

<details><summary><code>実装例</code></summary>
カメラコンポーネントの場合のコード

```cpp
class CameraBase
    : public iComponent
{
public:
	CameraBase();
	virtual ~CameraBase();

	bool Init()override;
    void Update();

	DirectX::XMFLOAT4X4 GetViewMatrix();
	DirectX::XMFLOAT4X4 GetProjMatrix();

	//
	DirectX::XMFLOAT3 GetPos()
	{
		Engine::Math::fVec3 pos = m_Transform->GetWorldPosition();
		return {pos.x,pos.y,pos.z};
	}
	//
	DirectX::XMFLOAT3 GetLook()
	{
		return m_look;
	}

	void SetMainCamera();

protected:
	DirectX::XMFLOAT3 m_look, m_up;	//ビュー行列に必要な変数
	float m_fovy, m_aspect,m_near,m_far;	//プロジェクション行列の設定に必要な変数
	Engine::Math::Transform* m_Transform;
};
```

</details>

***

</details>

<details><summary>class iObject</summary>
GameObjectやiSceneの基底クラス

```cpp
class iObject
{
public:
	iObject* GetParent()const;
	void AddChild(iObject* pChild);

	/// 自オブジェクトの子としてオブジェクトを生成
	template <typename TypeObject>
	TypeObject& thisCreateObject();

	/// @brief 初期化処理
	/// @return 成功ならtrue
	virtual bool Init() = 0;
	/// @brief 更新処理
	virtual void Update() = 0;
	/// @brief 描画処理
	/// @param Parentworld 自身のワールド座標
	virtual void Draw(const Engine::Math::Matrix& world) = 0;

	void Delete();
	void RemoveChild(iObject*);

	bool IsActive()const;
	void SetActive(bool IsActive);

	inline Engine::Math::Transform& GetTransform() { return m_Transform; }

	const ID GetID();

protected:
	iObject();
	virtual ~iObject();
	
	void UpdateChildren();
	void DrawChildren(const Engine::Math::Matrix& world);

private:
	void AddInitQueue(iObject* obj);

private:
	bool m_IsActive;
	Engine::unique_ID m_ID;
	iObject* m_pParent;
	std::deque<iObject*> m_Children;
	Engine::Math::Transform m_Transform;
};
```

</details>

<details><summary>class GameObject</summary>
ゲームオブジェクト

```cpp
class GameObject 
	: public iObject
{
public:
	GameObject();
	~GameObject();

	GameObject& operator=(const GameObject&) = delete;
	GameObject& operator=(GameObject&&) = delete;

	/// @brief コンポーネントの追加
	/// @tparam TypeComp 追加するコンポーネントの型
	/// @return 追加したコンポーネントのポインタ
	template<typename TypeComp, typename = std::enable_if_t<std::is_base_of_v<iComponent, TypeComp>>>
	inline TypeComp* AddComponent();

	/// @brief コンポーネントの取得
	/// @tparam TypeComp 取得するコンポーネントの型
	/// @return 取得したコンポーネントのポインタ
	template<typename TypeComp, typename = std::enable_if_t<std::is_base_of_v<iComponent, TypeComp>>>
	inline TypeComp* GetComponent();

	/// @brief 名前の設定
	/// @param name 設定する名前
	void SetName(const Name& name);
	/// @brief 名前の取得
	/// @return 名前
	const Name& GetName();
	/// @brief タグの取得
	/// @return タグ
	Tag GetTag();
	/// @brief タグの設定
	/// @param tag 設定するタグ
	void SetTag(Tag tag);

	virtual bool Init()override;
	virtual void Update()override;
	/// @brief 描画処理
	/// @param Parentworld 自身のワールド座標
	virtual void Draw(const Engine::Math::Matrix& world);

private:
	Name m_Name;// オブジェクト名
	unsigned m_Tag;// タグ
	std::deque<std::unique_ptr<iComponent>> m_Components;// 追加されたコンポーネント
};
```

<details><summary><code>使用例</code></summary>
ゲームオブジェクトの生成

```cpp
bool tekitouScene::Init()
{
    // 特に追加処理なければGameObjectクラスを生成でOK！
	GameObject& pObject = thisCreateObject<GameObject>();
    
    // 追加処理・機能を付けた物ならこう。
    PlayerObject& pPlayer = thisCreateObject<PlayerObject>();
    pPlayer.SetHP(100); // パラメーターの初期化はここ。
    
    // GameObjectのInit()は次ゲームループでUpdate()前に呼ばれます。
```

</details>

<details><summary><code>実装例</code></summary>
プレイヤーオブジェクトの場合のコード

```cpp
class PlayerObject
    :public GameObject
{
public:
    enum PLAYER_MODE;
public:
	PlayerObject();
	virtual ~PlayerObject();

	bool Init()override;
    void Update()override;

	PLAYER_MODE GetMode();

private:
    PLAYER_MODE m_mode;
    uint16 m_hp;
    uint16 m_mp;
    uint16 m_Atk;
    bool isDie;
	Engine::Math::Transform* m_Transform; 
};
```

</details>

***

</details>

<details><summary>class iScene</summary>
各シーンのベース

```cpp
class iScene 
	:public iObject
{
public:
	iScene();
	virtual ~iScene();

	template<typename TypeComp>
	inline TypeComp* AddSceneComponent();

private:
	void Loading(iScene** ppInstantChange);

private:
	bool m_LoadComplete;
	std::unique_ptr<iComponent> m_SceneComponent;
};
```

<details><summary><code>使用例</code></summary>
シーンの切り替え

```cpp
bool Supervision::Initialize()
{
	SceneManager::CreateInstance();
	SceneManager::GetInstance().ChangeScene<TitleScene>();
```

```cpp
bool hogeScene::Update()
{
	if(PlayerLife <= 0 )
	    SceneManager::GetInstance().ChangeScene<ResultScene>();
```

</details>

<details><summary><code>実装例</code></summary>
テストシーンの実装

```cpp
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
	Engine::Graphic::Model* m_pModel;
};
```

cpp側実装

```cpp
bool testScene::Init()
{
    // 各オブジェクト・コンポーネントの生成・初期化処理

	// カメラの生成
	GameObject& pCam = thisCreateObject<GameObject>();
	pCam.AddComponent<CameraDebug>()->SetMainCamera();

	GameObject& pObject = thisCreateObject<GameObject>();
	ModelRenderer* pModelRenderer = pObject.AddComponent<ModelRenderer>();
	pModelRenderer->Execute("Assets/Model/spot/spot.fbx");
	m_pModel = pModelRenderer->GetModel();

	Engine::Graphic::ShaderManager& sm = Engine::Graphic::ShaderManager::GetInstance();

	m_pModel->SetVertexShader("VertexShader");
	m_pModel->SetPixelShader("PixelShader");

	sm.LoadVertexShader("VertexShader")->Load("VertexShader");
	sm.LoadPixelShader("PixelShader")->Load("PixelShader");

    // ↑↑↑　ここら辺コンポーネントに説明アリ

	return true;
}

void testScene::Update()
{
    // カメラはコンポーネント側で制御しているためアップデートの明記は不要！
}

void testScene::Draw(const Engine::Math::Matrix& world)
{
    // ほぼSPのコード

	Engine::Graphic::iRenderTarget* pRT = Engine::Graphic::TextureManager::GetInstance().RecordRenderTarget("default").get();
	Engine::Graphic::GraphicsManager::GetInstance()->SetRenderTarget(1, &pRT, 
		Engine::Graphic::TextureManager::GetInstance().RecordDepstStencil("default").get());

	CameraBase* pCamera = Engine::System::CameraManager::GetInstance().GetMainCamera();
	Engine::Math::fVec4x4 wvp[3];
	wvp[1] = pCamera->GetViewMatrix();
	wvp[2] = pCamera->GetProjMatrix();

	wvp[0] = m_pModel->GetWorldMatrix();

	Engine::Graphic::ShaderManager::GetInstance().LoadVertexShader("VertexShader")->WriteBuffer(0, wvp);

	m_pModel->Draw();
}

```

</details>

***

</details>

## Engine::
エンジンの基本的な機能やゲームループなどの処理を内包します。\
開発時は基本的に参照をしますが、追加・編集は行いません。



<details><summary>class unique_ID</summary>
オブジェクトやその他ユニークなＩＤを使用したい場合に使ってください

```cpp
class unique_ID {
private: 
    static ID m_Counter;
    ID m_ID;
public:	
    unique_ID() { m_ID = ++m_Counter; }
	explicit operator ID() { return m_ID; }
};
```
</details>

## Engine::Math::
基本的な変数型や構造体の定義、数学的な挙動・計算の実装をしています

<details><summary>struct fVec~</summary>
各構造体の定義をしています。各演算子オーバーロード済
<br>fVec2~4, nVec2~4, fVec4x4, Matrixを定義（↓例

```cpp
struct fVec3 {
	static const int _SuffixNum = 3;
	union {
		struct {
			float x, y, z;
		};
		float v[_SuffixNum] = { 0.0f,0.0f,0.0f };
	};
};
bool operator==(const fVec3& Left, const fVec3& Right);
bool operator!=(const fVec3& Left, const fVec3& Right);
bool operator>(const fVec3& Left, const fVec3& Right);
bool operator<(const fVec3& Left, const fVec3& Right);
bool operator>=(const fVec3& Left, const fVec3& Right);
bool operator<=(const fVec3& Left, const fVec3& Right);
fVec3 operator+(const fVec3& Left, const fVec3& Right);
fVec3 operator-(const fVec3& Left, const fVec3& Right);
fVec3 operator*(const fVec3& Left, const fVec3& Right);
fVec3 operator/(const fVec3& Left, const fVec3& Right);
fVec3 operator+(const fVec3& Left, const float Right);
fVec3 operator-(const fVec3& Left, const float Right);
fVec3 operator*(const fVec3& Left, const float Right);
fVec3 operator/(const fVec3& Left, const float Right);
```
</details>

<details><summary>class Transform</summary>
位置・回転・拡縮をローカル座標で保持します。

```cpp
class Transform
{
public:
	Transform();
	~Transform();

	void Update();

	fVec3 GetLocalPosition();
	fVec3 GetLocalRotation();
	fVec3 GetLocalScale();
	fVec3 GetWorldPosition();
	fVec3 GetWorldRotation();
	fVec3 GetWorldScale();

	void  SetLocalPosition(fVec3 Get);
	void  SetLocalRotation(fVec3 Get);
	void  SetLocalScale(fVec3 Get);
	void  SetWorldPosition(fVec3 Get);
	void  SetWorldRotation(fVec3 Get);
	void  SetWorldScale(fVec3 Get);

	void SetParent(Transform* tf);
	void RemoveParent();

	void LookPoint(Transform* point);

	Matrix GetWorldMatrix(void);

private:
	void ChangeParent();

private:
	fVec3 m_Rotation; //ローカル座標の回転
	fVec3 m_Scale; //ローカル座標の拡大縮小
	fVec3 m_Position; //ローカル座標の位置

	bool m_IsLook;
	Transform* m_LookPoint;

	Transform* m_Parent;
};
```
</details>

<details><summary>Easing</summary>
StartからGoalまでイージングさせる関数
<br>イージング参考： https://gizma.com/easing/

```cpp
/// @brief イージングを行う関数
/// @tparam Type イージングさせたい型。 - + * 演算子をオーバーロード済なら構造体も可
/// @param alpha 0~1のイージング基準値を渡す
/// @param Start イージングの開始値
/// @param End イージングの終了値
/// @param EaseType イージングの種類
/// @return イージングされた値
template<typename Type>
Type Easing(float alpha, Type Start, Type End, Ease EaseType)
{
	Type result = End - Start;
    switch (EaseType) //イージングの種類毎に処理
    {...
    }
	return result * alpha + Start;
}
```
</details>

<details><summary>Vec::</summary>
ベクトルの正規化や長さを求める関数

```cpp
/// @brief ベクトルの長さを求める
/// @param Vector 求めるベクトル
/// @return ベクトルの長さ
float length(const fVec3& Vector);

/// @brief ベクトルを正規化する
/// @param Vector 正規化するベクトル
/// @return 正規化されたベクトル
fVec3 Nomalize(fVec3 Vector);
```
</details>

### Meta::

<details><summary>Multiply</summary>
掛け算をするメタ関数

```cpp
// 掛け算のメタ関数
template <float a, float b > 
inline constexpr float Multiply() { return a * b; }
template <uint32 a, uint32 b> 
inline constexpr float Multiply() { return a * b; }
```
</details>

<details><summary>Division</summary>
割り算をするメタ関数

```cpp
// 割り算のメタ関数
template <float a, float b > 
inline constexpr float Division() { return a / b; }
template <uint32 a, uint32 b> 
inline constexpr float Division() { return a / b; }
```
</details>

<details><summary>Factorial</summary>
階乗をするメタ関数

```cpp
// 階乗のメタ関数
template <uint32 N> 
inline constexpr uint32 Factorial() { return N * Factorial<N - 1>(); }
template <> 
inline constexpr uint32 Factorial<0>() { return 1; }

```
</details>

## Engine::System
エンジンの主なベース機能が格納される。

## Engine::Graphics
描画関連のクラス定義・実装
