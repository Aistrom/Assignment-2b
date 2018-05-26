#ifndef BULLET_H
#define BULLET_H

#include "GameObject.h"
#include "Collisions.h"

class Bullet : public GameObject
{
private:
	CBoundingBox m_boundingBox;

	enum class BulletTypes
	{
		BRAVE,
		SCARED,
		IGNORANCE,
		SUPRISED,
		RANDOM,
		PLAYER
	};
	BulletTypes m_type;
	float damage;
	int damagerange;

public:
	Bullet(Mesh* mesh, Shader* shader, Texture* texture, Vector3 position,int i);

	virtual void Update(float timestep,Vector3 position,Vector3 otherposition);

	void OnPlayerCollisionEnter();
	void OnPlayerCollisionStay();
	void OnPlayerCollisionExit();

	BulletTypes getm_type() { return m_type; }
	BulletTypes taketypes(int i) {
		switch (i)
		{
		case 1:
			return BulletTypes::BRAVE;
			break;
		case 2:
			return BulletTypes::RANDOM;
			break;
		case 3:
			return BulletTypes::IGNORANCE;
			break;
		case 4:
			return BulletTypes::SUPRISED;
			break;
		case 5:
			return  BulletTypes::SCARED;
			break;
		default:
			break;
		}
	}

	float getdamage() { return damage; }
	int getdamagerange() { return damagerange; }

	CBoundingBox GetBounds() { return m_boundingBox; }
};

#endif
