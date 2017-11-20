/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "Scene.h"
#include "Renderer.h"



//Object * pObject = NULL;

Scene * pScene = NULL;
DWORD CurrentTime;

int ClickCnt = 0;

void RenderScene(void)
{

	DWORD currTime = timeGetTime();
	DWORD elapsedTime = currTime - CurrentTime; //한프레임 그리는데 걸리는 시간임

	CurrentTime = currTime;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
	// Renderer Test
	if (pScene)
	{
	
		pScene->Render(); // 렌더하고

		pScene->UpdateObject(elapsedTime);
		pScene->CoolTimeCount(elapsedTime);

	}
	


	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		
			//pScene->m_pObjects->SetPosition(x - 300, -y + 300, 0);
			cout << x << "\t" << y << endl;

			pScene->AddActorObject(x - WINDOW_WIDTH/2, - y + WINDOW_HEIGHT/2, OBJECT_CHARACTER);
		
	 
		//ClickCnt++;
	}

	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();


}



int main(int argc, char **argv)
{
	//pObject = new Object[MAX_OBJECTS_COUNT];


	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Game Software Engineering KPU");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	pScene = new Scene;


	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	CurrentTime = timeGetTime();

	glutMainLoop();

	pScene->Release();
	delete pScene;
	return 0;
}

