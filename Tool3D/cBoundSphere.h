#pragma once


class cTransform;

class cBoundSphere
{
public: 
	D3DXVECTOR3 localCenter;
	float radius;
	D3DXVECTOR3 halfSize;

public:
	cBoundSphere(void);
	~cBoundSphere(void);

	//���� ������ ���Ϳ� �������� ��´�.
	void GetWorldCenterRadius( const cTransform* pTrans, D3DXVECTOR3* center, float* raidus );

	//���� ������ �׷�����.
	virtual void RenderGizmo( const cTransform* pTrans );

	virtual void SetBound( const D3DXVECTOR3* pCenter, const D3DXVECTOR3* pHalfSize );

};

