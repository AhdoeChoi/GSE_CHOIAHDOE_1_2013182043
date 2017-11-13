#pragma once

#include "Object.h"
#include "Renderer.h"


class Scene
{
private:
	float m_fObjectSize;
	float m_fBuildingSize;
	int m_iColorTimer;
	bool m_bColorChange[MAX_OBJECTS_COUNT];

	int m_nEnemy;
	int m_nBuilding;
	int m_nBullet;
	int m_nArrow;
	int m_iCollideCnt;

	int m_nObjects;

	bool m_bBuild;
	bool m_bCollideState;
	bool m_bCollideState_Bullet;

	GLuint m_Buildingtexture;


public:
	
	Player * m_pObjects = NULL;
	Building * m_pBuilding = NULL;
	Renderer *g_Renderer = NULL;
	
public:
	void UpdateObject(DWORD elapsedTime);
	void Render();
	void Animate();
	void Release();
	bool IsCollide(Object* pObject1, Object * pObject2, float distance);
	FLOAT3 Reflect(FLOAT3 direction, FLOAT3 normal);

	void ColideDetection();
	void ReflectDetection();
public:
	void AddActorObject(float x, float y, int objectType); //objectType 객체를 생성하는 함수
	void BuildObject();
public:
	Scene();
	~Scene();
};

