#ifndef HEALTH_H
#define HEALTH_H

#include "GameObject.h"
#include "Collisions.h"

class Health : public GameObject
{
private:
	CBoundingBox m_boundingBox;
	bool exist;

public:
	Health(Mesh* mesh, Shader* shader, Texture* texture, Vector3 position);

	void Update(float timestep);

	CBoundingBox GetBounds() { return m_boundingBox; }
	void OnPlayerCollisionEnter();
	void OnPlayerCollisionStay();
	void OnPlayerCollisionExit();

	bool GetExistence() { return exist; }
	void SetExistence(bool state) { exist = state; }

};

#endif