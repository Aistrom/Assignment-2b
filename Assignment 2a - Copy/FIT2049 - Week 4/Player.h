#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "InputController.h"
#include "Enemy.h"
#include "Wall.h"
#include "Bullet.h"
#include "Health.h"
#include "PhysicsObject.h"

class Player : public PhysicsObject
{
protected:
	InputController * m_input;

	float m_moveSpeed;
	float m_turnSpeed;
public:
	Player(Mesh* mesh, Shader* shader, Texture* texture, Vector3 position, InputController* input);

	virtual void Update(float timestep);

	void OnEnemiesCollisionEnter(GameObject* object);
	void OnEnemiesCollisionStay(GameObject* object);
	void OnEnemiesCollisionExit(GameObject* object);

	void OnHealthCollisionEnter(GameObject* object);
	void OnHealthCollisionStay(GameObject* object);
	void OnHealthCollisionExit(GameObject* object);

	void OnWallCollisionEnter(GameObject* object);
	void OnWallCollisionStay(GameObject* object);
	void OnWallCollisionExit(GameObject* object);

	void OnBulletCollisionEnter(GameObject* object);
	void OnBulletCollisionStay(GameObject* object);
	void OnBulletCollisionExit(GameObject* object);
};
#endif // !PLAYER_H
