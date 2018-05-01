#include "StdAfx.h"
#include "cBoundSphere.h"
#include "cTransform.h"


cBoundSphere::cBoundSphere(void)
{
}


cBoundSphere::~cBoundSphere(void)
{
}


//���� ������ ���Ϳ� �������� ��´�.
void cBoundSphere::GetWorldCenterRadius( const  cTransform* pTrans, D3DXVECTOR3* center, float* raidus )
{
	D3DXMATRIXA16 matFinal = pTrans->GetFinalMatrix();

	//���� ����
	D3DXVec3TransformCoord( center, &this->localCenter, &matFinal );

	D3DXVECTOR3 scale = pTrans->GetScale();

	//���� ����
	D3DXVECTOR3 halfSize;
	halfSize.x = this->halfSize.x * scale.x;
	halfSize.y = this->halfSize.y * scale.y;
	halfSize.z = this->halfSize.z * scale.z;

	*raidus = D3DXVec3Length( &halfSize );

}

//���� ������ �׷�����.
void cBoundSphere::RenderGizmo( const  cTransform* pTrans )
{
	D3DXVECTOR3 worldCenter;
	float radius;

	this->GetWorldCenterRadius( pTrans, &worldCenter,&radius );
	GIZMO_MGR->WireSphere( worldCenter, radius, 0xffffff00 );
}



void cBoundSphere::SetBound( const D3DXVECTOR3* pCenter, const D3DXVECTOR3* pHalfSize )
{
	this->localCenter = *pCenter;
	this->halfSize = *pHalfSize;
	this->radius = D3DXVec3Length( pHalfSize );
}