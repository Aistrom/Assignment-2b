#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.h"
#include "Bullet.h"
#include "Collisions.h"
#include "Wall.h"
#include "PhysicsObject.h"
#include "TimeKeeper.h"

class Enemy : public PhysicsObject
{
private:
	CBoundingBox m_boundingBox;

	float m_moveSpeed;
	float m_health;

	bool changingtarget = true;
	int x;
	int z;
	float traveltime;

	Vector3 side1;
	Vector3 side2;
	Vector3 side3;
	Vector3 side4;

	enum class EnemyTypes
	{
		BRAVE,
		SCARED,
		IGNORANCE,
		SUPRISED,
		RANDOM
	};
	EnemyTypes m_type;
public:
	Enemy(Mesh* mesh, Shader* shader, Texture* texture, Vector3 position,int i);

	virtual void Update(float timestep,Vector3 position);

	void OnPlayerBulletCollisionEnter(int damage);
	void OnPlayerBulletCollisionStay();
	void OnPlayerBulletCollisionExit();

	void OnWallCollisionEnter(Wall* other);
	void OnWallCollisionStay(Wall* other);
	void OnWallCollisionExit(Wall* other);


	float gethealth() { return m_health; }
	EnemyTypes GetTypes() { return m_type; }
	CBoundingBox GetBounds() { return m_boundingBox; }

	void BraveEnemy(Vector3 playerposition , float timestep);
	void ScaredEnemy(Vector3 playerposition, float timestep);
	void SuprisedEnemy(Vector3 playerposition , float timestep);
	void RandomEnemy(Vector3 playerposition , float timestep);
	void IgnoranceEnemy(Vector3 playerposition , float timestep);

	int randomvalue(int max, int min);
};
#endif