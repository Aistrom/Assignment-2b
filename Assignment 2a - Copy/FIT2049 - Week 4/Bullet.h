#ifndef BULLET_H
#define BULLET_H

#include "GameObject.h"
#include "Collisions.h"

class Bullet : public GameObject
{
private:
	CBoundingBox m_boundingBox;

public:
	Bullet(Mesh* mesh, Shader* shader, Texture* texture, Vector3 position);

	virtual void Update(float timestep,Vector3 position,Vector3 otherposition);

	void OnPlayerCollisionEnter();
	void OnPlayerCollisionStay();
	void OnPlayerCollisionExit();

	CBoundingBox GetBounds() { return m_boundingBox; }
};

#endif
