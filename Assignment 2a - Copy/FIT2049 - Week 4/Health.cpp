#include "Health.h"
#include "MathsHelper.h"

Health::Health(Mesh* mesh, Shader* shader, Texture* texture, Vector3 position) :
	GameObject(mesh, shader, texture, position)
{
	m_boundingBox = CBoundingBox(m_position + m_mesh->GetMin(), m_position + m_mesh->GetMax());
}

void Health::Update(float timestep)
{

}

void Health::OnPlayerCollisionEnter()
{

}

void Health::OnPlayerCollisionStay()
{

}

void Health::OnPlayerCollisionExit()
{

}