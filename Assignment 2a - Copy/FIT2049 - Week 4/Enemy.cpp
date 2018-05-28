#include "Enemy.h"

Enemy::Enemy(Mesh* mesh, Shader* shader, Texture* texture, Vector3 position,int i) :
	GameObject(mesh,shader,texture,position)
{
	switch (i)
	{
	case 1:
		m_type = EnemyTypes::BRAVE;
		m_moveSpeed = 2.0f;
		break;
	case 2:
		m_type = EnemyTypes::RANDOM;
		m_moveSpeed = 3.0f;
		break;
	case 3:
		m_type = EnemyTypes::IGNORANCE;
		m_moveSpeed = 1.0f;
		break;
	case 4:
		m_type = EnemyTypes::SUPRISED;
		m_moveSpeed = 3.0f;
		break;
	case 5:
		m_type = EnemyTypes::SCARED;
		m_moveSpeed = 5.0f;
		break;
	default:
		break;
	}
	m_boundingBox = CBoundingBox(m_position + m_mesh->GetMin(), m_position + m_mesh->GetMax());
};

void Enemy::Update(float timestep,Vector3 Position) {
	Vector3 player_position = Position - this->GetPosition(); // get the player position
	player_position.Normalize();
	this -> SetYRotation(atan2(player_position.x, player_position.z));

	

	Matrix heading = Matrix::CreateRotationY(atan2(player_position.x, player_position.z));

	Vector3 localRight = Vector3::TransformNormal(Vector3(1, 0, 0), heading);

	Vector3 localForwardXZ = localRight.Cross(Vector3(0, 1, 0));

	Vector3 currentPos = GetPosition() + Vector3(0.0f, 0.0f, 0.0f);

	currentPos += localForwardXZ * m_moveSpeed * timestep;

	SetPosition(currentPos);

	m_boundingBox.SetMin(m_position + Vector3(0, 0, 0));
	m_boundingBox.SetMax(m_position + Vector3(1, 1, 1));
};