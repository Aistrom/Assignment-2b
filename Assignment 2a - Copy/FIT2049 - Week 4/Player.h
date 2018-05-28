#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "InputController.h"
#include "Enemy.h"
#include "Wall.h"
#include "Bullet.h"
#include "Health.h"
#include "Warp.h"
#include "PhysicsObject.h"

class Player : public PhysicsObject
{
private:
	float m_moveSpeed;
	int m_ID;
	float m_health = 50;
protected:
	InputController * m_input;

	CBoundingBox m_boundingBox;

	float m_turnSpeed;
	float m_heading;
	float m_rotationSpeed;
public:
	Player(Mesh* mesh, Shader* shader, Texture* texture, Vector3 position, InputController* input,int ID);

	virtual void Update(float timestep);

	void OnEnemiesCollisionEnter(Enemy* other);
	void OnEnemiesCollisionStay(Enemy* other);
	void OnEnemiesCollisionExit(Enemy* other);

	void OnHealthCollisionEnter(Health* other);
	void OnHealthCollisionStay(Health* other);
	void OnHealthCollisionExit(Health* other);

	void OnWallCollisionEnter(Wall* other);
	void OnWallCollisionStay(Wall* other);
	void OnWallCollisionExit(Wall* other);

	void OnBulletCollisionEnter(Bullet* other);
	void OnBulletCollisionStay(Bullet* other);
	void OnBulletCollisionExit(Bullet* other);

	void OnWarpCollisionEnter(Warp* other, Vector3 position);
	void OnWarpCollisionStay(Warp* other, Vector3 position);
	void OnWarpCollisionExit(Warp* other, Vector3 position);

	int GetID() { return m_ID; };
	int getplayerhealth() { return m_health; }

	Vector3 stay;

	CBoundingBox GetBounds() { return m_boundingBox; }
};
#endif // !PLAYER_H
