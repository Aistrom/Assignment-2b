/*	FIT2049 - Example Code
*	Game.h
*	Created by Elliott Wilson & Mike Yeates - 2016 - Monash University
*	This class is the heart of our game and is also where our game logic will reside
*	It contains the overall Update and Render method for the whole game
*	You should eventually split some game logic into other objects which Game will manage
*	Watch the size of this class - it can grow out of control very fast!
*/

#ifndef GAME_H
#define GAME_H

#include "Direct3D.h"
#include "Camera.h"
#include "InputController.h"
#include "MeshManager.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Health.h"
#include "Bullet.h"
#include "PlayerBullet.h"
#include "Wall.h"
#include "Warp.h"
#include "CollisionManager.h"

#include <vector>

class Game
{
private:
	Camera* m_currentCam;		
	Direct3D* m_renderer;
	InputController* m_input;
	MeshManager* m_meshManager;
	TextureManager* m_textureManager;
	CollisionManager* m_collisionManager;

	Shader* m_unlitVertexColouredShader;
	Shader* m_unlitTexturedShader;

	Player* m_player;

	int w;

	char maze[12][12]; // maze matrix to store the placement of the gameobject on the worldspace 
	int maze2[12][12]; // maze2 matrix to store the placement of the game object in its array based on maze matrix
	int m_playerhealth; // player current health
	int enemiesstart;
	int EnemiesDefeated; // number of enemies defeated


	std::vector<GameObject*> m_gameObjects;
	std::vector<Wall*> m_wall;
	std::vector<Player*> m_players;
	std::vector<Health*> m_health;
	std::vector<Enemy*> m_enemies;
	std::vector<Warp*> m_warp;
	std::vector<Bullet*> m_bullet;
	std::vector<PlayerBullet*> m_Playerbullet;
	std::vector<bool> m_enemyexist;
	std::vector<bool> m_bulletexist;
	std::vector<bool> m_healthexist;


	// Splitting initialisation up into several steps
	void InitWall();
	void InitEnemies(int value);
	bool InitShaders();
	bool LoadMeshes();
	bool LoadTextures();
	void InitGameWorld();

public:
	Game();	
	~Game();

	bool Initialise(Direct3D* renderer, InputController* input); //The initialise method will load all of the content for the game (meshes, textures, etc.)

	void Update(float timestep);	//The overall Update method for the game. All gameplay logic will be done somewhere within this method
	void Render();	//The overall Render method for the game. Here all of the meshes that need to be drawn will be drawn

	int getPlayerhealth() { return m_playerhealth; }
	int randomvalue(int max, int min);
	void Shutdown(); //Cleanup everything we initialised
};
#endif