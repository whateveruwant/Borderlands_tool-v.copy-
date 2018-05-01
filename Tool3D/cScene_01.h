#pragma once
#include "cscene.h"
#include "SourceList.h"
#define	OBJECTMAXNUM 100
#define	ENEMYMAXNUM 100
class cTerrain;
struct sObject {
	cBaseObject*	mObject;
	string			filePath;
	bool			haveAnimation;
	bool			isObject;
};


class cScene_01 : public cScene
{
private:
	D3DXVECTOR3						m_hitPos;
	POINT							m_prevPos;

	vector<sObject*>				m_vObject;
	vector<sObject*>				m_vEnemy;

	bool							onObject;

public:
	sObject*						m_tmpObject;			//드랍하기전 임시적으로 저장할 오브젝트
	cTerrain*						m_pTerrain;
	SourceList*						sourceList;

	cScene_01(void);
	~cScene_01(void);

	virtual HRESULT Scene_Init();
	virtual void Scene_Release();
	virtual void Scene_Update( float timDelta );
	virtual void Scene_Render1();

	SourceList* GetList() {
		return sourceList;
	}

	////////////////////////////////////////////////////////////////////////////////
	void ResetMap();
	void Flatten();
	void Smooding();
	void ChangeTexture1();
	void ChangeTexture2();
	void ChangeTexture3();
	void ChangeTexture4();

	////////////////////////////////////////////////////////////////////////////////
	void ChoiceObject(string filePath, bool isAnim);
	void ChoiceEnemy(string filePath);
	void SaveObjectsToFile(string filePath);
	void LoadObjectToFile(string filePath);
	void SaveEnemysToFile(string filePath);
	void LoadEnemysToFile(string filePath);

	void SetScaling(float num);

	void ObjectClear() { m_vObject.clear(); }
	void EnemyClear() { m_vEnemy.clear(); }
};

