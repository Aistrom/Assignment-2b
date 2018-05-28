#include "Wall.h"
#include "MathsHelper.h"

Wall::Wall(Mesh* mesh, Shader* shader, Texture* texture, Vector3 position,int m_id) :
	GameObject(mesh, shader, texture, position)
{
	if (m_id == 1) {
		m_boundingBox = CBoundingBox(m_position + m_mesh->GetMin(), m_position + m_mesh->GetMax());;
	}
}

void Wall::Update(float timestep)
{

}

void Wall::OnPlayerCollisionEnter()
{

}

void Wall::OnPlayerCollisionStay()
{

}

void Wall::OnPlayerCollisionExit()
{

}

void Wall::OnEnemyCollisionEnter() {

}
void Wall::OnEnemyCollisionStay() {

}
void Wall::OnEnemyCollisionExit() {

}