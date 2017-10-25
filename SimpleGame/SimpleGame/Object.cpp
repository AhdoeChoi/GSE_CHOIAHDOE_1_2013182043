#include "stdafx.h"
#include "Object.h"



Object::Object()
{
	memset(&m_f3Position, 0, sizeof(m_f3Position));
	memset(&m_f4Color, 0, sizeof(m_f4Color));
	m_f3Direction.x = 0.0f;
	m_f3Direction.y = 0.0f;
	m_f3Direction.z = 0.0f;
	
	m_f4Color.r = 1.0f;
	m_f4Color.g = 1.0f;
	m_f4Color.b = 1.0f;
	m_f4Color.a = 1.0f;

}


Object::~Object()
{
}

void Object::Update()
{
	m_f3Position.x += m_f3Direction.x;
	m_f3Position.y += m_f3Direction.y;
	m_f3Position.z += m_f3Direction.z;





}
