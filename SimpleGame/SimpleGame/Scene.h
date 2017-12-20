#pragma once

#include "Object.h"
#include "Renderer.h"
#include "Sound.h"

class Scene
{
private:
	Sound *m_sound = NULL;
	int soundBG = 0;

private:
	int m_iClickCnt = 0;
	float m_fObjectSize;
	float m_fBuildingSize;
	int m_iColorTimer;
	bool m_bColorChange[MAX_OBJECTS_COUNT];
	float m_fBulletSize;
	float m_fArrowSize;
	int m_nEnemy;
	int m_nBuilding;
	int m_nBuilding_NORTH;
	int m_nBullet;
	int m_nArrow;
	int m_iCollideCnt;

	int m_nObjects;
	int m_nObjects_NORTH;

	bool m_bBuild;
	bool m_bCollideState;
	bool m_bCollideState_NORTH;
	bool m_bCollideState_Bullet;
	bool m_bCollideState_Bullet_NORTH;

	bool m_bCollideState_BuildingBullet_BuildingNorth;
	bool m_bCollideState_BuildingNorthBullet_Building;

	GLuint m_Buildingtexture;
	GLuint m_Buildingtexture_NORTH;
	GLuint m_BackGroundTexture;
	GLuint m_AnimationTexture;
	GLuint m_AnimationTexture_NORTH;
	GLuint m_SnowTexture;


	GLuint m_ParticleTextureBullet;
	int m_iAnimationFrameCnt = 0;
	float m_iScene_ElapsedTime = 0;
	int m_iAnimationFrame = 0;
public:
	float m_fCoolTime = 0;
	bool m_bCoolTimeFinish = true;
	bool m_bCoolTimeOn = false;
	Player * m_pObjects = NULL;
	Player * m_pObjects_NORTH = NULL;

	Building * m_pBuilding = NULL;
	Building * m_pBuilding_NORTH = NULL;

	Renderer *g_Renderer = NULL;

	Building * m_pBuildingNorth = NULL;
	Building * m_pBuildingSouth = NULL;

public:
	void CoolTimeCount(DWORD elapsedTime);
	void CoolTimeCheck();

public:
	float m_fNorthEnemyCreateTimer= 0;

	void NorthEnemyCreate(DWORD elapsedTime);
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

