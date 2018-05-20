#include "Health.h"
#include "MathsHelper.h"

Health::Health(Mesh* mesh, Shader* shader, Texture* texture, Vector3 position) :
	GameObject(mesh, shader, texture, position)
{
	m_boundingBox = CBoundingBox(m_position + m_mesh->GetMin(), m_position + m_mesh->GetMax());
}

void Health::Update(float timestep)
{
	// At the moment we don't need an item box to do anything

	// If this were a real game, our duties in here might include:
	//	- increase Y rotation so we spin on the spot
	//	- animate our scale so we shrink when dissapearing and grow when respawning
	//	- manage a respawn timer to delay our respawn
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