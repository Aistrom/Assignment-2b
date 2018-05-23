#pragma once
#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include <vector>
#include "Collisions.h"
#include "Player.h"
#include "Health.h"
#include "Enemy.h"
#include "Wall.h"
#include "Bullet.h"

#define MAX_ALLOWED_COLLISIONS 2048

class CollisionManager
{
private:
	std::vector<Player*>* m_players;
	std::vector<Health*>* m_health;
	std::vector<Enemy*>* m_enemies;
	std::vector<Wall*>* m_wall;
	std::vector<Bullet*>* m_bullet;


	GameObject* m_currentCollisions[MAX_ALLOWED_COLLISIONS];

	// We need to know what objects were colliding last frame so we can determine if a collision has just begun or ended
	GameObject* m_previousCollisions[MAX_ALLOWED_COLLISIONS];

	int m_nextCurrentCollisionSlot;

	// Check if we already know about two objects colliding
	bool ArrayContainsCollision(GameObject* arrayToSearch[], GameObject* first, GameObject* second);

	// Register that a collision has occurred
	void AddCollision(GameObject* first, GameObject* second);

	// Collision check helpers
	void PlayertoEnemies();
	void PlayertoWall();
	void PlayertoBullet();
	void PlayertoHealth();

public:
	CollisionManager(std::vector<Player*>* m_players,
	std::vector<Health*>* m_health, 
	std::vector<Enemy*>* m_enemies,
	std::vector<Wall*>* m_wall,
	std::vector<Bullet*>* m_bullet);
	void CheckCollisions();

};

#endif