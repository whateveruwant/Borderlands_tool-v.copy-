#include "StdAfx.h"
#include "cParticleQuad.h"


cParticleQuad::cParticleQuad(void)
{
}


cParticleQuad::~cParticleQuad(void)
{
}


void cParticleQuad::Start( 
		float liveTime,				//���̺� Ÿ��
		const D3DXVECTOR3* pos,		//���� ��ġ
		const D3DXVECTOR3* velo,		//���� �ӵ�
		const D3DXVECTOR3* accel,	//���� ��
		const D3DXVECTOR3* rotate,	//�ʴ� ȸ�� ��
		const D3DXVECTOR3* rotateAccel,	//�ʴ� ȸ�� ������
		float scale					//�⺻ ������
		)
{
	//Ȱ��ȭ ����
	m_bLive = true;

	//���̺� Ÿ�� �ʱ�ȭ
	m_fTotalLiveTime = liveTime;
	m_fDeltaLiveTime = 0.0f;

	//��ġ ������
	m_Transform.SetWorldPosition(
		pos->x, pos->y, pos->z );

	//���� �ӵ�
	m_Velocity = *velo;

	//����
	m_Accelation = *accel;

	//ȸ��
	m_Rotate = *rotate;

	//ȸ�� ����
	m_RotateAccel = *rotateAccel;

	//�⺻ ������
	m_fScale = scale;
}


void cParticleQuad::Update( float timeDelta )
{
	if( m_bLive == false ) return;

	//���̺� Ÿ���� �ٵǾ��ٸ�...
	if( m_fDeltaLiveTime > m_fTotalLiveTime ){
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

	m_Transform.RotateSelf( 
		m_Rotate.x * timeDelta, 
		m_Rotate.y * timeDelta, 
		m_Rotate.z * timeDelta ); 

	//��ƼŬ ����
	m_Velocity += m_Accelation * timeDelta;

	//��ƼŬ ȸ�� ����
	m_Rotate += m_RotateAccel * timeDelta;
}

//�ڽ��� ���� ������ �������� LPPARTICLEQUAD_VERTEX �� ���� �־��ش�.
void cParticleQuad::GetParticleVertex( 
		LPPARTICLEQUAD_VERTEX pOut, 
		DWORD* pIndex,
		const VEC_COLOR& colors,
		const VEC_SCALE& scales,
		DWORD dwParticleNum )
{
	//��ƼŬ ��ġ ��
    D3DXVECTOR3 center = m_Transform.GetWorldPosition();
	
	DWORD dwcolor = 0;
	float scale;


	//
	// ������ ����
	//

	//������ ���� ���
	float s = 0.0f;

	//������ �迭�� ������ �ε���
	int lastIndex = scales.size() - 1;

	if( m_fNomalizeLiveTime == 1.0f ){
		dwcolor = colors[ colors.size() -  1 ];
		scale = m_fScale * scales[ scales.size() - 1];
	}

	else if( m_fNomalizeLiveTime == 0.0f ){
		dwcolor = colors[ 0 ];
		scale = m_fScale * scales[0];
	}

	else{

		//������ ���͹�
		float interval = 1.0f / lastIndex;

		//���� ���̺� Ÿ�� ���� ���� ��ġ
		float position = m_fNomalizeLiveTime / interval;

		//�����ε���
		int startIndex = (int)position;

		//���� �ε���
		int endIndex = startIndex + 1;

		//������
		float fN = position - startIndex;
		s = ( scales[endIndex] - scales[startIndex] ) * fN + scales[startIndex];

		//���� ������ �� ����
		scale = m_fScale * s;



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

		dwcolor = (DWORD)( color );
	}


	//�����Ͽ� ���� halfSize;
	float halfScale = scale * 0.5f;

	//����
	D3DXVECTOR3 x = m_Transform.GetRight();
	D3DXVECTOR3 y = m_Transform.GetUp();

	//���� ���� ����
	( pOut + 0 )->pos = center + ( -x * halfScale ) + ( y * halfScale );
	( pOut + 1 )->pos = center + (  x * halfScale ) + ( y * halfScale );
	( pOut + 2 )->pos = center + ( -x * halfScale ) + ( -y * halfScale );
	( pOut + 3 )->pos = center + (  x * halfScale ) + ( -y * halfScale );

	( pOut + 0 )->uv = D3DXVECTOR2( 0, 0 );
	( pOut + 1 )->uv = D3DXVECTOR2( 1, 0 );
	( pOut + 2 )->uv = D3DXVECTOR2( 0, 1 );
	( pOut + 3 )->uv = D3DXVECTOR2( 1, 1 );

	( pOut + 0 )->color = dwcolor;
	( pOut + 1 )->color = dwcolor;
	( pOut + 2 )->color = dwcolor;
	( pOut + 3 )->color = dwcolor;


	//0----1
	//|   /|
	//|  / |
	//| /  |
	//|/   |
	//2----3

	//�ε��� ���� ���� ( �ε��� ������ ���ݱ��� �׷����� Quad ����ŭ �������� ���� �־�� �Ѵ� )
	*( pIndex + 0 ) = (dwParticleNum * 4 ) + 0;
	*( pIndex + 1 ) = (dwParticleNum * 4 ) + 1;
	*( pIndex + 2 ) = (dwParticleNum * 4 ) + 2;
	*( pIndex + 3 ) = (dwParticleNum * 4 ) + 2;
	*( pIndex + 4 ) = (dwParticleNum * 4 ) + 1;
	*( pIndex + 5 ) = (dwParticleNum * 4 ) + 3;

}