#pragma once

#include "cBaseObject.h"
#include "cParticle.h"


enum PATICLE_EMISSION_TYPE{
	PZERO,				//�������� ���
	SPHERE,				//������ ���
	SPHERE_OUTLINE,		//������ ����ϴµ� �ܺ�ǥ�鿡����....
	BOX					//�ڽ����� ���
};



//
// ��ƼŬ�� ��������ִ� ��
//
class cPartcleEmitter : public cBaseObject
{
private:
	DWORD				m_PaticleNum;				//������ �ѷ�
	cParticle*			m_pPaticles;				//��ƼŬ �迭
	LPPARTICLE_VERTEX	m_ParticleVerticles;		//��ƼŬ ���ؽ�
	float				m_fEmissionPerSec;			//�ʴ� �߻���

	DWORD				m_dwParticleCount;			//Ȱ��ȭ ����
	
	VEC_COLOR			m_Colors;					//��ƼŬ �÷� �迭
	VEC_SCALE			m_Scales;					//��ƼŬ ������ �迭

	//��ƼŬ ���̺� Ÿ�� �ִ� �ּ�
	float				m_fStartLiveTimeMin;
	float				m_fStartLiveTimeMax;
	
	//��ƼŬ ���� �ӵ� �ִ� �ּ�
	D3DXVECTOR3			m_StartVelocityMin;			
	D3DXVECTOR3			m_StartVelocityMax;

	//��ƼŬ ���� ���� �ִ� �ּ�
	D3DXVECTOR3			m_StartAccelateMin;
	D3DXVECTOR3			m_StartAccelateMax;

	//��ƼŬ ���� ������ �ִ� �ּ�
	float				m_fStartScaleMin;
	float				m_fStartScaleMax;

	
	bool				m_bEmission;				//���� �������̴�?
	float				m_fEmisionIntervalTime;		//���� ���� �ð�
	float				m_fEmisionDeltaTime;		//�ϳ� �����ϱ� �����ð�

	//particle Texture 
	LPDIRECT3DTEXTURE9	m_pTex;

	bool				m_bLocal;					//�����̴�?


public:
	//��ƼŬ ����Ÿ��
	PATICLE_EMISSION_TYPE	EmissionType;		//��ƼŬ ����Ÿ��

	//��ƼŬ ��������
	float					MinEmissionRangeX;		//X ��������
	float					MaxEmissionRangeX;		
	float					MinEmissionRangeY;		//Y ��������
	float					MaxEmissionRangeY;
	float					MinEmissionRangeZ;		//Z ��������
	float					MaxEmissionRangeZ;
	float					SphereEmissionRange;		//�������� ���� ������





public:
	cPartcleEmitter(void);
	~cPartcleEmitter(void);

	void Init( 
		DWORD partcleNum,					//�� ��ƼŬ ��
		float emission,						//�ʴ� �߻���
		float liveTimeMin,					//��ƼŬ�ϳ��� �ð�
		float liveTimeMax,
		const D3DXVECTOR3& velocityMin,		//��ƼŬ ���� �ӵ�
		const D3DXVECTOR3& velocityMax,
		const D3DXVECTOR3& accelMin,		//��ƼŬ ����
		const D3DXVECTOR3& accelMax,
		const VEC_COLOR& colors,			//��ƼŬ �÷� ���͹迭
		const VEC_SCALE& scales,			//��ƼŬ ������ �÷��迭
		float scaleMin,						//��ƼŬ ������
		float scaleMax,
		LPDIRECT3DTEXTURE9 pPaticleTexture,	//��ƼŬ Texture
		bool bLocal = false 				//�̰� true �� ��ƼŬ�� �������� ����Transform Local �������� �����δ�.
		);
	
	void Release();

	virtual void BaseObjectUpdate( float timeDelta ) override;			//BaseObject �� Update �� ����....
	virtual void BaseObjectRender() override;

	void StartEmission();			//��ƼŬ ���� ����
	void StopEmission();			//��ƼŬ ���� ����

	//��� �ȹ����� ���� ��Ʈ����.
	void Burst( int num, float minSpeed, float maxSpeed, float maxLife, float minLife );			

	void SetRenderLocal( bool bLocal ){
		m_bLocal = bLocal;
	}

	
private:
	void StartOneParticle();		//��ƼŬ �ϳ� ����

	//��ƼŬ �ϳ� ���� ( ���� �־ )
	void StartOneParticle( D3DXVECTOR3 dir, float life );
};

