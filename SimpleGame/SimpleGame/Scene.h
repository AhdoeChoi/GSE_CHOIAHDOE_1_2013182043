#pragma once

#include "Object.h"
#include "Renderer.h"


class Scene
{
public:
	Object * m_pObjects = NULL;
	Renderer *g_Renderer = NULL;

public:
	void Update();
	void Render();
	void Animate();
public:
	Scene();
	~Scene();
};

