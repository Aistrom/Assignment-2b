#include "Warp.h"
#include "MathsHelper.h"

Warp::Warp(Mesh* mesh, Shader* shader, Texture* texture, Vector3 position) :
	GameObject(mesh, shader, texture, position)
{
	SetPosition(m_position + Vector3(0, 0.5f, 0));
	m_boundingBox = CBoundingBox(m_position + Vector3(0, 0, 0), m_position + Vector3(1, 1, 1));
	m_pitch = 1;
}

void Warp::Update(float timestep, Vector3 playerposition) {
	Vector3 player_position = playerposition - this->GetPosition(); // get the player position
	player_position.Normalize();
	this->SetYRotation(atan2(player_position.x, player_position.z));

	m_boundingBox.SetMin(m_position + Vector3(0, 0, 0));
	m_boundingBox.SetMax(m_position + Vector3(1, 1, 1));

	m_pitch += 1;

	m_pitch = MathsHelper::Clamp(m_pitch, ToRadians(-80.0f), ToRadians(80.0f));

	Matrix pitch = Matrix::CreateRotationZ(m_pitch);

	SetZRotation(m_pitch * 10.0f * timestep);
};

void Warp::OnPlayerCollisionEnter() {
	OutputDebugString("Warp-Player Collision Enter\n");
};
void Warp::OnPlayerCollisionStay() {
	OutputDebugString("Warp-Player Collision Stay\n");
};
void Warp::OnPlayerCollisionExit() {
	OutputDebugString("Warp-Player Collision Exit\n");
};