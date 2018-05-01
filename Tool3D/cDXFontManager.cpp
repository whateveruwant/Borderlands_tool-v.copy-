#include "StdAfx.h"
#include "cDXFontManager.h"


cDXFontManager::cDXFontManager(void)
	: m_pDefultFont( NULL )
{
}


cDXFontManager::~cDXFontManager(void)
{
}


HRESULT cDXFontManager::Init( LPDIRECT3DDEVICE9 pDevice )
{
	//����Ʈ�� ���� Font ����
	if( FAILED( D3DXCreateFont(
		pDevice,				//����̽�
		15,					//��Ʈ�� ����, 
		0,					//��Ʈ�� �� ( �̰��� 0 �̸� �տ��� ������ ��Ʈ ���̿� ����Ͽ� ���� ��Ʈ�� ������ �ִ� ��Ⱦ�� ���� ���� ��ũ�Ⱑ �ڵ����� �������� ) 	
		FW_BOLD,			//��Ʈ�� �β� ����( FW_BOLD ��Ʈ�� BOLD ��Ÿ�� ũ�⸦ ���´� )
		1,					//�Ӹ� ( �׳� 1  )
		FALSE,				//���ڸ� ����
		DEFAULT_CHARSET,	//ĳ���� Set ( �׳� DEFAULT_CHARSET )
		OUT_DEFAULT_PRECIS,	//�ܰ� ó����� ( �׳� OUT_DEFAULT_PRECIS )
		DEFAULT_QUALITY,	//����Ƽ ( �׳� DEFAULT_QUALITY ),
		DEFAULT_PITCH | FF_DONTCARE,		//�۽�ü �йи��� ���� ( DEFAULT_PITCH | FF_DONTCARE )
		"����",				//���� ��Ʈ�̸� �׳� ��Ʈ�̸��� ��Ʈ������ ���� �ȴ�.
		&m_pDefultFont 
		) ) )
		return E_FAIL;

	return S_OK;
}

void cDXFontManager::Release()
{
	SAFE_RELEASE( m_pDefultFont );

	//Style Map ���ִ� ��Ʈ �� �ϴ�
	MAP_FONT_ITER iter;
	for( iter = m_FontStyleMap.begin() ; iter != m_FontStyleMap.end() ; ++iter ){
		SAFE_RELEASE( iter->second );
	}

}


void cDXFontManager::AddStyle( LPDIRECT3DDEVICE9 pDevice, std::string style,  std::string fontName, float fontSize )
{
	//�̹� style �̸��� Ű�� �����Ѵٸ� �߰����� �ʴ´�
	MAP_FONT_ITER find = m_FontStyleMap.find( style );
	if( find != m_FontStyleMap.end() )
		return;


	//���ο� ��Ʈ �߰�
	LPD3DXFONT newFont;
	D3DXCreateFont(
		pDevice,			//����̽�
		fontSize,			//��Ʈ�� ����, 
		0.0f,				//��Ʈ�� �� ( �̰��� 0 �̸� �տ��� ������ ��Ʈ ���̿� ����Ͽ� ���� ��Ʈ�� ������ �ִ� ��Ⱦ�� ���� ���� ��ũ�Ⱑ �ڵ����� �������� ) 	
		FW_BOLD,			//��Ʈ�� �β� ����( FW_BOLD ��Ʈ�� BOLD ��Ÿ�� ũ�⸦ ���´� )
		1,					//�Ӹ� ( �׳� 1  )
		FALSE,				//���ڸ� ����
		DEFAULT_CHARSET,	//ĳ���� Set ( �׳� DEFAULT_CHARSET )
		OUT_DEFAULT_PRECIS,	//�ܰ� ó����� ( �׳� OUT_DEFAULT_PRECIS )
		DEFAULT_QUALITY,	//����Ƽ ( �׳� DEFAULT_QUALITY ),
		DEFAULT_PITCH | FF_DONTCARE,		//�۽�ü �йи��� ���� ( DEFAULT_PITCH | FF_DONTCARE )
		fontName.c_str(),				//���� ��Ʈ�̸� �׳� ��Ʈ�̸��� ��Ʈ������ ���� �ȴ�.
		&newFont 
		);

	//style �̸��� Key Map �� �߰�
	m_FontStyleMap.insert( std::make_pair(style,newFont) );

}


void cDXFontManager::PrintText( std::string str, int x, int y, DWORD color )
{
	//��¿���
	RECT rcTextArea = { x, y, 0, 0 };

	m_pDefultFont->DrawTextA(
		NULL, 
		str.c_str(),		//string �� ������ char* �� ����
		-1, 
		&rcTextArea, 
		DT_LEFT | DT_NOCLIP,		// DT_NOCLIP ������ ���õ�
		color );

}	

void cDXFontManager::PrintTextShadow( std::string str, int x, int y, DWORD color, DWORD shadow )
{
	//������ ���� ��´�.
	PrintText( str, x + 1, y + 1, shadow );

	//���� Text �� ��´�.
	PrintText( str, x, y, color );
}

void cDXFontManager::PrintTextOutline( std::string str, int x, int y, DWORD color, DWORD outLine )
{
	//�ܰ� ��´�
	PrintText( str, x + 1, y, outLine );
	PrintText( str, x, y + 1, outLine );
	PrintText( str, x - 1, y, outLine );
	PrintText( str, x, y - 1, outLine );

	//���� Text �� ��´�.
	PrintText( str, x, y, color );
}

void  cDXFontManager::PrintStyleText( std::string style, std::string str, int x, int y, DWORD color )
{
	LPD3DXFONT pFont = NULL;

	//style Ű�� �ش�Ǵ� pair ��带 ã�� �ش���ġ�� ���� iter �� ����
	//���� ��ã�Ҵٸ�... end() �� �����ȴ�.
	MAP_FONT_ITER find = m_FontStyleMap.find( style );

	//��ã�Ҵٸ�.. Default ��Ÿ�Ϸ�.
	if( find == m_FontStyleMap.end() ){
		pFont = m_pDefultFont;
	}
	//ã�Ҵٸ�...
	else{
		pFont = find->second;
	}

	//��¿���
	RECT rcTextArea = { x, y, 0, 0 };

	pFont->DrawTextA(
		NULL, 
		str.c_str(),		//string �� ������ char* �� ����
		-1, 
		&rcTextArea, 
		DT_LEFT | DT_NOCLIP,		// DT_NOCLIP ������ ���õ�
		color );

}

void  cDXFontManager::PrintStyleTextShadow( std::string style, std::string str, int x, int y, DWORD color, DWORD shadow  )
{
	//������ ���� ��´�.
	PrintStyleText( style, str, x + 1, y + 1, shadow );

	//���� Text �� ��´�.
	PrintStyleText( style, str, x, y, color );
}

void  cDXFontManager::PrintStyleTextOutline( std::string style, std::string str, int x, int y, DWORD color, DWORD outLine  )
{
	//�ܰ� ��´�
	PrintStyleText( style, str, x + 1, y, outLine );
	PrintStyleText( style, str, x, y + 1, outLine );
	PrintStyleText( style, str, x - 1, y, outLine );
	PrintStyleText( style, str, x, y - 1, outLine );

	//���� Text �� ��´�.
	PrintStyleText( style, str, x, y, color );
}
