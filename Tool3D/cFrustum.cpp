#include "StdAfx.h"
#include "cFrustum.h"
#include "cTransform.h"

cFrustum::cFrustum(void)
{
	//���� ��ǥ ���� ����
	//					  4-------5  <-( 1, 1, 1 )
	//					 /|		 /|
	//					0-------1 |
	//					| 6-----|-7
	//					|/      |/
	//( -1, -1, 0 )->	2-------3
	m_RHWPos[0] = D3DXVECTOR3( -1,  1,  0 );
	m_RHWPos[1] = D3DXVECTOR3(  1,  1,  0 );
	m_RHWPos[2] = D3DXVECTOR3( -1, -1,  0 );
	m_RHWPos[3] = D3DXVECTOR3(  1, -1,  0 );
	m_RHWPos[4] = D3DXVECTOR3( -1,  1,  1 );
	m_RHWPos[5] = D3DXVECTOR3(  1,  1,  1 );
	m_RHWPos[6] = D3DXVECTOR3( -1, -1,  1 );
	m_RHWPos[7] = D3DXVECTOR3(  1, -1,  1 );

}


cFrustum::~cFrustum(void)
{
}

//�������� ���� ������Ʈ ( View * Projection ����� �䱸�Ѵ� )
void cFrustum::UpdateFrustum( const D3DXMATRIXA16* pmatViewProj )
{
	//ViewProjection �� �����
	D3DXMATRIXA16		matInv;
	D3DXMatrixInverse( &matInv, NULL, pmatViewProj );

	//���� ��ǥ�� ������ ����Ŀ� ����
	for( int i = 0 ; i < 8 ;  i++ ){
		D3DXVec3TransformCoord( m_Pos + i, m_RHWPos + i, &matInv );
	}

	
	//�÷� ������Ʈ
	//���� ��ǥ ���� ����
	//					  4-------5  <-( 1, 1, 1 )
	//					 /|		 /|
	//					0-------1 |
	//					| 6-----|-7
	//					|/      |/
	//( -1, -1, 0 )->	2-------3

	//���� �÷�
	PHYSICS_MGR->CreatePlane( &m_Plane[0], &m_Pos[0], &m_Pos[1], &m_Pos[2] );

	//�ĸ�
	PHYSICS_MGR->CreatePlane( &m_Plane[1], &m_Pos[5], &m_Pos[4], &m_Pos[7] );

	//����
	PHYSICS_MGR->CreatePlane( &m_Plane[2], &m_Pos[1], &m_Pos[5], &m_Pos[3] );

	//����
	PHYSICS_MGR->CreatePlane( &m_Plane[3], &m_Pos[4], &m_Pos[0], &m_Pos[6] );

	//���
	PHYSICS_MGR->CreatePlane( &m_Plane[4], &m_Pos[4], &m_Pos[5], &m_Pos[0] );

	//�ϴ�
	PHYSICS_MGR->CreatePlane( &m_Plane[5], &m_Pos[2], &m_Pos[3], &m_Pos[6] );

}

//Base ������Ʈ�� �������� �ȿ��ִ��� üũ
bool cFrustum::IsInFrustum( cBaseObject* pObject )
{
	//���� ������
	D3DXVECTOR3 worldCenter;
	float radius;

	pObject->BoundBox.GetWorldCenterRadius( 
		pObject->pTransform, 
		&worldCenter, 
		&radius );
		

	//worldCenter �� ����ü�� �� 6 ����ʿ� �ִ��� Ȯ��
	for( int i = 1 ; i < 6 ; i++ )
	{
		//����� �Ÿ�
		float dist = PHYSICS_MGR->PlaneDot( 
			&m_Plane[i], &worldCenter );

		//������ �̻� ����� ����ü �ȿ� ����....
		if( dist > radius )
			return false;
	}

	return true;
}

//�������� ����� �׸���.
void cFrustum::RenderGizmo()
{
	DWORD color = 0xff00ffff;
	//���� ��ǥ ���� ����
	//					  4-------5  <-( 1, 1, 1 )
	//					 /|		 /|
	//					0-------1 |
	//					| 6-----|-7
	//					|/      |/
	//( -1, -1, 0 )->	2-------3

	GIZMO_MGR->Line( m_Pos[0], m_Pos[1], color );
	GIZMO_MGR->Line( m_Pos[1], m_Pos[3], color );
	GIZMO_MGR->Line( m_Pos[3], m_Pos[2], color );
	GIZMO_MGR->Line( m_Pos[2], m_Pos[0], color );
							   
							   
	GIZMO_MGR->Line( m_Pos[4], m_Pos[5], color );
	GIZMO_MGR->Line( m_Pos[5], m_Pos[7], color );
	GIZMO_MGR->Line( m_Pos[7], m_Pos[6], color );
	GIZMO_MGR->Line( m_Pos[6], m_Pos[4], color );
							   
							   
	GIZMO_MGR->Line( m_Pos[0], m_Pos[4], color );
	GIZMO_MGR->Line( m_Pos[1], m_Pos[5], color );
	GIZMO_MGR->Line( m_Pos[3], m_Pos[7], color );
	GIZMO_MGR->Line( m_Pos[2], m_Pos[6], color );
}
