#pragma once


class Object
{
	int m_iObjectType = 0;
private:
	FLOAT3 m_f3Position;
	FLOAT4_COLOR m_f4Color;

	FLOAT3 m_f3Direction;
	
	int m_iLife;
public:
	Object();
	~Object();
	FLOAT3 GetPosition() { return m_f3Position; }
	FLOAT4_COLOR GetColor() { return m_f4Color; }
	FLOAT3 GetDirection() { return m_f3Direction; }

	void SetColor(FLOAT4_COLOR color) { m_f4Color = color; }
	void SetColor(float r, float g, float b, float a) { m_f4Color.r = r, m_f4Color.g = g, m_f4Color.b = b, m_f4Color.a = a; }

	void SetPosition(FLOAT3 position) { m_f3Position = position; }
	void SetPosition(float x, float y, float z) { m_f3Position.x = x, m_f3Position.y = y, m_f3Position.z = z; }

	void SetDirection(FLOAT3 direction) { m_f3Direction = direction; }
	void SetDirection(float x, float y, float z) { m_f3Direction.x = x, m_f3Direction.y = y, m_f3Direction.z = z; }

	void IncreaseLife(int life) { m_iLife += life;  }
	int GetLife() { return m_iLife; }
	void Update(DWORD elapsedTime);
	void SetObjectType(int objectType) { m_iObjectType = objectType; }
public:

};

class Enemy : public Object // 적군
{
public:
	Enemy();
	~Enemy();
};

class Ally : public Object //아군
{
public:
	Ally();
	~Ally();
};

class Building : public Object //아군
{
public:
	Building();
	~Building();
};

class Bullet: public Object //아군
{
public:
	Bullet();
	~Bullet();
};
class Arrow : public Object //아군
{
public:
	Arrow();
	~Arrow();
};