#include "Bullet.h"

Bullet::Bullet(Mesh* mesh, Shader* shader, Texture* texture, Vector3 position,int i) :
	GameObject(mesh, shader, texture, position)
{
	switch (i)
	{
	case 1:
		m_type = BulletTypes::BRAVE;
		damage = 3;
		damagerange = 2;
		break;
	case 2:
		m_type = BulletTypes::RANDOM;
		damage = 1;
		damagerange = 4;
		break;
	case 3:
		m_type = BulletTypes::IGNORANCE;
		damage = 2;
		damagerange = 1;
		break;
	case 4:
		m_type = BulletTypes::SUPRISED;
		damage = 2;
		damagerange = 3;
		break;
	case 5:
		m_type = BulletTypes::SCARED;
		damage = 0;
		damagerange = 5;
		break;
	case 6:
		m_type = BulletTypes::PLAYER;
		damage = 2;
		damagerange = 3;
		break;
	default:
		break;
	}
	m_boundingBox = CBoundingBox(m_position + m_mesh->GetMin(), m_position + m_mesh->GetMax());
	
};

void Bullet::Update(float timestep,Vector3 playerposition,Vector3 enemyposition) {
	Vector3 player_position = playerposition - this->GetPosition(); // get the player position
	player_position.Normalize();
	this->SetYRotation(atan2(player_position.x, player_position.z));

	SetPosition(enemyposition + Vector3(1, 1.25f, 1));

	m_boundingBox.SetMin(m_position + m_mesh->GetMin());
	m_boundingBox.SetMax(m_position + m_mesh->GetMax());
};

void Bullet::OnPlayerCollisionEnter() {
	OutputDebugString("Bullet-Player Collision Enter\n");
};
void Bullet::OnPlayerCollisionStay() {
	OutputDebugString("Bullet-Player Collision Stay\n");
};
void Bullet::OnPlayerCollisionExit() {
	OutputDebugString("Bullet-Player Collision Exit\n");
};