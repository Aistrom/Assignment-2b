#ifndef BULLET_H
#define BULLET_H

#include "GameObject.h"
#include "PhysicsObject.h"
#include "InputController.h"

class Bullet : public PhysicsObject
{
private:
	//CBoundingBox m_boundingBox;

public:
	Bullet(Mesh* mesh, Shader* shader, Texture* texture, Vector3 position,InputController* input);

	virtual void Update(float timestep);

	//CBoundingBox GetBounds() { return m_boundingBox; }
	void OnPlayerCollisionEnter(GameObject* object);
	void OnPlayerCollisionStay(GameObject* object);
	void OnPlayerCollisionExit(GameObject* object);

};

#endif