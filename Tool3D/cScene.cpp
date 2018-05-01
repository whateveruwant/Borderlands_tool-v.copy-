#include "StdAfx.h"
#include "cScene.h"
#include "cCamera.h"
#include "cLight_Direction.h"
#include "cTerrain.h"

cScene::cScene(void)
	: evironmentTexture(NULL), evironmemtSphereMesh(NULL)
{
	//ȯ�� Effect ���� ���´�.
	this->evironmentEffect =
		RESOURCE_FX->GetResource("../Resources/Shaders/EvironmentCUBE.fx");

	this->pMainCamera = new cCamera();

	//�⺻ ���� ����
	this->pSceneBaseDirectionLight = new cLight_Direction();

	//���⼺ ������ ī�޶� �� �����Ѵ�.
	this->pDirectionLightCamera = new cCamera();

	//���⼺���� �ڽĿ� ���δ�.
	//this->pDirectionLightCamera->AttachTo( this->pSceneBaseDirectionLight->pTransform );
	for (int i = 0; i < 4; ++i) {
		cLight_Direction* tmpLight = new cLight_Direction();
		tmpLight->Color = D3DXCOLOR(1, 1, 1, 1);
		tmpLight->Intensity = 0.35f;
		tmpLight->pTransform->RotateWorld(0, 90.0f * ONE_RAD * i, 0);
		pSceneDarkLight.push_back(tmpLight);
	}

	//�⺻ ��
	this->pSceneBaseDirectionLight->Color = D3DXCOLOR(1, 1, 1, 1);
	this->pSceneBaseDirectionLight->Intensity = 1.0f;

	//�׸��� �Ÿ�
	shadowDistance = 100.0f;

	//ī�޶��� ��������� �ٲ۴�...
	this->pDirectionLightCamera->bOrtho = true;
	this->pDirectionLightCamera->camNear = 0.1f;
	this->pDirectionLightCamera->camFar = shadowDistance * 2.0f;
	this->pDirectionLightCamera->aspect = 1;
	this->pDirectionLightCamera->orthoSize = shadowDistance * 1.5f;	//����ũ��� �׸���ũ���...

																	//���⼺���� ī�޶��� RenderToTexture �غ�
	this->pDirectionLightCamera->ReadyShadowTexture(4096);
}


cScene::~cScene(void)
{
	SAFE_RELEASE(evironmentTexture);
	SAFE_RELEASE(evironmemtSphereMesh);

	SAFE_DELETE(this->pMainCamera);

	SAFE_DELETE(this->pSceneBaseDirectionLight);
	SAFE_DELETE(this->pDirectionLightCamera);

	for (int i = 0; i < 4; ++i) {
		SAFE_DELETE(pSceneDarkLight[i]);
	}
}


HRESULT cScene::Init()
{
	//���� �ʱ�ȭ �̷������.
	if (FAILED(this->Scene_Init()))
		return E_FAIL;

	//����ī�޶� RenderToTexture �غ�
	this->pMainCamera->ReadyRenderToTexture(0, WINSIZE_X, WINSIZE_Y);
	this->pMainCamera->ReadyRenderToTexture(1, WINSIZE_X, WINSIZE_Y);
	this->pMainCamera->ReadyRenderToTexture(2, WINSIZE_X, WINSIZE_Y);

	this->pMainCamera->ReadyRenderToTexture(5, WINSIZE_X / 4, WINSIZE_Y / 4);		//Blur Temp1
	this->pMainCamera->ReadyRenderToTexture(6, WINSIZE_X / 4, WINSIZE_Y / 4);		//Blur Temp2

	this->pMainCamera->ReadyRenderToTexture(9, WINSIZE_X, WINSIZE_Y);		//Grap ��


																			//0----1
																			//|   /|
																			//|  / |
																			//| /  |
																			//|/   |
																			//3----2

	this->scenePlaneVertex[0].pos = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
	this->scenePlaneVertex[1].pos = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	this->scenePlaneVertex[2].pos = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
	this->scenePlaneVertex[3].pos = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);

	this->scenePlaneVertex[0].uv = D3DXVECTOR2(0.0f, 0.0f);
	this->scenePlaneVertex[1].uv = D3DXVECTOR2(1.0f, 0.0f);
	this->scenePlaneVertex[2].uv = D3DXVECTOR2(1.0f, 1.0f);
	this->scenePlaneVertex[3].uv = D3DXVECTOR2(0.0f, 1.0f);

	this->scenePlaneIndex[0] = 0;
	this->scenePlaneIndex[1] = 1;
	this->scenePlaneIndex[2] = 3;
	this->scenePlaneIndex[3] = 3;
	this->scenePlaneIndex[4] = 1;
	this->scenePlaneIndex[5] = 2;


	this->postEffect = RESOURCE_FX->GetResource("../Resources/Shaders/PostEffect.fx");

	return S_OK;
}

void cScene::Release()
{

	//���� ������ �Ͼ��.
	this->Scene_Release();
}

void cScene::Update(float timeDelta)
{
	pMainCamera->DefaultControl(timeDelta);

	pMainCamera->UpdateCamToDevice(Device);
	pMainCamera->UpdateFrustum();

	//����ī�޶� DirectionLight �� ������ ������ü ����ٴϰ�....

	//���� ��ġ
	D3DXVECTOR3 camPos = pMainCamera->GetWorldPosition();		//����ī�޶��� ��ġ
	D3DXVECTOR3 camFront = pMainCamera->GetForward();			//����ī�޶��� ����
	D3DXVECTOR3 lightDir = pSceneBaseDirectionLight->pTransform->GetForward();	//���⼺ ������ ����

	D3DXVECTOR3 lightPos = camPos +
		(camFront * (shadowDistance * 0.5f)) +
		(-lightDir * shadowDistance);

	this->pDirectionLightCamera->SetWorldPosition(lightPos.x, lightPos.y, lightPos.z);
	this->pDirectionLightCamera->LookDirection(lightDir);


	//���� ������Ʈ�� �Ͼ��.
	this->Scene_Update(timeDelta);
}

void cScene::Render()
{
	this->pMainCamera->RenderTextureBegin(0, 0, 0x00101010);		//0 �� ���������� 0 �� RenderTarget
	this->pMainCamera->RenderTextureBegin(1, 1, 0xff000000);		//1 �� ���������� 1 �� RenderTarget
																	//this->pMainCamera->RenderTextureBegin( 2, 2, 0x00000000 );		//2 �� ���������� 2 �� RenderTarget

																	//ȯ�� ����
	this->RenderEnvironment();

	//�����ȴ�.
	this->Scene_Render0();
	this->Scene_Render1();
	this->Scene_Render2();


#ifdef _DEBUG		//����� ��忡���� ����
	//����̽� ������ ���� ���
	//���� �׸���
#endif

	//�߿� RenderTextureBegin �������� ����.
	//this->pMainCamera->RenderTextureEnd( 2, 2 );		//2 ������������ ���õ� 2 RenderTarget �� ���� ��Ų��. 
	this->pMainCamera->RenderTextureEnd(1, 1);		//1 ������������ ���õ� 1 RenderTarget �� ���� ��Ų��. 
	this->pMainCamera->RenderTextureEnd(0, 0);		//0 ������������ ���õ� 0 RenderTarget �� ���� ��Ų��. 


													//
													// Post Effect

	this->RenderBase();													//
	//RenderColorLevel();
	this->RenderOutline();		//�ƿ����� �׷���
	//GIZMO_MGR->WorldGrid(1, 32);
	//this->RenderGlow();		//��� ���̰� ����


	this->Scene_Render_AfterPostEffect(this->pMainCamera->GetRenderTexture(0));


	////���ö���Ʈ ����
	//SPRITE_MGR->BeginSpriteRender();
	//this->Scene_RenderSprite();
	//SPRITE_MGR->EndSpriteRender();

}

//���� ī�޶��� RenderToTexture �� ������Ʈ�Ѵ�.
void cScene::RenderToMainCamTexture()
{
}


void cScene::SetEnvironment(std::string cubeFilePath)
{
	//������ ȯ����� ���õǾ������� ����..
	SAFE_RELEASE(evironmentTexture);

	//ȯ��� �ε�
	D3DXCreateCubeTextureFromFile(
		Device,
		cubeFilePath.c_str(),
		&evironmentTexture);

	//ȯ�汸 �ε��Ǿ����� �ʴٸ�....
	if (this->evironmemtSphereMesh == NULL)
	{
		D3DXCreateSphere(Device,
			3.0f,
			20,
			20,
			&evironmemtSphereMesh, NULL);
	}

}


//ȯ�汸 ����
void cScene::RenderEnvironment()
{
	//ȯ�� �� �ε��Ȱ� ���ٸ� �����ض�.....
	if (this->evironmentTexture == NULL)
		return;

	//ȯ�� Effect ����
	this->evironmentEffect->SetTexture("MyCube_Tex", this->evironmentTexture);

	//WVP ��Ʈ����
	D3DXMATRIXA16 matWorld = this->pMainCamera->GetFinalMatrix();
	D3DXMATRIXA16 matViewProj = this->pMainCamera->GetViewProjectionMatrix();
	D3DXMATRIXA16 matWVP = matWorld * matViewProj;

	this->evironmentEffect->SetMatrix("matWVP", &matWVP);
	this->evironmentEffect->SetMatrix("matWorld", &matWorld);


	//�׷���...
	UINT numPass;
	this->evironmentEffect->Begin(&numPass, 0);		//���̴��� �׸��ٴ� ���� �˸��� pass ���� ��´�.

	for (UINT i = 0; i < numPass; i++)	//���� ����� ����.
	{
		this->evironmentEffect->BeginPass(i);			//i��° ��������

		this->evironmemtSphereMesh->DrawSubset(0);

		this->evironmentEffect->EndPass();				//i��° ������
	}
	this->evironmentEffect->End();						//���̴��� �׸��� ��



}


void cScene::ReadyShadowMap(std::vector<cBaseObject*>* renderObjects, cTerrain* pTerrain)
{
	//���⼺������ ���� ī�޶��� Frustum ������Ʈ
	this->pDirectionLightCamera->UpdateMatrix();
	this->pDirectionLightCamera->UpdateFrustum();


	//���̷��Ƕ����� ī�޶� ������ �ֵ鸸 �׸���...
	static std::vector<cBaseObject*>		shadowCullObject;
	shadowCullObject.clear();

	for (int i = 0; i < renderObjects->size(); i++) {

		//�������� �ȿ� �ִ�?
		if (this->pDirectionLightCamera->Frustum.IsInFrustum((*renderObjects)[i]))
		{
			shadowCullObject.push_back((*renderObjects)[i]);
		}
	}


	//������ �� �׸���.
	this->pDirectionLightCamera->RenderShadowBegin();

	cXMesh_Static::SetCamera(this->pDirectionLightCamera);
	cXMesh_Skinned::SetCamera(this->pDirectionLightCamera);

	for (int i = 0; i < shadowCullObject.size(); i++) {
		shadowCullObject[i]->RenderShadow();
	}

	//���� Terrain �� ������ ���� �׷����Ѵٸ�...
	if (pTerrain != NULL)
	{
		pTerrain->RenderShadow(this->pDirectionLightCamera);
	}

	this->pDirectionLightCamera->RenderShadowEnd();


	//���� Terrain �� ������ ���� �����Ѵٸ�...
	if (pTerrain != NULL)
	{
		pTerrain->m_pTerrainEffect->SetTexture("Shadow_Tex",
			this->pDirectionLightCamera->GetShadowTexture());

		pTerrain->m_pTerrainEffect->SetMatrix("matLightViewProjection",
			&this->pDirectionLightCamera->GetViewProjectionMatrix());
	}



	//������ Texture
	cXMesh_Static::sStaticMeshEffect->SetTexture("Shadow_Tex",
		this->pDirectionLightCamera->GetShadowTexture());

	//������ ���
	cXMesh_Static::sStaticMeshEffect->SetMatrix("matLightViewProjection",
		&this->pDirectionLightCamera->GetViewProjectionMatrix());


	//������ Texture
	cXMesh_Skinned::sSkinnedMeshEffect->SetTexture("Shadow_Tex",
		this->pDirectionLightCamera->GetShadowTexture());

	//������ ���
	cXMesh_Skinned::sSkinnedMeshEffect->SetMatrix("matLightViewProjection",
		&this->pDirectionLightCamera->GetViewProjectionMatrix());
}


//����ī�޶��� ���� Texture �� ��´�.
LPDIRECT3DTEXTURE9 cScene::GetTexture() {
	return this->pMainCamera->GetRenderTexture(0);
}



/// Post Effect Functions ///////////////////////////////////////////////////////////////////

void cScene::RenderBase()
{
	this->postEffect->SetTechnique("Base");

	this->postEffect->SetTexture("screenTex", this->pMainCamera->GetRenderTexture(0));

	float pixelU = 1.0f / WINSIZE_X;
	float pixelV = 1.0f / WINSIZE_Y;
	this->postEffect->SetFloat("pixelSizeU", pixelU);
	this->postEffect->SetFloat("pixelSizeV", pixelV);
	this->postEffect->SetFloat("pixelHalfSizeU", pixelU * 0.5f);
	this->postEffect->SetFloat("pixelHalfSizeV", pixelV * 0.5f);

	UINT iPass;
	this->postEffect->Begin(&iPass, 0);
	for (UINT i = 0; i < iPass; i++) {
		this->postEffect->BeginPass(i);

		Device->SetFVF(SCENE_VERTEX::FVF);
		Device->DrawIndexedPrimitiveUP(
			D3DPT_TRIANGLELIST,
			0,
			4,
			2,
			this->scenePlaneIndex,
			D3DFMT_INDEX16,
			this->scenePlaneVertex,
			sizeof(SCENE_VERTEX));


		this->postEffect->EndPass();
	}
	this->postEffect->End();
}


void cScene::RenderOutline()
{
	this->postEffect->SetTechnique("OutLine");

	this->postEffect->SetTexture("screenTex", this->pMainCamera->GetRenderTexture(0));
	this->postEffect->SetTexture("normalTex", this->pMainCamera->GetRenderTexture(1));

	float pixelU = 1.0f / WINSIZE_X;
	float pixelV = 1.0f / WINSIZE_Y;
	this->postEffect->SetFloat("pixelSizeU", pixelU);
	this->postEffect->SetFloat("pixelSizeV", pixelV);
	this->postEffect->SetFloat("pixelHalfSizeU", pixelU * 0.5f);
	this->postEffect->SetFloat("pixelHalfSizeV", pixelV * 0.5f);

	UINT iPass;
	this->postEffect->Begin(&iPass, 0);
	for (UINT i = 0; i < iPass; i++) {
		this->postEffect->BeginPass(i);

		Device->SetFVF(SCENE_VERTEX::FVF);
		Device->DrawIndexedPrimitiveUP(
			D3DPT_TRIANGLELIST,
			0,
			4,
			2,
			this->scenePlaneIndex,
			D3DFMT_INDEX16,
			this->scenePlaneVertex,
			sizeof(SCENE_VERTEX));


		this->postEffect->EndPass();
	}
	this->postEffect->End();
}


void cScene::RenderBBo()
{

	//
	// Blur Scene ����
	//

	float pixelU = 1.0f / WINSIZE_X;
	float pixelV = 1.0f / WINSIZE_Y;
	this->postEffect->SetFloat("pixelSizeU", pixelU);
	this->postEffect->SetFloat("pixelSizeV", pixelV);
	this->postEffect->SetFloat("pixelHalfSizeU", pixelU * 0.5f);
	this->postEffect->SetFloat("pixelHalfSizeV", pixelV * 0.5f);


	for (int i = 0; i < 10; i++)
	{

		//BlurX

		this->pMainCamera->RenderTextureBegin(0, 5, 0x00101010);
		this->postEffect->SetTechnique("BlurX");

		if (i == 0)
		{
			this->postEffect->SetTexture("screenTex", this->pMainCamera->GetRenderTexture(0));
		}

		else
		{
			this->postEffect->SetTexture("screenTex", this->pMainCamera->GetRenderTexture(6));
		}

		UINT iPass;
		this->postEffect->Begin(&iPass, 0);
		for (UINT i = 0; i < iPass; i++) {
			this->postEffect->BeginPass(i);

			Device->SetFVF(SCENE_VERTEX::FVF);
			Device->DrawIndexedPrimitiveUP(
				D3DPT_TRIANGLELIST,
				0,
				4,
				2,
				this->scenePlaneIndex,
				D3DFMT_INDEX16,
				this->scenePlaneVertex,
				sizeof(SCENE_VERTEX));


			this->postEffect->EndPass();
		}
		this->postEffect->End();

		this->pMainCamera->RenderTextureEnd(0, 5);


		//BlurY

		pixelU = 1.0f / (WINSIZE_X / 4);		//5 �� Texture �� Size�� WINSIZE_X / 2 
		pixelV = 1.0f / (WINSIZE_Y / 4);		//5 �� Texture �� Size�� WINSIZE_X / 2 
		this->postEffect->SetFloat("pixelSizeU", pixelU);
		this->postEffect->SetFloat("pixelSizeV", pixelV);
		this->postEffect->SetFloat("pixelHalfSizeU", pixelU * 0.5f);
		this->postEffect->SetFloat("pixelHalfSizeV", pixelV * 0.5f);


		this->pMainCamera->RenderTextureBegin(0, 6, 0x00101010);
		this->postEffect->SetTechnique("BlurY");
		this->postEffect->SetTexture("screenTex", this->pMainCamera->GetRenderTexture(5));

		iPass;
		this->postEffect->Begin(&iPass, 0);
		for (UINT i = 0; i < iPass; i++) {
			this->postEffect->BeginPass(i);

			Device->SetFVF(SCENE_VERTEX::FVF);
			Device->DrawIndexedPrimitiveUP(
				D3DPT_TRIANGLELIST,
				0,
				4,
				2,
				this->scenePlaneIndex,
				D3DFMT_INDEX16,
				this->scenePlaneVertex,
				sizeof(SCENE_VERTEX));


			this->postEffect->EndPass();
		}
		this->postEffect->End();

		this->pMainCamera->RenderTextureEnd(0, 6);

	}

	//
	// BBo Render
	//
	this->postEffect->SetTechnique("BBo");
	this->postEffect->SetTexture("screenTex", this->pMainCamera->GetRenderTexture(0));
	this->postEffect->SetTexture("blurTex", this->pMainCamera->GetRenderTexture(6));

	pixelU = 1.0f / WINSIZE_X;
	pixelV = 1.0f / WINSIZE_Y;
	this->postEffect->SetFloat("pixelSizeU", pixelU);
	this->postEffect->SetFloat("pixelSizeV", pixelV);
	this->postEffect->SetFloat("pixelHalfSizeU", pixelU * 0.5f);
	this->postEffect->SetFloat("pixelHalfSizeV", pixelV * 0.5f);

	UINT iPass;
	this->postEffect->Begin(&iPass, 0);
	for (UINT i = 0; i < iPass; i++) {
		this->postEffect->BeginPass(i);

		Device->SetFVF(SCENE_VERTEX::FVF);
		Device->DrawIndexedPrimitiveUP(
			D3DPT_TRIANGLELIST,
			0,
			4,
			2,
			this->scenePlaneIndex,
			D3DFMT_INDEX16,
			this->scenePlaneVertex,
			sizeof(SCENE_VERTEX));


		this->postEffect->EndPass();
	}
	this->postEffect->End();
}


void cScene::RenderDepthOfField()
{
	//
	// Blur Scene ����
	//

	float pixelU = 1.0f / WINSIZE_X;
	float pixelV = 1.0f / WINSIZE_Y;
	this->postEffect->SetFloat("pixelSizeU", pixelU);
	this->postEffect->SetFloat("pixelSizeV", pixelV);
	this->postEffect->SetFloat("pixelHalfSizeU", pixelU * 0.5f);
	this->postEffect->SetFloat("pixelHalfSizeV", pixelV * 0.5f);


	for (int i = 0; i < 10; i++)
	{

		//BlurX

		this->pMainCamera->RenderTextureBegin(0, 5, 0x00101010);
		this->postEffect->SetTechnique("BlurX");

		if (i == 0)
		{
			this->postEffect->SetTexture("screenTex", this->pMainCamera->GetRenderTexture(0));
		}

		else
		{
			this->postEffect->SetTexture("screenTex", this->pMainCamera->GetRenderTexture(6));
		}

		UINT iPass;
		this->postEffect->Begin(&iPass, 0);
		for (UINT i = 0; i < iPass; i++) {
			this->postEffect->BeginPass(i);

			Device->SetFVF(SCENE_VERTEX::FVF);
			Device->DrawIndexedPrimitiveUP(
				D3DPT_TRIANGLELIST,
				0,
				4,
				2,
				this->scenePlaneIndex,
				D3DFMT_INDEX16,
				this->scenePlaneVertex,
				sizeof(SCENE_VERTEX));


			this->postEffect->EndPass();
		}
		this->postEffect->End();

		this->pMainCamera->RenderTextureEnd(0, 5);


		//BlurY

		pixelU = 1.0f / (WINSIZE_X / 4);		//5 �� Texture �� Size�� WINSIZE_X / 2 
		pixelV = 1.0f / (WINSIZE_Y / 4);		//5 �� Texture �� Size�� WINSIZE_X / 2 
		this->postEffect->SetFloat("pixelSizeU", pixelU);
		this->postEffect->SetFloat("pixelSizeV", pixelV);
		this->postEffect->SetFloat("pixelHalfSizeU", pixelU * 0.5f);
		this->postEffect->SetFloat("pixelHalfSizeV", pixelV * 0.5f);


		this->pMainCamera->RenderTextureBegin(0, 6, 0x00101010);
		this->postEffect->SetTechnique("BlurY");
		this->postEffect->SetTexture("screenTex", this->pMainCamera->GetRenderTexture(5));

		iPass;
		this->postEffect->Begin(&iPass, 0);
		for (UINT i = 0; i < iPass; i++) {
			this->postEffect->BeginPass(i);

			Device->SetFVF(SCENE_VERTEX::FVF);
			Device->DrawIndexedPrimitiveUP(
				D3DPT_TRIANGLELIST,
				0,
				4,
				2,
				this->scenePlaneIndex,
				D3DFMT_INDEX16,
				this->scenePlaneVertex,
				sizeof(SCENE_VERTEX));


			this->postEffect->EndPass();
		}
		this->postEffect->End();

		this->pMainCamera->RenderTextureEnd(0, 6);

	}



	this->postEffect->SetTechnique("DepthOfField");
	this->postEffect->SetTexture("screenTex", this->pMainCamera->GetRenderTexture(0));
	this->postEffect->SetTexture("blurTex", this->pMainCamera->GetRenderTexture(6));
	this->postEffect->SetTexture("normalTex", this->pMainCamera->GetRenderTexture(1));

	pixelU = 1.0f / WINSIZE_X;
	pixelV = 1.0f / WINSIZE_Y;
	this->postEffect->SetFloat("pixelSizeU", pixelU);
	this->postEffect->SetFloat("pixelSizeV", pixelV);
	this->postEffect->SetFloat("pixelHalfSizeU", pixelU * 0.5f);
	this->postEffect->SetFloat("pixelHalfSizeV", pixelV * 0.5f);

	UINT iPass;
	this->postEffect->Begin(&iPass, 0);
	for (UINT i = 0; i < iPass; i++) {
		this->postEffect->BeginPass(i);

		Device->SetFVF(SCENE_VERTEX::FVF);
		Device->DrawIndexedPrimitiveUP(
			D3DPT_TRIANGLELIST,
			0,
			4,
			2,
			this->scenePlaneIndex,
			D3DFMT_INDEX16,
			this->scenePlaneVertex,
			sizeof(SCENE_VERTEX));


		this->postEffect->EndPass();
	}
	this->postEffect->End();
}


void cScene::RenderColorLevel()
{
	//
	// Color Level
	//

	this->postEffect->SetTechnique("ColorLevel");
	this->postEffect->SetTexture("screenTex", this->pMainCamera->GetRenderTexture(0));

	this->postEffect->SetFloat("InBlack", 79);
	this->postEffect->SetFloat("InWhite", 216);
	this->postEffect->SetFloat("Gamma", 0.39);
	this->postEffect->SetFloat("OutBlack", 15);
	this->postEffect->SetFloat("OutWhite", 255);

	float pixelU = 1.0f / WINSIZE_X;
	float pixelV = 1.0f / WINSIZE_Y;
	this->postEffect->SetFloat("pixelSizeU", pixelU);
	this->postEffect->SetFloat("pixelSizeV", pixelV);
	this->postEffect->SetFloat("pixelHalfSizeU", pixelU * 0.5f);
	this->postEffect->SetFloat("pixelHalfSizeV", pixelV * 0.5f);

	UINT iPass;
	this->postEffect->Begin(&iPass, 0);
	for (UINT i = 0; i < iPass; i++) {
		this->postEffect->BeginPass(i);

		Device->SetFVF(SCENE_VERTEX::FVF);
		Device->DrawIndexedPrimitiveUP(
			D3DPT_TRIANGLELIST,
			0,
			4,
			2,
			this->scenePlaneIndex,
			D3DFMT_INDEX16,
			this->scenePlaneVertex,
			sizeof(SCENE_VERTEX));


		this->postEffect->EndPass();
	}
	this->postEffect->End();
}


void cScene::RenderGlow()
{
	//
	// Color Level
	//

	//5 ���� �׸���.
	this->pMainCamera->RenderTextureBegin(0, 5, 0x00101010);

	this->postEffect->SetTechnique("ColorLevel");
	this->postEffect->SetTexture("screenTex", this->pMainCamera->GetRenderTexture(0));

	this->postEffect->SetFloat("InBlack", 79);
	this->postEffect->SetFloat("InWhite", 139);
	this->postEffect->SetFloat("Gamma", 0.54f);
	this->postEffect->SetFloat("OutBlack", 0);
	this->postEffect->SetFloat("OutWhite", 200);

	float pixelU = 1.0f / (WINSIZE_X / 4);
	float pixelV = 1.0f / (WINSIZE_Y / 4);
	this->postEffect->SetFloat("pixelSizeU", pixelU);
	this->postEffect->SetFloat("pixelSizeV", pixelV);
	this->postEffect->SetFloat("pixelHalfSizeU", pixelU * 0.5f);
	this->postEffect->SetFloat("pixelHalfSizeV", pixelV * 0.5f);

	UINT iPass;
	this->postEffect->Begin(&iPass, 0);
	for (UINT i = 0; i < iPass; i++) {
		this->postEffect->BeginPass(i);

		Device->SetFVF(SCENE_VERTEX::FVF);
		Device->DrawIndexedPrimitiveUP(
			D3DPT_TRIANGLELIST,
			0,
			4,
			2,
			this->scenePlaneIndex,
			D3DFMT_INDEX16,
			this->scenePlaneVertex,
			sizeof(SCENE_VERTEX));

		this->postEffect->EndPass();
	}
	this->postEffect->End();

	this->pMainCamera->RenderTextureEnd(0, 5);

	//
	// Color Level �����Ȱ� �� ó��
	//
	for (int i = 0; i < 10; i++)
	{
		//BlurX

		this->pMainCamera->RenderTextureBegin(0, 6, 0x00101010);
		this->postEffect->SetTechnique("BlurX");
		this->postEffect->SetTexture("screenTex", this->pMainCamera->GetRenderTexture(5));

		UINT iPass;
		this->postEffect->Begin(&iPass, 0);
		for (UINT i = 0; i < iPass; i++) {
			this->postEffect->BeginPass(i);

			Device->SetFVF(SCENE_VERTEX::FVF);
			Device->DrawIndexedPrimitiveUP(
				D3DPT_TRIANGLELIST,
				0,
				4,
				2,
				this->scenePlaneIndex,
				D3DFMT_INDEX16,
				this->scenePlaneVertex,
				sizeof(SCENE_VERTEX));


			this->postEffect->EndPass();
		}
		this->postEffect->End();

		this->pMainCamera->RenderTextureEnd(0, 6);


		//BlurY
		this->pMainCamera->RenderTextureBegin(0, 5, 0x00101010);
		this->postEffect->SetTechnique("BlurY");
		this->postEffect->SetTexture("screenTex", this->pMainCamera->GetRenderTexture(6));

		iPass;
		this->postEffect->Begin(&iPass, 0);
		for (UINT i = 0; i < iPass; i++) {
			this->postEffect->BeginPass(i);

			Device->SetFVF(SCENE_VERTEX::FVF);
			Device->DrawIndexedPrimitiveUP(
				D3DPT_TRIANGLELIST,
				0,
				4,
				2,
				this->scenePlaneIndex,
				D3DFMT_INDEX16,
				this->scenePlaneVertex,
				sizeof(SCENE_VERTEX));


			this->postEffect->EndPass();
		}
		this->postEffect->End();

		this->pMainCamera->RenderTextureEnd(0, 5);

	}



	this->postEffect->SetTechnique("BBo");
	this->postEffect->SetFloat("blurAmout", 1.5f);
	this->postEffect->SetTexture("screenTex", this->pMainCamera->GetRenderTexture(0));
	this->postEffect->SetTexture("blurTex", this->pMainCamera->GetRenderTexture(5));

	pixelU = 1.0f / WINSIZE_X;
	pixelV = 1.0f / WINSIZE_Y;
	this->postEffect->SetFloat("pixelSizeU", pixelU);
	this->postEffect->SetFloat("pixelSizeV", pixelV);
	this->postEffect->SetFloat("pixelHalfSizeU", pixelU * 0.5f);
	this->postEffect->SetFloat("pixelHalfSizeV", pixelV * 0.5f);

	iPass;
	this->postEffect->Begin(&iPass, 0);
	for (UINT i = 0; i < iPass; i++) {
		this->postEffect->BeginPass(i);

		Device->SetFVF(SCENE_VERTEX::FVF);
		Device->DrawIndexedPrimitiveUP(
			D3DPT_TRIANGLELIST,
			0,
			4,
			2,
			this->scenePlaneIndex,
			D3DFMT_INDEX16,
			this->scenePlaneVertex,
			sizeof(SCENE_VERTEX));


		this->postEffect->EndPass();
	}
	this->postEffect->End();


}
