#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.h"
#include "InputController.h"
#include "Player.h"
#include "Wall.h"
#include "Bullet.h"
#include "Health.h"
#include "PhysicsObject.h"

class Enemy : public PhysicsObject
{
private:
	enum class EnemyTypes
	{
		BRAVE,
		SCARED,
		IGNORANCE,
		SUPRISED,
		RANDOM
	};
protected:
	InputController * m_input;

	float m_moveSpeed;
	float m_turnSpeed;
public:
	Enemy(Mesh* mesh, Shader* shader, Texture* texture, Vector3 position, InputController* input);

	virtual void Update(float timestep);
};
#endif