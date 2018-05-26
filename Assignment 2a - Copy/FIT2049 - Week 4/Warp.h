#pragma once
#ifndef WARP_H
#define WARP_H

#include "GameObject.h"
#include "Collisions.h"

class Warp : public GameObject
{
private:
	CBoundingBox m_boundingBox;
	float m_pitch;
	int i;
public:
	Warp(Mesh* mesh, Shader* shader, Texture* texture, Vector3 position);

	void Update(float timestep,Vector3 position);

	CBoundingBox GetBounds() { return m_boundingBox; }
	void OnPlayerCollisionEnter();
	void OnPlayerCollisionStay();
	void OnPlayerCollisionExit();

};

#endif