#include "Bullet.h"

Bullet::Bullet(Mesh* mesh, Shader* shader, Texture* texture, Vector3 position, InputController* input) :
	PhysicsObject(mesh, shader, texture, position)
{

};

void Bullet::Update(float timestep) {

};

void Bullet::OnPlayerCollisionEnter(GameObject* object) {
	OutputDebugString("Bullet-Player Collision Enter\n");
};
void Bullet::OnPlayerCollisionStay(GameObject* object) {
	OutputDebugString("Bullet-Player Collision Stay\n");
};
void Bullet::OnPlayerCollisionExit(GameObject* object) {
	OutputDebugString("Bullet-Player Collision Exit\n");
};