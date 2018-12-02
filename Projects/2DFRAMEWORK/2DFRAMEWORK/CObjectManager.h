#pragma once
#include <map>
#include "CMonster.h"
#include "MyPacket.h"
class CGameObject;
//class CPlayer;
class CBullet;
class CObjectManager : public CSingleTonBase<CObjectManager>
{
	std::map<E_OBJECT, std::vector<CGameObject*>> m_ObjMap;
public:
	std::vector<CGameObject*> ObjList;
public:

	CObjectManager();
	~CObjectManager();
	void Update();


	void AddGameObject(CGameObject* obj, E_OBJECT objType, int xPos, int yPos, int size);
	void SetObjlist(vector<CGameObject*> &Obj);
	std::vector<CGameObject*> GetObjlist() {return ObjList; }
	CGameObject* FindGameObject(E_OBJECT objType, int idx);
	void CheckEnemybyPlayerBulletCollision(vector<CBullet*> bullet, vector<CMonster*> Target);
	

};

