#include "Component.hxx"

#include "../Object/Object.hxx"

iObject* iComponent::GetGameObject() {
	return NullptrCheck(m_pObject);
}
