#include "StdAfx.h"
#include "cTrailRender.h"


cTrailRender::cTrailRender(void)
{
}


cTrailRender::~cTrailRender(void)
{
}

void		cTrailRender::Init( float trailLiveTime, float width, LPDIRECT3DTEXTURE9 pTrailTex, D3DXCOLOR color, LPDIRECT3DTEXTURE9 pDistortTex )
{
	//�ʴ� 60 �������̶� �������� ���� �����ð��� ����� Trail Line �ִ�� 
	this->m_nTrailMaxNum = (int)( trailLiveTime * 60 ) + 10;		//+10 �� Ȥ�ó�.....

	//LOG_MGR->AddLog( "%d Trail ����", m_nTrailMaxNum );

	//Trail �����ð� ����
	this->m_fLineTime = trailLiveTime;

	//Trail ����ü �迭 ����
	this->m_pTrails = new Trail[ this->m_nTrailMaxNum ];

	//Vertex ���� Trail ���� 2 ��
	this->m_pTrailVertices = new TrailVertex[ this->m_nTrailMaxNum * 2];

	//�ﰢ�� ���� Trail ���� 2 �� ( TrailIndex �̰� �ϳ��� Triangle �ϳ� �̴� )
	this->m_pTrailIndices = new TrailIndex[ this->m_nTrailMaxNum * 2];

	//�ڽ� Transfom Widht ���� ���߾� ����
	this->m_LeftTransform.SetWorldPosition( width * -0.5f, 0.0f, 0.0f );
	this->m_RightTransform.SetWorldPosition( width * 0.5f, 0.0, 0.0f );
	
	//�ڽ� ���δ�.
	this->Transform.AddChild( &m_LeftTransform );
	this->Transform.AddChild( &m_RightTransform );

	//�ε��� �ʱ�ȭ ( �� ���� ���� ���̸� Ȱ��ȭ �� ������ �������� �ʴ´� )
	this->m_nHeadIndex = 0;
	this->m_nTailIndex = 0;

	//Texture ����
	m_pTrailTexture = pTrailTex;
	m_pDistortTexture = pDistortTex;

	//������
	this->TrailGenStart();

	//�ܰ� Effect
	m_pDistortEffect = RESOURCE_FX->GetResource( "../Resources/Shaders/Distort_1.fx" );


	//GrabTexture
	Device->CreateTexture(
		WINSIZE_X, 
		WINSIZE_Y, 
		1,							//�Ӹ�ü�� ����
		D3DUSAGE_RENDERTARGET,		//RenderTarget �� Texture�̴�
		D3DFMT_A8R8G8B8,			//TEXTURE ���� RenderTexture ����D3DFMT_A8R8G8B8 ������
		D3DPOOL_DEFAULT,			//RenderTarget �� Texture �� Pool �� Default
		&m_pGrabTexture,
		NULL );


	this->m_TrailColor = color;

}
void		cTrailRender::Release()
{
	SAFE_DELETE_ARR( m_pTrails );
	SAFE_DELETE_ARR( m_pTrailVertices );
	SAFE_DELETE_ARR( m_pTrailIndices );

	SAFE_RELEASE( m_pGrabTexture );

}
void		cTrailRender::Update(float timeDelta)
{
	//i ���� Ȱ��ȭ �� ���� ��ġ�̴�.
	int i = m_nHeadIndex - 1; //m_nHeadIndex �� �߰��� ��ġ�̱� ������ ���� �ε����� �̰��� 1 �� ���ڸ� ���� �ȴ�.

	//m_nHeadIndex �� -1 �̵Ǵ� ��� �ε����� Trail �迭�� �Ǹ����� �ε����� �ȴ�.
	if( i < 0 ) 
		i = m_nTrailMaxNum - 1;

	//TailIndex ������ ���� �� ����
	m_nTailIndex = i;

	//����.
	while( true )
	{
		//��Ȱ��ȭ �� Trail �� �����ٸ� ���Ŀ��� ���� �� �̹Ƿ� Ż��
		if( m_pTrails[i].bLive == false )
			break;

		//Ȱ��ȭ�� Trail Line ���� �ð� ���.
		m_pTrails[i].leftTime -= timeDelta;

		//�̰� �ð��� �� �����ٸ� ���̻��� ���Ŀ� Ȱ��ȭ �� ������ ���� ���� �ǹǷ� ��Ȱ��ȭ ��Ű�� Ż��
		if( m_pTrails[i].leftTime < 0.0f ){
			m_pTrails[i].bLive = false;
			//LOG_MGR->AddLog( "%d ���λ���", i );
			break;
		}

		//i ���� ��� �ε��� ���� �Դٸ� �ѹ� ��ȸ �Ѱ��� �ǹǷ� ����
		if( i == m_nHeadIndex )
			break;

		//�ε����� ���ٷ� ���� ���� �ε����� �ϳ� ����.
		i--;

		//������ �Ǵ� ��� �迭�� �� ������ �ε����� ����.
		if( i < 0 )
			i = m_nTrailMaxNum - 1;

		//TailIndex ������ ���� �� ����
		m_nTailIndex = i;
	}

	//������ �� ���̶��..
	if( this->b_LineGen )
	{
		//���� ��ġ ����
		D3DXVECTOR3 nowLeftPos = m_LeftTransform.GetWorldPosition();
		D3DXVECTOR3 nowRightPos = m_RightTransform.GetWorldPosition();

		//������ ������ġ
		int nextLineIndex = m_nHeadIndex + 1;
		if( nextLineIndex >= m_nTrailMaxNum )	//�Ѿ�� �ٽ� ó������...
			nextLineIndex = 0;	

		//��ġ�� ��ȭ�� �ְ� ������ ������ġ�� m_nTailIndex �� �ƴ϶��...
		if( ( nowLeftPos != m_PrevLeftPosition || nowRightPos != m_PrevRightPosition ) &&
			nextLineIndex != m_nTailIndex )
		{
			this->m_pTrails[ this->m_nHeadIndex ].p0 = nowLeftPos;
			this->m_pTrails[ this->m_nHeadIndex ].p1 = nowRightPos;
			this->m_pTrails[ this->m_nHeadIndex ].bLive = true;
			this->m_pTrails[ this->m_nHeadIndex ].leftTime = m_fLineTime;

			//��� �ε����� ���� �ε�����...
			m_nHeadIndex = nextLineIndex;
			

			//LOG_MGR->AddLog( "%d �����߰�", m_nHeadIndex );

		}

		//���� ��ġ ���� ��ġ�� ����
		m_PrevLeftPosition = nowLeftPos;
		m_PrevRightPosition = nowRightPos;
	}

	

}
void		cTrailRender::Render()
{
	
	DWORD triNum = 0;
	DWORD verNum = 0;

	int i = m_nHeadIndex - 1;
	if( i < 0 ) 
		i = m_nTrailMaxNum - 1;

	//���� ���� �߰� ( ������ ������ �־�� �ﰢ���� �����ȴ�.
	m_pTrailVertices[verNum].pos = m_pTrails[i].p0;
	m_pTrailVertices[verNum].uv.y = 1;
	m_pTrailVertices[verNum].uv.x = 0.0f;		//���� ������ UV.x �����̴�.
	m_pTrailVertices[verNum].color = this->m_TrailColor;
	verNum++;

	m_pTrailVertices[verNum].pos = m_pTrails[i].p1;
	m_pTrailVertices[verNum].uv.y = 0;
	m_pTrailVertices[verNum].uv.x = 0.0f;		//���� ������ UV.x �����̴�.
	m_pTrailVertices[verNum].color = this->m_TrailColor;
	verNum++;

	//���� ���� ���� ���� 
	i--;
	if( i < 0 ) 
		i = m_nTrailMaxNum - 1;

	while( true )
	{
		//�ϳ��� ��Ȱ��ȭ �� ������ �����ٸ�...
		if( m_pTrails[i].bLive == false )
			break;

		float uvX = 1.0f - ( m_pTrails[i].leftTime / m_fLineTime );		//UV�� x �� ���� �ð���� ���ȴ�.

		m_pTrailVertices[verNum].pos = m_pTrails[i].p0;
		m_pTrailVertices[verNum].uv.y = 1;
		m_pTrailVertices[verNum].uv.x =uvX;
		m_pTrailVertices[verNum].color = this->m_TrailColor;
		
		verNum++;

		m_pTrailVertices[verNum].pos = m_pTrails[i].p1;
		m_pTrailVertices[verNum].uv.y = 0;
		m_pTrailVertices[verNum].uv.x = uvX;		//���� ������ UV.x �����̴�.
		m_pTrailVertices[verNum].color = this->m_TrailColor;

		verNum++;
		
		m_pTrailIndices[ triNum + 0 ] = TrailIndex( triNum + 0, triNum + 1, triNum + 2 );
		m_pTrailIndices[ triNum + 1 ] = TrailIndex( triNum + 2, triNum + 1, triNum + 3 );
		triNum += 2;

		if( i == m_nHeadIndex )
			break;

		i--;
		if( i < 0 )
			i = m_nTrailMaxNum - 1;
	}

	//������ ��ġ�� ���� �������� ��������� ������ ���� ����� �ʱ�ȭ �Ǿ�� �Ѵ�.
	D3DXMATRIXA16	matWorld;
	D3DXMatrixIdentity( &matWorld );
	Device->SetTransform( D3DTS_WORLD, &matWorld );

	//��� �ٱ׸���.
	Device->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

	//Texture ����
	Device->SetTexture( 0, m_pTrailTexture );

	//���� ����.
	DWORD prevLight;
	Device->GetRenderState( D3DRS_LIGHTING, &prevLight );
	Device->SetRenderState( D3DRS_LIGHTING, FALSE );

	//���� ���� Ȱ��ȭ
	Device->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
	Device->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	Device->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );
	Device->SetRenderState( D3DRS_ZWRITEENABLE, FALSE );


	//���� �׸���.
	Device->SetFVF( TrailVertex::FVF );
	Device->DrawIndexedPrimitiveUP(
		D3DPT_TRIANGLELIST, 
		0, 
		verNum,
		triNum,
		m_pTrailIndices, 
		D3DFMT_INDEX32, 
		m_pTrailVertices, 
		sizeof( TrailVertex ) );


	//�ٽ� ���� ���´�.
	Device->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );
	Device->SetTexture( 0, NULL );
	Device->SetRenderState( D3DRS_LIGHTING, prevLight );
	Device->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE );
	Device->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );


	this->Transform.RenderGimozo( Device );
	this->m_LeftTransform.RenderGimozo( Device );
	this->m_RightTransform.RenderGimozo( Device );
}


void		cTrailRender::TrailGenStart()
{
	//�� Ȱ��ȭ ���� true
	this->b_LineGen = true;

	//���� ��ġ ���
	this->m_PrevLeftPosition = this->m_LeftTransform.GetWorldPosition();
	this->m_PrevRightPosition = this->m_RightTransform.GetWorldPosition();
}

void		cTrailRender::RenderDistort( cCamera* pCam )
{
	//�ְ� Texture �� ������ �ȱ׸���.
	if( m_pDistortTexture == NULL )
	{
		this->Render();
		return;
	}


	DWORD triNum = 0;
	DWORD verNum = 0;

	int i = m_nHeadIndex - 1;
	if( i < 0 ) 
		i = m_nTrailMaxNum - 1;

	//���� ���� �߰� ( ������ ������ �־�� �ﰢ���� �����ȴ�.
	m_pTrailVertices[verNum].pos = m_pTrails[i].p0;
	m_pTrailVertices[verNum].uv.y = 1;
	m_pTrailVertices[verNum].uv.x = 0.0f;		//���� ������ UV.x �����̴�.
	verNum++;

	m_pTrailVertices[verNum].pos = m_pTrails[i].p1;
	m_pTrailVertices[verNum].uv.y = 0;
	m_pTrailVertices[verNum].uv.x = 0.0f;		//���� ������ UV.x �����̴�.
	verNum++;

	//���� ���� ���� ���� 
	i--;
	if( i < 0 ) 
		i = m_nTrailMaxNum - 1;

	while( true )
	{
		//�ϳ��� ��Ȱ��ȭ �� ������ �����ٸ�...
		if( m_pTrails[i].bLive == false )
			break;

		float uvX = 1.0f - ( m_pTrails[i].leftTime / m_fLineTime );		//UV�� x �� ���� �ð���� ���ȴ�.

		m_pTrailVertices[verNum].pos = m_pTrails[i].p0;
		m_pTrailVertices[verNum].uv.y = 1;
		m_pTrailVertices[verNum].uv.x =uvX;
		verNum++;

		m_pTrailVertices[verNum].pos = m_pTrails[i].p1;
		m_pTrailVertices[verNum].uv.y = 0;
		m_pTrailVertices[verNum].uv.x = uvX;		//���� ������ UV.x �����̴�.
		verNum++;
		
		m_pTrailIndices[ triNum + 0 ] = TrailIndex( triNum + 0, triNum + 1, triNum + 2 );
		m_pTrailIndices[ triNum + 1 ] = TrailIndex( triNum + 2, triNum + 1, triNum + 3 );
		triNum += 2;

		if( i == m_nHeadIndex )
			break;

		i--;
		if( i < 0 )
			i = m_nTrailMaxNum - 1;
	}











	//Grab Texture ��´�.
	GetDeviceGrabTexture( Device, m_pGrabTexture );

	//
	// Effect �� �׸���.
	//
	
	//������ ��ġ�� ���� �������� ��������� ������ ���� ����� �ʱ�ȭ �Ǿ�� �Ѵ�.
	D3DXMATRIXA16	matWorld;
	D3DXMatrixIdentity( &matWorld );
	m_pDistortEffect->SetMatrix( "matWorld", &matWorld );

	D3DXMATRIXA16 matViewProj = pCam->GetViewProjectionMatrix();
	m_pDistortEffect->SetMatrix( "matViewProj", &matViewProj );
	m_pDistortEffect->SetTexture( "grabTexture_Tex", m_pGrabTexture );
	m_pDistortEffect->SetFloat( "DistortPower",0.01f );
	m_pDistortEffect->SetFloat( "CamNear", pCam->camNear );
	m_pDistortEffect->SetFloat( "CamFar", pCam->camFar );
	m_pDistortEffect->SetTexture( "distortNormal_Tex", m_pDistortTexture );

	m_pDistortEffect->Begin( 0, 0 );
	m_pDistortEffect->BeginPass( 0 );
	
	//��� �ٱ׸���.
	Device->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	Device->SetRenderState( D3DRS_ZWRITEENABLE, FALSE );


	//���� �׸���.
	Device->SetFVF( TrailVertex::FVF );
	Device->DrawIndexedPrimitiveUP(
		D3DPT_TRIANGLELIST, 
		0, 
		verNum,
		triNum,
		m_pTrailIndices, 
		D3DFMT_INDEX32, 
		m_pTrailVertices, 
		sizeof( TrailVertex ) );

	Device->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );
	Device->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );


	m_pDistortEffect->EndPass();
	m_pDistortEffect->End();

	
	this->Transform.RenderGimozo( Device );
	this->m_LeftTransform.RenderGimozo( Device );
	this->m_RightTransform.RenderGimozo( Device );


}

void		cTrailRender::TrailGenStop()
{
	//�� Ȱ��ȭ ���� false
	this->b_LineGen = false;
}