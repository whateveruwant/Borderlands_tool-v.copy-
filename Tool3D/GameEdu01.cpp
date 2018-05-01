#include "StdAfx.h"
#include "GameEdu01.h"
#include <D3dx9math.h>
#include <stdio.h>
#include "cScene_01.h"

CGameEdu01::CGameEdu01(void)
{
}


CGameEdu01::~CGameEdu01(void)
{
}

void CGameEdu01::OnInit()
{
	//씬생성
	m_pNowScene = new cScene_01();
	m_pNowScene->Init();
}

void CGameEdu01::OnRender()
{
	GIZMO_MGR->WorldGrid(1, 64);
	m_pNowScene->Render();
	//char str[100];
	//sprintf(str, "FPS: %d", m_nFPS);
	//DXFONT_MGR->PrintText(str, 0, 0, 0xffff0000);
}

void CGameEdu01::OnUpdate()
{	
	//DWORD dwCurTime = GetTickCount();
	//static DWORD dwOldTime = GetTickCount();
	//static DWORD dwAccumulateTime = 0; // 누적 시간
	//m_dwElapsedTime = dwCurTime - dwOldTime;
	//dwOldTime = dwCurTime;
	//
	//dwAccumulateTime += m_dwElapsedTime;
	//if( dwAccumulateTime >= 1000 ) {
	//	dwAccumulateTime = 0;
	//	m_nFPS = m_nFPSCount;
	//	m_nFPSCount = 0;
	//}
	//m_nFPSCount++;

	//한프레임 갱신 시간
	double timeDelta = TIME_MGR->GetFrameDeltaSec();

	//씬업데이트
	m_pNowScene->Update(static_cast<float>(timeDelta));
}

void CGameEdu01::OnRelease()
{
	//씬해재
	m_pNowScene->Release();
	SAFE_DELETE(m_pNowScene);
}

void CGameEdu01::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//switch (message)
	//{
	//case WM_KEYDOWN:
	//	switch (wParam)
	//	{
	//	case VK_ESCAPE:
	//		DestroyWindow();
	//		break;
	//	}
	//	break;
	//
	//case WM_DESTROY:			//윈도우가 파괴된다면..
	//	PostQuitMessage(0);	//프로그램 종료 요청 ( 메시지 루프를 빠져나가게 된다 )
	//	break;
	//}
	return;
}

void CGameEdu01::ResetMap()
{
	m_pNowScene->ResetMap();
}

void CGameEdu01::Flatten()
{
	m_pNowScene->Flatten();
}

void CGameEdu01::Smoothing()
{
	m_pNowScene->Smooding();
}
