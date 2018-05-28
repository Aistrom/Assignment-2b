#include "Enemy.h"

Enemy::Enemy(Mesh* mesh, Shader* shader, Texture* texture, Vector3 position,int i) :
	PhysicsObject(mesh,shader,texture,position)
{
	switch (i)
	{
	case 1:
		m_type = EnemyTypes::BRAVE;
		m_moveSpeed = 2.0f;
		m_health = 10;
		break;
	case 2:
		m_type = EnemyTypes::RANDOM;
		m_moveSpeed = 4.0f;
		m_health = 10;
		break;
	case 3:
		m_type = EnemyTypes::IGNORANCE;
		m_moveSpeed = 3.0f;
		m_health = 10;
		break;
	case 4:
		m_type = EnemyTypes::SUPRISED;
		m_moveSpeed = 5.0f;
		m_health = 10;
		break;
	case 5:
		m_type = EnemyTypes::SCARED;
		m_moveSpeed = 7.0f;
		m_health = 10;
		break;
	default:
		break;
	}
	m_boundingBox = CBoundingBox(m_position + m_mesh->GetMin(), m_position + m_mesh->GetMax());
};

void Enemy::Update(float timestep,Vector3 Position) {
	
	if (this->m_type == EnemyTypes::BRAVE) {
		BraveEnemy(Position,timestep);
	}
	else if (this->m_type == EnemyTypes::SCARED) {
		ScaredEnemy(Position, timestep);
	}
	else if (this->m_type == EnemyTypes::SUPRISED) {
		SuprisedEnemy(Position, timestep);
	}
	else if (this->m_type == EnemyTypes::IGNORANCE) {
		IgnoranceEnemy(Position, timestep);
	}
	else if (this->m_type == EnemyTypes::RANDOM) {
		RandomEnemy(Position, timestep);
	}
	m_boundingBox.SetMin(m_position + m_mesh->GetMin());
	m_boundingBox.SetMax(m_position + m_mesh->GetMax());
	
};

void Enemy::OnPlayerBulletCollisionEnter(int damage) {
	m_health -= damage;
	std::cout << m_health;
};
void Enemy::OnPlayerBulletCollisionStay() {

};
void Enemy::OnPlayerBulletCollisionExit() {

};


void Enemy::OnWallCollisionEnter(Wall* other) {
	ApplyForce((m_position - other->GetPosition()) * 0.1f);
}
void Enemy::OnWallCollisionStay(Wall* other) {

}
void Enemy::OnWallCollisionExit(Wall* other) {

}

void Enemy::BraveEnemy(Vector3 position,float timestep) {
	Vector3 player_position = position - this->GetPosition(); // get the player position
	
	player_position.Normalize();
	this->SetYRotation(atan2(player_position.x, player_position.z));

	Matrix heading = Matrix::CreateRotationY(atan2(player_position.x, player_position.z));

	Vector3 localRight = Vector3::TransformNormal(Vector3(1, 0, 0), heading);

	Vector3 localForwardXZ = localRight.Cross(Vector3(0, 1, 0));

	Vector3 currentPos = GetPosition() + Vector3(0.0f, 0.0f, 0.0f);

	currentPos += localForwardXZ * m_moveSpeed * timestep;

	SetPosition(currentPos);
}
void Enemy::SuprisedEnemy(Vector3 position, float timestep) {
	if (this->GetPosition().x - position.x < 5 & this->GetPosition().z - position.z < 5)
	{
		Vector3 player_position = position - this->GetPosition(); // get the player position

		player_position.Normalize();
		this->SetYRotation(atan2(player_position.x, player_position.z));
	}
	else {
		BraveEnemy(position,timestep);
	}
}
void Enemy::ScaredEnemy(Vector3 position, float timestep) {
	if (this->GetPosition().x - position.x < 5 & this->GetPosition().z - position.z < 5)
	{
		if (traveltime - TimeKeeper::GetTimeFromStart() < 4) {
			
			int value = randomvalue(4, 1);

			if (value == 1) {
				BraveEnemy(side1, timestep);
			}
			else if (value == 2) {
				BraveEnemy(side2, timestep);
			}
			else if (value == 3) {
				BraveEnemy(side3, timestep);
			}
			else if (value == 4) {
				BraveEnemy(side4, timestep);
			}
		}
		else {
			Vector3 side1 = Vector3(1, 0, 1);
			Vector3 side2 = Vector3(1, 0, 48);
			Vector3 side3 = Vector3(48, 0, 1);
			Vector3 side4 = Vector3(48, 0, 48);
		}
			
	}
	else {
		float traveltime = TimeKeeper::GetTimeFromStart();
		Vector3 player_position = position - this->GetPosition(); // get the player position

		player_position.Normalize();
		this->SetYRotation(atan2(player_position.x, player_position.z));
	}
}
void Enemy::IgnoranceEnemy(Vector3 position, float timestep) {
	if (this->GetPosition().x - position.x < 5 & this->GetPosition().z - position.z < 5)
	{
		RandomEnemy(position, timestep);
	}
	else {
		Vector3 player_position = position - this->GetPosition(); // get the player position

		player_position.Normalize();
		this->SetYRotation(atan2(player_position.x, player_position.z));
	}
}
void Enemy::RandomEnemy(Vector3 position, float timestep) {


	if (changingtarget) {
		x = randomvalue(48, 1);
		z = randomvalue(48, 1);

		changingtarget = false;
		traveltime = TimeKeeper::GetTimeFromStart();
	}
	else {
		Vector3 player_position = Vector3(x,0.0f,z) - this->GetPosition(); // get the player position

		player_position.Normalize();
		this->SetYRotation(atan2(player_position.x, player_position.z));

		Matrix heading = Matrix::CreateRotationY(atan2(player_position.x, player_position.z));

		Vector3 localRight = Vector3::TransformNormal(Vector3(1, 0, 0), heading);

		Vector3 localForwardXZ = localRight.Cross(Vector3(0, 1, 0));

		Vector3 currentPos = GetPosition() + Vector3(0.0f, 0.0f, 0.0f);

		currentPos += localForwardXZ * m_moveSpeed * timestep;
		SetPosition(currentPos);
		if (TimeKeeper::GetTimeFromStart() - traveltime > 2) {
			changingtarget = true;
		}
	}
}

int Enemy::randomvalue(int max, int min) {
	int r;

	const unsigned int range = 1 + max - min;
	const unsigned int buckets = RAND_MAX / range;
	const unsigned int limit = buckets * range;

	/* Create equal size buckets all in a row, then fire randomly towards
	* the buckets until you land in one of them. All buckets are equally
	* likely. If you land off the end of the line of buckets, try again. */
	do
	{
		r = rand();
	} while (r >= limit);

	return min + (r / buckets);
}