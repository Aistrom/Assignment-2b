/*	FIT2049 - Example Code
*	Game.cpp
*	Created by Elliott Wilson & Mike Yeates - 2016 - Monash University
*/

#include "Game.h"
#include "TexturedShader.h"
#include "Window.h"
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
	m_currentCam = new Camera(input);
	m_playerhealth = 10;

	if (!InitShaders())
		return false;

	if (!LoadMeshes())
		return false;

	if (!LoadTextures())
		return false;


	InitGameWorld();

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

void Game::InitGameWorld()
{
	//Create a maze matrix
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			if ((i == 0 || i == 11) || (j == 0 || j == 11)) {
				maze[i][j] = 'W';
			}
			else
			{
				int number = rand() % 3;
				switch (number)
				{
				case 0:
					maze[i][j] = 'W';
					break;
				default:
					maze[i][j] = 'E';
					break;
				}
			}
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
		case 5:
			number = rand() % 2 + 5;
			number2 = rand() % 2 + 2;
			maze[number][number2] = 'G';
			break;
		case 6:
			number = rand() % 2 + 5;
			number2 = rand() % 2 + 8;
			maze[number][number2] = 'B';
			warpA[0][0] = number;
			warpA[0][1] = number2;
			break;
		case 7:
			number = rand() % 2 + 8;
			number2 = rand() % 2 + 2;
			maze[number][number2] = 'B';
			warpB[0][0] = number;
			warpB[0][1] = number2;
			break;
		default:
			break;
		}
		maze[number + 1][number2] = 'E';
		maze[number - 1][number2] = 'E';
		maze[number][number2 + 1] = 'E';
		maze[number][number2 - 1] = 'E';
	}

	// the player
	maze[2][1] = 'E';
	maze[1][2] = 'E';
	maze[1][1] = 'P';

	int k = 0;
	EnemiesDefeated = 0;

	// Loop to put the game object based on the maze matrix that are previously created 
	// Also, put its position in the game object array on maze2 matrix similiar to maze for easy access
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			if (maze[i][j] == 'E') {
				m_gameObjects.push_back(new GameObject(m_meshManager->GetMesh("Assets/Meshes/floor_tile.obj"),
					m_unlitTexturedShader,
					m_input,
					Vector3(i, 0.0f, j),
					m_textureManager->GetTexture("Assets/Textures/tile_white.png"), 1));
				maze2[i][j] = k;
				k += 1;
			}
			else if (maze[i][j] == 'P') {
				m_gameObjects.push_back(new GameObject(m_meshManager->GetMesh("Assets/Meshes/player_capsule.obj"),
					m_unlitTexturedShader,
					m_input,
					Vector3(1.0f, 0.0f, 1.0f),
					m_textureManager->GetTexture("Assets/Textures/checkerboard.jpg"), 0));
				maze2[i][j] = k;
				playerid = k;
				k += 1;
				m_gameObjects.push_back(new GameObject(m_meshManager->GetMesh("Assets/Meshes/floor_tile.obj"),
					m_unlitTexturedShader,
					m_input,
					Vector3(i, 0.0f, j),
					m_textureManager->GetTexture("Assets/Textures/tile_white.png"), 1));
				maze2[i][j] = k;
				k += 1;
			}
			else if (maze[i][j] == 'B') {
				m_gameObjects.push_back(new GameObject(m_meshManager->GetMesh("Assets/Meshes/floor_tile.obj"),
					m_unlitTexturedShader,
					m_input,
					Vector3(i, 0.0f, j),
					m_textureManager->GetTexture("Assets/Textures/tile_blue.png"),1));
				maze2[i][j] = k;
				k += 1;
			}
			else if (maze[i][j] == 'G') {
				m_gameObjects.push_back(new GameObject(m_meshManager->GetMesh("Assets/Meshes/player_capsule.obj"),
					m_unlitTexturedShader,
					m_input,
					Vector3(i, 0.0f, j),
					m_textureManager->GetTexture("Assets/Textures/green_board.jpg"), 1));
				maze3[i][j] = k;
				k += 1;
				m_gameObjects[maze3[i][j]]->SetUniformScale(0.5f);
				m_gameObjects[maze3[i][j]]->SetPosition(Vector3(i, 1.0f, j));
				m_gameObjects[maze3[i][j]]->SetXRotation(1.5);
				m_gameObjects.push_back(new GameObject(m_meshManager->GetMesh("Assets/Meshes/floor_tile.obj"),
					m_unlitTexturedShader,
					m_input,
					Vector3(i, 0.0f, j),
					m_textureManager->GetTexture("Assets/Textures/tile_green.png"), 1));
				maze2[i][j] = k;
				k += 1;
			}
			else if (maze[i][j] == 'R') {
				m_gameObjects.push_back(new GameObject(m_meshManager->GetMesh("Assets/Meshes/enemy.obj"),
					m_unlitTexturedShader,
					m_input,
					Vector3(i, 0.0f, j),
					m_textureManager->GetTexture("Assets/Textures/gradient_redPink.png"), 2));
				maze3[i][j] = k;
				k += 1;
				m_gameObjects.push_back(new GameObject(m_meshManager->GetMesh("Assets/Meshes/floor_tile.obj"),
					m_unlitTexturedShader,
					m_input,
					Vector3(i, 0.0f, j),
					m_textureManager->GetTexture("Assets/Textures/tile_red.png"), 1));
				maze2[i][j] = k;
				k += 1;
			}
			else if (maze[i][j] == 'Q') {
				m_gameObjects.push_back(new GameObject(m_meshManager->GetMesh("Assets/Meshes/enemy.obj"),
					m_unlitTexturedShader,
					m_input,
					Vector3(i, 0.0f, j), m_textureManager->GetTexture("Assets/Textures/gradient_redOrange.png"), 2));
				maze3[i][j] = k;
				k += 1;
				m_gameObjects.push_back(new GameObject(m_meshManager->GetMesh("Assets/Meshes/floor_tile.obj"),
					m_unlitTexturedShader,
					m_input,
					Vector3(i, 0.0f, j),
					m_textureManager->GetTexture("Assets/Textures/tile_red2.png"), 1));
				maze2[i][j] = k;
				k += 1;
			}
			else if (maze[i][j] == 'A') {
				m_gameObjects.push_back(new GameObject(m_meshManager->GetMesh("Assets/Meshes/enemy.obj"),
					m_unlitTexturedShader,
					m_input,
					Vector3(i, 0.0f, j), m_textureManager->GetTexture("Assets/Textures/gradient_redLighter.png"), 2));
				maze3[i][j] = k;
				k += 1;
				m_gameObjects.push_back(new GameObject(m_meshManager->GetMesh("Assets/Meshes/floor_tile.obj"),
					m_unlitTexturedShader,
					m_input,
					Vector3(i, 0.0f, j),
					m_textureManager->GetTexture("Assets/Textures/tile_red3.png"), 1));
				maze2[i][j] = k;
				k += 1;
			}
			else if (maze[i][j] == 'Y') {
				m_gameObjects.push_back(new GameObject(m_meshManager->GetMesh("Assets/Meshes/enemy.obj"),
					m_unlitTexturedShader,
					m_input,
					Vector3(i, 0.0f, j), m_textureManager->GetTexture("Assets/Textures/gradient_red.png"), 2));
				maze3[i][j] = k;
				k += 1;
				m_gameObjects.push_back(new GameObject(m_meshManager->GetMesh("Assets/Meshes/floor_tile.obj"),
					m_unlitTexturedShader,
					m_input,
					Vector3(i, 0.0f, j),
					m_textureManager->GetTexture("Assets/Textures/tile_red4.png"), 1));
				maze2[i][j] = k;
				k += 1;
			}
			else if (maze[i][j] == 'Z') {
				m_gameObjects.push_back(new GameObject(m_meshManager->GetMesh("Assets/Meshes/enemy.obj"),
					m_unlitTexturedShader,
					m_input,
					Vector3(i, 0.0f, j), m_textureManager->GetTexture("Assets/Textures/gradient_redDarker.png"), 2));
				maze3[i][j] = k;
				k += 1;
				m_gameObjects.push_back(new GameObject(m_meshManager->GetMesh("Assets/Meshes/floor_tile.obj"),
					m_unlitTexturedShader,
					m_input,
					Vector3(i, 0.0f, j),
					m_textureManager->GetTexture("Assets/Textures/tile_red5.png"), 1));
				maze2[i][j] = k;
				k += 1;
			}
			else if (maze[i][j] == 'W') {
				m_gameObjects.push_back(new GameObject(m_meshManager->GetMesh("Assets/Meshes/floor_tile.obj"),
					m_unlitTexturedShader,
					m_input,
					Vector3(i, 0.0f, j),
					m_textureManager->GetTexture("Assets/Textures/tile_white.png"), 1));
				maze2[i][j] = k;
				k += 1;
				m_gameObjects.push_back(new GameObject(m_meshManager->GetMesh("Assets/Meshes/wall_tile.obj"),
				m_unlitTexturedShader,
				m_input,
				Vector3(i, 0.0f, j),
				m_textureManager->GetTexture("Assets/Textures/checkerboard.jpg"),1));
				maze2[i][j] = k;
				k += 1;
			}
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
			Vector3 initial = m_gameObjects[i]->GetPosition(); 

			m_gameObjects[i]->Update(timestep);
			if (m_gameObjects[i]->GetID() == 0) {
					Vector3 after = m_gameObjects[i]->GetPosition();
					int x = after.x;
					int z = after.z;

					m_currentCam->SetPosition(after + Vector3(0.0f, 1.5f, 0.0f));
					//Whenever the player move the mouse to the center turn the camera back to the center
					m_currentCam->SetLookAt(after + Vector3(0.0f, 1.5f, 1.0f));

					// If statement which tracks the mouse position and turn the camera accordingly
					if (m_input->GetMouseX() < 380) {
						m_currentCam->SetLookAt(m_gameObjects[i]->GetPosition() + Vector3(-1.0f, 1.5f, 0.0f));
					}
					else if (m_input->GetMouseX() > 380 && m_input->GetMouseX() < 530) {
						m_currentCam->SetLookAt(m_gameObjects[i]->GetPosition() + Vector3(-1.0f, 1.5f, 1.0f));
					}
					else if (m_input->GetMouseX() > 630 && m_input->GetMouseX() < 880) {
						m_currentCam->SetLookAt(m_gameObjects[i]->GetPosition() + Vector3(1.0f, 1.5f, 1.0f));
					}
					else if (m_input->GetMouseX() > 880) {
						m_currentCam->SetLookAt(m_gameObjects[i]->GetPosition() + Vector3(1.0f, 1.5f, 0.0f));
					}
					else if (m_input->GetMouseY() < 290) {
						m_currentCam->SetLookAt(m_gameObjects[i]->GetPosition() + Vector3(0.0f, 1.8f, 1.0f));
					}
					else if (m_input->GetMouseY() > 390) {
						m_currentCam->SetLookAt(m_gameObjects[i]->GetPosition() + Vector3(0.0f, 1.0f, 1.0f));
					}

					if (maze[x][z] == 'W')
					{
						m_gameObjects[i]->SetPosition(initial);
					}
					else if (maze[x][z] == 'D')
					{
						m_gameObjects[i]->SetPosition(initial);
					}
					else if (maze[x][z] == 'B')
					{
						if (after == Vector3(warpA[0][0], 0, warpA[0][1])) {
							m_gameObjects[i]->SetPosition(Vector3(warpB[0][0], 0, warpB[0][1]));
						}
						else {
							m_gameObjects[i]->SetPosition(Vector3(warpA[0][0], 0, warpA[0][1]));
						}
						m_gameObjects[maze2[warpA[0][0]][warpA[0][1]]]->SetTexture(m_textureManager->GetTexture("Assets/Textures/tile_disabled.png"));
						m_gameObjects[maze2[warpB[0][0]][warpB[0][1]]]->SetTexture(m_textureManager->GetTexture("Assets/Textures/tile_disabled.png"));
						maze[warpA[0][0]][warpA[0][1]] = 'D';
						maze[warpB[0][0]][warpB[0][1]] = 'D';
						cout << "You step on a Warp tile\n";
					}
					else if (maze[x][z] == 'R')
					{
						cout << "You step on a level one enemy tile\n";
						m_playerhealth -= 1;
						cout << "You received one damage\n";
						cout << "Health" + to_string(m_playerhealth) + "/10\n";
						m_gameObjects[maze2[x][z]]->SetTexture(m_textureManager->GetTexture("Assets/Textures/tile_disabled.png"));
						delete(m_gameObjects[maze3[x][z]]);//delete the object when the player walk on top of the tile
						m_gameObjects[maze3[x][z]] = NULL;// sets it to null so that it wont try to call the function of a null object
						maze[x][z] = 'D';
						EnemiesDefeated += 1;
					}
					else if (maze[x][z] == 'Q')
					{
						cout << "You step on a level two enemy tile\n";
						m_playerhealth -= 2;
						cout << "You received two damage\n";
						cout << "Health" + to_string(m_playerhealth) + "/10\n";
						m_gameObjects[maze2[x][z]]->SetTexture(m_textureManager->GetTexture("Assets/Textures/tile_disabled.png"));
						delete(m_gameObjects[maze3[x][z]]); //delete the object when the player walk on top of the tile
						m_gameObjects[maze3[x][z]] = NULL; // sets it to null so that it wont try to call the function of a null object
						maze[x][z] = 'D';
						EnemiesDefeated += 1;
					}
					else if (maze[x][z] == 'A')
					{
						cout << "You step on a level three enemy tile\n";
						m_playerhealth -= 3;
						cout << "You received three damage\n";
						cout << "Health" + to_string(m_playerhealth) + "/10\n";
						m_gameObjects[maze2[x][z]]->SetTexture(m_textureManager->GetTexture("Assets/Textures/tile_disabled.png"));
						delete(m_gameObjects[maze3[x][z]]);//delete the object when the player walk on top of the tile
						m_gameObjects[maze3[x][z]] = NULL;// sets it to null so that it wont try to call the function of a null object
						maze[x][z] = 'D';
						EnemiesDefeated += 1;
					}
					else if (maze[x][z] == 'Y')
					{
						cout << "You step on a level four enemy tile\n";
						m_playerhealth -= 4;
						cout << "You received four damage\n";
						cout << "Health" + to_string(m_playerhealth) + "/10\n";
						m_gameObjects[maze2[x][z]]->SetTexture(m_textureManager->GetTexture("Assets/Textures/tile_disabled.png"));
						delete(m_gameObjects[maze3[x][z]]);//delete the object when the player walk on top of the tile
						m_gameObjects[maze3[x][z]] = NULL;// sets it to null so that it wont try to call the function of a null object
						maze[x][z] = 'D';
						EnemiesDefeated += 1;
					}
					else if (maze[x][z] == 'Z')
					{
						cout << "You step on a level five enemy tile\n";
						m_playerhealth -= 5;
						cout << "You received five damage\n";
						cout << "Health" + to_string(m_playerhealth) + "/10\n";
						m_gameObjects[maze2[x][z]]->SetTexture(m_textureManager->GetTexture("Assets/Textures/tile_disabled.png"));
						delete(m_gameObjects[maze3[x][z]]);//delete the object when the player walk on top of the tile
						m_gameObjects[maze3[x][z]] = NULL;// sets it to null so that it wont try to call the function of a null object
						maze[x][z] = 'D';
						EnemiesDefeated += 1;
					}
					else if (maze[x][z] == 'G')
					{
						m_playerhealth = 10;
						cout << "You step on a heal tile\n";
						cout << "You restore to full health\n";
						cout << "Health" + to_string(m_playerhealth) + "/10\n";
						m_gameObjects[maze2[x][z]]->SetTexture(m_textureManager->GetTexture("Assets/Textures/tile_disabled.png"));
						delete(m_gameObjects[maze3[x][z]]);//delete the object when the player walk on top of the tile
						m_gameObjects[maze3[x][z]] = NULL;// sets it to null so that it wont try to call the function of a null object
						maze[x][z] = 'D';
					}
					else
					{
						m_gameObjects[maze2[x][z]]->SetTexture(m_textureManager->GetTexture("Assets/Textures/tile_disabled.png"));
						maze[x][z] = 'D';
					}
					if (m_playerhealth < 1) {
						m_gameObjects[i]->SetID(1);
						cout << "Your Health is 0\n";
						cout << "----------GAME OVER-------------\n";
						system("PAUSE");
						exit(0);
					}
					if (EnemiesDefeated == 5) {
						m_gameObjects[i]->SetID(1);
						cout << "You have defeated all of the enemies\n";
						cout << "----------YOU WIN-------------\n";
						system("PAUSE");
						exit(0);
					}
					if ((maze[x + 1][z] == 'W' || maze[x + 1][z] == 'D') &&
						(maze[x - 1][z] == 'W' || maze[x - 1][z] == 'D') &&
						(maze[x][z + 1] == 'W' || maze[x][z + 1] == 'D') &&
						(maze[x][z - 1] == 'W' || maze[x][z - 1] == 'D'))
					{
						m_gameObjects[i]->SetID(1);
						cout << "There are no more tile you can go to\n";
						cout << "----------GAME OVER-------------\n";
						system("PAUSE");
						exit(0);
					}
				}
			if (m_gameObjects[i]->GetID() == 2) {
				Vector3 player_position = m_gameObjects[playerid]->GetPosition(); // get the player position
				float x = initial.x - player_position.x; //get the difference of x for enemy and player
				float z = initial.z - player_position.z; // get the difference of y for enemy and player
				float rotation = atan2(-x,z);
				m_gameObjects[i]->SetYRotation(rotation);
			}
		}
	}

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

