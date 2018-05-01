#pragma once

class cBaseObject;

class cFrustum
{
private:
	D3DXVECTOR3				m_RHWPos[8];		//viewProjection ��ȯ�� ��ġ
	D3DXVECTOR3				m_Pos[8];			//��ȯ �� ��ġ
	D3DXPLANE				m_Plane[6];			//����ü �÷�


public:
	cFrustum(void);
	~cFrustum(void);

	//�������� ���� ������Ʈ ( View * Projection ����� �䱸�Ѵ� )
	void UpdateFrustum( const D3DXMATRIXA16* pmatViewProj );

	//Base ������Ʈ�� �������� �ȿ��ִ��� üũ
	bool IsInFrustum( cBaseObject* pObject );

	//�������� ����� �׸���.
	void RenderGizmo();

};

