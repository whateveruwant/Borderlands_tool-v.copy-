#include "StdAfx.h"
#include "cResourceMgr_Texture.h"


cResourceMgr_Texture::cResourceMgr_Texture(void)
{
}


cResourceMgr_Texture::~cResourceMgr_Texture(void)
{
}


//�ε� ��ĸ� ������ 
LPDIRECT3DTEXTURE9 cResourceMgr_Texture::LoadResource( std::string filePath, void* pParam )
{
	//�ؽ��� �ε�
	LPDIRECT3DTEXTURE9	pNewTex = NULL;
	if (FAILED(D3DXCreateTextureFromFile(Device, filePath.c_str(), &pNewTex))) {
		//LOG_MGR->AddLog("%s �ҷ����� ����", filePath.c_str());
		return NULL;
	}

	return pNewTex;
}

//���� ��ĸ� ������
void cResourceMgr_Texture::ReleaseResource( LPDIRECT3DTEXTURE9 data )
{
	
	//data->Release();
	SAFE_RELEASE( data );


}