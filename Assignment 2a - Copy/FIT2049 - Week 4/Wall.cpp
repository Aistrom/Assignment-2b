#include "Wall.h"
#include "MathsHelper.h"

Wall::Wall(Mesh* mesh, Shader* shader, Texture* texture, Vector3 position) :
	GameObject(mesh, shader, texture, position)
{
	m_boundingBox = CBoundingBox(m_position + Vector3(0, 0, 0), m_position + Vector3(1,1,1));;
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