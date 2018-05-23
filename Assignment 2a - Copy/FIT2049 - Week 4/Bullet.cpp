#include "Bullet.h"

Bullet::Bullet(Mesh* mesh, Shader* shader, Texture* texture, Vector3 position) :
	GameObject(mesh, shader, texture, position)
{
	m_boundingBox = CBoundingBox(m_position + m_mesh->GetMin(), m_position + m_mesh->GetMax());
};

void Bullet::Update(float timestep,Vector3 playerposition,Vector3 enemyposition) {
	Vector3 player_position = playerposition - this->GetPosition(); // get the player position
	player_position.Normalize();
	this->SetYRotation(atan2(player_position.x, player_position.z));

	SetPosition(enemyposition);

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