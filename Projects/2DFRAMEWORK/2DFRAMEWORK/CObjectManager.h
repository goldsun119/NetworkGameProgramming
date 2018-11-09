#pragma once
#include <map>
class CGameObject;
//class CPlayer;
class CObjectManager : public CSingleTonBase<CRenderManager>
{
	std::map<E_OBJECT, std::vector<CGameObject*>> m_ObjMap;

public:

	CObjectManager();
	~CObjectManager();
	void Update();


	void AddGameObject(CGameObject* obj, E_OBJECT eType);
	
	CGameObject* FindGameObject(E_OBJECT objType, int idx);
};

