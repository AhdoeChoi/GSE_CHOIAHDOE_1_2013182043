#include "stdafx.h"
#include "Object.h"


Object::Object()
{
	memset(&m_f3Position, 0, sizeof(m_f3Position));
	memset(&m_f4Color, 0, sizeof(m_f4Color));
	
	m_f3Velocity.x = 5.0f;
	m_f3Velocity.y = 0.0f;
	m_f3Velocity.z = 0.0f;
	
}


Object::~Object()
{
}

void Object::Update()
{
	m_f3Position.x += m_f3Velocity.x;
	m_f3Position.y += m_f3Velocity.y;
	m_f3Position.z += m_f3Velocity.z;

}