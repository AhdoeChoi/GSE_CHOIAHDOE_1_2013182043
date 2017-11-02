#include "stdafx.h"
#include "Scene.h"


Scene::Scene()
{
	m_fObjectSize = 10;
	m_iColorTimer = 0;
	
	BuildObject();


	// Initialize Renderer
	g_Renderer = new Renderer(500, 500);
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
	m_nEnemy = 0;
	m_nBuilding = 0;
	m_nBullet = 0;
	m_nArrow = 0;
}

Scene::~Scene()
{


}

void Scene::BuildObject()
{
	m_pObjects = new Object[MAX_OBJECTS_COUNT];

	default_random_engine dre;
	uniform_real_distribution<> urPosition(-225.f, 225.f);
	uniform_real_distribution<> urMovingDirect(0.0, 0.155f);
	dre.seed(time(NULL)); //매번달라지게하기위해 seed값을줌

	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		float ur_x = urPosition(dre);
		float ur_y = urPosition(dre);
		FLOAT3 ur_center;
		ur_center.x = ur_x;
		ur_center.y = ur_y;
		ur_center.z = 0;

		m_pObjects[i].SetPosition(ur_x, ur_y, 0);
		m_pObjects[i].SetDirection(urMovingDirect(dre), urMovingDirect(dre), 0);
		//m_pObjects[i].SetOOBB(ur_center,m_fObjectSize);

	}
	AddActorObject(0,0, OBJECT_BUILDING);
}

void Scene::Update(DWORD elapsedTime)
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		m_pObjects[i].Update(elapsedTime);

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


	for (int i = 0; i < m_nBuilding +1 ; ++i)
	{
	
		g_Renderer->DrawSolidRect(m_pBuilding[i].GetPosition().x/*x좌표*/,
			m_pBuilding[i].GetPosition().y/*y좌표*/,
			m_pBuilding[i].GetPosition().z/*z좌표*/,
			100,/*크기*/
			m_pBuilding[i].GetColor().r/*red*/, m_pBuilding[i].GetColor().g/*green*/, m_pBuilding[i].GetColor().b/*blue*/, m_pBuilding[i].GetColor().a/*alpha*/);
	}

}

void Scene::Animate()
{

	default_random_engine dre;
	uniform_real_distribution<> urColor(0.5, 1.0);
	dre.seed(time(NULL)); //매번달라지게하기위해 seed값을줌

	++m_iColorTimer;

	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		for (int j = (i + 1); j < MAX_OBJECTS_COUNT; j++) //충돌체크 i= i끼리 할필요없고 i랑j 했으면 j랑i는 할필요 없어서 이렇게 for문 돌리는거임
		{
			if (IsCollide(&m_pObjects[i], &m_pObjects[j]))
			{
				//cout << m_pObjects[0].GetLife() << endl;

				FLOAT3 swapDirection;
				swapDirection.x = m_pObjects[i].GetDirection().x;
				swapDirection.y = m_pObjects[i].GetDirection().y;
				swapDirection.z = m_pObjects[i].GetDirection().z;

				m_pObjects[i].SetDirection(m_pObjects[j].GetDirection());
				//m_pObjects[i].SetPosition(m_pObjects[i].GetPosition().x + 2 *m_pObjects[j].GetDirection().x, m_pObjects[i].GetPosition().y + 2 * m_pObjects[j].GetDirection().y, m_pObjects[i].GetPosition().z + 2 * m_pObjects[j].GetDirection().z);
				m_pObjects[i].SetPosition(m_pObjects[i].GetPosition().x + 2 *m_pObjects[j].GetDirection().x, m_pObjects[i].GetPosition().y + 2 * m_pObjects[j].GetDirection().y, m_pObjects[i].GetPosition().z + 2 * m_pObjects[j].GetDirection().z);

				m_pObjects[j].SetDirection(swapDirection);
				//m_pObjects[i].SetDirection(Reflect(m_pObjects[i].GetDirection(),m_pObjects[j].GetDirection()));
				//m_pObjects[j].SetDirection(Reflect(m_pObjects[j].GetDirection(),swapDirection));

				m_pObjects[i].SetColor(255, 0, 0, 0);
				m_pObjects[j].SetColor(255, 0, 0, 0);

				/*m_pObjects[i].IncreaseLife(-1);
				m_pObjects[j].IncreaseLife(-1);*/ //여기이상해 ㅠ

				if (m_pObjects[i].GetLife() < 0)
				{
					m_pObjects[i].SetPosition(3333, 333333, 3333); // 이거 삭제로 바꿀것
				}
				if (m_pObjects[j].GetLife() < 0)
				{
					m_pObjects[j].SetPosition(3853, 333333, 3333); // 이거 삭제로 바꿀것

				}
			}
		}
	}
	//cout << m_pObjects[0].GetPosition().x << "\t" << m_pObjects[0].GetPosition().y << "\t" << m_pObjects[0].GetPosition().z << endl;

	if (m_iColorTimer > 100)
	{
		m_iColorTimer = 0;
		for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		{
			m_pObjects[i].SetColor(1, 1, 1, 0);
		}

	}


	FLOAT3 xup;
	xup.x = 0;
	xup.y = -1;
	xup.z = 0;

	FLOAT3 xdown;
	xdown.x = 0;
	xdown.y = 1;
	xdown.z = 0;

	FLOAT3 yleft;
	yleft.x = 1;
	yleft.y = 0;
	yleft.z = 0;

	FLOAT3 yright;
	yright.x = -1;
	yright.y = 0;
	yright.z = 0;
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		//cout << m_pObjects[i].GetPosition().y << endl;
		if (m_pObjects[i].GetPosition().y > 250)
		{
			m_pObjects[i].SetDirection(Reflect(m_pObjects[i].GetDirection(), xup));
			m_pObjects[i].SetPosition(m_pObjects[i].GetPosition().x , m_pObjects[i].GetPosition().y - 1 , m_pObjects[i].GetPosition().z);

		}

		//cout << m_pObjects[i].GetPosition().y << endl;
		if (m_pObjects[i].GetPosition().y < -250)
		{
			m_pObjects[i].SetDirection(Reflect(m_pObjects[i].GetDirection(), xdown));
			m_pObjects[i].SetPosition(m_pObjects[i].GetPosition().x, m_pObjects[i].GetPosition().y + 1, m_pObjects[i].GetPosition().z);

		}

		if (m_pObjects[i].GetPosition().x < -250)
		{
			m_pObjects[i].SetDirection(Reflect(m_pObjects[i].GetDirection(), yleft));
			m_pObjects[i].SetPosition(m_pObjects[i].GetPosition().x +1, m_pObjects[i].GetPosition().y, m_pObjects[i].GetPosition().z);

		}

		if (m_pObjects[i].GetPosition().x > 250)
		{
			m_pObjects[i].SetDirection(Reflect(m_pObjects[i].GetDirection(), yright));
			m_pObjects[i].SetPosition(m_pObjects[i].GetPosition().x-1, m_pObjects[i].GetPosition().y, m_pObjects[i].GetPosition().z);

		}
	}
	//cout << m_pObjects[0].GetPosition().x << "\t" << m_pObjects[0].GetPosition().y << "\t" << m_pObjects[0].GetPosition().z << endl;
	//cout << m_pObjects[1].GetVelocity().x << "\t" << m_pObjects[1].GetVelocity().y << "\t" << m_pObjects[1].GetVelocity().z << endl;
}
bool Scene::IsCollide(Object* pObject1, Object * pObject2)
{
	float Distance = sqrt(pow((pObject1->GetPosition().x - pObject2->GetPosition().x), 2) + pow((pObject1->GetPosition().y - pObject2->GetPosition().y), 2) + pow((pObject1->GetPosition().z - pObject2->GetPosition().z), 2));
	if (Distance < 10)
		return true;
	return false;
}
FLOAT3 Scene::Reflect(FLOAT3 direction, FLOAT3 normal)
{
	FLOAT3 reflectionVector;

	using namespace Vector3;


	reflectionVector = Add(direction, Multiple(Multiple(normal, 2), DotProduct(Multiple(direction, -1), normal)));
	//R = P + 2n(-P 내적 n)


	return reflectionVector;
}
void Scene::AddActorObject(float x, float y, int objectType)
{
	switch (objectType)
	{
	case OBJECT_ARROW:

		break;

	case OBJECT_BUILDING:
		if (m_pBuilding == NULL)
		{
			m_pBuilding = new Building[MAX_BUILDING_COUNT];
		
		}
		if (m_nBuilding < MAX_BUILDING_COUNT)
		{
			m_pBuilding[m_nBuilding].SetPosition(x, y, 0);
			m_pBuilding[m_nBuilding].SetColor(1, 1, 0, 1);
			m_nBuilding++;

		}
		break;
		
	case OBJECT_BULLET:
		break;

	case OBJECT_CHARACTER:
		break;

	}
}
void Scene::Release()
{
	delete[] m_pObjects;
	delete g_Renderer;


}
