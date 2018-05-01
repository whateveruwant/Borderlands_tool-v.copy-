#pragma once
#include "d3dapp.h"
#include <d3dx9math.h>
#include <D3dx9shape.h>
#include "cScene.h"
#include "cScene_01.h"
#include "SourceList.h"

class CGameEdu01 : public CD3DApp
{
	virtual void OnInit();
	virtual void OnRender();
	virtual void OnUpdate();
	virtual void OnRelease();

	DWORD m_dwElapsedTime;
	unsigned int m_nFPS, m_nFPSCount;

private:

public:
	cScene_01*					m_pNowScene;

	CGameEdu01(void);
	~CGameEdu01(void);

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	SourceList* GetList() {
		return m_pNowScene->GetList();
	}
	void ResetMap();
	void Flatten();
	void Smoothing();
};