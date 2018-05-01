#include "StdAfx.h"
#include "cParticle.h"


cParticle::cParticle(void)
 :m_bLive( false )
{
}


cParticle::~cParticle(void)
{
}



void cParticle::Start( 
		float liveTime,				//���̺� Ÿ��
		const D3DXVECTOR3* pos,		//���� ��ġ
		const D3DXVECTOR3* velo,	//���� �ӵ�
		const D3DXVECTOR3* accel,	//���� ��
		float scale					//�⺻ ������
		)
{
	//Ȱ��ȭ ����
	m_bLive = true;

	//���̺� Ÿ�� �ʱ�ȭ
	m_fTotalLiveTime = liveTime;
	m_fDeltaLiveTime = 0.0f;
	m_fNomalizeLiveTime = 0.0f;


	//��ġ ������
	m_Transform.SetWorldPosition( pos->x, pos->y, pos->z );

	//���� �ӵ�
	m_Velocity = *velo;

	//����
	m_Accelation = *accel;

	//�⺻ ������
	m_fScale = scale;
}


void cParticle::Update( float timeDelta )
{
	if( m_bLive == false ) return;
	
	//���̺� Ÿ���� �ٵǾ��ٸ�...
	if( m_fDeltaLiveTime >= m_fTotalLiveTime ){
		m_bLive = false;
	}

	//Ȱ��ȭ �ð� �״´�.
	m_fDeltaLiveTime += timeDelta;

	//����ȭ�� �ð����� ���
	m_fNomalizeLiveTime = m_fDeltaLiveTime / m_fTotalLiveTime;
	if( m_fNomalizeLiveTime > 1.0f )
		m_fNomalizeLiveTime = 1.0f;


	//��ƼŬ ���� �̵�
	m_Transform.MovePositionWorld(
		m_Velocity.x * timeDelta, 
		m_Velocity.y * timeDelta, 
		m_Velocity.z * timeDelta );

	//��ƼŬ ����
	m_Velocity += m_Accelation * timeDelta;

}


//�ڽ��� ���� ������ �������� LPPARTICLE_VERTEX �� ���� �־��ش�.
void cParticle::GetParticleVertex( 
		LPPARTICLE_VERTEX pOut, 
		const VEC_COLOR& colors,
		const VEC_SCALE& scales )
{

	//��ƼŬ ��ġ ��
	pOut->pos = m_Transform.GetWorldPosition();

	if( m_fNomalizeLiveTime == 1.0f ){
		pOut->color = colors[ colors.size() -  1 ];
		pOut->size = m_fScale * scales[ scales.size() - 1];
		return;
	}

	else if( m_fNomalizeLiveTime == 0.0f ){
		pOut->color = colors[ 0 ];
		pOut->size = m_fScale * scales[ 0 ];
		return;
	}

	
	//
	// ������ ����
	//

	// ������ ���� ���
	float s = 0.0f;

	//������ �迭�� ������ �ε���
	int lastIndex = scales.size() - 1;

	//������ ���͹�
	float interval = 1.0f / lastIndex;

	//���� ���̺� Ÿ�� ���� ���� ��ġ
	float position = m_fNomalizeLiveTime / interval;
	//position �� ���� �����κ��� ���Ǵ� �迭�� �ε����� �Ǵ� ���̰�.
	//�Ҽ��� �κ��� ���� �迭�������� �������� �ȴ�.


	//�����ε���
	int startIndex = (int)position;
	
	//���� �ε���
	int endIndex = startIndex + 1;

	//������
	float fN = position - startIndex;
	s = Lerp( scales[startIndex], scales[endIndex], fN );

	//���� ������ �� ����
	pOut->size = m_fScale * s;


	//
	// �÷� ����
	//

	//�÷� �迭�� ������ �ε���
	lastIndex = colors.size() - 1;

	//�÷� ���͹�
	interval = 1.0f / lastIndex;

	//���� ���̺� Ÿ�� ���� ���� ��ġ
	position = m_fNomalizeLiveTime / interval;

	//�����ε���
	startIndex = (int)position;

	//���� �ε���
	endIndex = startIndex + 1;

	//������
	fN = position - startIndex;




	//���� �÷���
	D3DXCOLOR color;

	//�÷� ���� ����
	D3DXColorLerp(&color,			//���
		&colors[startIndex],		//from
		&colors[endIndex],			//to
		fN );						//normalize Factor

	
	//���� �÷��� ����
	pOut->color = (DWORD)( color );
}


