#include "GameObject.hxx"

GameObject::GameObject()
	: m_Components()
	, m_Name()
	, m_Tag(0)
{

}
GameObject::~GameObject()
{

}

void GameObject::SetName(const Name& name)
{
	m_Name = name;
}

const Name& GameObject::GetName()
{
	return m_Name;
}

Tag GameObject::GetTag()
{
	return m_Tag;
}

void GameObject::SetTag(Tag tag)
{
	m_Tag = tag;
}

bool GameObject::Init() {
	for (auto& elem : m_Components) {
		elem.get()->Init();
	}
	return true;
}
void GameObject::Update() {
	for (auto& elem : m_Components) {
		elem.get()->Update();
	}
}
