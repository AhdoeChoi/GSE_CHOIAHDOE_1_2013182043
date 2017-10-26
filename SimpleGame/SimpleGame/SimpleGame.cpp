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

void RenderScene(void)
{

	DWORD currTime = timeGetTime();
	DWORD elapsedTime = currTime - CurrentTime; //�������� �׸��µ� �ɸ��� �ð���

	CurrentTime = currTime;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
	// Renderer Test
	if (pScene)
	{
	
		pScene->Render(); // �����ϰ�

		pScene->Update(elapsedTime);


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

	   pScene->m_pObjects->SetPosition(x - 300, -y + 300, 0);
		cout << x << "\t" << y << endl;
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
	glutInitWindowSize(600, 600);
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

