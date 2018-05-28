#include "Player.h"

Player::Player(Mesh* mesh, Shader* shader, Texture* texture, Vector3 position, InputController* input,int ID) :
	PhysicsObject(mesh, shader, texture, position)
{
	m_input = input;
	m_ID = ID;
	m_moveSpeed = 5.0f;
	m_rotationSpeed = 1.0f;

	m_frictionAmount = 0.08f;

	m_boundingBox = CBoundingBox(m_position + Vector3(0, 0, 0), m_position + Vector3(1,1.5,1));
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
		m_position = currentPos;

		m_boundingBox.SetMin(m_position + Vector3(0, 0, 0));
		m_boundingBox.SetMax(m_position + Vector3(1, 1.5, 1));

		PhysicsObject::Update(timestep);
};

void Player::OnEnemiesCollisionEnter(Enemy* other) {
	OutputDebugString("Player-Enemies Collision Enter\n");
	std::cout << "You collided with the enemy, You Lose";
	PostQuitMessage(0);
};
void Player::OnEnemiesCollisionStay(Enemy* other){
	OutputDebugString("Player-Enemies Collision Stay\n");
};
void Player::OnEnemiesCollisionExit(Enemy* other) {

	OutputDebugString("Player-Enemies Collision Exit\n");
};

void Player::OnHealthCollisionEnter(Health* other) {
	OutputDebugString("Player-Health Collision Enter\n");
	m_health += 20;
	std::cout << m_health;
	std::cout << "\n";
};
void Player::OnHealthCollisionStay(Health* other) {
	OutputDebugString("Player-Health Collision Stay\n");
};
void Player::OnHealthCollisionExit(Health* other) {
	OutputDebugString("Player-Health Collision Exit\n");
};

void Player::OnWallCollisionEnter(Wall* other) {
	OutputDebugString("Player-Wall Collision Enter\n");
	ApplyForce((m_position - other->GetPosition()) * 0.1f) ;
};
void Player::OnWallCollisionStay(Wall* other) {
	OutputDebugString("Player-Wall Collision Stay\n");


};
void Player::OnWallCollisionExit(Wall* other) {
	OutputDebugString("Player-Wall Collision Exit\n");
};

void Player::OnBulletCollisionEnter(Bullet* other) {
	m_health -= other->getdamage();
	std::cout << m_health;
	std::cout << "\n";
	OutputDebugString("Player-Bullet Collision Enter\n");
};
void Player::OnBulletCollisionStay(Bullet* other) {
	OutputDebugString("Player-Bullet Collision Stay\n");
};
void Player::OnBulletCollisionExit(Bullet* other) {
	OutputDebugString("Player-Bullet Collision Exit\n");
};


void Player::OnWarpCollisionEnter(Warp* other, Vector3 position) {
	OutputDebugString("Player-Warp Collision Enter\n");
	SetPosition(position + Vector3(-1, 0, 0));
};
void Player::OnWarpCollisionStay(Warp* other, Vector3 position) {
	OutputDebugString("Player-Warp Collision Stay\n");
};
void Player::OnWarpCollisionExit(Warp* other, Vector3 position) {
	OutputDebugString("Player-Warp Collision Exit\n");
};
