#pragma once
class cCamera;
class cLight_Direction;

class cTerrain;

class cScene
{
private:
	typedef struct SCENE_VERTEX {
		D3DXVECTOR3 pos;
		D3DXVECTOR2 uv;
		enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1 };
	}SCENE_VERTEX, *LPSCENE_VETEX;

protected:
	cCamera*						pMainCamera;
	LPDIRECT3DCUBETEXTURE9			evironmentTexture;			//ȯ�� Texture
	LPD3DXMESH						evironmemtSphereMesh;		//ȯ�� ��
	LPD3DXEFFECT					evironmentEffect;			//ȯ�� Effect

	SCENE_VERTEX					scenePlaneVertex[4];		//���÷� ���ؽ�
	WORD							scenePlaneIndex[6];			//�ε���

	LPD3DXEFFECT					postEffect;					//PostEffect
	vector<cLight*>					pSceneDarkLight;			//���� ��ġ�� �⺻������
	cLight_Direction*				pSceneBaseDirectionLight;	//���� ��ġ�� �⺻������
	cCamera*						pDirectionLightCamera;		//���⼺ ������ ���� ī�޶�...

	float							shadowDistance;				//�׸��� �Ÿ�

public:

	cScene(void);
	~cScene(void);

	HRESULT Init();
	void Release();
	void Update(float timeDelta);
	void Render();

	//���� ī�޶��� RenderToTexture �� ������Ʈ�Ѵ�.
	void RenderToMainCamTexture();

	void SetEnvironment(std::string cubeFilePath);

	void ReadyShadowMap(std::vector<cBaseObject*>* renderObjects, cTerrain* pTerrain = NULL);


	//����ī�޶��� ���� Texture �� ��´�.
	LPDIRECT3DTEXTURE9 GetTexture();

private:

	//������ ȣ��� �Լ����� �߻��Լ���...
	virtual HRESULT Scene_Init() = 0;
	virtual void Scene_Release() = 0;
	virtual void Scene_Update(float timDelta) = 0;


	virtual void Scene_Render0() {}
	virtual void Scene_Render1() = 0;
	virtual void Scene_Render2() {}
	virtual void Scene_Render_AfterPostEffect(LPDIRECT3DTEXTURE9 pScreen) {}

	virtual void Scene_RenderSprite() {}

	//ȯ�汸 ����
	void RenderEnvironment();


private:
	void RenderBase();
	void RenderOutline();
	void RenderBBo();
	void RenderDepthOfField();
	void RenderColorLevel();
	void RenderGlow();

};