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

	m_iLife = 5;
	m_iObjectType = -1;
}


Object::~Object()
{
}

void Object::Update(DWORD elapsedTime)
{
	//m_f3Position.x += 1 * m_f3Direction.x;
	//m_f3Position.y += 1 * m_f3Direction.y;
	//m_f3Position.z += 1 * m_f3Direction.z;
	
	m_f3Position.x += elapsedTime * (m_f3Direction).x;
	m_f3Position.y += elapsedTime * (m_f3Direction).y;
	m_f3Position.z += elapsedTime * (m_f3Direction).z;



}
Enemy::Enemy()
{

}
Enemy::~Enemy()
{

}
Ally::Ally()
{

}
Ally::~Ally()
{

}
Building::Building()
{

}
Building::~Building()
{

}
Bullet::Bullet()
{

}
Bullet::~Bullet()
{

}
Arrow::Arrow()
{

}
Arrow::~Arrow()
{

}