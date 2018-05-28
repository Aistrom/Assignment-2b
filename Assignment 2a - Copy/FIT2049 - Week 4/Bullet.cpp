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

		frequency = 2;

		break;
	case 2:
		m_type = BulletTypes::RANDOM;
		damage = 1;
		damagerange = 4;

		frequency = 3;
		break;
	case 3:
		m_type = BulletTypes::IGNORANCE;
		damage = 2;
		damagerange = 1;
		frequency = 2;
		break;
	case 4:
		m_type = BulletTypes::SUPRISED;
		damage = 2;
		damagerange = 3;
		frequency = 3;
		break;
	case 5:
		m_type = BulletTypes::SCARED;
		damage = 0;
		damagerange = 5;
		frequency = 5;
		break;
	default:
		break;
	}
	m_boundingBox = CBoundingBox(m_position + Vector3(0,-1,0), m_position + Vector3(1,1,1));
	isflying = false;
	
};

void Bullet::Update(float timestep,Vector3 playerposition,Vector3 enemyposition) {
	if (isflying == false) {
		Vector3 player_position = playerposition - enemyposition; // get the player position
		player_position.Normalize();
		this->SetYRotation(atan2(player_position.x, player_position.z));

		SetPosition(enemyposition + Vector3(0, 1.25f, 0));
		traveltime = TimeKeeper::GetTimeFromStart();
		if (traveltime % frequency < 1.2) {
			isflying = true;
		}
	}
	else
	{
		if (TimeKeeper::GetTimeFromStart() - traveltime > 4) {
			isflying = false;
		}
		Matrix heading = Matrix::CreateRotationY(this->GetYRotation());

		Vector3 localRight = Vector3::TransformNormal(Vector3(1, 0, 0), heading);

		Vector3 localForwardXZ = localRight.Cross(Vector3(0, 1, 0));

		Vector3 currentPos = GetPosition() + Vector3(0.0f, 0.0f, 0.0f);

		currentPos += localForwardXZ * m_moveSpeed * timestep;

		SetPosition(currentPos);
	}
	
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

unsigned int Bullet::getdamage() {
	
	int r;
	const unsigned int range = 1 + damagerange - 0;
	const unsigned int buckets = RAND_MAX / range;
	const unsigned int limit = buckets * range;

	/* Create equal size buckets all in a row, then fire randomly towards
	* the buckets until you land in one of them. All buckets are equally
	* likely. If you land off the end of the line of buckets, try again. */
	do
	{
		r = rand();
	} while (r >= limit);

	return damage + 0 + (r / buckets);

	 
}