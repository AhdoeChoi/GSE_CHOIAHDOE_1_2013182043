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

#include "Object.h"
#include "Renderer.h"
#include <iostream>

using namespace std;


Renderer *g_Renderer = NULL;
Object * pObject = NULL;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);


	// Renderer Test
	if (pObject)
	{
		g_Renderer->DrawSolidRect(pObject->GetPosition().x/*xÁÂÇ¥*/, pObject->GetPosition().y/*yÁÂÇ¥*/, pObject->GetPosition().z/*zÁÂÇ¥*/, 100/*Å©±â*/, 0/*red*/, 100/*green*/, 51/*blue*/, 1/*alpha*/);

	}
	//g_Renderer->DrawSolidRect(pObject->GetPosition().x + (pObject->GetPosition().x + pObject->GetVelocity().x),
	//	pObject->GetPosition().y + (pObject->GetPosition().y + pObject->GetVelocity().y),
	//	pObject->GetPosition().z + (pObject->GetPosition().z + pObject->GetVelocity().z),
	//	100, 0, 100, 51, 1);


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

		pObject->SetPosition(x - 300, -y + 300, 0);
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

void Update(int value)
{



	pObject->Update();
	glutTimerFunc(100, Update, 1);


}


int main(int argc, char **argv)
{
	pObject = new Object;

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

	// Initialize Renderer
	g_Renderer = new Renderer(500, 500);
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);
	glutTimerFunc(100, Update, 1);

	glutMainLoop();

	delete g_Renderer;
	delete pObject;
	return 0;
}

