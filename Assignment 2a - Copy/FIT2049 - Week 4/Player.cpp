#include "Player.h"

Player::Player(Mesh* mesh, Shader* shader, Texture* texture, Vector3 position, InputController* input,int ID) :
	PhysicsObject(mesh, shader, texture, position)
{
	m_input = input;
	m_ID = ID;
	m_moveSpeed = 1.0f;
	m_rotationSpeed = 1.0f;
};

void Player::Update(float timestep) {
		m_heading += m_input->GetMouseDeltaX() * m_rotationSpeed * timestep;
		Matrix heading = Matrix::CreateRotationY(m_heading);
		Vector3 localRight = Vector3::TransformNormal(Vector3(1, 0, 0), heading);

		// Essentially our local forward vector but always parallel with the ground
		// Remember a cross product gives us a vector perpendicular to the two input vectors
		Vector3 localForwardXZ = localRight.Cross(Vector3(0, 1, 0));
		// We're going to need this a lot. Store it locally here to save on our function calls 
		Vector3 currentPos = GetPosition() + Vector3(0.0f, 0.0f, 0.0f);


		if (m_input->GetKeyHold('W'))
		{
			currentPos += localForwardXZ * m_moveSpeed * timestep;
		}
		if (m_input->GetKeyHold('S'))
		{
			currentPos -= localForwardXZ * m_moveSpeed * timestep;
		}
		if (m_input->GetKeyHold('A'))
		{
			currentPos -= localRight * m_moveSpeed * timestep;
		}
		if (m_input->GetKeyHold('D'))
		{
			currentPos += localRight * m_moveSpeed * timestep;
		}
		std::cout << currentPos.x;
		m_position = currentPos;
};

void Player::OnEnemiesCollisionEnter(GameObject* object) {
	OutputDebugString("Player-Enemies Collision Enter\n");
};
void Player::OnEnemiesCollisionStay(GameObject* object){
	OutputDebugString("Player-Enemies Collision Stay\n");
};
void Player::OnEnemiesCollisionExit(GameObject* object) {
	OutputDebugString("Player-Enemies Collision Exit\n");
};

void Player::OnHealthCollisionEnter(GameObject* object) {
	OutputDebugString("Player-Health Collision Enter\n");
};
void Player::OnHealthCollisionStay(GameObject* object) {
	OutputDebugString("Player-Health Collision Stay\n");
};
void Player::OnHealthCollisionExit(GameObject* object) {
	OutputDebugString("Player-Health Collision Exit\n");
};

void Player::OnWallCollisionEnter(GameObject* object) {
	OutputDebugString("Player-Wall Collision Enter\n");
};
void Player::OnWallCollisionStay(GameObject* object) {
	OutputDebugString("Player-Wall Collision Stay\n");
};
void Player::OnWallCollisionExit(GameObject* object) {
	OutputDebugString("Player-Wall Collision Exit\n");
};

void Player::OnBulletCollisionEnter(GameObject* object) {
	OutputDebugString("Player-Bullet Collision Enter\n");
};
void Player::OnBulletCollisionStay(GameObject* object) {
	OutputDebugString("Player-Bullet Collision Stay\n");
};
void Player::OnBulletCollisionExit(GameObject* object) {
	OutputDebugString("Player-Bullet Collision Exit\n");
};
