#pragma once
#ifndef BULLETP_H
#define BULLETP_H

#include "GameObject.h"
#include "Collisions.h"
#include "InputController.h"
#include "TimeKeeper.h"

class PlayerBullet : public GameObject
{
private:
	CBoundingBox m_boundingBox;
	float damage;
	int damagerange;
	InputController* m_input;
	float m_moveSpeed = 20.0f;
	bool isMoving;
	bool isStop;
	float traveltime;

public:
	PlayerBullet(Mesh* mesh, Shader* shader, Texture* texture, Vector3 position, InputController* input);

	virtual void Update(float timestep, Vector3 otherposition,Vector3 lookat);

	void OnEnemiesCollisionEnter();
	void OnEnemiesCollisionStay();
	void OnEnemiesCollisionExit();

	float getdamage() { return damage; }
	int getdamagerange() { return damagerange; }

	CBoundingBox GetBounds() { return m_boundingBox; }
};

#endif