#pragma once

typedef struct FLOAT3
{
	float x;
	float y;
	float z;

}FLOAT3;

typedef struct FLOAT4
{
	float x;
	float y;
	float z;
	float a;
}FLOAT4;

class Object
{
private:
	FLOAT3 m_f3Position;
	FLOAT4 m_f4Color;

	FLOAT3 m_f3Velocity;

public:
	Object();
	~Object();
	FLOAT3 GetPosition() { return m_f3Position; }
	FLOAT4 GetColor() { return m_f4Color; }
	FLOAT3 GetVelocity() { return m_f3Velocity; }

	void SetPosition(FLOAT3 position) { m_f3Position = position; }
	void SetPosition(int x, int y, int z) { m_f3Position.x = x, m_f3Position.y = y, m_f3Position.z = z; }


	void Update();
};

