#include "StdAfx.h"
#include "cScene_01.h"
#include "cTerrain.h"
#include "cCamera.h"
#include "cLight_Direction.h"

cScene_01::cScene_01(void)
{
}

cScene_01::~cScene_01(void)
{
}

HRESULT cScene_01::Scene_Init()
{
	{
		sourceList = new SourceList;
		sourceList->sEnvironment = "../Resources/TextureCUBE/grassenvmap1024.dds";
		sourceList->sHeightMap = "../Resources/Testures/Default512.png";
		sourceList->sTerrain1 = "../Resources/Testures/terrain1.jpg";
		sourceList->sTerrain2 = "../Resources/Testures/terrain2.png";
		sourceList->sTerrain3 = "../Resources/Testures/terrain3.png";
		sourceList->sTerrain4 = "../Resources/Testures/terrain4.png";
		sourceList->sSplatMap = "../Resources/Testures/Default512_Splat.png";
		sourceList->fCellSize = 1.0f;
		sourceList->fHeightScale = 200.0f;
		sourceList->iSmoothLevel = 0;
		sourceList->iTileNum = 100;
		sourceList->fRangeSize = 10.0f;
		sourceList->eTab = BASE;
		sourceList->iHeightMax = 100;
		sourceList->fOpacity = 1.0f;
		sourceList->bPlus = true;
		sourceList->iBottom = 0;
		sourceList->eBrushType = eBrushType_3rd;
		sourceList->eBrushTexture = eBrushTexture::eBrushTexture_1st;
		sourceList->sTmpObject = "../Resources/Meshes/Objects/vendingMachine.X";
		sourceList->fObjectScale = 0.1f;
	}

	{
		m_pTerrain = new cTerrain();
		m_pTerrain->SetSource(sourceList);
		m_pTerrain->Init(
			sourceList->sHeightMap.c_str(),
			sourceList->sTerrain1.c_str(),
			sourceList->sTerrain2.c_str(),
			sourceList->sTerrain3.c_str(),
			sourceList->sTerrain4.c_str(),
			sourceList->sSplatMap.c_str(),
			sourceList->fCellSize,
			sourceList->fHeightScale,
			sourceList->iSmoothLevel,
			sourceList->iTileNum);
	}
	
	m_hitPos = D3DXVECTOR3(0, 0, 0);

	//환경구세팅
	this->SetEnvironment(sourceList->sEnvironment);

	//기본라이트 방향
	this->pSceneBaseDirectionLight->pTransform->RotateWorld(
		90.0f * ONE_RAD, 0, 0);

	this->pMainCamera->SetWorldPosition(0, 100.0f, 0);
	m_prevPos = { 0, 0};

	onObject = false;

	m_tmpObject = new sObject();
	return S_OK;
}

void cScene_01::Scene_Release()
{
	m_pTerrain->Release();
	SAFE_DELETE(m_pTerrain);
	SAFE_DELETE(sourceList);
	m_vObject.clear();
	m_vEnemy.clear();
	//for (int i = 0; i < m_vObject.size() - 1; ++i) {
	//	SAFE_DELETE(m_vObject[i]);
	//}
	SAFE_DELETE(m_tmpObject);
}

void cScene_01::Scene_Update(float timDelta)
{
	D3DXVECTOR3 pHit;
	D3DXVECTOR3 pHitNormal;
	Ray ray;
	RECT rect = { 0, 0, 1240 , 787 };
	POINT ptMousePos = GetMousePos();
	if (PtInRect(&rect, ptMousePos)) {
		D3DXVECTOR2 screenPos(ptMousePos.x, ptMousePos.y);
		this->pMainCamera->ComputeRay(&ray, &screenPos);
		//Terrain 이랑 Ray체크
		this->m_pTerrain->IsIntersectRay(&m_hitPos, &ray);
		if (onObject) {
			m_tmpObject->mObject->pTransform->SetWorldPosition(m_hitPos);
			m_tmpObject->mObject->SetActive(true);
		}
		if (KEY_MGR->IsStayDown(VK_LBUTTON)) {
			switch (sourceList->eTab)
			{
			case BASE:
				break;
			case HEIGHT:
				if (m_prevPos.x != ptMousePos.x || m_prevPos.y != ptMousePos.y) {
					m_pTerrain->ChangeHeightMap(m_hitPos);
					m_prevPos = ptMousePos;
				}
				break;
			case SPLAT:
				m_pTerrain->ChangeSplatMap(m_hitPos);
				break;
			case OBJECT:
				break;
			}
		}

		if (KEY_MGR->IsOnceDown(VK_LBUTTON)) {
			switch (sourceList->eTab)
			{
			case BASE:
				break;
			case HEIGHT:
				break;
			case SPLAT:
				break;
			case OBJECT:
				if (!onObject) {
					for (int i = 0; i < m_vObject.size(); ++i) {
						if (PHYSICS_MGR->IsRayHitBound(&ray, &m_vObject[i]->mObject->BoundBox, m_vObject[i]->mObject->pTransform, &pHit, &pHitNormal)) {
							m_tmpObject = m_vObject[i];
							m_vObject.erase(m_vObject.begin() + i);
							onObject = true;
						}
					}
					for (int i = 0; i < m_vEnemy.size(); ++i) {
						if (PHYSICS_MGR->IsRayHitBound(&ray, &m_vEnemy[i]->mObject->BoundBox, m_vEnemy[i]->mObject->pTransform, &pHit, &pHitNormal)) {
							m_tmpObject = m_vEnemy[i];
							m_vEnemy.erase(m_vEnemy.begin() + i);
							onObject = true;
						}
					}
				}
				else {
					if(m_tmpObject->isObject)
						m_vObject.push_back(m_tmpObject);
					else
						m_vEnemy.push_back(m_tmpObject);
					onObject = false;
				}
				break;
			}
		}
	}

	if (KEY_MGR->IsOnceDown(VK_RETURN)) {
		m_pTerrain->SaveHeightMap();
		m_pTerrain->SaveSplatMap();
	}

	if (onObject) {
		m_tmpObject->mObject->Update(timDelta);
		m_tmpObject->mObject->pTransform->DefaultControl2(timDelta);
	}
	else {
		pSceneBaseDirectionLight->pTransform->DefaultControl2(timDelta);
	}

	for (int i = 0; i < m_vObject.size(); ++i) {
		m_vObject.at(i)->mObject->Update(timDelta);
	}
	for (int i = 0; i < m_vEnemy.size(); ++i) {
		m_vEnemy.at(i)->mObject->Update(timDelta);
	}
}

void cScene_01::Scene_Render1()
{
	m_pTerrain->Render(this->pMainCamera, pSceneBaseDirectionLight);
	Device->SetRenderState(D3DRS_FOGENABLE, TRUE);
	if (onObject) {
		m_tmpObject->mObject->Render();
		m_tmpObject->mObject->BoundBox.RenderGizmo(m_tmpObject->mObject->pTransform);
	}
	if (sourceList->eTab != OBJECT) m_pTerrain->RenderBrush(this->m_hitPos, sourceList->fRangeSize, 0xff000000, Device);
	for (int i = 0; i < m_vObject.size(); ++i) {
		m_vObject.at(i)->mObject->Render();
		//m_vObject.at(i)->mObject->BoundBox.RenderGizmo(m_vObject.at(i)->mObject->pTransform);
	}
	for (int i = 0; i < m_vEnemy.size(); ++i) {
		m_vEnemy.at(i)->mObject->Render();
	}
	cXMesh_Static::SetBaseLight(this->pSceneBaseDirectionLight);
	cXMesh_Static::SetLighting(&pSceneDarkLight);
	cXMesh_Static::SetCamera(this->pMainCamera);
	//cXMesh_Skinned::SetLighting(&pSceneDarkLight);
}

void cScene_01::ResetMap()
{
	m_pTerrain->Release();
	SAFE_DELETE(m_pTerrain);
	m_pTerrain = new cTerrain();
	m_pTerrain->SetSource(sourceList);
	m_pTerrain->Init(
		sourceList->sHeightMap.c_str(),
		sourceList->sTerrain1.c_str(),
		sourceList->sTerrain2.c_str(),
		sourceList->sTerrain3.c_str(),
		sourceList->sTerrain4.c_str(),
		sourceList->sSplatMap.c_str(),
		sourceList->fCellSize,
		sourceList->fHeightScale,
		sourceList->iSmoothLevel,
		sourceList->iTileNum);
}

void cScene_01::Flatten()
{
	m_pTerrain->Flatten();
	sourceList->iBottom = sourceList->iHeightMax;
}

void cScene_01::Smooding()
{
	m_pTerrain->ChangeSmoothLevel(sourceList->iSmoothLevel);
}

void cScene_01::ChangeTexture1()
{
	m_pTerrain->ChangeTerrain1(sourceList->sTerrain1);
}

void cScene_01::ChangeTexture2()
{
	m_pTerrain->ChangeTerrain2(sourceList->sTerrain2);
}

void cScene_01::ChangeTexture3()
{
	m_pTerrain->ChangeTerrain3(sourceList->sTerrain3);
}

void cScene_01::ChangeTexture4()
{
	m_pTerrain->ChangeTerrain4(sourceList->sTerrain4);
}

void cScene_01::ChoiceObject(string filePath, bool isAnim)
{
	//if (m_tmpObject != nullptr) SAFE_DELETE(m_tmpObject);
	//SAFE_DELETE(m_tmpObject);
	m_tmpObject = new sObject();
	m_tmpObject->filePath = filePath;
	m_tmpObject->haveAnimation = isAnim;
	m_tmpObject->mObject = new cBaseObject(); 
	m_tmpObject->mObject->SetMesh(RESOURCE_STATICXMESH->GetResource(filePath));
	m_tmpObject->mObject->pTransform->SetScale(sourceList->fObjectScale, sourceList->fObjectScale, sourceList->fObjectScale);
	m_tmpObject->isObject = true;
	onObject = true;
}

void cScene_01::ChoiceEnemy(string filePath)
{
	m_tmpObject = new sObject();
	m_tmpObject->filePath = filePath;
	m_tmpObject->mObject = new cBaseObject();
	m_tmpObject->mObject->SetMesh(RESOURCE_STATICXMESH->GetResource(filePath));
	m_tmpObject->mObject->pTransform->SetScale(0.1f, 0.1f, 0.1f);
	m_tmpObject->isObject = false;
	onObject = true;
}

void cScene_01::SaveObjectsToFile(string filePath)
{
	sObjectSaveData tmpData[OBJECTMAXNUM];
	ZeroMemory(&tmpData, OBJECTMAXNUM);
	for (int i = 0; i < m_vObject.size(); ++i) {
		tmpData[i].isSet = true;
		tmpData[i].haveAnimation = m_vObject[i]->haveAnimation;
		sprintf(tmpData[i].sfilePath, m_vObject[i]->filePath.c_str(), 100);
		tmpData[i].axis[0] = m_vObject[i]->mObject->pTransform->GetRight();
		tmpData[i].axis[1] = m_vObject[i]->mObject->pTransform->GetUp();
		tmpData[i].axis[2] = m_vObject[i]->mObject->pTransform->GetForward();
		tmpData[i].position = m_vObject[i]->mObject->pTransform->GetWorldPosition();
		tmpData[i].scale = m_vObject[i]->mObject->pTransform->GetScale();
	}
	for (int i = m_vObject.size(); i < OBJECTMAXNUM; ++i) {
		tmpData[i].isSet = false;
	}
	HANDLE file;
	DWORD write;
	file = CreateFile(filePath.c_str() ,
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	WriteFile(file, &tmpData, sizeof(sObjectSaveData)*OBJECTMAXNUM, &write, NULL);
	CloseHandle(file);
}

void cScene_01::LoadObjectToFile(string filePath)
{
	sObjectSaveData tmpData[OBJECTMAXNUM];
	ZeroMemory(&tmpData, OBJECTMAXNUM);
	HANDLE file;
	DWORD read;
	file = CreateFile(filePath.c_str(),
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	ReadFile(file, &tmpData, sizeof(sObjectSaveData)*OBJECTMAXNUM, &read, NULL);
	CloseHandle(file);

	m_vObject.clear();
	for (int i = 0; i < OBJECTMAXNUM; ++i) {
		if (tmpData[i].isSet == false) break;
		sObject* tmpObject;
		tmpObject = new sObject;
		tmpObject->filePath = tmpData[i].sfilePath;
		tmpObject->haveAnimation = tmpData[i].haveAnimation;
		tmpObject->mObject = new cBaseObject();
		tmpObject->mObject->SetMesh(RESOURCE_STATICXMESH->GetResource(tmpObject->filePath));
		tmpObject->mObject->pTransform->SetScale(tmpData[i].scale);
		tmpObject->mObject->pTransform->SetWorldPosition(tmpData[i].position);
		tmpObject->mObject->pTransform->SetAxises(tmpData[i].axis);
		tmpObject->mObject->SetActive(true);
		m_vObject.push_back(tmpObject);
	}
}

void cScene_01::SaveEnemysToFile(string filePath)
{
	sEnemySaveData tmpData[ENEMYMAXNUM];
	ZeroMemory(&tmpData, ENEMYMAXNUM);
	for (int i = 0; i < m_vEnemy.size(); ++i) {
		tmpData[i].isSet = true;
		sprintf(tmpData[i].sfilePath, m_vEnemy[i]->filePath.c_str(), 100);
		tmpData[i].position = m_vEnemy[i]->mObject->pTransform->GetWorldPosition();
	}
	for (int i = m_vEnemy.size(); i < ENEMYMAXNUM; ++i) {
		tmpData[i].isSet = false;
	}
	HANDLE file;
	DWORD write;
	file = CreateFile(filePath.c_str(),
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	WriteFile(file, &tmpData, sizeof(sEnemySaveData)*ENEMYMAXNUM, &write, NULL);
	CloseHandle(file);
}

void cScene_01::LoadEnemysToFile(string filePath)
{
	sEnemySaveData tmpData[ENEMYMAXNUM];
	ZeroMemory(&tmpData, ENEMYMAXNUM);
	HANDLE file;
	DWORD read;
	file = CreateFile(filePath.c_str(),
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	ReadFile(file, &tmpData, sizeof(sEnemySaveData)*ENEMYMAXNUM, &read, NULL);
	CloseHandle(file);

	m_vEnemy.clear();
	for (int i = 0; i < ENEMYMAXNUM; ++i) {
		if (tmpData[i].isSet == false) break;
		sObject* tmpObject;
		tmpObject = new sObject;
		tmpObject->filePath = tmpData[i].sfilePath;
		tmpObject->mObject = new cBaseObject();
		tmpObject->mObject->SetMesh(RESOURCE_STATICXMESH->GetResource(tmpObject->filePath));
		tmpObject->mObject->pTransform->SetWorldPosition(tmpData[i].position);
		tmpObject->mObject->pTransform->SetScale(0.1f, 0.1f, 0.1f);
		tmpObject->mObject->SetActive(true);
		m_vEnemy.push_back(tmpObject);
	}
}

void cScene_01::SetScaling(float num)
{
	sourceList->fObjectScale = num;
	if (onObject) {
		m_tmpObject->mObject->pTransform->SetScale(sourceList->fObjectScale, sourceList->fObjectScale, sourceList->fObjectScale);
	}
}
