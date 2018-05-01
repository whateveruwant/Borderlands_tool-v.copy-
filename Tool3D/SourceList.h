#pragma once
enum eTabSelecter {BASE, HEIGHT, SPLAT, OBJECT};
enum eBrushType { eBrushType_1st, eBrushType_2nd, eBrushType_3rd, eBrushType_Eraser};
enum eBrushTexture { eBrushTexture_1st, eBrushTexture_2nd, eBrushTexture_3rd, eBrushTexture_4th };
struct SourceList {
	string sHeightMap;
	string sTerrain1;
	string sTerrain2;
	string sTerrain3;
	string sTerrain4;
	string sSplatMap;

	string sEnvironment;

	float fCellSize;
	float fHeightScale;
	int iSmoothLevel;
	int	iTileNum;

	float fRangeSize;
	float fDepth;

	int iHeightMax;
	float fOpacity;
	bool bPlus;
	int iBottom;
	eBrushType eBrushType;
	eBrushTexture eBrushTexture;
	eTabSelecter eTab;

	string sTmpObject;
	float fObjectScale;
};

struct sObjectSaveData {
	bool			isSet;
	char			sfilePath[100];
	D3DXVECTOR3		scale;
	D3DXVECTOR3		position;
	D3DXVECTOR3		axis[3];
	bool			haveAnimation;
};

struct sEnemySaveData {
	bool			isSet;
	char			sfilePath[100];
	D3DXVECTOR3		position;
};