#include "stdafx.h"
#include "Scene.h"


Scene::Scene()
{
	m_fObjectSize = 10;
	m_fBuildingSize = 100;
	m_iColorTimer = 0;
	m_nObjects = 0;
	m_nBuilding = 0;
	m_nEnemy = 0;
	m_nBullet = 0;
	m_nArrow = 0;
	m_nObjects_NORTH = 0;
	m_iCollideCnt = 0;
	m_fNorthEnemyCreateTimer = 0;
	m_fBulletSize = 8;
	m_fArrowSize = 8;

	m_bCollideState = false;
	m_bCollideState_NORTH = false;
	m_bCollideState_Bullet = false;
	m_bCollideState_Bullet_NORTH = false;
	m_bCollideState_BuildingBullet_BuildingNorth = false;
	m_bCollideState_BuildingNorthBullet_Building = false;

	m_Buildingtexture = g_Renderer->CreatePngTexture("../Textures/PNGs/Grass28.png");
	m_Buildingtexture_NORTH = g_Renderer->CreatePngTexture("../Textures/PNGs/Tree.png");
	m_BackGroundTexture = g_Renderer->CreatePngTexture("../Textures/PNGs/Background.png");
	m_AnimationTexture = g_Renderer->CreatePngTexture("../Textures/PNGs/Animation.png");
	m_AnimationTexture_NORTH = g_Renderer->CreatePngTexture("../Textures/PNGs/Animation_NORTH.png");
	m_ParticleTextureBullet = g_Renderer->CreatePngTexture("../Textures/PNGs/Particle.png");
	BuildObject();


	// Initialize Renderer
	g_Renderer = new Renderer(WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}

}

Scene::~Scene()
{


}

void Scene::BuildObject()
{
	m_pObjects = new Player[MAX_OBJECTS_COUNT];
	m_pObjects_NORTH = new Player[MAX_OBJECTS_COUNT];

	AddActorObject(-150,-300, OBJECT_BUILDING_SOUTH);
	AddActorObject(0, -300, OBJECT_BUILDING_SOUTH);
	AddActorObject(150, -300, OBJECT_BUILDING_SOUTH);

	AddActorObject(-150, 300, OBJECT_BUILDING_NORTH);
	AddActorObject(0, 300, OBJECT_BUILDING_NORTH);
	AddActorObject(150, 300, OBJECT_BUILDING_NORTH);

}
void Scene::NorthEnemyCreate(DWORD elapsedTime)
{
	m_fNorthEnemyCreateTimer += elapsedTime;

	//cout << m_fNorthEnemyCreateTimer << endl;

	if (m_fNorthEnemyCreateTimer / 1000 > 5)
	{
		//cout << " 자동생성" << endl;
		AddActorObject(0, 0, OBJECT_CHARACTER_NORTH);
		m_fNorthEnemyCreateTimer = 0;
	}

	for (int i = 0; i < m_nObjects_NORTH; ++i)
	{
		//cout << m_pObjects_NORTH[i].GetPosition().x << "\t" << m_pObjects_NORTH[i].GetPosition().y << "\t" << m_pObjects_NORTH[i].GetPosition().z << endl;
	}
}
void Scene::UpdateObject(DWORD elapsedTime)
{
	
	for (int i = 0; i < m_nObjects; ++i)
	{
		m_pObjects[i].Update(elapsedTime);

	}

	for (int i = 0; i < m_nObjects_NORTH; ++i)
	{
		m_pObjects_NORTH[i].Update(elapsedTime);

	}

	for (int i = 0; i < m_nBuilding; ++i)
	{
		m_pBuilding[i].Update(elapsedTime);

	}

	for (int i = 0; i < m_nBuilding_NORTH; ++i)
	{
		m_pBuilding_NORTH[i].Update(elapsedTime);

	}
	Animate();
	NorthEnemyCreate(elapsedTime);

	//cout << m_pObjects[0].m_CircleCollider.m_f3Center.x << "\t" << m_pObjects[0].m_CircleCollider.m_f3Center.y << "\t" << m_pObjects[0].m_CircleCollider.m_f3Center.z << endl;


}

void Scene::Render()
{
	//cout << "Render()" << endl;

	//cout << m_pObjects[0].GetPosition().x << "\t" << m_pObjects[0].GetPosition().y << endl;
	for (int i = 0; i < m_nObjects; ++i)
	{
		g_Renderer->DrawTexturedRectSeq(m_pObjects[i].GetPosition().x,
			m_pObjects[i].GetPosition().y,
			m_pObjects[i].GetPosition().z,
			50, 1, 1, 1, 1, m_AnimationTexture, m_iAnimationFrame/2, 0, 6,1, 0.3);

		//g_Renderer->DrawSolidRect(m_pObjects[i].GetPosition().x/*x좌표*/,
		//	m_pObjects[i].GetPosition().y/*y좌표*/,
		//	m_pObjects[i].GetPosition().z/*z좌표*/,
		//	m_fObjectSize,/*크기*/
		//	m_pObjects[i].GetColor().r/*red*/, m_pObjects[i].GetColor().g/*green*/, m_pObjects[i].GetColor().b/*blue*/, m_pObjects[i].GetColor().a/*alpha*/,0.2);

		g_Renderer->DrawSolidRectGauge(m_pObjects[i].GetPosition().x/*x좌표*/,
			m_pObjects[i].GetPosition().y + 30/*y좌표*/,
			m_pObjects[i].GetPosition().z/*z좌표*/,
			50, 10,
			0, 0, 1, 1,
			m_pObjects[i].GetLife() / (float)10, 0.2);
		
	}
	 
	for (int i = 0; i < m_nObjects_NORTH; ++i)
	{
		g_Renderer->DrawTexturedRectSeq(m_pObjects_NORTH[i].GetPosition().x,
			m_pObjects_NORTH[i].GetPosition().y,
			m_pObjects_NORTH[i].GetPosition().z,
			50, 1, 1, 1, 1, m_AnimationTexture_NORTH, m_iAnimationFrame / 2, 0, 6, 1, 0.3);

		//g_Renderer->DrawSolidRect(m_pObjects_NORTH[i].GetPosition().x/*x좌표*/,
		//	m_pObjects_NORTH[i].GetPosition().y/*y좌표*/,
		//	m_pObjects_NORTH[i].GetPosition().z/*z좌표*/,
		//	m_fObjectSize,/*크기*/
		//	m_pObjects_NORTH[i].GetColor().r/*red*/, m_pObjects_NORTH[i].GetColor().g/*green*/, m_pObjects_NORTH[i].GetColor().b/*blue*/, m_pObjects_NORTH[i].GetColor().a/*alpha*/,0.2);

		g_Renderer->DrawSolidRectGauge(m_pObjects_NORTH[i].GetPosition().x/*x좌표*/,
			m_pObjects_NORTH[i].GetPosition().y + 30/*y좌표*/,
			m_pObjects_NORTH[i].GetPosition().z/*z좌표*/,
			50, 10,
			0, 0, 1, 1,
			m_pObjects_NORTH[i].GetLife() / (float)10, 0.2);
	}


	for (int i = 0; i < m_nBuilding; ++i)
	{
		g_Renderer->DrawTexturedRect(m_pBuilding[i].GetPosition().x/*x좌표*/,
			m_pBuilding[i].GetPosition().y/*y좌표*/,
			m_pBuilding[i].GetPosition().z/*z좌표*/,
			m_fBuildingSize,/*크기*/
			m_pBuilding[i].GetColor().r/*red*/, m_pBuilding[i].GetColor().g/*green*/, m_pBuilding[i].GetColor().b/*blue*/, m_pBuilding[i].GetColor().a/*alpha*/, m_Buildingtexture,0.1);

		g_Renderer->DrawSolidRectGauge(m_pBuilding[i].GetPosition().x/*x좌표*/,
			m_pBuilding[i].GetPosition().y + 50/*y좌표*/,
			m_pBuilding[i].GetPosition().z/*z좌표*/,
			100, 10,
			0, 0, 1, 1,
			(float)m_pBuilding[i].GetLife() / (float)40, 0.2);
	}

	for (int i = 0; i < m_nBuilding_NORTH; ++i)
	{
		g_Renderer->DrawTexturedRect(m_pBuilding_NORTH[i].GetPosition().x/*x좌표*/,
			m_pBuilding_NORTH[i].GetPosition().y/*y좌표*/,
			m_pBuilding_NORTH[i].GetPosition().z/*z좌표*/,
			m_fBuildingSize,/*크기*/
			m_pBuilding_NORTH[i].GetColor().r/*red*/, m_pBuilding_NORTH[i].GetColor().g/*green*/, m_pBuilding_NORTH[i].GetColor().b/*blue*/, m_pBuilding_NORTH[i].GetColor().a/*alpha*/, m_Buildingtexture_NORTH, 0.1);

		g_Renderer->DrawSolidRectGauge(m_pBuilding_NORTH[i].GetPosition().x/*x좌표*/,
			m_pBuilding_NORTH[i].GetPosition().y + 50/*y좌표*/,
			m_pBuilding_NORTH[i].GetPosition().z/*z좌표*/,
			100, 10,
			1, 0, 0, 1,
			(float)m_pBuilding_NORTH[i].GetLife() / (float)40, 0.2);
	}

	g_Renderer->DrawTexturedRect(0/*x좌표*/,
		0/*y좌표*/,
		0/*z좌표*/,
		800,/*크기*/
		1/*red*/, 1/*green*/, 1/*blue*/, 1/*alpha*/, m_BackGroundTexture, 0.99);



	
	cout << m_iScene_ElapsedTime << endl;

	for (int i = 0; i < m_nBuilding; ++i)
	{
		for (auto iter = m_pBuilding[i].m_listBullet.begin(); iter != m_pBuilding[i].m_listBullet.end(); ++iter)
		{
			g_Renderer->DrawParticle((*iter)->GetPosition().x, (*iter)->GetPosition().y, (*iter)->GetPosition().z, 10, 1, 1, 1, 1, -((*iter)->GetDirection().x), -((*iter)->GetDirection().y), m_ParticleTextureBullet, m_iScene_ElapsedTime / (float)1000);
			g_Renderer->DrawSolidRect((*iter)->GetPosition().x, (*iter)->GetPosition().y, (*iter)->GetPosition().z, m_fBulletSize, (*iter)->GetColor().r, (*iter)->GetColor().g, (*iter)->GetColor().b, (*iter)->GetColor().a,0.3);
		}
	}
	
	for (int i = 0; i < m_nBuilding_NORTH; ++i)
	{
		for (auto iter = m_pBuilding_NORTH[i].m_listBullet.begin(); iter != m_pBuilding_NORTH[i].m_listBullet.end(); ++iter)
		{
			g_Renderer->DrawParticle((*iter)->GetPosition().x, (*iter)->GetPosition().y, (*iter)->GetPosition().z, 10, 1, 1, 1, 1, -((*iter)->GetDirection().x), -((*iter)->GetDirection().y), m_ParticleTextureBullet, m_iScene_ElapsedTime / (float)1000);
			g_Renderer->DrawSolidRect((*iter)->GetPosition().x, (*iter)->GetPosition().y, (*iter)->GetPosition().z, m_fBulletSize, (*iter)->GetColor().r, (*iter)->GetColor().g, (*iter)->GetColor().b, (*iter)->GetColor().a, 0.3);
		}
	}

	for (int i = 0; i < m_nObjects; ++i)
	{
		for (auto iter = m_pObjects[i].m_listArrow.begin(); iter != m_pObjects[i].m_listArrow.end(); ++iter)
		{
			//g_Renderer->DrawParticle((*iter)->GetPosition().x, (*iter)->GetPosition().y, (*iter)->GetPosition().z, 10, 1, 1, 1, 1, -((*iter)->GetDirection().x), -((*iter)->GetDirection().y), m_ParticleTextureBullet, m_iScene_ElapsedTime / (float)1000);
			g_Renderer->DrawSolidRect((*iter)->GetPosition().x, (*iter)->GetPosition().y, (*iter)->GetPosition().z, m_fArrowSize, (*iter)->GetColor().r, (*iter)->GetColor().g, (*iter)->GetColor().b, (*iter)->GetColor().a,0.3);
		}
	}

	for (int i = 0; i < m_nObjects_NORTH; ++i)
	{
		for (auto iter = m_pObjects_NORTH[i].m_listArrow.begin(); iter != m_pObjects_NORTH[i].m_listArrow.end(); ++iter)
		{
			//g_Renderer->DrawParticle((*iter)->GetPosition().x, (*iter)->GetPosition().y, (*iter)->GetPosition().z, 10, 1, 1, 1, 1, -((*iter)->GetDirection().x), -((*iter)->GetDirection().y), m_ParticleTextureBullet, m_iScene_ElapsedTime / (float)1000);
			g_Renderer->DrawSolidRect((*iter)->GetPosition().x, (*iter)->GetPosition().y, (*iter)->GetPosition().z, m_fArrowSize, (*iter)->GetColor().r, (*iter)->GetColor().g, (*iter)->GetColor().b, (*iter)->GetColor().a,0.3);
		}
	}

}

void Scene::Animate()
{
	if (m_iAnimationFrameCnt > 18)
	{
		++m_iAnimationFrame;
		m_iAnimationFrameCnt = 0;
	}
	++ m_iAnimationFrameCnt;

	++m_iColorTimer;

	ColideDetection();
	ReflectDetection();

	/*if (m_iColorTimer > 200)
	{
		m_iColorTimer = 0;
		for (int i = 0; i < m_nObjects; ++i)
		{
			m_pObjects[i].SetColor(1, 1, 1, 1);
		}

	}*/
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_pObjects[i].GetLifeTime() > OBJECT_DELETE_TIME)
		{
			m_pObjects[i].SetPosition(3853, 333333, 3333); // 이거 삭제로 바꿀것

		}
	}
	
	for(int i = 0; i < m_nBuilding;++i)
		m_pBuilding[i].BulletShot(OBJECT_BUILDING_SOUTH);

	for (int i = 0; i < m_nBuilding_NORTH; ++i)
		m_pBuilding_NORTH[i].BulletShot(OBJECT_BUILDING_NORTH);

	for (int i = 0; i < m_nObjects; ++i)
		m_pObjects[i].BulletShot();
	for (int i = 0; i < m_nObjects_NORTH; ++i)
		m_pObjects_NORTH[i].BulletShot();

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

					/*m_pObjects[i].SetColor(255, 0, 0, 1);
					m_pObjects[j].SetColor(255, 0, 0, 1);*/
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

	//////////////

	for (int i = 0; i < m_nObjects_NORTH; i++)
	{
		for (int j = (i + 1); j < m_nObjects_NORTH; j++) //충돌체크 i= i끼리 할필요없고 i랑j 했으면 j랑i는 할필요 없어서 이렇게 for문 돌리는거임
		{
			if (IsCollide(&m_pObjects_NORTH[i], &m_pObjects_NORTH[j], m_fObjectSize))
			{
				if (m_bCollideState_NORTH == false)
				{
					//cout << m_pObjects[0].GetLife() << endl;

					FLOAT3 swapDirection;
					swapDirection.x = m_pObjects_NORTH[i].GetDirection().x;
					swapDirection.y = m_pObjects_NORTH[i].GetDirection().y;
					swapDirection.z = m_pObjects_NORTH[i].GetDirection().z;

					m_pObjects_NORTH[i].SetDirection(m_pObjects_NORTH[j].GetDirection());
					//m_pObjects[i].SetPosition(m_pObjects[i].GetPosition().x + 2 *m_pObjects[j].GetDirection().x, m_pObjects[i].GetPosition().y + 2 * m_pObjects[j].GetDirection().y, m_pObjects[i].GetPosition().z + 2 * m_pObjects[j].GetDirection().z);
					m_pObjects_NORTH[i].SetPosition(m_pObjects_NORTH[i].GetPosition().x + 10 * m_pObjects_NORTH[j].GetDirection().x, m_pObjects_NORTH[i].GetPosition().y + 10 * m_pObjects_NORTH[j].GetDirection().y, m_pObjects_NORTH[i].GetPosition().z + 10 * m_pObjects_NORTH[j].GetDirection().z);

					m_pObjects_NORTH[j].SetDirection(swapDirection);
					m_pObjects_NORTH[j].SetPosition(m_pObjects_NORTH[j].GetPosition().x + 10 * swapDirection.x, m_pObjects_NORTH[j].GetPosition().y + 10 * swapDirection.y, m_pObjects_NORTH[j].GetPosition().z + 10 * swapDirection.z);

					//m_pObjects[i].SetDirection(Reflect(m_pObjects[i].GetDirection(),m_pObjects[j].GetDirection()));
					//m_pObjects[j].SetDirection(Reflect(m_pObjects[j].GetDirection(),swapDirection));

					
					//++m_iCollideCnt;

					//cout << m_iCollideCnt << endl;

					m_bCollideState_NORTH = true;
				}
				else
				{
					m_bCollideState_NORTH = false;

				}
			}
		}
	}

	//for (int i = 0; i < m_nObjects; i++) //빌딩과 캐릭터 충돌
	//{
	//	for (int j = 0; j < m_nBuilding; j++)
	//	{
	//		if (IsCollide(&m_pObjects[i], &m_pBuilding[j], m_fBuildingSize))
	//		{

	//			m_pObjects[i].SetPosition(3333, 333333, 3333); // 이거 삭제로 바꿀것
	//			m_pBuilding[j].DamageAnimate();
	//			m_pBuilding[j].IncreaseLife(-CHARACTER_LIFE);
	//			if (m_pBuilding[j].GetLife() < 0)
	//			{
	//				m_pBuilding[j].SetPosition(3333, 333333, 3333); // 이거 삭제로 바꿀것

	//			}
	//		}
	//	}
	//}

	for (int i = 0; i < m_nObjects; i++) //빌딩과 캐릭터 충돌
	{
		for (int j = 0; j < m_nBuilding_NORTH; j++)
		{
			if (IsCollide(&m_pObjects[i], &m_pBuilding_NORTH[j], m_fBuildingSize / (float)2))
			{

				m_pObjects[i].SetPosition(3333, 333333, 3333); // 이거 삭제로 바꿀것
				m_pBuilding_NORTH[j].DamageAnimate();
				if (m_pBuilding_NORTH[j].GetLife() > 0)
					m_pBuilding_NORTH[j].IncreaseLife(-CHARACTER_LIFE);
				if (m_pBuilding_NORTH[j].GetLife() <= 0)
				{
					m_pBuilding_NORTH[j].SetPosition(3333, 333333, 3333); // 이거 삭제로 바꿀것

				}
			}
		}
	}

	for (int i = 0; i < m_nObjects_NORTH; i++) //빌딩과 캐릭터_NORTH 충돌
	{
		for (int j = 0; j < m_nBuilding; j++)
		{
			if (IsCollide(&m_pObjects_NORTH[i], &m_pBuilding[j], m_fBuildingSize / (float)2))
			{

				m_pObjects_NORTH[i].SetPosition(3333, 333333, 3333); // 이거 삭제로 바꿀것
				m_pBuilding[j].DamageAnimate();
				if (m_pBuilding[j].GetLife() > 0)
					m_pBuilding[j].IncreaseLife(-CHARACTER_LIFE);
				if (m_pBuilding[j].GetLife() <= 0)
				{
					m_pBuilding[j].SetPosition(3333, 333333, 3333); // 이거 삭제로 바꿀것

				}
			}
		}
	}


	//for (int i = 0; i < m_nObjects; ++i) //빌딩의총알과 오브젝트 충돌
	//{
	//	for (auto iter = m_pBuilding->m_listBullet.begin(); iter != m_pBuilding->m_listBullet.end(); ++iter)
	//	{
	//		float Distance = sqrt(pow((m_pObjects[i].GetPosition().x - (*iter)->GetPosition().x), 2) + pow((m_pObjects[i].GetPosition().y - (*iter)->GetPosition().y), 2) + pow((m_pObjects[i].GetPosition().z - (*iter)->GetPosition().z), 2));

	//		if (Distance < m_fObjectSize)
	//		{
	//			if (m_bCollideState_Bullet == false)
	//			{
	//				//cout << m_pObjects[0].GetLife() << endl;

	//				FLOAT3 swapDirection;
	//				swapDirection.x = m_pObjects[i].GetDirection().x;
	//				swapDirection.y = m_pObjects[i].GetDirection().y;
	//				swapDirection.z = m_pObjects[i].GetDirection().z;

	//				m_pObjects[i].SetDirection((*iter)->GetDirection());
	//				//m_pObjects[i].SetPosition(m_pObjects[i].GetPosition().x + 2 *m_pObjects[j].GetDirection().x, m_pObjects[i].GetPosition().y + 2 * m_pObjects[j].GetDirection().y, m_pObjects[i].GetPosition().z + 2 * m_pObjects[j].GetDirection().z);
	//				m_pObjects[i].SetPosition(m_pObjects[i].GetPosition().x + 10 * (*iter)->GetDirection().x, m_pObjects[i].GetPosition().y + 10 * (*iter)->GetDirection().y, m_pObjects[i].GetPosition().z + 10 * (*iter)->GetDirection().z);

	//				//.

	//				//m_pObjects[i].SetDirection(Reflect(m_pObjects[i].GetDirection(),m_pObjects[j].GetDirection()));
	//				//m_pObjects[j].SetDirection(Reflect(m_pObjects[j].GetDirection(),swapDirection));


	//				//++m_iCollideCnt;

	//				//cout << m_iCollideCnt << endl;

	//				m_pObjects[i].IncreaseLife(-BULLET_LIFE);
	//			

	//				if (m_pObjects[i].GetLife() < 0)
	//				{
	//					m_pObjects[i].SetPosition(3333, 333333, 3333); // 이거 삭제로 바꿀것
	//				}
	//				
	//				m_bCollideState_Bullet = true;
	//				(*iter)->SetPosition(33333, 34433, 33333);

	//			}
	//			else
	//			{
	//				m_bCollideState_Bullet = false;

	//			}
	//		}
	//	}
	//}



	for (int i = 0; i < m_nObjects; ++i) //빌딩_NORTH 총알과 오브젝트 충돌
	{
		for (auto iter = m_pBuilding_NORTH->m_listBullet.begin(); iter != m_pBuilding_NORTH->m_listBullet.end(); ++iter)
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

					//.

					//m_pObjects[i].SetDirection(Reflect(m_pObjects[i].GetDirection(),m_pObjects[j].GetDirection()));
					//m_pObjects[j].SetDirection(Reflect(m_pObjects[j].GetDirection(),swapDirection));


					//++m_iCollideCnt;

					//cout << m_iCollideCnt << endl;

					if (m_pObjects[i].GetLife() > 0)
					m_pObjects[i].IncreaseLife(-BULLET_LIFE);


					if (m_pObjects[i].GetLife() <= 0)
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

	//빌딩 총알과 OBJECT_NORT 충돌 체크
	for (int i = 0; i < m_nObjects_NORTH; ++i) //빌딩_NORTH 총알과 오브젝트 충돌
	{
		for (auto iter = m_pBuilding->m_listBullet.begin(); iter != m_pBuilding->m_listBullet.end(); ++iter)
		{
			float Distance = sqrt(pow((m_pObjects_NORTH[i].GetPosition().x - (*iter)->GetPosition().x), 2) + pow((m_pObjects_NORTH[i].GetPosition().y - (*iter)->GetPosition().y), 2) + pow((m_pObjects_NORTH[i].GetPosition().z - (*iter)->GetPosition().z), 2));

			if (Distance < m_fObjectSize)
			{
				if (m_bCollideState_Bullet_NORTH == false)
				{
					//cout << m_pObjects[0].GetLife() << endl;

					FLOAT3 swapDirection;
					swapDirection.x = m_pObjects_NORTH[i].GetDirection().x;
					swapDirection.y = m_pObjects_NORTH[i].GetDirection().y;
					swapDirection.z = m_pObjects_NORTH[i].GetDirection().z;

					m_pObjects_NORTH[i].SetDirection((*iter)->GetDirection());
					//m_pObjects[i].SetPosition(m_pObjects[i].GetPosition().x + 2 *m_pObjects[j].GetDirection().x, m_pObjects[i].GetPosition().y + 2 * m_pObjects[j].GetDirection().y, m_pObjects[i].GetPosition().z + 2 * m_pObjects[j].GetDirection().z);
					m_pObjects_NORTH[i].SetPosition(m_pObjects_NORTH[i].GetPosition().x + 10 * (*iter)->GetDirection().x, m_pObjects_NORTH[i].GetPosition().y + 10 * (*iter)->GetDirection().y, m_pObjects_NORTH[i].GetPosition().z + 10 * (*iter)->GetDirection().z);

					//.

					//m_pObjects[i].SetDirection(Reflect(m_pObjects[i].GetDirection(),m_pObjects[j].GetDirection()));
					//m_pObjects[j].SetDirection(Reflect(m_pObjects[j].GetDirection(),swapDirection));


					//++m_iCollideCnt;

					//cout << m_iCollideCnt << endl;

					if (m_pObjects_NORTH[i].GetLife() > 0)
						m_pObjects_NORTH[i].IncreaseLife(-BULLET_LIFE);


					if (m_pObjects_NORTH[i].GetLife() <= 0)
					{
						m_pObjects_NORTH[i].SetPosition(3333, 333333, 3333); // 이거 삭제로 바꿀것
					}

					m_bCollideState_Bullet_NORTH = true;
					(*iter)->SetPosition(33333, 34433, 33333);

				}
				else
				{
					m_bCollideState_Bullet_NORTH = false;

				}
			}
		}
	}



	//오브젝트_NORTH 쏜 Arrow랑 Building 충돌 검사
	for (int i = 0; i < m_nObjects_NORTH; ++i)
	{
		for (auto iter = m_pObjects_NORTH[i].m_listArrow.begin(); iter != m_pObjects_NORTH[i].m_listArrow.end(); ++iter)
		{
			for (int j = 0; j < m_nBuilding; ++j)
			{
				float Distance = sqrt(pow((m_pBuilding[j].GetPosition().x - (*iter)->GetPosition().x), 2) + pow((m_pBuilding[j].GetPosition().y - (*iter)->GetPosition().y), 2) + pow((m_pBuilding[j].GetPosition().z - (*iter)->GetPosition().z), 2));
				if (Distance < 25)
				{
					(*iter)->SetPosition(3333, 333333, 3333); // 이거 삭제로 바꿀것
					m_pBuilding[j].DamageAnimate();

					if (m_pBuilding[j].GetLife() > 0)
					m_pBuilding[j].IncreaseLife(-ARROW_LIFE);
					if (m_pBuilding[j].GetLife() <= 0)
					{
						m_pBuilding[j].SetPosition(3333, 333333, 3333); // 이거 삭제로 바꿀것

					}
				}
				//cout << "무한 " << endl;

			}


		}
	}

	//플레이어가 쏜 Arrow랑 Building)NORTH 충돌 검사
	for (int i = 0; i < m_nObjects; ++i)
	{
		for (auto iter = m_pObjects[i].m_listArrow.begin(); iter != m_pObjects[i].m_listArrow.end(); ++iter)
		{
			for (int j = 0; j < m_nBuilding_NORTH; ++j)
			{
				float Distance = sqrt(pow((m_pBuilding_NORTH[j].GetPosition().x - (*iter)->GetPosition().x), 2) + pow((m_pBuilding_NORTH[j].GetPosition().y - (*iter)->GetPosition().y), 2) + pow((m_pBuilding_NORTH[j].GetPosition().z - (*iter)->GetPosition().z), 2));
				if (Distance < 25)
				{
					(*iter)->SetPosition(3333, 333333, 3333); // 이거 삭제로 바꿀것
					m_pBuilding_NORTH[j].DamageAnimate();

					if (m_pBuilding_NORTH[j].GetLife() > 0)
					m_pBuilding_NORTH[j].IncreaseLife(-ARROW_LIFE);
					if (m_pBuilding_NORTH[j].GetLife() <= 0)
					{
						m_pBuilding_NORTH[j].SetPosition(3333, 333333, 3333); // 이거 삭제로 바꿀것

					}
				}
				//cout << "무한 " << endl;

			}


		}
	}


	//플레이어가 쏜 Arrow랑 오브젝트_NORTH끼리 충돌검사
	for (int i = 0; i < m_nObjects; ++i)
	{
		for (auto iter = m_pObjects[i].m_listArrow.begin(); iter != m_pObjects[i].m_listArrow.end(); ++iter)
		{
			for (int j = 0; j < m_nObjects_NORTH; ++j)
			{
				float Distance = sqrt(pow((m_pObjects_NORTH[j].GetPosition().x - (*iter)->GetPosition().x), 2) + pow((m_pObjects_NORTH[j].GetPosition().y - (*iter)->GetPosition().y), 2) + pow((m_pObjects_NORTH[j].GetPosition().z - (*iter)->GetPosition().z), 2));
				if (Distance < 15 &&	i!=j/*m_pObjects[i].GetPosition().x != m_pObjects[j].GetPosition().x && m_pObjects[i].GetPosition().y != m_pObjects[j].GetPosition().y*/)
				{
					(*iter)->SetPosition(3333, 333333, 3333); // 이거 삭제로 바꿀것

					if (m_pObjects_NORTH[j].GetLife() > 0)
					m_pObjects_NORTH[j].IncreaseLife(-ARROW_LIFE);
					m_pObjects_NORTH[j].SetDirection((*iter)->GetDirection().x * 0.5, (*iter)->GetDirection().y * 0.5 , (*iter)->GetDirection().z * 0.5);
					if (m_pObjects_NORTH[j].GetLife() <= 0)
					{
						m_pObjects_NORTH[j].SetPosition(3333, 333333, 3333); // 이거 삭제로 바꿀것

					}
				}
				//cout << "무한 " << endl;

			}


		}
	}



	//빌딩 총알과 빌딩 충돌체크
	//1. 빌딩이 쏜 총알이 빌딩_NORTH와 충돌한경우
	for (int i = 0; i < m_nBuilding_NORTH; ++i) 
	{
		for (int j = 0; j < m_nBuilding; ++j)
		{
			for (auto iter = m_pBuilding[j].m_listBullet.begin(); iter != m_pBuilding[j].m_listBullet.end(); ++iter)
			{
				float Distance = sqrt(pow((m_pBuilding_NORTH[i].GetPosition().x - (*iter)->GetPosition().x), 2) + pow((m_pBuilding_NORTH[i].GetPosition().y - (*iter)->GetPosition().y), 2) + pow((m_pBuilding_NORTH[i].GetPosition().z - (*iter)->GetPosition().z), 2));

				if (Distance < 20)
				{
					if (m_bCollideState_BuildingBullet_BuildingNorth == false)
					{
						//cout << m_pObjects[0].GetLife() << endl;
						cout << "남쪽에서 쏜 총알에 북쪽이 맞았습니다." << endl;

						if (m_pBuilding_NORTH[i].GetLife() > 0)
						m_pBuilding_NORTH[i].IncreaseLife(-BULLET_LIFE);


						if (m_pBuilding_NORTH[i].GetLife() <= 0)
						{
							m_pBuilding_NORTH[i].SetPosition(3333, 333333, 3333); // 이거 삭제로 바꿀것
						}

						m_bCollideState_BuildingBullet_BuildingNorth = true;
						(*iter)->SetPosition(33333, 34433, 33333);

					}
					else
					{
						m_bCollideState_BuildingBullet_BuildingNorth = false;

					}
				}
			}
		}
		
	}



	//2. 빌딩_NORTH가 쏜 총알이 빌딩과 충돌한 경우
	for (int i = 0; i < m_nBuilding; ++i) //빌딩의총알과 오브젝트 충돌
	{
		for (int j = 0; j < m_nBuilding_NORTH; ++j)
		{
			for (auto iter = m_pBuilding_NORTH[j].m_listBullet.begin(); iter != m_pBuilding_NORTH[j].m_listBullet.end(); ++iter)
			{
				float Distance = sqrt(pow((m_pBuilding[i].GetPosition().x - (*iter)->GetPosition().x), 2) + pow((m_pBuilding[i].GetPosition().y - (*iter)->GetPosition().y), 2) + pow((m_pBuilding[i].GetPosition().z - (*iter)->GetPosition().z), 2));

				if (Distance < 20)
				{
					if (m_bCollideState_BuildingNorthBullet_Building == false)
					{
						//cout << m_pObjects[0].GetLife() << endl;
						cout << "북쪽에서 쏜 총알에 남쪽이이 맞았습니다." << endl;


						if (m_pBuilding[i].GetLife() > 0)
						m_pBuilding[i].IncreaseLife(-BULLET_LIFE);


						if (m_pBuilding[i].GetLife() <= 0)
						{
							m_pBuilding[i].SetPosition(3333, 333333, 3333); // 이거 삭제로 바꿀것
						}

						m_bCollideState_BuildingNorthBullet_Building = true;
						(*iter)->SetPosition(33333, 34433, 33333);

					}
					else
					{
						m_bCollideState_BuildingNorthBullet_Building = false;

					}
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
	//요깅
	for (int i = 0; i < m_nObjects; ++i)
	{
		//cout << m_pObjects[i].GetPosition().y << endl;
		if (m_pObjects[i].GetPosition().y > WINDOW_HEIGHT / 2 )
		{
			m_pObjects[i].SetDirection(Reflect(m_pObjects[i].GetDirection(), xup));
			m_pObjects[i].SetPosition(m_pObjects[i].GetPosition().x, m_pObjects[i].GetPosition().y - 1, m_pObjects[i].GetPosition().z);

		}

		//cout << m_pObjects[i].GetPosition().y << endl;
		if (m_pObjects[i].GetPosition().y < -WINDOW_HEIGHT / 2)
		{
			m_pObjects[i].SetDirection(Reflect(m_pObjects[i].GetDirection(), xdown));
			m_pObjects[i].SetPosition(m_pObjects[i].GetPosition().x, m_pObjects[i].GetPosition().y + 1, m_pObjects[i].GetPosition().z);

		}

		if (m_pObjects[i].GetPosition().x < -WINDOW_WIDTH/2)
		{
			m_pObjects[i].SetDirection(Reflect(m_pObjects[i].GetDirection(), yleft));
			m_pObjects[i].SetPosition(m_pObjects[i].GetPosition().x + 1, m_pObjects[i].GetPosition().y, m_pObjects[i].GetPosition().z);

		}

		if (m_pObjects[i].GetPosition().x > WINDOW_WIDTH / 2)
		{
			m_pObjects[i].SetDirection(Reflect(m_pObjects[i].GetDirection(), yright));
			m_pObjects[i].SetPosition(m_pObjects[i].GetPosition().x - 1, m_pObjects[i].GetPosition().y, m_pObjects[i].GetPosition().z);

		}
	}

	/////
	for (int i = 0; i < m_nObjects_NORTH; ++i)
	{
		//cout << m_pObjects[i].GetPosition().y << endl;
		if (m_pObjects_NORTH[i].GetPosition().y > WINDOW_HEIGHT / 2)
		{
			m_pObjects_NORTH[i].SetDirection(Reflect(m_pObjects_NORTH[i].GetDirection(), xup));
			m_pObjects_NORTH[i].SetPosition(m_pObjects_NORTH[i].GetPosition().x, m_pObjects_NORTH[i].GetPosition().y - 1, m_pObjects_NORTH[i].GetPosition().z);

		}

		//cout << m_pObjects[i].GetPosition().y << endl;
		if (m_pObjects_NORTH[i].GetPosition().y < -WINDOW_HEIGHT / 2)
		{
			m_pObjects_NORTH[i].SetDirection(Reflect(m_pObjects_NORTH[i].GetDirection(), xdown));
			m_pObjects_NORTH[i].SetPosition(m_pObjects_NORTH[i].GetPosition().x, m_pObjects_NORTH[i].GetPosition().y + 1, m_pObjects_NORTH[i].GetPosition().z);

		}

		if (m_pObjects_NORTH[i].GetPosition().x < -WINDOW_WIDTH / 2)
		{
			m_pObjects_NORTH[i].SetDirection(Reflect(m_pObjects_NORTH[i].GetDirection(), yleft));
			m_pObjects_NORTH[i].SetPosition(m_pObjects_NORTH[i].GetPosition().x + 1, m_pObjects_NORTH[i].GetPosition().y, m_pObjects_NORTH[i].GetPosition().z);

		}

		if (m_pObjects_NORTH[i].GetPosition().x > WINDOW_WIDTH / 2)
		{
			m_pObjects_NORTH[i].SetDirection(Reflect(m_pObjects_NORTH[i].GetDirection(), yright));
			m_pObjects_NORTH[i].SetPosition(m_pObjects_NORTH[i].GetPosition().x - 1, m_pObjects_NORTH[i].GetPosition().y, m_pObjects_NORTH[i].GetPosition().z);

		}
	}
}
FLOAT3 Scene::Reflect(FLOAT3 direction, FLOAT3 normal)
{
	FLOAT3 reflectionVector;

	using namespace Vector3;


	reflectionVector = Add(direction, Multiple(Multiple(normal, 2), DotProduct(Multiple(direction, -1), normal)));
	//R = P + 2n(-P 내적 n)

	Vector3::Normalize(reflectionVector);
	return reflectionVector;
}
void Scene::AddActorObject(float x, float y, int objectType)
{
	switch (objectType)
	{
	case OBJECT_ARROW:

		break;

	case OBJECT_BUILDING_SOUTH:
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
	case OBJECT_BUILDING_NORTH:
		if (m_pBuilding_NORTH == NULL)
		{
			m_pBuilding_NORTH = new Building[MAX_BUILDING_COUNT];

		}
		if (m_nBuilding_NORTH < MAX_BUILDING_COUNT)
		{
			m_pBuilding_NORTH[m_nBuilding_NORTH].SetPosition(x, y, 0);
			m_pBuilding_NORTH[m_nBuilding_NORTH].SetColor(1, 1, 0, 1);
			m_pBuilding_NORTH[m_nBuilding_NORTH].SetLife(BUILDING_LIFE);
			m_nBuilding_NORTH++;

		}
		break;


	case OBJECT_BULLET:
		break;

	case OBJECT_CHARACTER:
		
		if (m_iClickCnt < MAX_OBJECTS_COUNT)
		{
			//coolTime Check
			m_bCoolTimeOn = true;
			//coolTime Count On
			cout << x << "!" << y << endl;
			if (y > 0) y = 0;

			if (m_bCoolTimeFinish == true)
			{
				m_bCoolTimeFinish = false;
			
				m_pObjects[m_nObjects].SetPosition(x, y, 0);


				cout << m_pObjects[m_nObjects].GetPosition().x << "\t" << m_pObjects[m_nObjects].GetPosition().y << endl << "\t" << "유후" << endl;
				m_pObjects[m_nObjects].SetDirection((((float)std::rand() / (float)RAND_MAX) - 0.5f), (((float)std::rand() / (float)RAND_MAX) - 0.5f), 0);
				m_pObjects[m_nObjects].SetLife(CHARACTER_LIFE);
				//m_pObjects[m_nObjects].SetLifeTime(clock());

				if (m_nObjects < MAX_OBJECTS_COUNT)
				{
					m_nObjects++;

				}
				//cout << "생성해떠염" << endl;
				//m_pobjects[i].setoobb(ur_center,m_fobjectsize);


				break;
			}
			else
			{
				//cout << "생성못해염" << endl;
				break;

			}
		}
		m_iClickCnt++;
	case OBJECT_CHARACTER_NORTH:
		if (m_nObjects_NORTH < MAX_OBJECTS_COUNT)
		{
			//m_pObjects_NORTH[m_nObjects_NORTH].SetPosition((((float)std::rand() / (float)RAND_MAX) - 0.5f), (((float)std::rand() / (float)RAND_MAX) - 0.5f), 0);
			m_pObjects_NORTH[m_nObjects_NORTH].SetPosition((200 * ((float)std::rand() / (float)RAND_MAX) - 0.5f), (360 * ((float)std::rand() / (float)RAND_MAX)), 0);

			m_pObjects_NORTH[m_nObjects_NORTH].SetDirection((((float)std::rand() / (float)RAND_MAX) - 0.5f), (((float)std::rand() / (float)RAND_MAX)), 0);
			m_pObjects_NORTH[m_nObjects_NORTH].SetLife(CHARACTER_LIFE);
			m_pObjects_NORTH[m_nObjects_NORTH].SetColor(0, 0, 1, 1);
			m_nObjects_NORTH++;
			break;
		}
			break;

	
	}

}
void Scene::CoolTimeCount(DWORD elapsedTime)
{
	m_iScene_ElapsedTime += elapsedTime;

	
	//cout << "----------------------------------" << endl;
	//for (int i = 0; i < m_nBuilding_NORTH; ++i)
	//{
	//	cout << m_pBuilding_NORTH[i].GetLife() << endl;
	//}
	//cout << "----------------------------------" << endl;

	if (m_bCoolTimeOn == true)
	{
		m_fCoolTime += elapsedTime;
	
	}
	if (m_fCoolTime > 7000)
	{
		m_fCoolTime = 0;
		m_bCoolTimeFinish = true;
	}
	//cout << m_fCoolTime << endl;
	//cout << m_bCoolTimeFinish << endl;
}
void Scene::CoolTimeCheck()
{

}
void Scene::Release()
{
	
	delete[] m_pObjects;
	delete[] m_pObjects_NORTH;

	delete g_Renderer;
	delete[] m_pBuilding_NORTH;
	delete[] m_pBuilding;


}
