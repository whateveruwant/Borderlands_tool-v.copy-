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
	//����̽� ����
	g_hWnd = hWnd;
	//g_hInst = AfxGetInstanceHandle();
	MyUtil::CreateDevice();

	//�Ŵ��� ����
	TIME_MGR->Init();
	DXFONT_MGR->Init(Device);
	GIZMO_MGR->Init(Device);
	DXFONT_MGR->AddStyle(Device, "����ü", "�ü�ü", 30);
	SPRITE_MGR->Init(Device);

	OnInit();

    return S_OK;
}

void CD3DApp::Render()
{
	//���۸� û���Ѵ�
	HRESULT result = Device->Clear(
		0,							//û���� ������ D3DRECT �迭 ����		( ��ü Ŭ���� 0 )
		NULL,						//û���� ������ D3DRECT �迭 ������		( ��ü Ŭ���� NULL )
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,		//û�ҵ� ���� �÷��� ( D3DCLEAR_TARGET �÷�����, D3DCLEAR_ZBUFFER ���̹���, D3DCLEAR_STENCIL ���ٽǹ���
		0xff123434,					//�÷����۸� û���ϰ� ä���� ����( 0xAARRGGBB )
		1.0f,						//���̹��۸� û���Ұ� ( 0 ~ 1, 0 �� ī�޶󿡼� ���ϰ���� 1 �� ī�޶󿡼� ���� �� )
		0							//���ٽ� ���۸� ä�ﰪ
	);

	//���� û�Ұ� �����ߴٸ�.......
	if (SUCCEEDED(result))
	{
		//����̽� ������ ���� ���
		Device->BeginScene();

#ifdef _DEBUG		//����� ��忡���� ����
		//����̽� ������ ���� ���
		//���� �׸���

#endif

		OnRender();

		//Ÿ������ ���
		TIME_MGR->DrawTimeInfo();
		//����̽� ������ ���� ���
		Device->EndScene();

		//�������� ���۳����� ȭ�鿡 ����
		Device->Present(0, 0, 0, 0);
	}

}

void CD3DApp::Update()
{
	//Ÿ�ӸŴ��� ������Ʈ
	TIME_MGR->UpdateTime(60.0f);

	OnUpdate();
}

void CD3DApp::Cleanup()
{
	OnRelease();

	//����̽� ����
	ReleaseDevice();
	//�Ŵ��� ����
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

