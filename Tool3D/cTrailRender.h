#pragma once

#include "cCamera.h"

class cTrailRender
{
private:


	//Trail Line ����ü
	typedef struct tagTrail{
		D3DXVECTOR3 p0;
		D3DXVECTOR3 p1;
		float x;				//�ش� Trail �� UV X
		float leftTime;
		bool bLive;

		tagTrail(){
			bLive = false;
		}

	}Trail, *LPTrail;

	//Trail Vertex
	typedef struct tagTrailVertex{
		D3DXVECTOR3 pos;
		DWORD		color;
		D3DXVECTOR2 uv;
		
		enum{ FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 };

		tagTrailVertex(){

			color = 0xff00ffff;
		}
	}TrailVertex, *LPTrailVertex;

	//Trail Index ����ü ( �̰� �ϳ��� �ﰢ�� �ϳ��� )
	typedef struct tagTrailIndex{
		DWORD	i0;
		DWORD	i1;
		DWORD	i2;

		tagTrailIndex()
			: i0(0), i1(0), i2(0)
		{
		}

		tagTrailIndex( DWORD _0, DWORD _1, DWORD _2 )
			: i0(_0), i1(_1), i2(_2)
		{
		}

	}TrailIndex, *LPTrailIndex;

public:
	cTransform	Transform;		//Trail Transform  ( ���� �����̸� ������ �����. )

private:
	cTransform	m_LeftTransform;	//Trail Left Child Transform
	cTransform	m_RightTransform;	//Trail Right Child Transform

	D3DXVECTOR3	m_PrevLeftPosition;		//Left ���� ������ ��ġ ( ��ġ�� ��ȭ�� �ľ��ϱ� ���� )
	D3DXVECTOR3 m_PrevRightPosition;	//Right ���� ������ ��ġ ( ��ġ�� ��ȭ�� �ľ��ϱ� ���� )

	int				m_nTrailMaxNum;		//Trail Line ����ü �ִ� ��		
	LPTrail			m_pTrails;			//Trail Line ����ü ȯ��ť�� ����Ҳ���
	LPTrailVertex	m_pTrailVertices;	//���� ����ü �迭
	LPTrailIndex	m_pTrailIndices;	//���� �ε��� �迭

	bool		b_LineGen;				//���� ���� ���� 

	int			m_nHeadIndex;			//��� ��ġ ( ������ġ ) 
	int			m_nTailIndex;			//���� ��ġ

	// |  |  |  |  |  |  |  |  
    // ��					  ��
	// TailIndex			  HeadIndex ( �߰��� ��ġ ������ �׷����� ���� Head �� ���� ���� �׷����� )

	float		m_fLineTime;			//�ϳ��� ������ ����ִ� �ð�
	
	LPDIRECT3DTEXTURE9		m_pTrailTexture;		//�Ϲ� Texture 
	LPDIRECT3DTEXTURE9		m_pDistortTexture;		//�ܰ ���Ǵ� Texture

	//Distort Effect
	LPD3DXEFFECT			m_pDistortEffect;

	LPDIRECT3DTEXTURE9		m_pGrabTexture;

	D3DXCOLOR				m_TrailColor;			//����

public:
	cTrailRender(void);
	~cTrailRender(void);

	void		Init( float trailLiveTime, float width, LPDIRECT3DTEXTURE9 pTrailTex, D3DXCOLOR color, LPDIRECT3DTEXTURE9 pDistortTex );
	void		Release();
	void		Update(float timeDelta);
	void		Render();
	void		RenderDistort( cCamera* pCam );


	void		TrailGenStart();
	void		TrailGenStop();
};

