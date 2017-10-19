#include "stdafx.h"
#include "Scene.h"


Scene::Scene()
{
	m_pObjects = new Object[MAX_OBJECTS_COUNT];

	default_random_engine dre;
	uniform_real_distribution<> urPosition(-35.f, 35.f);
	uniform_real_distribution<> urMovingDirect(-1.0, 1.0f);
	dre.seed(time(NULL)); //�Ź��޶������ϱ����� seed������

	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		m_pObjects[i].SetPosition(urPosition(dre), urPosition(dre),0);
		m_pObjects[i].SetDirection(urMovingDirect(dre), urMovingDirect(dre), 0);
	}
	

	// Initialize Renderer
	g_Renderer = new Renderer(500, 500);
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
}

Scene::~Scene()
{
	delete[] m_pObjects;
	delete g_Renderer;

	cout << "�Ҹ��� ȣ��" << endl;

}

void Scene::Update()
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		m_pObjects[i].Update();
	}
}

void Scene::Render()
{
	//cout << "Render()" << endl;

	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		g_Renderer->DrawSolidRect(m_pObjects[i].GetPosition().x/*x��ǥ*/,
			m_pObjects[i].GetPosition().y/*y��ǥ*/,
			m_pObjects[i].GetPosition().z/*z��ǥ*/, 3/*ũ��*/, 255/*red*/, 255/*green*/, 255/*blue*/, 1/*alpha*/);
	}
	
}

void Scene::Animate()
{
	
	//for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	//{
	//	for (int j = (i + 1); j < MAX_OBJECTS_COUNT; j++) //�浹üũ i= i���� ���ʿ���� i��j ������ j��i�� ���ʿ� ��� �̷��� for�� �����°���
	//	{
	//		if ((m_pObjects[i]).GetPosition().x - m_pObjects[j].GetPosition().x < 4 && (m_pObjects[i]).GetPosition().y - m_pObjects[j].GetPosition().y < 4)
	//		{
	//			FLOAT3 SwapPosition = m_pObjects[i].GetVelocity();

	//			m_pObjects[i].SetDirection(m_pObjects[j].GetVelocity());
	//			(m_pObjects[j]).SetDirection(SwapPosition);
	//		}
	//	}
	//}
}