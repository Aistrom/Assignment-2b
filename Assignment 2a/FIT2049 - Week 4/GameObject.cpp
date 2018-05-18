#include "GameObject.h"



GameObject::GameObject(Mesh* mesh, Shader* shader, InputController* input, Vector3 position,int id)
{
	m_mesh = mesh;
	m_shader = shader;
	m_input = input;
	m_position = position;
	m_texture = NULL;
	m_ID = id;

	m_rotX = m_rotY = m_rotZ = 0.0f;
	SetUniformScale(1.0f);

	m_moveSpeed = 1.5f;
	m_rotateSpeed = 1.0f;

}

GameObject::GameObject(Mesh* mesh, Shader* shader, InputController* input, Vector3 position, Texture* texture,int id)
{
	m_mesh = mesh;
	m_shader = shader;
	m_input = input;
	m_position = position;
	m_texture = texture;
	m_ID = id;

	m_rotX = m_rotY = m_rotZ = 0.0f;
	SetUniformScale(1.0f);

	m_moveSpeed = 5.0f;
	m_rotateSpeed = 1.0f;

}

GameObject::~GameObject()
{
}

void GameObject::Update(float timestep)
{
	if (m_ID == 0) {
		// Translation along the world axes
		if (m_input->GetKeyHold(VK_LEFT))
		{
			// Note you can instead use Vector3::Left etc. as a shorthand when declaring unit vectors
			m_position += Vector3(-1.0f, 0.0f, 0.0f) ;
		}
		if (m_input->GetKeyHold(VK_RIGHT))
		{
			m_position += Vector3(1.0f, 0.0f, 0.0f);
		}
		if (m_input->GetKeyHold(VK_UP))
		{
			m_position += Vector3(0.0f, 0.0f, 1.0f);
		}
		if (m_input->GetKeyHold(VK_DOWN))
		{
			m_position += Vector3(0.0f, 0.0f, -1.0f);
		}
	}
}

void GameObject::Render(Direct3D* renderer, Camera* cam)
{
	if (m_mesh)
	{
		m_world = Matrix::CreateScale(m_scaleX, m_scaleY, m_scaleZ) * Matrix::CreateFromYawPitchRoll(m_rotY, m_rotX, m_rotZ) * Matrix::CreateTranslation(m_position);
		m_mesh->Render(renderer, m_shader, m_world, cam, m_texture);
	}

}




