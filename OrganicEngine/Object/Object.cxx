#include "Object.hxx"

#include "GameObject.hxx"
#include "../Engine/System/SceneManager.hxx"

iObject::iObject()
	: m_pParent(nullptr)
	, m_Children()
	, m_IsActive(true)
{
}

iObject::~iObject()
{
	m_Children.clear();
}

iObject* iObject::GetParent() const
{
	return m_pParent;
}

void iObject::AddChild(iObject* pChild)
{
	m_Children.push_back(pChild);
	pChild->m_pParent = this;
}

bool iObject::IsActive() const
{
	return m_IsActive && (m_pParent ? m_pParent->IsActive() : true);
}

void iObject::SetActive(bool IsActive)
{
	m_IsActive = IsActive;
}

const ID iObject::GetID()
{
	return static_cast<ID>(m_ID);
}

void iObject::UpdateChildren()
{
	if (!m_IsActive)
		return;
	Update();
	for (auto& elem : m_Children)
		elem->UpdateChildren();
}

void iObject::DrawChildren(const Engine::Math::Matrix& world) {
	if (!m_IsActive)
		return;
	// 自分のワールドマトリックスを計算
	Engine::Math::Matrix now = Engine::Math::GetWorldMatrix(world,this->m_Transform);
	Draw(now);
	for (auto& elem : m_Children)
		elem->DrawChildren(now);
}

void iObject::Delete()
{

	while (!m_Children.empty()) {
		m_Children.front()->Delete();
		m_Children.pop_front();
	}
}

/// @brief 切り離し処理。必ず削除や異動と一緒に使うこと
/// @param pChild 
void iObject::RemoveChild(iObject* pChild)
{
	for (int i = 0; i < m_Children.size(); i++) {
		if (m_Children[i] == pChild) {
			m_Children.erase(m_Children.begin() + i);
			break;
		}
	}
}

void iObject::AddInitQueue(iObject* obj)
{
	Engine::System::SceneManager::GetInstance().m_InitQueue.push(obj);
}
