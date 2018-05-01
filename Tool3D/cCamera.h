#pragma once

#include "cTransform.h"
#include "cFrustum.h"

#define MAX_RENDERTARGET 10

class cCamera : public cTransform
{
public:
	struct RenderTarget{
		LPDIRECT3DTEXTURE9		m_pRenderTexture;				//�������� Texture
		LPDIRECT3DSURFACE9		m_pRenderSurface;				//���� Texture Deapth ���ۿ� Stencil ���۰� �ִ� Surface
		LPDIRECT3DSURFACE9		m_pDeviceTargetSurface;
		LPDIRECT3DSURFACE9		m_pDeviceDepthAndStencilSurface;

		RenderTarget(){
			m_pRenderTexture = NULL;			
			m_pRenderSurface = NULL;						
			m_pDeviceTargetSurface = NULL;		
			m_pDeviceDepthAndStencilSurface = NULL;		
		}
	};


public:
	float fov;			//ī�޶� ȭ��
	float camNear;		//ī�޶� Near
	float camFar;		//ī�޶� Far
	float aspect;		//ī�޶� ��Ⱦ��
	bool bOrtho;		//������?
	float orthoSize;	//�����û�����

protected:
	D3DXMATRIXA16		matView;		//�����
	D3DXMATRIXA16		matProjection;	//�������
	D3DXMATRIXA16		matViewProjection;	//�� * �������

private:
	RenderTarget		renderTargets[MAX_RENDERTARGET];
	RenderTarget		shadow;

public:
	cFrustum			Frustum;


public:
	cCamera(void);
	~cCamera(void);


	//������İ� View ����� ������Ʈ
	void UpdateMatrix();

	//View ��İ� ���� ����� ����
	void UpdateCamToDevice( LPDIRECT3DDEVICE9 pDevice );

	//�������� ������Ʈ
	void UpdateFrustum();

	//ī�޶� ���� ����� ��´�.
	D3DXMATRIXA16 GetViewMatrix() const{
		return this->matView;
	}

	D3DXMATRIXA16 GetProjectionMatrix() const{
		return this->matProjection;
	}

	D3DXMATRIXA16 GetViewProjectionMatrix() const{
		return this->matViewProjection;
	}

	//ȭ�� ����
	void SetFov( float fov ){
		this->fov = fov;
	}

	float GetFov(){
		return this->fov;
	}

	void OrthoToggle(){
		this->bOrtho = !this->bOrtho;
	}

	//ȭ���� ��ġ�� ������ ī�޶��� ���� ���̸� ��´�
	void ComputeRay( LPRay pOutRay, const D3DXVECTOR2* screenPos ); 

	//���� ��ġ��  ȭ���� ��ġ�� ��´�.
	bool GetWorldPosToScreenPos( D3DXVECTOR2* pScreenPos, const D3DXVECTOR3* pWorldPos );




	//���� Texture �� �غ� �Ѵ�. ( ������ RenderTarget �ε��� )
	void ReadyRenderToTexture( int idx, int width, int height );

	//Shadow Map Texture�� �غ��Ѵ�.
	void ReadyShadowTexture( int size );

	//���� Texture �� ������ ���� ( �������� �������� �ѹ� �� RenderTarget Index )
	void RenderTextureBegin( int stageNumber, int idx, DWORD clearColor );

	//���� Texture �� ������ ���� ( �������� ����� �������� �ѹ� �� RenderTarget Index )
	void RenderTextureEnd( int stageNumber, int idx);

	//������ Map ���� ����
	void RenderShadowBegin();

	//������ Map ���� ����
	void RenderShadowEnd();



	//���� Texture ��´�. ( ���� ���� �ε��� )
	LPDIRECT3DTEXTURE9 GetRenderTexture( int idx );

	//������ Texture ��´�.
	LPDIRECT3DTEXTURE9 GetShadowTexture();


};

