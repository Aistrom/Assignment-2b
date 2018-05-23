#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.h"
#include "Bullet.h"
#include "Collisions.h"

class Enemy : public GameObject
{
private:
	CBoundingBox m_boundingBox;

	float m_moveSpeed;

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

	EnemyTypes GetTypes() { return m_type; }
	CBoundingBox GetBounds() { return m_boundingBox; }
};
#endif