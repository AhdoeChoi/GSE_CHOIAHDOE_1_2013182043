#pragma once

#include "Object.h"
#include "Renderer.h"


class Scene
{
private:
	float m_fObjectSize;
	int m_iColorTimer;
	bool m_bColorChange[MAX_OBJECTS_COUNT];

	int m_nEnemy;
	int m_nBuilding;
	int m_nBullet;
	int m_nArrow;


public:
	
	Object * m_pObjects = NULL;
	Object * m_pBullet = NULL;
	Object * m_pArrow = NULL;
	Building * m_pBuilding = NULL;
	Renderer *g_Renderer = NULL;
	
public:
	void Update(DWORD elapsedTime);
	void Render();
	void Animate();
	void Release();
	bool IsCollide(Object* pObject1, Object * pObject2);
	FLOAT3 Reflect(FLOAT3 direction, FLOAT3 normal);
public:
	void AddActorObject(float x, float y, int objectType); //objectType 객체를 생성하는 함수
	void BuildObject();
public:
	Scene();
	~Scene();
};

