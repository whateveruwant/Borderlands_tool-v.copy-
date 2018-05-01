#pragma once
#include "cbaseobject.h"
#include "cParticleQuad.h"

class cQuadParticleEmitter :public cBaseObject
{
private:

	DWORD					m_PaticleNum;				//������ �ѷ�
	cParticleQuad*			m_pPaticles;				//��ƼŬ �迭
	cParticleQuad**			m_pSortArray;				//��ƼŬ ��Ʈ�� Array

	LPPARTICLEQUAD_VERTEX	m_ParticleVerticles;		//��ƼŬ ���ؽ�
	DWORD*					m_ParticleIndex;			//��ƼŬ �ε���

	float					m_fEmissionPerSec;			//�ʴ� �߻���
	DWORD					m_dwParticleCount;			//Ȱ��ȭ ����

	VEC_COLOR				m_Colors;					//��ƼŬ �÷� �迭
	VEC_SCALE				m_Scales;					//��ƼŬ ������ �迭

	cTransform*				m_pCameraTransform;			//ī�޶� Ʈ������
	bool					m_bCameraSort;				//ī�޶� �Ÿ��� ��Ʈ�Ҳ���?....


	//��ƼŬ ���̺� Ÿ�� �ִ� �ּ�
	float				m_fStartLiveTimeMin;
	float				m_fStartLiveTimeMax;

	//��ƼŬ ���� �ӵ� �ִ� �ּ�
	D3DXVECTOR3			m_StartVelocityMin;			
	D3DXVECTOR3			m_StartVelocityMax;

	//��ƼŬ ���� ���� �ִ� �ּ�
	D3DXVECTOR3			m_StartAccelateMin;
	D3DXVECTOR3			m_StartAccelateMax;

	//��ƼŬ �����Ҷ� ȸ�� ���۰� �ִ� �ּ�
	D3DXVECTOR3			m_StartSetRotateMin;
	D3DXVECTOR3			m_StartSetRotateMax;

	//��ƼŬ ���� ȸ�� �ִ� �ּ�
	D3DXVECTOR3			m_StartRotateMin;
	D3DXVECTOR3			m_StartRotateMax;
	
	//��ƼŬ ȸ�� ���� �ִ� �ּ�
	D3DXVECTOR3			m_StartRotateAccelateMin;
	D3DXVECTOR3			m_StartRotateAccelateMax;

	//��ƼŬ ���� ������ �ִ� �ּ�
	float				m_fStartScaleMin;
	float				m_fStartScaleMax;

	bool				m_bEmission;				//���� �������̴�?
	float				m_fEmisionIntervalTime;		//���� ���� �ð�
	float				m_fEmisionDeltaTime;		//�ϳ� �����ϱ� �����ð�

	//particle Texture 
	LPDIRECT3DTEXTURE9		m_pTex;

	bool				m_bLocal;



public:
	cQuadParticleEmitter(void);
	~cQuadParticleEmitter(void);


	HRESULT Init( 
		DWORD partcleNum,					//�� ��ƼŬ ��
		float emission,						//�ʴ� �߻���
		float liveTimeMin,
		float liveTimeMax,
		const D3DXVECTOR3& velocityMin,
		const D3DXVECTOR3& velocityMax,
		const D3DXVECTOR3& accelMin,
		const D3DXVECTOR3& accelMax,
		const D3DXVECTOR3& startRotateMin,		//�����Ҷ� ȸ�� �ּҰ� 
		const D3DXVECTOR3& startRotateMax,		//�����Ҷ� ȸ�� �ִ밪
		const D3DXVECTOR3& rotateMin,			//�����ӿ����� ȸ�� �ּҷ�
		const D3DXVECTOR3& rotateMax,			//�����ӿ����� ȸ�� �ִ뷮
		const D3DXVECTOR3& rotateAccelMin,		//������ ���ӿ����� ȸ�� �ּҷ�
		const D3DXVECTOR3& rotateAccelMax,		//������ ���ӿ����� ȸ�� �ִ뷮
		const VEC_COLOR& colors,
		const VEC_SCALE& scales, 
		float scaleMin,
		float scaleMax,
		LPDIRECT3DTEXTURE9 pTex,
		bool bLocal = false
		);
	
	void Release();

	virtual void BaseObjectUpdate( float timeDelta ) override;			//BaseObject �� Update �� ����....
	virtual void BaseObjectRender() override;


	void StartEmission();			//��ƼŬ ���� ����
	void StopEmission();			//��ƼŬ ���� ����

	//ī�޶� ������ �Ҳ���?
	void SetCameraSort( cTransform* pCameraTrans, bool bSort );

	
	void SetRenderLocal( bool bLocal ){
		m_bLocal = bLocal;
	}



private:

	void StartOneParticle();		//��ƼŬ �ϳ� ����

};

