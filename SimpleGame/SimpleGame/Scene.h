#pragma once

#include "Object.h"
#include "Renderer.h"


class Scene
{
private:
	float m_fObjectSize;
public:
	Object * m_pObjects = NULL;
	Renderer *g_Renderer = NULL;

public:
	void Update();
	void Render();
	void Animate();
	void Release();
	bool IsCollide(Object* pObject1, Object * pObject2);
	FLOAT3 Reflect(FLOAT3 direction, FLOAT3 normal);
public:
	Scene();
	~Scene();
};

