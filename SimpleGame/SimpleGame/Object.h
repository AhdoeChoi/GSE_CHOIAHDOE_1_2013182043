#pragma once


class Object
{
	int m_iObjectType = 0;
public:
	FLOAT3 m_f3Position;
	FLOAT4_COLOR m_f4Color;

	FLOAT3 m_f3Direction;
	
	int m_iLife;
	float m_fLifeTime;
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

	void SetDirection(FLOAT3 direction) { m_f3Direction = direction;   }
	void SetDirection(float x, float y, float z) { m_f3Direction.x = x, m_f3Direction.y = y, m_f3Direction.z = z; }

	float GetLifeTime() { return m_fLifeTime; }

	void IncreaseLife(int life) { m_iLife += life;  }
	void SetLife(int life) { m_iLife = life; }
	int GetLife() { return m_iLife; }
	void Update(DWORD elapsedTime);
	void SetObjectType(int objectType) { m_iObjectType = objectType; }

public:

};
class Player : public Object
{

};


class Bullet : public Object //아군
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
private:
	float m_fShootTimer_Bullet;
	bool m_bShootState_Bullet;

	float m_fShootTimer_Arrow;
	bool m_bShootState_Arrow;
public:
	list<Bullet*>	m_listBullet;
	int	m_nBullet;

	list<Arrow*>	m_listArrow;
public:
	Building();
	~Building();
	void DamageAnimate();
	void BulletShot();

	void ArrowShot();

	void Update(DWORD elapsedTime);
};
