#pragma once

#include <vector>
#include "cTransform.h"

//��ƼŬ ���� ����ü
typedef struct tagPARTICLEQUAD_VERTEX{
	D3DXVECTOR3 pos;			//���� ��ġ
	DWORD color;				//���� �÷�
	D3DXVECTOR2 uv;				//���� UV
	enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 };
}PARTICLEQUAD_VERTEX, *LPPARTICLEQUAD_VERTEX;

typedef std::vector<D3DXCOLOR>			VEC_COLOR;
typedef std::vector<float>				VEC_SCALE;

class cParticleQuad
{
public:
	cTransform		m_Transform;		//��ƼŬ�� ��ġ��

private:
	bool			m_bLive;			//Ȱ��ȭ ����
	
	float			m_fTotalLiveTime;	//�� Ȱ��ȭ �ð�
	float			m_fDeltaLiveTime;	//Ȱ��ȭ ���� �ð�
	float			m_fNomalizeLiveTime;//Ȱ��ȭ ���� �ð�( 0 ~ 1 )

	
	D3DXVECTOR3		m_Velocity;			//��ƼŬ�� �ӵ�����
	D3DXVECTOR3		m_Accelation;		//�ʴ� �����ϴ� ���Ӻ���
	D3DXVECTOR3		m_Rotate;			//�ʴ� ȸ�� ����
	D3DXVECTOR3		m_RotateAccel;		//�ʴ� �����ϴ� ȸ������

	float			m_fScale;			//�⺻ �����ϰ�

public:
	cParticleQuad(void);
	~cParticleQuad(void);

	void Start( 
		float liveTime,				//���̺� Ÿ��
		const D3DXVECTOR3* pos,		//���� ��ġ
		const D3DXVECTOR3* velo,		//���� �ӵ�
		const D3DXVECTOR3* accel,	//���� ��
		const D3DXVECTOR3* rotate,	//�ʴ� ȸ�� ��
		const D3DXVECTOR3* rotateAccel,	//�ʴ� ȸ�� ������
		float scale					//�⺻ ������
		);

	void Update( float timeDelta );	

	//�ڽ��� ���� ������ �������� LPPARTICLEQUAD_VERTEX �� ���� �־��ش�.
	void GetParticleVertex( 
		LPPARTICLEQUAD_VERTEX pOut, 
		DWORD* pIndex,
		const VEC_COLOR& colors,
		const VEC_SCALE& scales,
		DWORD dwParticleNum );

	bool isLive(){
		return m_bLive;
	}

	
};

