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
	m_rotationSpeed = 1.0f;

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
	m_rotationSpeed = 1.0f;

}

GameObject::GameObject()
{
	m_position = Vector3::Zero;
	m_rotX = m_rotY = m_rotZ = 0;
	SetUniformScale(1.0f);
	m_world = Matrix::Identity;
	m_mesh = NULL;
	m_texture = NULL;
	m_shader = NULL;
}
GameObject::GameObject(Mesh* mesh, Shader* shader)
{
	m_position = Vector3::Zero;
	m_rotX = m_rotY = m_rotZ = 0;
	SetUniformScale(1.0f);
	m_world = Matrix::Identity;
	m_mesh = mesh;
	m_texture = NULL;
	m_shader = shader;
}
GameObject::GameObject(Mesh* mesh, Shader* shader, Texture* texture)
{
	m_position = Vector3::Zero;
	m_rotX = m_rotY = m_rotZ = 0;
	SetUniformScale(1.0f);
	m_world = Matrix::Identity;
	m_mesh = mesh;
	m_texture = texture;
	m_shader = shader;
}
GameObject::GameObject(Mesh* mesh, Shader* shader, Vector3 position)
{
	m_position = position;
	m_rotX = m_rotY = m_rotZ = 0;
	SetUniformScale(1.0f);
	m_world = Matrix::Identity;
	m_mesh = mesh;
	m_texture = NULL;
	m_shader = shader;
}
GameObject::GameObject(Mesh* mesh, Shader* shader, Texture* texture, Vector3 position)
{
	m_position = position;
	m_rotX = m_rotY = m_rotZ = 0;
	SetUniformScale(1.0f);
	m_world = Matrix::Identity;
	m_mesh = mesh;
	m_texture = texture;
	m_shader = shader;
}

GameObject::~GameObject()
{
}

void GameObject::Update(float timestep)
{

}

void GameObject::Render(Direct3D* renderer, Camera* cam)
{
	if (m_mesh != NULL)
	{
		m_world = Matrix::CreateScale(m_scaleX, m_scaleY, m_scaleZ) * Matrix::CreateFromYawPitchRoll(m_rotY, m_rotX, m_rotZ) * Matrix::CreateTranslation(m_position);
		m_mesh->Render(renderer, m_shader, m_world, cam, m_texture);
	}

}




