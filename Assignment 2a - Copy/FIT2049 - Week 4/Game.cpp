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
	
	m_playerhealth = 10;

	if (!InitShaders())
		return false;

	if (!LoadMeshes())
		return false;

	if (!LoadTextures())
		return false;

	InitGameWorld();

	m_collisionManager = new CollisionManager(&m_players, &m_health, &m_enemies, &m_wall, &m_bullet);
	m_currentCam = new FlyingCamera(m_input, m_players[0]->GetPosition(), m_players[0]);
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

	if (!m_meshManager->Load(m_renderer, "Assets/Meshes/progress_cube.obj"))
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

	if (!m_textureManager->Load(m_renderer, "Assets/Textures/tile_blue.png"))
		return false;

	if (!m_textureManager->Load(m_renderer, "Assets/Textures/tile_green.png"))
		return false;
	if (!m_textureManager->Load(m_renderer, "Assets/Textures/green_board.jpg"))
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
	if (!m_textureManager->Load(m_renderer, "Assets/Textures/tile_blue.png"))
		return false;
	if (!m_textureManager->Load(m_renderer, "Assets/Textures/tile_green.png"))

	if (!m_textureManager->Load(m_renderer, "Assets/Textures/tile_red.png"))
		return false;
	if (!m_textureManager->Load(m_renderer, "Assets/Textures/tile_red2.png"))
		return false;
	if (!m_textureManager->Load(m_renderer, "Assets/Textures/tile_red3.png"))
		return false;
	if (!m_textureManager->Load(m_renderer, "Assets/Textures/tile_red4.png"))
		return false;
	if (!m_textureManager->Load(m_renderer, "Assets/Textures/tile_red5.png"))
		return false;
	if (!m_textureManager->Load(m_renderer, "Assets/Textures/tile_disabled.png"))
		return false;

	if (!m_textureManager->Load(m_renderer, "Assets/Textures/tile_white.png"))
		return false;

	if (!m_textureManager->Load(m_renderer, "Assets/Textures/tile_orange.png"))
		return false;


	return true;
}

void Game::InitEnemies()
{
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			if (maze[i][j] == 'R') {
				Enemy* enemy = new Enemy(m_meshManager->GetMesh("Assets/Meshes/enemy.obj"),
					m_unlitTexturedShader, m_textureManager->GetTexture("Assets/Textures/gradient_redPink.png"),
					Vector3(i, 0, j), 1);
				m_enemies.push_back(enemy);
				m_gameObjects.push_back(enemy);
				Bullet* bullet = new Bullet(m_meshManager->GetMesh("Assets/Meshes/bullet.obj"),
					m_unlitTexturedShader, m_textureManager->GetTexture("Assets/Textures/gradient_redPink.png"),
					Vector3(i, 1.25f, j));
				m_bullet.push_back(bullet);
				m_gameObjects.push_back(bullet);
			}
			else if (maze[i][j] == 'Q') {
				Enemy* enemy = new Enemy(m_meshManager->GetMesh("Assets/Meshes/enemy.obj"),
					m_unlitTexturedShader, m_textureManager->GetTexture("Assets/Textures/gradient_redOrange.png"),
					Vector3(i, 0, j), 2);
				m_enemies.push_back(enemy);
				m_gameObjects.push_back(enemy);
				Bullet* bullet = new Bullet(m_meshManager->GetMesh("Assets/Meshes/bullet.obj"),
					m_unlitTexturedShader, m_textureManager->GetTexture("Assets/Textures/gradient_redOrange.png"),
					Vector3(i, 1.25, j));
				m_bullet.push_back(bullet);
				m_gameObjects.push_back(bullet);
			}
			else if (maze[i][j] == 'A') {
				Enemy* enemy = new Enemy(m_meshManager->GetMesh("Assets/Meshes/enemy.obj"),
					m_unlitTexturedShader, m_textureManager->GetTexture("Assets/Textures/gradient_redLighter.png"),
					Vector3(i, 0, j), 3);
				m_enemies.push_back(enemy);
				m_gameObjects.push_back(enemy);
				Bullet* bullet = new Bullet(m_meshManager->GetMesh("Assets/Meshes/bullet.obj"),
					m_unlitTexturedShader, m_textureManager->GetTexture("Assets/Textures/gradient_redLighter.png"),
					Vector3(i, 1.25, j));
				m_bullet.push_back(bullet);
				m_gameObjects.push_back(bullet);
			}
			else if (maze[i][j] == 'Y') {
				Enemy* enemy = new Enemy(m_meshManager->GetMesh("Assets/Meshes/enemy.obj"),
					m_unlitTexturedShader, m_textureManager->GetTexture("Assets/Textures/gradient_red.png"),
					Vector3(i, 0, j), 4);
				m_enemies.push_back(enemy);
				m_gameObjects.push_back(enemy);
				Bullet* bullet = new Bullet(m_meshManager->GetMesh("Assets/Meshes/bullet.obj"),
					m_unlitTexturedShader, m_textureManager->GetTexture("Assets/Textures/gradient_red.png"),
					Vector3(i, 1.25, j));
				m_bullet.push_back(bullet);
				m_gameObjects.push_back(bullet);
			}
			else if (maze[i][j] == 'Z') {
				Enemy* enemy = new Enemy(m_meshManager->GetMesh("Assets/Meshes/enemy.obj"),
					m_unlitTexturedShader, m_textureManager->GetTexture("Assets/Textures/gradient_redDarker.png"),
					Vector3(i, 0, j), 5);
				m_enemies.push_back(enemy);
				m_gameObjects.push_back(enemy);
				Bullet* bullet = new Bullet(m_meshManager->GetMesh("Assets/Meshes/bullet.obj"),
					m_unlitTexturedShader, m_textureManager->GetTexture("Assets/Textures/gradient_redDarker.png"),
					Vector3(i, 1.25, j));
				m_bullet.push_back(bullet);
				m_gameObjects.push_back(bullet);
			}
		}
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
					botposition);
				m_gameObjects.push_back(botwall);
				m_wall.push_back(botwall);
				Vector3 topposition = Vector3(i, 1, j);
				Wall* topwall = new Wall(m_meshManager->GetMesh("Assets/Meshes/wall_tile.obj"),
					m_unlitTexturedShader,
					m_textureManager->GetTexture("Assets/Textures/checkerboard.jpg"),
					topposition);
				m_gameObjects.push_back(topwall);
				m_wall.push_back(topwall);
			}

		}
	}
}

void Game::InitGameWorld()
{
	InitWall();
	//Create a maze matrix
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			maze[i][j] = 'E';
		}
	}

	// Random placement of enemies, health, and warp tile
	for (int i = 0; i < 8; i++) {
		int number;
		int number2;
		switch (i)
		{
		case 0:
			number = rand() % 2 + 2;
			number2 = rand() % 2 + 2;
			maze[number][number2] = 'R';
			break;
		case 1:
			number = rand() % 2 + 5;
			number2 = rand() % 2 + 5;
			maze[number][number2] = 'Q';
			break;
		case 2:
			number = rand() % 2 + 8;
			number2 = rand() % 2 + 8;
			maze[number][number2] = 'A';
			break;
		case 3:
			number = rand() % 2 + 2;
			number2 = rand() % 2 + 5;
			maze[number][number2] = 'Z';
			break;
		case 4:
			number = rand() % 2 + 2;
			number2 = rand() % 2 + 8;
			maze[number][number2] = 'Y';
			break;
		default:
			break;
		}
	}
	InitEnemies(); //initialize enemies position on the map
	EnemiesDefeated = 0;
	cout << m_gameObjects.size();
	m_player = new Player(m_meshManager->GetMesh("Assets/Meshes/player_capsule.obj"),
		m_unlitTexturedShader,
		m_textureManager->GetTexture("Assets/Textures/checkerboard.jpg"),
		Vector3(40, 0, 30),
		m_input,0);
	m_gameObjects.push_back(m_player);
	m_players.push_back(m_player);
	m_gameObjects.back()->SetUniformScale(0.0001f);
	Health* health = new Health(m_meshManager->GetMesh("Assets/Meshes/player_capsule.obj"),
		m_unlitTexturedShader,
		m_textureManager->GetTexture("Assets/Textures/green_board.jpg"),
		Vector3(4, 0, 4));
	m_gameObjects.push_back(health);
	m_health.push_back(health);
	m_gameObjects.back()->SetZRotation(1.5f);
	m_gameObjects.back()->SetUniformScale(0.5f);
	m_gameObjects.back()->SetPosition(m_gameObjects.back()->GetPosition() + Vector3(0, 1.5f, 0));
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
	m_input->BeginUpdate();

	// control what happened if the player step on a specific tile
	// all tiles that are stepped on by the player regardless of color are disabled and cannot be step on again
	for (unsigned int i = 0; i < m_gameObjects.size(); i++)
	{
		if (m_gameObjects[i] != NULL) {
			m_gameObjects[i]->Update(timestep);
		}
	}

	for (unsigned int i = 0; i < m_enemies.size(); i++) {
		m_enemies[i]->Update(timestep, m_player->GetPosition());
		m_bullet[i]->Update(timestep, m_player->GetPosition(),m_enemies[i]->GetPosition());
	}



	m_collisionManager->CheckCollisions();

	m_player->Update(timestep);

	m_currentCam->Update(timestep);

	m_input->EndUpdate();
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

