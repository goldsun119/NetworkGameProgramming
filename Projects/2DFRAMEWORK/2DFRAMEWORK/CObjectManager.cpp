#include "stdafx.h"
#include "CObjectManager.h"
#include "CGameObject.h"

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

void CObjectManager::Update()
{
}

void CObjectManager::AddGameObject(CGameObject* obj, E_OBJECT objType)
{
	//todo ���ӿ�����Ʈ ��ӹ��� Ŭ������ �Ѱܹް�. �Ѱܹ������ �����ϰ�

	//�� Ÿ�Ը������ ���� Ȯ���ϰ�
	//�װ� ���ٸ� �׋� �μ�Ʈ�� ����. 
	

	//�ֳ� ���� Ȯ��
	auto iter = m_ObjMap.find(objType);
	if (iter != m_ObjMap.end()) //������ ����Ʈ�� ����
		m_ObjMap[objType].push_back(obj);
	else //������ ����Ʈ�� ���� ����
	{
		ObjList.push_back(obj);
		m_ObjMap.insert(std::make_pair(objType, ObjList)); 

	}
	
	//������ �� ������Ʈ����Ʈ�� ����. m_ObjMap[objType].pushback(obj)

}
void CObjectManager::SetObjlist(vector<CGameObject*> &Obj) {
	Obj= ObjList;
}