#include "CollisionManager.h"

CollisionManager::CollisionManager(std::vector<Player*>* players,std::vector<Health*>* health,std::vector<Enemy*>* enemies,std::vector<Wall*>* walls,std::vector<Bullet*>* bullets, std::vector<Warp*>* warps, std::vector<PlayerBullet*>* playerbullet)
{
	m_players = players;
	m_wall = walls;
	m_enemies = enemies;
	m_health = health;
	m_bullet = bullets;
	m_warp = warps;
	m_playerbullet = playerbullet;

	memset(m_currentCollisions, 0, sizeof(m_currentCollisions));
	memset(m_previousCollisions, 0, sizeof(m_previousCollisions));

	m_nextCurrentCollisionSlot = 0;
};

void CollisionManager::CheckCollisions()
{
	// Check Player to item box collisions
	PlayertoBullet();
	PlayertoEnemies();
	PlayertoHealth();
	PlayertoWall();
	PlayertoWarp();
	EnemiestoPlayerBullet();

	// Move all current collisions into previous
	memcpy(m_previousCollisions, m_currentCollisions, sizeof(m_currentCollisions));

	// Clear out current collisions
	memset(m_currentCollisions, 0, sizeof(m_currentCollisions));

	// Now current collisions is empty, we'll start adding from the start again
	m_nextCurrentCollisionSlot = 0;

}

bool CollisionManager::ArrayContainsCollision(GameObject* arrayToSearch[], GameObject* first, GameObject* second)
{
	// See if these two GameObjects appear one after the other in specified collisions array
	// Stop one before length so we don't overrun as we'll be checking two elements per iteration
	for (int i = 0; i < MAX_ALLOWED_COLLISIONS - 1; i += 2)
	{
		if ((arrayToSearch[i] == first && arrayToSearch[i + 1] == second) ||
			arrayToSearch[i] == second && arrayToSearch[i + 1] == first)
		{
			// Found them!
			return true;
		}
	}

	// These objects were not colliding last frame
	return false;
}

void CollisionManager::AddCollision(GameObject* first, GameObject* second)
{
	// Add the two colliding objects to the current collisions array
	// We keep track of the next free slot so no searching is required
	m_currentCollisions[m_nextCurrentCollisionSlot] = first;
	m_currentCollisions[m_nextCurrentCollisionSlot + 1] = second;

	m_nextCurrentCollisionSlot += 2;
}

void CollisionManager::PlayertoWall()
{
	// We'll check each Player against every item box
	// Note this is not overly efficient, both in readability and runtime performance

	for (unsigned int i = 0; i < m_players->size(); i++)
	{
		for (unsigned int j = 0; j < m_wall->size(); j++)
		{
			// Don't need to store pointer to these objects again but favouring clarity
			// Can't index into these directly as they're a pointer to a vector. We need to dereference them first
			Player* Player = (*m_players)[i];
			Wall* Wall = (*m_wall)[j];

			CBoundingBox PlayerBounds = Player->GetBounds();
			CBoundingBox WallBounds = Wall->GetBounds();

			// Are they colliding this frame?
			bool isColliding = CheckCollision(PlayerBounds, WallBounds);
			// Were they colliding last frame?
			bool wasColliding = ArrayContainsCollision(m_previousCollisions, Player, Wall);

			if (isColliding)
			{
				// Register the collision
				AddCollision(Player, Wall);

				if (wasColliding)
				{
					// We are colliding this frame and we were also colliding last frame - that's a collision stay
					// Tell the item box a Player has collided with it (we could pass it the actual Player too if we like)
					Wall->OnPlayerCollisionStay();
					Player->OnWallCollisionStay(Wall);
				}
				else
				{
					// We are colliding this frame and we weren't last frame - that's a collision enter
					Wall->OnPlayerCollisionEnter();
					Player->OnWallCollisionEnter(Wall);
				}
			}
			else
			{
				if (wasColliding)
				{
					// We aren't colliding this frame but we were last frame - that's a collision exit
					Wall->OnPlayerCollisionExit();
					Player->OnWallCollisionExit(Wall);
				}
			}
		}
	}
}

void CollisionManager::PlayertoEnemies()
{
	// We'll check each Player against every item box
	// Note this is not overly efficient, both in readability and runtime performance

	for (unsigned int i = 0; i < m_players->size(); i++)
	{
		for (unsigned int j = 0; j < m_enemies->size(); j++)
		{
			// Don't need to store pointer to these objects again but favouring clarity
			// Can't index into these directly as they're a pointer to a vector. We need to dereference them first
			Player* Player = (*m_players)[i];
			Enemy* Enemy = (*m_enemies)[j];

			if (Enemy != NULL) {
				CBoundingBox PlayerBounds = Player->GetBounds();
				CBoundingBox EnemyBounds = Enemy->GetBounds();

				// Are they colliding this frame?
				bool isColliding = CheckCollision(PlayerBounds, EnemyBounds);
				// Were they colliding last frame?
				bool wasColliding = ArrayContainsCollision(m_previousCollisions, Player, Enemy);

				if (isColliding)
				{
					// Register the collision
					AddCollision(Player, Enemy);

					if (wasColliding)
					{
						// We are colliding this frame and we were also colliding last frame - that's a collision stay
						// Tell the item box a Player has collided with it (we could pass it the actual Player too if we like)
						Player->OnEnemiesCollisionStay(Enemy);
					}
					else
					{
						// We are colliding this frame and we weren't last frame - that's a collision enter
						Player->OnEnemiesCollisionEnter(Enemy);
					}
				}
				else
				{
					if (wasColliding)
					{
						// We aren't colliding this frame but we were last frame - that's a collision exit
						Player->OnEnemiesCollisionExit(Enemy);
					}
				}
			}
		}
	}
}

void CollisionManager::PlayertoHealth()
{
	// We'll check each Player against every item box
	// Note this is not overly efficient, both in readability and runtime performance

	for (unsigned int i = 0; i < m_players->size(); i++)
	{
		for (unsigned int j = 0; j < m_health->size(); j++)
		{
			// Don't need to store pointer to these objects again but favouring clarity
			// Can't index into these directly as they're a pointer to a vector. We need to dereference them first
			Player* Player = (*m_players)[i];
			Health* Health = (*m_health)[j];

			CBoundingBox PlayerBounds = Player->GetBounds();
			CBoundingBox HealthBounds = Health->GetBounds();

			// Are they colliding this frame?
			bool isColliding = CheckCollision(PlayerBounds, HealthBounds);
			// Were they colliding last frame?
			bool wasColliding = ArrayContainsCollision(m_previousCollisions, Player, Health);

			if (isColliding)
			{
				// Register the collision
				AddCollision(Player, Health);

				if (wasColliding)
				{
					// We are colliding this frame and we were also colliding last frame - that's a collision stay
					// Tell the item box a Player has collided with it (we could pass it the actual Player too if we like)
					Health->OnPlayerCollisionStay();
					Player->OnHealthCollisionStay(Health);
				}
				else
				{
					// We are colliding this frame and we weren't last frame - that's a collision enter
					Health->OnPlayerCollisionEnter();
					Player->OnHealthCollisionEnter(Health);
				}
			}
			else
			{
				if (wasColliding)
				{
					// We aren't colliding this frame but we were last frame - that's a collision exit
					Health->OnPlayerCollisionExit();
					Player->OnHealthCollisionExit(Health);
				}
			}
		}
	}
}

void CollisionManager::PlayertoBullet()
{
	// We'll check each Player against every item box
	// Note this is not overly efficient, both in readability and runtime performance

	for (unsigned int i = 0; i < m_players->size(); i++)
	{
		for (unsigned int j = 0; j < m_bullet->size(); j++)
		{
			// Don't need to store pointer to these objects again but favouring clarity
			// Can't index into these directly as they're a pointer to a vector. We need to dereference them first
			Player* Player = (*m_players)[i];
			Bullet* bullet = (*m_bullet)[j];

			if (bullet != NULL) {
				CBoundingBox PlayerBounds = Player->GetBounds();
				CBoundingBox bulletBounds = bullet->GetBounds();

				// Are they colliding this frame?
				bool isColliding = CheckCollision(PlayerBounds, bulletBounds);
				// Were they colliding last frame?
				bool wasColliding = ArrayContainsCollision(m_previousCollisions, Player, bullet);

				if (isColliding)
				{
					// Register the collision
					AddCollision(Player, bullet);

					if (wasColliding)
					{
						// We are colliding this frame and we were also colliding last frame - that's a collision stay
						// Tell the item box a Player has collided with it (we could pass it the actual Player too if we like)
						bullet->OnPlayerCollisionStay();
						Player->OnBulletCollisionStay(bullet);
					}
					else
					{
						// We are colliding this frame and we weren't last frame - that's a collision enter
						bullet->OnPlayerCollisionEnter();
						Player->OnBulletCollisionEnter(bullet);
					}
				}
				else
				{
					if (wasColliding)
					{
						// We aren't colliding this frame but we were last frame - that's a collision exit
						bullet->OnPlayerCollisionExit();
						Player->OnBulletCollisionExit(bullet);
					}
				}
			}
		}
	}
}

void CollisionManager::PlayertoWarp()
{
	// We'll check each Player against every item box
	// Note this is not overly efficient, both in readability and runtime performance

	for (unsigned int i = 0; i < m_players->size(); i++)
	{
		for (unsigned int j = 0; j < m_warp->size(); j++)
		{
			// Don't need to store pointer to these objects again but favouring clarity
			// Can't index into these directly as they're a pointer to a vector. We need to dereference them first
			Player* Player = (*m_players)[i];
			Warp* Warp = (*m_warp)[j];

			CBoundingBox PlayerBounds = Player->GetBounds();
			CBoundingBox WarpBounds = Warp->GetBounds();

			// Are they colliding this frame?
			bool isColliding = CheckCollision(PlayerBounds, WarpBounds);
			// Were they colliding last frame?
			bool wasColliding = ArrayContainsCollision(m_previousCollisions, Player, Warp);
			if (isColliding)
			{
				// Register the collision
				AddCollision(Player, Warp);

				if (wasColliding)
				{
					// We are colliding this frame and we were also colliding last frame - that's a collision stay
					// Tell the item box a Player has collided with it (we could pass it the actual Player too if we like)
					Warp->OnPlayerCollisionStay();
					Player->OnWarpCollisionStay(Warp,(*m_warp)[1-j]->GetPosition());
				}
				else
				{
					// We are colliding this frame and we weren't last frame - that's a collision enter
					Warp->OnPlayerCollisionEnter();
					Player->OnWarpCollisionEnter(Warp, (*m_warp)[1 - j]->GetPosition());
				}
			}
			else
			{
				if (wasColliding)
				{
					// We aren't colliding this frame but we were last frame - that's a collision exit
					Warp->OnPlayerCollisionExit();
					Player->OnWarpCollisionExit(Warp, (*m_warp)[1 - j]->GetPosition());
				}
			}
		}
	}
}

void CollisionManager::EnemiestoPlayerBullet()
{
	// We'll check each Player against every item box
	// Note this is not overly efficient, both in readability and runtime performance

	for (unsigned int i = 0; i < m_playerbullet->size(); i++)
	{
		for (unsigned int j = 0; j < m_enemies->size(); j++)
		{
			// Don't need to store pointer to these objects again but favouring clarity
			// Can't index into these directly as they're a pointer to a vector. We need to dereference them first
			PlayerBullet* PlayerBullet = (*m_playerbullet)[i];
			Enemy* Enemies = (*m_enemies)[j];

			if (Enemies != NULL) {
				CBoundingBox PlayerBulletBounds = PlayerBullet->GetBounds();
				CBoundingBox EnemiesBounds = Enemies->GetBounds();

				// Are they colliding this frame?
				bool isColliding = CheckCollision(PlayerBulletBounds, EnemiesBounds);
				// Were they colliding last frame?
				bool wasColliding = ArrayContainsCollision(m_previousCollisions, PlayerBullet, Enemies);
				if (isColliding)
				{

					// Register the collision
					AddCollision(PlayerBullet, Enemies);

					if (wasColliding)
					{
						// We are colliding this frame and we were also colliding last frame - that's a collision stay
						// Tell the item box a PlayerBullet has collided with it (we could pass it the actual PlayerBullet too if we like)
						Enemies->OnPlayerBulletCollisionStay();
						PlayerBullet->OnEnemiesCollisionStay();
					}
					else
					{
						// We are colliding this frame and we weren't last frame - that's a collision enter
						Enemies->OnPlayerBulletCollisionEnter(PlayerBullet->getdamage());
						PlayerBullet->OnEnemiesCollisionEnter();
					}
				}
				else
				{
					if (wasColliding)
					{
						// We aren't colliding this frame but we were last frame - that's a collision exit
						Enemies->OnPlayerBulletCollisionExit();
						PlayerBullet->OnEnemiesCollisionExit();
					}
				}
			}
		}
	}
}

void CollisionManager::EnemiestoWall()
{
	// We'll check each Player against every item box
	// Note this is not overly efficient, both in readability and runtime performance

	for (unsigned int i = 0; i < m_enemies->size(); i++)
	{
		for (unsigned int j = 0; j < m_wall->size(); j++)
		{
			// Don't need to store pointer to these objects again but favouring clarity
			// Can't index into these directly as they're a pointer to a vector. We need to dereference them first
			Enemy* Enemy = (*m_enemies)[i];
			Wall* Wall = (*m_wall)[j];

			CBoundingBox EnemyBounds = Enemy->GetBounds();
			CBoundingBox WallBounds = Wall->GetBounds();

			// Are they colliding this frame?
			bool isColliding = CheckCollision(EnemyBounds, WallBounds);
			// Were they colliding last frame?
			bool wasColliding = ArrayContainsCollision(m_previousCollisions, Enemy, Wall);

			if (isColliding)
			{
				// Register the collision
				AddCollision(Enemy, Wall);

				if (wasColliding)
				{
					// We are colliding this frame and we were also colliding last frame - that's a collision stay
					// Tell the item box a Enemy has collided with it (we could pass it the actual Enemy too if we like)
					Wall->OnEnemyCollisionStay();
					Enemy->OnWallCollisionStay(Wall);
				}
				else
				{
					// We are colliding this frame and we weren't last frame - that's a collision enter
					Wall->OnEnemyCollisionEnter();
					Enemy->OnWallCollisionEnter(Wall);
				}
			}
			else
			{
				if (wasColliding)
				{
					// We aren't colliding this frame but we were last frame - that's a collision exit
					Wall->OnEnemyCollisionExit();
					Enemy->OnWallCollisionExit(Wall);
				}
			}
		}
	}
}


