/*	FIT2049 - Example Code
*	Game.cpp
*	Created by Elliott Wilson & Mike Yeates - 2016 - Monash University
*/

#include "Game.h"
#include "TexturedShader.h"
#include "Window.h"
#include "FlyingCamera.h"
#include <iostream>
#include <string>

using namespace std;

Game::Game()
{
	m_renderer = NULL;
	m_currentCam = NULL;
	m_input = NULL;
	m_meshManager = NULL;
	m_textureManager = NULL;
	m_unlitTexturedShader = NULL;
	m_unlitVertexColouredShader = NULL;
	m_playerhealth = NULL;
}

Game::~Game() {}

bool Game::Initialise(Direct3D* renderer, InputController* input)
{
	m_renderer = renderer;	
	m_input = input;
	m_meshManager = new MeshManager();
	m_textureManager = new TextureManager();

	if (!InitShaders())
		return false;

	if (!LoadMeshes())
		return false;

	if (!LoadTextures())
		return false;

	InitGameWorld();

	m_collisionManager = new CollisionManager(&m_players, &m_health, &m_enemies, &m_wall, &m_bullet,&m_warp,&m_Playerbullet);
	m_currentCam = new FlyingCamera(m_input, m_players[0]->GetPosition(), m_players[0]);
	m_currentCam->SetLookAt(Vector3(1, 0, 25));
	return true;
}

bool Game::InitShaders()
{
	m_unlitVertexColouredShader = new Shader();
	if (!m_unlitVertexColouredShader->Initialise(m_renderer->GetDevice(), L"Assets/Shaders/VertexShader.vs", L"Assets/Shaders/VertexColourPixelShader.ps"))
		return false;
	
	m_unlitTexturedShader = new TexturedShader();
	if (!m_unlitTexturedShader->Initialise(m_renderer->GetDevice(), L"Assets/Shaders/VertexShader.vs", L"Assets/Shaders/TexturedPixelShader.ps"))
		return false;

	return true;
}

bool Game::LoadMeshes()
{
	// Don't load a mesh until you've completed its "Create" function in the Mesh class
	// If you get a "Could not create window" error, you're loading an incomplete mesh
	
	if (!m_meshManager->Load(m_renderer, "Assets/Meshes/floor_tile.obj"))
		return false;

	if (!m_meshManager->Load(m_renderer, "Assets/Meshes/wall_tile.obj"))
		return false;

	if (!m_meshManager->Load(m_renderer, "Assets/Meshes/player_capsule.obj"))
		return false;
	
	if (!m_meshManager->Load(m_renderer, "Assets/Meshes/enemy.obj"))
		return false;
	if (!m_meshManager->Load(m_renderer, "Assets/Meshes/bullet.obj"))
		return false;

	return true;
}

bool Game::LoadTextures()
{
	if (!m_textureManager->Load(m_renderer, "Assets/Textures/checkerboard.jpg"))
		return false;
	if (!m_textureManager->Load(m_renderer, "Assets/Textures/green_board.jpg"))
		return false;
	if (!m_textureManager->Load(m_renderer, "Assets/Textures/blue_board.jpg"))
		return false;

	if (!m_textureManager->Load(m_renderer, "Assets/Textures/gradient_red.png"))
		return false;
	if (!m_textureManager->Load(m_renderer, "Assets/Textures/gradient_redDarker.png"))
		return false;
	if (!m_textureManager->Load(m_renderer, "Assets/Textures/gradient_redLighter.png"))
		return false;
	if (!m_textureManager->Load(m_renderer, "Assets/Textures/gradient_redOrange.png"))
		return false;
	if (!m_textureManager->Load(m_renderer, "Assets/Textures/gradient_redPink.png"))
		return false;

	if (!m_textureManager->Load(m_renderer, "Assets/Textures/tile_white.png"))
		return false;


	return true;
}

void Game::InitEnemies(int value)
{
	int i = randomvalue(20, 1);
	int j = randomvalue(48, 1);
	if (value == 1) {
				Enemy* enemy = new Enemy(m_meshManager->GetMesh("Assets/Meshes/enemy.obj"),
					m_unlitTexturedShader, m_textureManager->GetTexture("Assets/Textures/gradient_redPink.png"),
					Vector3(i, 0, j), 1);
				m_enemies.push_back(enemy);
				m_gameObjects.push_back(enemy);
				Bullet* bullet = new Bullet(m_meshManager->GetMesh("Assets/Meshes/bullet.obj"),
					m_unlitTexturedShader, m_textureManager->GetTexture("Assets/Textures/gradient_redPink.png"),
					Vector3(i, 1.25f, j),1);
				m_bullet.push_back(bullet);
				m_gameObjects.push_back(bullet);
			}
	else if (value == 2) {
				Enemy* enemy = new Enemy(m_meshManager->GetMesh("Assets/Meshes/enemy.obj"),
					m_unlitTexturedShader, m_textureManager->GetTexture("Assets/Textures/gradient_redOrange.png"),
					Vector3(i, 0, j), 2);
				m_enemies.push_back(enemy);
				m_gameObjects.push_back(enemy);
				Bullet* bullet = new Bullet(m_meshManager->GetMesh("Assets/Meshes/bullet.obj"),
					m_unlitTexturedShader, m_textureManager->GetTexture("Assets/Textures/gradient_redOrange.png"),
					Vector3(i, 1.25, j),2);
				m_bullet.push_back(bullet);
				m_gameObjects.push_back(bullet);
			}
	else if (value == 3) {
				Enemy* enemy = new Enemy(m_meshManager->GetMesh("Assets/Meshes/enemy.obj"),
					m_unlitTexturedShader, m_textureManager->GetTexture("Assets/Textures/gradient_redLighter.png"),
					Vector3(i, 0, j), 3);
				m_enemies.push_back(enemy);
				m_gameObjects.push_back(enemy);
				Bullet* bullet = new Bullet(m_meshManager->GetMesh("Assets/Meshes/bullet.obj"),
					m_unlitTexturedShader, m_textureManager->GetTexture("Assets/Textures/gradient_redLighter.png"),
					Vector3(i, 1.25, j),3);
				m_bullet.push_back(bullet);
				m_gameObjects.push_back(bullet);
			}
	else if (value == 4) {
				Enemy* enemy = new Enemy(m_meshManager->GetMesh("Assets/Meshes/enemy.obj"),
					m_unlitTexturedShader, m_textureManager->GetTexture("Assets/Textures/gradient_red.png"),
					Vector3(i, 0, j), 4);
				m_enemies.push_back(enemy);
				m_gameObjects.push_back(enemy);
				Bullet* bullet = new Bullet(m_meshManager->GetMesh("Assets/Meshes/bullet.obj"),
					m_unlitTexturedShader, m_textureManager->GetTexture("Assets/Textures/gradient_red.png"),
					Vector3(i, 1.25, j),4);
				m_bullet.push_back(bullet);
				m_gameObjects.push_back(bullet);
			}
	else if (value == 5) {
				Enemy* enemy = new Enemy(m_meshManager->GetMesh("Assets/Meshes/enemy.obj"),
					m_unlitTexturedShader, m_textureManager->GetTexture("Assets/Textures/gradient_redDarker.png"),
					Vector3(i, 0, j), 5);
				m_enemies.push_back(enemy);
				m_gameObjects.push_back(enemy);
				Bullet* bullet = new Bullet(m_meshManager->GetMesh("Assets/Meshes/bullet.obj"),
					m_unlitTexturedShader, m_textureManager->GetTexture("Assets/Textures/gradient_redDarker.png"),
					Vector3(i, 1.25, j),5);
				m_bullet.push_back(bullet);
				m_gameObjects.push_back(bullet);
			}
	else {

	}
}

void Game::InitWall() 
{
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			if ((i == 0 || i == 49) || (j == 0 || j == 49)) {
				Vector3 botposition = Vector3(i, 0, j);
				Wall* botwall = new Wall(m_meshManager->GetMesh("Assets/Meshes/wall_tile.obj"),
					m_unlitTexturedShader,
					m_textureManager->GetTexture("Assets/Textures/checkerboard.jpg"),
					botposition,1);
				m_gameObjects.push_back(botwall);
				m_wall.push_back(botwall);
				Vector3 topposition = Vector3(i, 1, j);
				Wall* topwall = new Wall(m_meshManager->GetMesh("Assets/Meshes/wall_tile.obj"),
					m_unlitTexturedShader,
					m_textureManager->GetTexture("Assets/Textures/checkerboard.jpg"),
					topposition,2);
				m_gameObjects.push_back(topwall);
				m_wall.push_back(topwall);
			}

		}
	}
}

void Game::InitGameWorld()
{
	EnemiesDefeated = 0;
	//Create a maze matrix
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			maze[i][j] = 'E';
		}
	}

	// Random placement of enemies
	for (int i = 0; i < 30; i++) {
		int r = randomvalue(8, 1);
		InitEnemies(r); //initialize enemies position on the map
	}

	InitWall();
	int enemiesstart = m_gameObjects.size();
	EnemiesDefeated = 0;
	m_player = new Player(m_meshManager->GetMesh("Assets/Meshes/player_capsule.obj"),
		m_unlitTexturedShader,
		m_textureManager->GetTexture("Assets/Textures/checkerboard.jpg"),
		Vector3(40, 0, 30),
		m_input,0);
	m_gameObjects.push_back(m_player);
	m_players.push_back(m_player);
	m_gameObjects.back()->SetUniformScale(0.0001f);
	PlayerBullet* Playerbullet = new PlayerBullet(m_meshManager->GetMesh("Assets/Meshes/bullet.obj"),
		m_unlitTexturedShader, m_textureManager->GetTexture("Assets/Textures/gradient_redDarker.png"),
		Vector3(40, 1.25, 30), m_input);
	m_Playerbullet.push_back(Playerbullet);
	m_gameObjects.push_back(Playerbullet);
	m_gameObjects.back()->SetUniformScale(0.0001f);
	
	for (int i = 0; i < 1; i++)
	{
		Warp* FirstWarp = new Warp(m_meshManager->GetMesh("Assets/Meshes/player_capsule.obj"),
			m_unlitTexturedShader,
			m_textureManager->GetTexture("Assets/Textures/blue_board.jpg"),
			Vector3(20, 0, 40));
		m_gameObjects.push_back(FirstWarp);
		m_warp.push_back(FirstWarp);
		Warp* SecondWarp = new Warp(m_meshManager->GetMesh("Assets/Meshes/player_capsule.obj"),
			m_unlitTexturedShader,
			m_textureManager->GetTexture("Assets/Textures/blue_board.jpg"),
			Vector3(40, 0, 20));
		m_gameObjects.push_back(SecondWarp);
		m_warp.push_back(SecondWarp);
	}
	Health* health = new Health(m_meshManager->GetMesh("Assets/Meshes/player_capsule.obj"),
		m_unlitTexturedShader,
		m_textureManager->GetTexture("Assets/Textures/green_board.jpg"),
		Vector3(4, 0, 4));
	m_gameObjects.push_back(health);
	m_health.push_back(health);
	m_gameObjects.back()->SetZRotation(1.5f);
	m_gameObjects.back()->SetUniformScale(0.5f);
	m_gameObjects.back()->SetPosition(m_gameObjects.back()->GetPosition() + Vector3(0, 1.5f, 0));

	m_healthexist.push_back(true);

	// Loop to put the game object based on the maze matrix that are previously created 
	// Also, put its position in the game object array on maze2 matrix similiar to maze for easy access
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			m_gameObjects.push_back(new GameObject(m_meshManager->GetMesh("Assets/Meshes/floor_tile.obj"),
				m_unlitTexturedShader,
				m_input,
				Vector3(i, 0, j),
				m_textureManager->GetTexture("Assets/Textures/tile_white.png"), 1));
		}
	}
}

void Game::Update(float timestep)
{
	if (m_player->getplayerhealth() > 0 & EnemiesDefeated != m_enemies.size()) {
		m_input->BeginUpdate();

		EnemiesDefeated = 0;
		for (unsigned int i = 0; i < m_enemies.size(); i++) {
			if (m_enemies[i] != NULL) {
				int hp = m_enemies[i]->gethealth();
				if (hp >= 0) {
					m_enemies[i]->Update(timestep, m_player->GetPosition());
					m_bullet[i]->Update(timestep, m_player->GetPosition(), m_enemies[i]->GetPosition());
				}
				else {
					delete m_enemies[i];
					m_enemies[i] = NULL;
					delete m_bullet[i];
					m_bullet[i] = NULL;

					m_gameObjects[2 * i] = NULL;
					m_gameObjects[2 * i + 1] = NULL;
				}
			}
			else {
				EnemiesDefeated += 1;
			}
		}

		for (unsigned int i = 0; i < m_gameObjects.size(); i++)
		{
			if (m_gameObjects[i] != NULL) {
				m_gameObjects[i]->Update(timestep);
			}
		}

		for (unsigned int i = 0; i < 2; i++)
		{
			m_warp[i]->Update(timestep, m_player->GetPosition());
		}


		m_collisionManager->CheckCollisions();


		m_currentCam->Update(timestep);
		m_player->Update(timestep);
		m_Playerbullet.back()->Update(timestep, m_player->GetPosition(), m_currentCam->GetLookAt());


		m_input->EndUpdate();
	}
}

int Game::randomvalue(int max, int min) {
	int r;

	const unsigned int range = 1 + max - min;
	const unsigned int buckets = RAND_MAX / range;
	const unsigned int limit = buckets * range;

	/* Create equal size buckets all in a row, then fire randomly towards
	* the buckets until you land in one of them. All buckets are equally
	* likely. If you land off the end of the line of buckets, try again. */
	do
	{
		r = rand();
	} while (r >= limit);

	return min + (r / buckets);
}

void Game::Render()
{
	m_renderer->BeginScene(0.2f, 0.2f, 0.2f, 1.0f);

	for (unsigned int i = 0; i < m_gameObjects.size(); i++)
	{
		if (m_gameObjects[i] != NULL) {
			m_gameObjects[i]->Render(m_renderer, m_currentCam);
		}
	}


	m_renderer->EndScene();
}

void Game::Shutdown()
{
	for (unsigned int i = 0; i < m_gameObjects.size(); i++)
	{
		delete m_gameObjects[i];
	}

	m_gameObjects.empty();

	if (m_currentCam)
	{
		delete m_currentCam;
		m_currentCam = NULL;
	}

	if (m_unlitVertexColouredShader)
	{
		m_unlitVertexColouredShader->Release();
		delete m_unlitVertexColouredShader;
		m_unlitVertexColouredShader = NULL;
	}

	if (m_meshManager)
	{
		m_meshManager->Release();
		delete m_meshManager;
		m_meshManager = NULL;
	}

	if (m_textureManager)
	{
		m_textureManager->Release();
		delete m_textureManager;
		m_textureManager = NULL;
	}

}

