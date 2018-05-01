#pragma once

#include <vector>
#include "cTransform.h"

//��ƼŬ ���� ����ü
typedef struct tagPARTICLE_VERTEX{
	D3DXVECTOR3 pos;			//���� ��ġ
	float size;					//��ƼŬ ���� ���� ������
	DWORD color;				//���� �÷�
	enum { FVF = D3DFVF_XYZ  | D3DFVF_PSIZE | D3DFVF_DIFFUSE };
}PARTICLE_VERTEX, *LPPARTICLE_VERTEX;


typedef std::vector<D3DXCOLOR>			VEC_COLOR;
typedef std::vector<float>				VEC_SCALE;

//
// ���� �ϳ������� ����
//
class cParticle
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
	float			m_fScale;			//�⺻ �����ϰ�

public:
	cParticle(void);
	~cParticle(void);

	void Start( 
		float liveTime,				//���̺� Ÿ��
		const D3DXVECTOR3* pos,		//���� ��ġ
		const D3DXVECTOR3* velo,	//���� �ӵ�
		const D3DXVECTOR3* accel,	//���� ��
		float scale					//�⺻ ������
		);

	void Update( float timeDelta );	

	//�ڽ��� ���� ������ �������� LPPARTICLE_VERTEX �� ���� �־��ش�.
	void GetParticleVertex( 
		LPPARTICLE_VERTEX pOut, 
		const VEC_COLOR& colors,
		const VEC_SCALE& scales );


	bool isLive(){
		return m_bLive;
	}


};

