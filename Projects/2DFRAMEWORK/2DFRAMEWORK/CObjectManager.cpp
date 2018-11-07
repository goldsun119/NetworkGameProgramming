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

void CObjectManager::AddGameObject(CGameObject* obj, E_OBJECT objType)
{
	//todo 게임오브젝트 상속받은 클래스를 넘겨받게. 넘겨받은대로 생성하게

	//이 타입만들어진 맵을 확인하고
	//그게 없다면 그떄 인서트로 만듬. 
	//if(!m_ObjMap[objType].size())
	std::vector<CGameObject*> ObjList;

	//있나 없나 확인
	auto iter = m_ObjMap.find(objType);
	if (iter != m_ObjMap.end())
		m_ObjMap[objType].push_back(obj);
	else
	{
		ObjList.push_back(obj);
		m_ObjMap.insert(std::make_pair(objType, ObjList)); //없을 때

	}

	//있으면 저 오브젝트리스트로 들어가서. m_ObjMap[objType].pushback(obj)

}
