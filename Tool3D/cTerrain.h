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
	
	//Terrain 정점 구조체
	typedef struct tagTERRAINVERTEX{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 normal;				
		D3DXVECTOR3 binormal;
		D3DXVECTOR3 tangent;
		D3DXVECTOR2 baseUV;			//0~1 UV
		D3DXVECTOR2 tileUV;			//타일 UV 
	}TERRAINVERTEX, *LPTERRAINVERTEX;

	//Terrain 인덱스 구조체 ( 요고 구조체 하나가 삼각형 하나를 담당한다 )
	typedef struct tagTERRAINTRI{
		DWORD dw0;
		DWORD dw1;
		DWORD dw2;
	}TERRAINTRI, *LPTERRAINTRI;

private:
	LPDIRECT3DVERTEXBUFFER9				m_pTerrainVB;		//터레인 정점 버퍼
	LPDIRECT3DINDEXBUFFER9				m_pTerrainIB;		//터레인 인덱스 버퍼
	LPDIRECT3DVERTEXDECLARATION9		m_pTerrainDecl;		//터레인 정점 Decl

	float				m_fHeightScale;						//높이스케일 ( 픽셀컬러가 255 일때 높이 )
	float				m_fCellScale;						//셀하나의 크기

	int					m_nVerNumX;							//가로 정점수
	int					m_nVerNumZ;							//깊이 정점수
	int					m_nTotalVerNum;						//총 정점수

	int					m_nCellNumX;						//가로 셀수
	int					m_nCellNumZ;						//깊이 셀수
	int					m_nTotalCellNum;					//총 셀수
	int					m_nTotalTri;						//삼각형 갯수

	float				m_fTerrainSizeZ;					//터레인 가로 사이즈
	float				m_fTerrainSizeX;					//터레인 세로 사이즈

	//정확한 높이 계산을 위해 필요하다...
	float				m_fTerrainStartX;					//터레인 시작 위치X
	float				m_fTerrainStartZ;					//터레인 시작 위치Z
	float				m_fTerrainEndX;
	float				m_fTerrainEndZ;

	LPDIRECT3DTEXTURE9					m_pHeightMap;		//터레인 높이 맵

	cQuadTree*							m_pQuadTree;		//쿼드 트리

	
	LPDIRECT3DTEXTURE9	m_pTexTile_0;						//터레인 0 층 타일
	LPDIRECT3DTEXTURE9	m_pTexTile_1;						//터레인 1 층 타일
	LPDIRECT3DTEXTURE9	m_pTexTile_2;						//터레인 2 층 타일
	LPDIRECT3DTEXTURE9	m_pTexTile_3;						//터레인 3 층 타일
	LPDIRECT3DTEXTURE9  m_pTexSlat;							//스플렛팅 Texture

	SourceList*			sourceList;
	LPTERRAINTRI pIndices;
public:
	LPD3DXEFFECT		m_pTerrainEffect;					//터레인 Effect
	LPTERRAINVERTEX		m_pTerrainVertices;					//터레인 정점정보

public:
	cTerrain(void);
	~cTerrain(void);

	void SetSource(SourceList* pSourceList) {
		sourceList = pSourceList;
	}

	//초기화 
	HRESULT Init( 
		const char* szHeightMapName,		//높이맵 이름
		const char* szTile_0,				// 타일 이미지 0
		const char* szTile_1,				// 타일 이미지 1
		const char* szTile_2,				// 타일 이미지 2
		const char* szTile_3,				// 타일 이미지 3
		const char* szTileSplat,			// 타일 이미지 컨트롤 ( RGB Black )
		float cellSize,						// 하나의 셀크기
		float heightScale,					// 높이 스케일
		int smoothLevel,					// 스무싱 처리 횟수
		int tileNum							// 타일링 갯수
		);

	//해제
	void Release();

	//랜더
	void Render( cCamera* pCam, cLight_Direction* pDirectionLight );
	void RenderWire();
	void Render( cCamera* pCam, cLight_Direction* pDirectionLight, cCamera* pDirectionLightCamera );
	void RenderShadow( cCamera* pDirectionLightCam );

	//Ray 히트 위치를 얻는다.
	bool IsIntersectRay( D3DXVECTOR3* pOut, const LPRay pRay ); 

	//해당 X, Z 위치의 지형의 높이를 얻는다.
	float GetHeight( float x, float z );

	//해당 X, Z 위치의 경사 벡터를 얻는다.
	bool GetSlant( D3DXVECTOR3* pOut, float gravityPower, float x, float z );

	// 수정함수
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


	//브러쉬 렌더함수
	void RenderBrush(const D3DXVECTOR3& centerPos, float radius, DWORD color, LPDIRECT3DDEVICE9 pDevice);
	void SaveHeightMap();
	void SaveSplatMap();
	void CreateAndSaveMiniMap();

private:
	//터레인 만들기
	HRESULT CreateTerrain( int smooth, int tileNum );
	//터레인 스무싱
	void SmoothTerrain( int passed );

};