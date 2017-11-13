#include "stdafx.h"
#include "Scene.h"


Scene::Scene()
{
	m_fObjectSize = 10;
	m_fBuildingSize = 40;
	m_iColorTimer = 0;
	m_nObjects = 0;
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

	m_iCollideCnt = 0;

	m_bCollideState = false;
	m_bCollideState_Bullet = false;
}

Scene::~Scene()
{


}

void Scene::BuildObject()
{
	m_pObjects = new Player[MAX_OBJECTS_COUNT];

	AddActorObject(0,0, OBJECT_BUILDING);
}

void Scene::UpdateObject(DWORD elapsedTime)
{
	for (int i = 0; i < m_nObjects; ++i)
	{
		m_pObjects[i].Update(elapsedTime);

	}

	for (int i = 0; i < m_nBuilding+1; ++i)
	{
		m_pBuilding[i].Update(elapsedTime);

	}
	Animate();

	//cout << m_pObjects[0].m_CircleCollider.m_f3Center.x << "\t" << m_pObjects[0].m_CircleCollider.m_f3Center.y << "\t" << m_pObjects[0].m_CircleCollider.m_f3Center.z << endl;


}

void Scene::Render()
{
	//cout << "Render()" << endl;

	for (int i = 0; i < m_nObjects; ++i)
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
			m_fBuildingSize,/*크기*/
			m_pBuilding[i].GetColor().r/*red*/, m_pBuilding[i].GetColor().g/*green*/, m_pBuilding[i].GetColor().b/*blue*/, m_pBuilding[i].GetColor().a/*alpha*/);
	}


	for (auto iter = m_pBuilding->m_listBullet.begin(); iter != m_pBuilding->m_listBullet.end(); ++iter)
	{
		g_Renderer->DrawSolidRect((*iter)->GetPosition().x, (*iter)->GetPosition().y, (*iter)->GetPosition().z, 10, (*iter)->GetColor().r, (*iter)->GetColor().g, (*iter)->GetColor().b, (*iter)->GetColor().a);
	}

}

void Scene::Animate()
{

	++m_iColorTimer;

	ColideDetection();
	ReflectDetection();

	if (m_iColorTimer > 200)
	{
		m_iColorTimer = 0;
		for (int i = 0; i < m_nObjects; ++i)
		{
			m_pObjects[i].SetColor(1, 1, 1, 0);
		}

	}
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_pObjects[i].GetLifeTime() > OBJECT_DELETE_TIME)
		{
			m_pObjects[i].SetPosition(3853, 333333, 3333); // 이거 삭제로 바꿀것

		}
	}
	
	for(int i = 0; i < m_nBuilding+1;++i)
	m_pBuilding[i].BulletShot();

}
bool Scene::IsCollide(Object* pObject1, Object * pObject2,float distance)
{
	float Distance = sqrt(pow((pObject1->GetPosition().x - pObject2->GetPosition().x), 2) + pow((pObject1->GetPosition().y - pObject2->GetPosition().y), 2) + pow((pObject1->GetPosition().z - pObject2->GetPosition().z), 2));
	if (Distance < distance)
	{
		return true;
	}
	return false;
}
void Scene::ColideDetection()
{
	for (int i = 0; i < m_nObjects; i++)
	{
		for (int j = (i + 1); j < m_nObjects; j++) //충돌체크 i= i끼리 할필요없고 i랑j 했으면 j랑i는 할필요 없어서 이렇게 for문 돌리는거임
		{
			if (IsCollide(&m_pObjects[i], &m_pObjects[j], m_fObjectSize))
			{
				if (m_bCollideState == false)
				{
					//cout << m_pObjects[0].GetLife() << endl;

					FLOAT3 swapDirection;
					swapDirection.x = m_pObjects[i].GetDirection().x;
					swapDirection.y = m_pObjects[i].GetDirection().y;
					swapDirection.z = m_pObjects[i].GetDirection().z;

					m_pObjects[i].SetDirection(m_pObjects[j].GetDirection());
					//m_pObjects[i].SetPosition(m_pObjects[i].GetPosition().x + 2 *m_pObjects[j].GetDirection().x, m_pObjects[i].GetPosition().y + 2 * m_pObjects[j].GetDirection().y, m_pObjects[i].GetPosition().z + 2 * m_pObjects[j].GetDirection().z);
					m_pObjects[i].SetPosition(m_pObjects[i].GetPosition().x + 10 * m_pObjects[j].GetDirection().x, m_pObjects[i].GetPosition().y + 10 * m_pObjects[j].GetDirection().y, m_pObjects[i].GetPosition().z + 10 * m_pObjects[j].GetDirection().z);

					m_pObjects[j].SetDirection(swapDirection);
					m_pObjects[j].SetPosition(m_pObjects[j].GetPosition().x + 10 * swapDirection.x, m_pObjects[j].GetPosition().y + 10 * swapDirection.y, m_pObjects[j].GetPosition().z + 10 * swapDirection.z);

					//m_pObjects[i].SetDirection(Reflect(m_pObjects[i].GetDirection(),m_pObjects[j].GetDirection()));
					//m_pObjects[j].SetDirection(Reflect(m_pObjects[j].GetDirection(),swapDirection));

					m_pObjects[i].SetColor(255, 0, 0, 0);
					m_pObjects[j].SetColor(255, 0, 0, 0);

					//++m_iCollideCnt;

					//cout << m_iCollideCnt << endl;

					m_bCollideState = true;
				}
				else
				{
					m_bCollideState = false;

				}
			}
		}
	}

	for (int i = 0; i < m_nObjects; i++) //빌딩과 캐릭터 충돌
	{
		for (int j = 0; j < m_nBuilding + 1; j++)
		{
			if (IsCollide(&m_pObjects[i], &m_pBuilding[j], m_fBuildingSize))
			{

				m_pObjects[i].SetPosition(3333, 333333, 3333); // 이거 삭제로 바꿀것
				m_pBuilding[j].DamageAnimate();
				m_pBuilding[j].IncreaseLife(-CHARACTER_LIFE);
				if (m_pBuilding[j].GetLife() < 0)
				{
					m_pBuilding[j].SetPosition(3333, 333333, 3333); // 이거 삭제로 바꿀것

				}
			}
		}
	}

	for (int i = 0; i < m_nObjects; ++i) //총알과 오브젝트 충돌
	{
		for (auto iter = m_pBuilding->m_listBullet.begin(); iter != m_pBuilding->m_listBullet.end(); ++iter)
		{
			float Distance = sqrt(pow((m_pObjects[i].GetPosition().x - (*iter)->GetPosition().x), 2) + pow((m_pObjects[i].GetPosition().y - (*iter)->GetPosition().y), 2) + pow((m_pObjects[i].GetPosition().z - (*iter)->GetPosition().z), 2));

			if (Distance < m_fObjectSize)
			{
				if (m_bCollideState_Bullet == false)
				{
					//cout << m_pObjects[0].GetLife() << endl;

					FLOAT3 swapDirection;
					swapDirection.x = m_pObjects[i].GetDirection().x;
					swapDirection.y = m_pObjects[i].GetDirection().y;
					swapDirection.z = m_pObjects[i].GetDirection().z;

					m_pObjects[i].SetDirection((*iter)->GetDirection());
					//m_pObjects[i].SetPosition(m_pObjects[i].GetPosition().x + 2 *m_pObjects[j].GetDirection().x, m_pObjects[i].GetPosition().y + 2 * m_pObjects[j].GetDirection().y, m_pObjects[i].GetPosition().z + 2 * m_pObjects[j].GetDirection().z);
					m_pObjects[i].SetPosition(m_pObjects[i].GetPosition().x + 10 * (*iter)->GetDirection().x, m_pObjects[i].GetPosition().y + 10 * (*iter)->GetDirection().y, m_pObjects[i].GetPosition().z + 10 * (*iter)->GetDirection().z);

				
					//m_pObjects[i].SetDirection(Reflect(m_pObjects[i].GetDirection(),m_pObjects[j].GetDirection()));
					//m_pObjects[j].SetDirection(Reflect(m_pObjects[j].GetDirection(),swapDirection));


					//++m_iCollideCnt;

					//cout << m_iCollideCnt << endl;

					m_pObjects[i].IncreaseLife(-BULLET_LIFE);
				

					if (m_pObjects[i].GetLife() < 0)
					{
						m_pObjects[i].SetPosition(3333, 333333, 3333); // 이거 삭제로 바꿀것
					}
					
					m_bCollideState_Bullet = true;
					(*iter)->SetPosition(33333, 34433, 33333);

				}
				else
				{
					m_bCollideState_Bullet = false;

				}
			}
		}
	}

}

void Scene::ReflectDetection()
{

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
	for (int i = 0; i < m_nObjects; ++i)
	{
		//cout << m_pObjects[i].GetPosition().y << endl;
		if (m_pObjects[i].GetPosition().y > 250)
		{
			m_pObjects[i].SetDirection(Reflect(m_pObjects[i].GetDirection(), xup));
			m_pObjects[i].SetPosition(m_pObjects[i].GetPosition().x, m_pObjects[i].GetPosition().y - 1, m_pObjects[i].GetPosition().z);

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
			m_pObjects[i].SetPosition(m_pObjects[i].GetPosition().x + 1, m_pObjects[i].GetPosition().y, m_pObjects[i].GetPosition().z);

		}

		if (m_pObjects[i].GetPosition().x > 250)
		{
			m_pObjects[i].SetDirection(Reflect(m_pObjects[i].GetDirection(), yright));
			m_pObjects[i].SetPosition(m_pObjects[i].GetPosition().x - 1, m_pObjects[i].GetPosition().y, m_pObjects[i].GetPosition().z);

		}
	}
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
			m_pBuilding[m_nBuilding].SetLife(BUILDING_LIFE);
			m_nBuilding++;

		}
		break;
		
	case OBJECT_BULLET:
		break;

	case OBJECT_CHARACTER:
		default_random_engine dre;
		uniform_real_distribution<> urmovingdirect(-0.35f, 0.255f);
		dre.seed(time(NULL)); //매번달라지게하기위해 seed값을줌


		m_pObjects[m_nObjects].SetPosition(x, y, 0);
		m_pObjects[m_nObjects].SetDirection(urmovingdirect(dre), urmovingdirect(dre), 0);
		m_pObjects[m_nObjects].SetLife(CHARACTER_LIFE);
		//m_pObjects[m_nObjects].SetLifeTime(clock());

		if (m_nObjects < MAX_OBJECTS_COUNT)
		{
			m_nObjects++;

		}
		//m_pobjects[i].setoobb(ur_center,m_fobjectsize);


		break;

	}
}
void Scene::Release()
{
	delete[] m_pObjects;
	delete g_Renderer;


}
