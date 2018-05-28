#include "PlayerBullet.h"

PlayerBullet::PlayerBullet(Mesh* mesh, Shader* shader, Texture* texture, Vector3 position, InputController* input) :
	GameObject(mesh, shader, texture, position)
{
	m_input = input;
	m_boundingBox = CBoundingBox(m_position + m_mesh->GetMin(), m_position + m_mesh->GetMax());

	isMoving = false;
	isStop = true;

	damage = 11;
};

void PlayerBullet::Update(float timestep, Vector3 Playerposition,Vector3 cameralookat) {
	Vector3 camera_position = cameralookat - this->GetPosition(); // get the camera lookat
	camera_position.Normalize();
	Matrix heading;

	if (m_input->GetMouseUp(LEFT_MOUSE) && isMoving != true) {
		isMoving = true;
		isStop = false;
		traveltime = TimeKeeper::GetTimeFromStart();
		this->SetUniformScale(1.0f);
	}

	else if (isMoving == true) {
		if (TimeKeeper::GetTimeFromStart() - traveltime >= 1) {
			isStop = true;
			isMoving = false;
			this->SetUniformScale(0.0001f);
		}
		Matrix heading = Matrix::CreateRotationY(this->GetYRotation());

		Vector3 localRight = Vector3::TransformNormal(Vector3(1, 0, 0), heading);

		Vector3 localForwardXZ = localRight.Cross(Vector3(0, 1, 0));

		Vector3 currentPos = GetPosition() + Vector3(0.0f, 0.0f, 0.0f);

		currentPos += localForwardXZ * m_moveSpeed * timestep;

		SetPosition(currentPos);
		
	}
	else if (isStop == true){
		SetPosition(Playerposition + Vector3(0, 1.25f, 0));
		this->SetYRotation(atan2(camera_position.x, camera_position.z));
	}

	m_boundingBox.SetMin(m_position + m_mesh->GetMin());
	m_boundingBox.SetMax(m_position + m_mesh->GetMax());


};

void PlayerBullet::OnEnemiesCollisionEnter() {

};
void PlayerBullet::OnEnemiesCollisionStay() {

};
void PlayerBullet::OnEnemiesCollisionExit() {

};