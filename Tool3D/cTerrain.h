#pragma once

class cQuadTree;
class cCamera;
class cLight_Direction;
#include "SourceList.h"
#define CIRCLEGIZMO_SEGMENTS 36

class cTerrain
{
public:
	typedef struct tagGIZMOVERTEX {
		D3DXVECTOR3 pos;
		DWORD color;
		enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE };
	}GIZMOVERTEX, *LPGIZMOVERTEX;	
	
	//Terrain ���� ����ü
	typedef struct tagTERRAINVERTEX{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 normal;				
		D3DXVECTOR3 binormal;
		D3DXVECTOR3 tangent;
		D3DXVECTOR2 baseUV;			//0~1 UV
		D3DXVECTOR2 tileUV;			//Ÿ�� UV 
	}TERRAINVERTEX, *LPTERRAINVERTEX;

	//Terrain �ε��� ����ü ( ��� ����ü �ϳ��� �ﰢ�� �ϳ��� ����Ѵ� )
	typedef struct tagTERRAINTRI{
		DWORD dw0;
		DWORD dw1;
		DWORD dw2;
	}TERRAINTRI, *LPTERRAINTRI;

private:
	LPDIRECT3DVERTEXBUFFER9				m_pTerrainVB;		//�ͷ��� ���� ����
	LPDIRECT3DINDEXBUFFER9				m_pTerrainIB;		//�ͷ��� �ε��� ����
	LPDIRECT3DVERTEXDECLARATION9		m_pTerrainDecl;		//�ͷ��� ���� Decl

	float				m_fHeightScale;						//���̽����� ( �ȼ��÷��� 255 �϶� ���� )
	float				m_fCellScale;						//���ϳ��� ũ��

	int					m_nVerNumX;							//���� ������
	int					m_nVerNumZ;							//���� ������
	int					m_nTotalVerNum;						//�� ������

	int					m_nCellNumX;						//���� ����
	int					m_nCellNumZ;						//���� ����
	int					m_nTotalCellNum;					//�� ����
	int					m_nTotalTri;						//�ﰢ�� ����

	float				m_fTerrainSizeZ;					//�ͷ��� ���� ������
	float				m_fTerrainSizeX;					//�ͷ��� ���� ������

	//��Ȯ�� ���� ����� ���� �ʿ��ϴ�...
	float				m_fTerrainStartX;					//�ͷ��� ���� ��ġX
	float				m_fTerrainStartZ;					//�ͷ��� ���� ��ġZ
	float				m_fTerrainEndX;
	float				m_fTerrainEndZ;

	LPDIRECT3DTEXTURE9					m_pHeightMap;		//�ͷ��� ���� ��

	cQuadTree*							m_pQuadTree;		//���� Ʈ��

	
	LPDIRECT3DTEXTURE9	m_pTexTile_0;						//�ͷ��� 0 �� Ÿ��
	LPDIRECT3DTEXTURE9	m_pTexTile_1;						//�ͷ��� 1 �� Ÿ��
	LPDIRECT3DTEXTURE9	m_pTexTile_2;						//�ͷ��� 2 �� Ÿ��
	LPDIRECT3DTEXTURE9	m_pTexTile_3;						//�ͷ��� 3 �� Ÿ��
	LPDIRECT3DTEXTURE9  m_pTexSlat;							//���÷��� Texture

	SourceList*			sourceList;
	LPTERRAINTRI pIndices;
public:
	LPD3DXEFFECT		m_pTerrainEffect;					//�ͷ��� Effect
	LPTERRAINVERTEX		m_pTerrainVertices;					//�ͷ��� ��������

public:
	cTerrain(void);
	~cTerrain(void);

	void SetSource(SourceList* pSourceList) {
		sourceList = pSourceList;
	}

	//�ʱ�ȭ 
	HRESULT Init( 
		const char* szHeightMapName,		//���̸� �̸�
		const char* szTile_0,				// Ÿ�� �̹��� 0
		const char* szTile_1,				// Ÿ�� �̹��� 1
		const char* szTile_2,				// Ÿ�� �̹��� 2
		const char* szTile_3,				// Ÿ�� �̹��� 3
		const char* szTileSplat,			// Ÿ�� �̹��� ��Ʈ�� ( RGB Black )
		float cellSize,						// �ϳ��� ��ũ��
		float heightScale,					// ���� ������
		int smoothLevel,					// ������ ó�� Ƚ��
		int tileNum							// Ÿ�ϸ� ����
		);

	//����
	void Release();

	//����
	void Render( cCamera* pCam, cLight_Direction* pDirectionLight );
	void RenderWire();
	void Render( cCamera* pCam, cLight_Direction* pDirectionLight, cCamera* pDirectionLightCamera );
	void RenderShadow( cCamera* pDirectionLightCam );

	//Ray ��Ʈ ��ġ�� ��´�.
	bool IsIntersectRay( D3DXVECTOR3* pOut, const LPRay pRay ); 

	//�ش� X, Z ��ġ�� ������ ���̸� ��´�.
	float GetHeight( float x, float z );

	//�ش� X, Z ��ġ�� ��� ���͸� ��´�.
	bool GetSlant( D3DXVECTOR3* pOut, float gravityPower, float x, float z );

	// �����Լ�
	void ChangeHeightMap(const D3DXVECTOR3& centerPos);
	void ChangeSplatMap(const D3DXVECTOR3& centerPos);
	void Flatten();
	void ResetHeightInfo();
	void ChangeTerrain1(string szTile_0) {
		m_pTexTile_0 = RESOURCE_TEXTURE->GetResource(szTile_0);
	}
	void ChangeTerrain2(string szTile_1) {
		m_pTexTile_1 = RESOURCE_TEXTURE->GetResource(szTile_1);
	}
	void ChangeTerrain3(string szTile_2) {
		m_pTexTile_2 = RESOURCE_TEXTURE->GetResource(szTile_2);
	}
	void ChangeTerrain4(string szTile_3) {
		m_pTexTile_3 = RESOURCE_TEXTURE->GetResource(szTile_3);
	}
	void ChangeSmoothLevel(int smoothing);
	void ChangeCellSize();
	void ChangeHeightScale();
	void ChangeTileNum();


	//�귯�� �����Լ�
	void RenderBrush(const D3DXVECTOR3& centerPos, float radius, DWORD color, LPDIRECT3DDEVICE9 pDevice);
	void SaveHeightMap();
	void SaveSplatMap();
	void CreateAndSaveMiniMap();

private:
	//�ͷ��� �����
	HRESULT CreateTerrain( int smooth, int tileNum );
	//�ͷ��� ������
	void SmoothTerrain( int passed );

};