#include "stdafx.h"
#include "CObjectManager.h"
#include "CGameObject.h"
#include "CBullet.h"
#include "Framework.h"

CObjectManager::CObjectManager()
{
}


CObjectManager::~CObjectManager()
{
}

CGameObject* CObjectManager::FindGameObject(E_OBJECT objType, int idx)
{
	
	//_ObjMap.find(obj)
	for (unsigned int i = 0; i < m_ObjMap[objType].size(); ++i)
	{
		if (m_ObjMap[objType][i]->GetMyIdx() == idx)
			return m_ObjMap[objType][i];
	}
	
}

void CObjectManager::CheckEnemybyPlayerBulletCollision(vector<CBullet*> Bullet, vector<CMonster*> Target)
{
	for (vector<CBullet*>::iterator bulletIter = Bullet.begin(); bulletIter < Bullet.end(); ++bulletIter )
	{
		for (vector<CMonster*>::iterator enemy = Target.begin(); enemy < Target.end(); ++enemy)
		{

			if((*bulletIter)->IsCrashtoEnemy(*enemy))
			{
				if ((*bulletIter)->getType() == -1)
					(*enemy)->SetHp((*enemy)->GetHp() - 10);
				else if ((*bulletIter)->getType() == 0)
				{

					(*enemy)->SetHp((*enemy)->GetHp() - 10);
					
				}

				if ((*enemy)->GetHp() <= 0) {
					(*enemy)->alive = false;
					enemyInfo[idx].alive = false;
					enemyInfo[idx].index = (*enemy)->GetMyIdx();
					idx++;
				}
			}
			
		}

	}
	//===================TODO ����================================
	send(FRAMEWORK->GetSock(), (char*)&idx, sizeof(idx), 0);
	for (int i = 0; i <= idx; ++i) {
		send(FRAMEWORK->GetSock(), (char*)&enemyInfo[i], sizeof(enemyInfo[i]), 0);
	}
	//====================================================
}

void CObjectManager::Update()
{
}

void CObjectManager::AddGameObject(CGameObject* obj, E_OBJECT objType, int xPos, int yPos, int size) {
	
	//todo ���ӿ�����Ʈ ��ӹ��� Ŭ������ �Ѱܹް�. �Ѱܹ������ �����ϰ�

	//�� Ÿ�Ը������ ���� Ȯ���ϰ�
	//�װ� ���ٸ� �׋� �μ�Ʈ�� ����. 


	//�ֳ� ���� Ȯ��
	auto iter = m_ObjMap.find(objType);
	if (iter != m_ObjMap.end()) //������ ����Ʈ�� ����
	{
		obj->SetPos(xPos, yPos);
		obj->SetSize(size);
		obj->SetType(objType);
		obj->SetHp(20);//temp
		m_ObjMap[objType].push_back(obj);
		//m_ObjMap[objType].begin()
	}
	else //������ ����Ʈ�� ���� ����
	{
		obj->SetPos(xPos, yPos);
		obj->SetSize(size);
		obj->SetType(objType);
		obj->SetHp(20);//temp
		ObjList.push_back(obj);
		m_ObjMap.insert(std::make_pair(objType, ObjList));

	}

	//������ �� ������Ʈ����Ʈ�� ����. m_ObjMap[objType].pushback(obj)

	
}
void CObjectManager::SetObjlist(vector<CGameObject*> &Obj) {
	Obj= ObjList;
}