#pragma once
#include "Framework.h"

class CScene;
class CSceneManager :public CSingleTonBase<CSceneManager> //: public FrameWork
{
public:
	CSceneManager();
	virtual ~CSceneManager();
	bool m_IsChangeScene;
public:
	virtual void Render(HDC memDc);// override;
	virtual void Update();// override;
	virtual void Destroy();// override;

	void ChangeState(E_SCENE state);
	void SetScene(E_SCENE state);
	E_SCENE GetScene();
	E_SCENE m_SceneType;
	CScene* m_pScene;
private:
	vector<CScene*> vSceneContainer;
};

