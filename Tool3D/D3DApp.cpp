#include "StdAfx.h"
#include "D3DApp.h"

CD3DApp::CD3DApp(void)
{
}


CD3DApp::~CD3DApp(void)
{
}


HRESULT CD3DApp::InitD3D( HWND hWnd )
{
	//디바이스 생성
	g_hWnd = hWnd;
	//g_hInst = AfxGetInstanceHandle();
	MyUtil::CreateDevice();

	//매니져 셋팅
	TIME_MGR->Init();
	DXFONT_MGR->Init(Device);
	GIZMO_MGR->Init(Device);
	DXFONT_MGR->AddStyle(Device, "예의체", "궁서체", 30);
	SPRITE_MGR->Init(Device);

	OnInit();

    return S_OK;
}

void CD3DApp::Render()
{
	//버퍼를 청소한다
	HRESULT result = Device->Clear(
		0,							//청소할 영역의 D3DRECT 배열 갯수		( 전체 클리어 0 )
		NULL,						//청소할 영역의 D3DRECT 배열 포인터		( 전체 클리어 NULL )
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,		//청소될 버퍼 플레그 ( D3DCLEAR_TARGET 컬러버퍼, D3DCLEAR_ZBUFFER 깊이버퍼, D3DCLEAR_STENCIL 스텐실버퍼
		0xff123434,					//컬러버퍼를 청소하고 채워질 색상( 0xAARRGGBB )
		1.0f,						//깊이버퍼를 청소할값 ( 0 ~ 1, 0 이 카메라에서 제일가까운 1 이 카메라에서 제일 먼 )
		0							//스텐실 버퍼를 채울값
	);

	//버퍼 청소가 성공했다면.......
	if (SUCCEEDED(result))
	{
		//디바이스 랜더링 시작 명령
		Device->BeginScene();

#ifdef _DEBUG		//디버그 모드에서만 실행
		//디바이스 랜더링 종료 명령
		//월드 그리드

#endif

		OnRender();

		//타임정보 출력
		TIME_MGR->DrawTimeInfo();
		//디바이스 랜더링 종료 명령
		Device->EndScene();

		//랜더링된 버퍼내용을 화면에 전송
		Device->Present(0, 0, 0, 0);
	}

}

void CD3DApp::Update()
{
	//타임매니져 업데이트
	TIME_MGR->UpdateTime(60.0f);

	OnUpdate();
}

void CD3DApp::Cleanup()
{
	OnRelease();

	//디바이스 해제
	ReleaseDevice();
	//매니져 해제
	GIZMO_MGR->Release();
	cGizmoManager::ReleaseInstance();
	TIME_MGR->Release();
	cTimeMgr::ReleaseInstance();
	KEY_MGR->Release();
	cKeyMgr::ReleaseInstance();
	DXFONT_MGR->Release();
	cDXFontManager::ReleaseInstance();
	SPRITE_MGR->Release();
	cSpriteManager::ReleaseInstance();
	cPhysicManager::ReleaseInstance();

	RESOURCE_TEXTURE->ClearResource();
	cResourceMgr_Texture::ReleaseInstance();
	RESOURCE_FX->ClearResource();
	cResourceMgr_ShaderFX::ReleaseInstance();
	RESOURCE_STATICXMESH->ClearResource();
	cResourceMgr_XStaticMesh::ReleaseInstance();
	RESOURCE_SKINNEDXMESH->ClearResource();
	cResourceMgr_XSkinnedMesh::ReleaseInstance();
}

