#ifndef WALL_H
#define WALL_H

#include "GameObject.h"

class Wall : public GameObject
{
private:
	CBoundingBox m_boundingBox;

public:
	Wall(Mesh* mesh, Shader* shader, Texture* texture, Vector3 position);

	void Update(float timestep);

	//CBoundingBox GetBounds() { return m_boundingBox; }
	void OnPlayerCollisionEnter();
	void OnPlayerCollisionStay();
	void OnPlayerCollisionExit();

};

#endif