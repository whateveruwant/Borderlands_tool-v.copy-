#pragma once
#include "clight.h"

class cLight_Point : public cLight
{
public:
	float				minRange;			//���� �ּҰŸ� 
	float				maxRange;			//���� �ִ�Ÿ�
	float				distancePow;		//�Ÿ� ������


public:
	cLight_Point(void);
	~cLight_Point(void);

	virtual D3DXMATRIXA16 GetLightMatrix();

	virtual void RenderGizmo();

};

