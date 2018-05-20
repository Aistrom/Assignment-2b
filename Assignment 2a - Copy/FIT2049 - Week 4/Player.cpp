#include "Player.h"

Player::Player(Mesh* mesh, Shader* shader, Texture* texture, Vector3 position, InputController* input) :
	PhysicsObject(mesh, shader, texture, position)
{

};

void Player::Update(float timestep) {

};

void Player::OnEnemiesCollisionEnter(GameObject* object) {
	OutputDebugString("Player-Enemies Collision Enter\n");
};
void Player::OnEnemiesCollisionStay(GameObject* object){
	OutputDebugString("Player-Enemies Collision Stay\n");
};
void Player::OnEnemiesCollisionExit(GameObject* object) {
	OutputDebugString("Player-Enemies Collision Exit\n");
};

void Player::OnHealthCollisionEnter(GameObject* object) {
	OutputDebugString("Player-Health Collision Enter\n");
};
void Player::OnHealthCollisionStay(GameObject* object) {
	OutputDebugString("Player-Health Collision Stay\n");
};
void Player::OnHealthCollisionExit(GameObject* object) {
	OutputDebugString("Player-Health Collision Exit\n");
};

void Player::OnWallCollisionEnter(GameObject* object) {
	OutputDebugString("Player-Wall Collision Enter\n");
};
void Player::OnWallCollisionStay(GameObject* object) {
	OutputDebugString("Player-Wall Collision Stay\n");
};
void Player::OnWallCollisionExit(GameObject* object) {
	OutputDebugString("Player-Wall Collision Exit\n");
};

void Player::OnBulletCollisionEnter(GameObject* object) {
	OutputDebugString("Player-Bullet Collision Enter\n");
};
void Player::OnBulletCollisionStay(GameObject* object) {
	OutputDebugString("Player-Bullet Collision Stay\n");
};
void Player::OnBulletCollisionExit(GameObject* object) {
	OutputDebugString("Player-Bullet Collision Exit\n");
};
