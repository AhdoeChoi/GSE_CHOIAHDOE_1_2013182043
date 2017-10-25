#include "stdafx.h"
#include "Scene.h"


Scene::Scene()
{
	m_fObjectSize = 4;

	m_pObjects = new Object[MAX_OBJECTS_COUNT];

	default_random_engine dre;
	uniform_real_distribution<> urPosition(-35.f, 35.f);
	uniform_real_distribution<> urMovingDirect(-1.0, 1.0f);
	dre.seed(time(NULL)); //매번달라지게하기위해 seed값을줌

	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		float ur_x = urPosition(dre);
		float ur_y = urPosition(dre);
		FLOAT3 ur_center;
		ur_center.x = ur_x;
		ur_center.y = ur_y;
		ur_center.z = 0;

		m_pObjects[i].SetPosition(ur_x, ur_y,0);
		m_pObjects[i].SetDirection(urMovingDirect(dre), urMovingDirect(dre), 0);
		//m_pObjects[i].SetOOBB(ur_center,m_fObjectSize);

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


}

void Scene::Update()
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		m_pObjects[i].Update();
		
	}
	Animate();

	//cout << m_pObjects[0].m_CircleCollider.m_f3Center.x << "\t" << m_pObjects[0].m_CircleCollider.m_f3Center.y << "\t" << m_pObjects[0].m_CircleCollider.m_f3Center.z << endl;

	
}

void Scene::Render()
{
	//cout << "Render()" << endl;

	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		g_Renderer->DrawSolidRect(m_pObjects[i].GetPosition().x/*x좌표*/,
			m_pObjects[i].GetPosition().y/*y좌표*/,
			m_pObjects[i].GetPosition().z/*z좌표*/,
			m_fObjectSize,/*크기*/
			m_pObjects[i].GetColor().r/*red*/, m_pObjects[i].GetColor().g/*green*/, m_pObjects[i].GetColor().b/*blue*/, m_pObjects[i].GetColor().a/*alpha*/);
	}
	
}

void Scene::Animate()
{
	
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		for (int j = (i + 1); j < MAX_OBJECTS_COUNT; j++) //충돌체크 i= i끼리 할필요없고 i랑j 했으면 j랑i는 할필요 없어서 이렇게 for문 돌리는거임
		{
			if (IsCollide(&m_pObjects[i], &m_pObjects[j]))
			{
				FLOAT3 swapDirection;
				swapDirection.x = m_pObjects[i].GetPosition().x;
				swapDirection.y = m_pObjects[i].GetPosition().y;
				swapDirection.z = m_pObjects[i].GetPosition().z;

				/*m_pObjects[i].SetDirection(m_pObjects[j].GetDirection());
				m_pObjects[j].SetDirection(swapDirection);*/

				m_pObjects[i].SetColor(0, 0, 0,0);
				m_pObjects[j].SetColor(0, 0, 0, 0);
			}
		}
	}

	//FLOAT3 a;
	//a.x = 0;
	//a.y = -1;
	//a.z = 0;
	//for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	//{
	//	if (m_pObjects[i].GetPosition().y < 0)
	//	{
	//		m_pObjects[i].SetDirection(Reflect(m_pObjects[i].GetDirection(), a));
	//	}
	//}

	//cout << m_pObjects[1].GetVelocity().x << "\t" << m_pObjects[1].GetVelocity().y << "\t" << m_pObjects[1].GetVelocity().z << endl;
}
bool Scene::IsCollide(Object* pObject1, Object * pObject2)
{
	
	if (sqrt(pow((pObject1->GetPosition().x - pObject2->GetPosition().x), 2) + pow((pObject1->GetPosition().y - pObject2->GetPosition().y), 2) + pow((pObject1->GetPosition().z - pObject2->GetPosition().z),2)) < 2)
	return true;
}
//FLOAT3 Scene::Reflect(FLOAT3 direction, FLOAT3 normal)
//{
//	FLOAT3 reflectionVector;
//	FLOAT3 twice;
//
//
////	reflectionVector = Vector3::Add(direction, Vector3::Multiple(Vector3::Multiple(normal, 2), Vector3::DotProduct(Vector3::Multiple(direction, -1), normal)));
//		//R = P + 2n(-P 내적 n)
//
//	return reflectionVector;
//}

void Scene::Release()
{
	delete[] m_pObjects;
	delete g_Renderer;


}
