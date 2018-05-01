#include "StdAfx.h"
#include "cPartcleEmitter.h"


cPartcleEmitter::cPartcleEmitter(void)
{
}


cPartcleEmitter::~cPartcleEmitter(void)
{
}


void cPartcleEmitter::Init( 
		DWORD partcleNum,					//�� ��ƼŬ ��
		float emission,						//�ʴ� �߻���
		float liveTimeMin,					//��ƼŬ�ϳ��� �ð�
		float liveTimeMax,
		const D3DXVECTOR3& velocityMin,		//��ƼŬ ���� �ӵ�
		const D3DXVECTOR3& velocityMax,
		const D3DXVECTOR3& accelMin,		//��ƼŬ ����
		const D3DXVECTOR3& accelMax,
		const VEC_COLOR& colors,			//��ƼŬ �÷� ���͹迭
		const VEC_SCALE& scales,			//��ƼŬ ������ �÷��迭
		float scaleMin,						//��ƼŬ ������
		float scaleMax,
		LPDIRECT3DTEXTURE9 pPaticleTexture,	//��ƼŬ Texture
		bool bLocal  				//�̰� true �� ��ƼŬ�� �������� ����Transform Local �������� �����δ�.
		)
{
	//�ش� ��ƼŬ ������ �� ��ƼŬ ��
	m_PaticleNum = partcleNum;

	//����ƼŬ ����ŭ ���ؽ� �迭�� �����.
	m_ParticleVerticles = new PARTICLE_VERTEX[ m_PaticleNum ];

	//��ƼŬ ��ü ����
	m_pPaticles = new cParticle[ m_PaticleNum ];

	//�ʴ� ������
	m_fEmissionPerSec = emission;

	//�ʴ� ������ ���� �߻� ����
	m_fEmisionIntervalTime = 1.0f / m_fEmissionPerSec;

	//���� �ð��� 0
	m_fEmisionDeltaTime = 0.0f;

	//�߻� ���� false
	m_bEmission = false;


	//�÷� ����
	//m_Colors = colors;
	m_Colors.clear();
	for( int i = 0 ; i < colors.size() ;i++ )
		m_Colors.push_back( colors[i] );


	//������ ����
	//m_Scales = scales;
	m_Scales.clear();
	for( int i = 0 ; i < scales.size() ;i++ )
		m_Scales.push_back( scales[i] );
	

	//���� ���̺� Ÿ�� ����
	m_fStartLiveTimeMin = liveTimeMin;
	m_fStartLiveTimeMax = liveTimeMax;

	//���� �ӵ� ����
	m_StartVelocityMin = velocityMin;
	m_StartVelocityMax = velocityMax;

	//���� ���� ����
	m_StartAccelateMin = accelMin;
	m_StartAccelateMax = accelMax;

	
	//���� ������ ����
	m_fStartScaleMin = scaleMin;
	m_fStartScaleMax = scaleMax;


	//���ۼ��� �ʱ�ȭ
	m_dwParticleCount = 0;

	//Texture ����
	m_pTex = pPaticleTexture;


	m_bLocal = bLocal;


	EmissionType = PZERO;


}

void cPartcleEmitter::Release()
{
	SAFE_DELETE_ARR( m_pPaticles );
	SAFE_DELETE_ARR( m_ParticleVerticles );
}

//��� �ȹ����� ���� ��Ʈ����.
void cPartcleEmitter::Burst( int num, float minSpeed, float maxSpeed, float maxLife, float minLife )
{
	for( int i = 0 ; i < num ; i++ )
	{
		D3DXVECTOR3 randVec( 
			RandomFloatRange( -1.0f, 1.0f ),
			RandomFloatRange( -1.0f, 1.0f ),
			RandomFloatRange( -1.0f, 1.0f ) );

		D3DXVec3Normalize( &randVec, &randVec  );
		randVec*= RandomFloatRange( minSpeed, maxSpeed );


		StartOneParticle( randVec, RandomFloatRange(maxLife,minLife ) );
	}
}

void cPartcleEmitter::BaseObjectUpdate( float timeDelta )	
{
		//��� ��ƼŬ ������Ʈ
	for( int i = 0 ; i < m_PaticleNum ; i++ ){
		m_pPaticles[i].Update( timeDelta );
	}

	//�ʰ� ���� �߻� ���´�?
	if( m_bEmission ){

		//�ϳ� �߻��ϰ� �����ð�
 		m_fEmisionDeltaTime += timeDelta;

		while( m_fEmisionDeltaTime >= m_fEmisionIntervalTime){	

			m_fEmisionDeltaTime -= m_fEmisionIntervalTime;
			//��ƼŬ �ϳ� �߻�
			StartOneParticle();
		}

	}





}
void cPartcleEmitter::BaseObjectRender()
{
	//�׸� ��ƼŬ ��
	DWORD drawParticleNum = 0;

	for( int i = 0 ; i < m_PaticleNum ; i++ ){

		//�ش���ƼŬ�� Ȱ��ȭ ���̴�?
		if( m_pPaticles[i].isLive() ){

			//�ش� ��ƼŬ�� ������ ��´�.
			m_pPaticles[i].GetParticleVertex(
				m_ParticleVerticles + drawParticleNum,
				m_Colors, m_Scales );


			drawParticleNum++;

		}



	}


	Device->SetRenderState( D3DRS_LIGHTING, false );		//�������� ����.
	Device->SetRenderState( D3DRS_POINTSPRITEENABLE, true );	//����Ʈ ���ö���Ʈ Ȱ��ȭ
	Device->SetRenderState( D3DRS_POINTSCALEENABLE, true );	//����Ʈ�� �����ϰ� ���̰ڴ�.
	Device->SetRenderState( D3DRS_POINTSIZE_MIN, FloatToDWORD( 0.0f ) );		//����Ʈ�� �ּ� ũ�� ( ȭ����� )
	Device->SetRenderState( D3DRS_POINTSIZE_MAX, FloatToDWORD( 500.0f ) );		//����Ʈ�� �ִ� ũ�� ( ȭ����� )
	//Device->SetRenderState( D3DRS_POINTSIZE, FloatToDWORD( 10.0f ) );			//����Ʈ ���� ������ ( ������ ����Ʈ ����� ������ ���õǴµ� );

	Device->SetRenderState( D3DRS_ZWRITEENABLE, false );	//z ������ ���⸦ ���´�.



	//��µǴ� POINT size 
	//finalSize = viewportHeight * pointSize *  sqrt( 1 / ( A + B(D) + C(D^2) )  );
	//�Ʒ��� ���� �ϸ� �ڿ������� �Ÿ��� ���� �������� ��Ÿ��
	Device->SetRenderState( D3DRS_POINTSCALE_A, FloatToDWORD( 0.0f ) );
	Device->SetRenderState( D3DRS_POINTSCALE_B, FloatToDWORD( 0.0f ) );
	Device->SetRenderState( D3DRS_POINTSCALE_C, FloatToDWORD( 1.0f ) );

	//���� ���� ����
	Device->SetRenderState( D3DRS_ALPHABLENDENABLE, true );
	Device->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	Device->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE);

	//Texture �� ���� Diffuse ���⼭�� �����÷��� ���İ� �� ���� ���� ����� �Ѵ�.
	Device->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE );
	Device->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE );
	Device->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE );

	D3DXMATRIXA16 matWorld;
	
	if( m_bLocal == false )
		D3DXMatrixIdentity( &matWorld );
	else
		matWorld = this->pTransform->GetFinalMatrix();

	Device->SetTransform( D3DTS_WORLD, &matWorld );


	//��ƼŬ Texture ����
	Device->SetTexture( 0, m_pTex );

	//��ƼŬ ���� ���
	Device->SetFVF( PARTICLE_VERTEX::FVF );
	Device->DrawPrimitiveUP( 
		D3DPT_POINTLIST, 
		drawParticleNum, 
		m_ParticleVerticles, 
		sizeof( PARTICLE_VERTEX ) );


	//��ƼŬ �׸��� ���� ��ó��
	Device->SetRenderState( D3DRS_LIGHTING, true );
	Device->SetRenderState( D3DRS_POINTSPRITEENABLE, false );
	Device->SetRenderState( D3DRS_POINTSCALEENABLE, false );
	Device->SetRenderState( D3DRS_ALPHABLENDENABLE, false );
	Device->SetRenderState( D3DRS_ZWRITEENABLE, true );	

	Device->SetTexture( 0, NULL );

}

//��ƼŬ ���� ����
void cPartcleEmitter::StartEmission()
{
	m_bEmission = true;
}

//��ƼŬ ���� ����
void cPartcleEmitter::StopEmission()
{
	m_bEmission = false;
}





///////////////////////////////////////////////////


//��ƼŬ �ϳ� ����
void cPartcleEmitter::StartOneParticle()
{
	//���̺� Ÿ�� ����
	float liveTime = RandomFloatRange(
		m_fStartLiveTimeMin, m_fStartLiveTimeMax );

	
	//��ƼŬ�� ������ ��ġ
	D3DXVECTOR3 position;
	
	//������ �ƴѰ�� �ڽ��� ���� ��ġ���� �����ϰ� 
	if( this->m_bLocal == false )
		position = this->pTransform->GetWorldPosition();

	//������ ��� 0 ���� �����Ѵ�.
	else
		position = D3DXVECTOR3( 0, 0, 0 );

	//���� ������ ���� �߰� ��ġ....
	if( EmissionType == PATICLE_EMISSION_TYPE::SPHERE )
	{
		//��������
		D3DXVECTOR3 randDir(
			RandomFloatRange( -1.0f, 1.0f ),
			RandomFloatRange( -1.0f, 1.0f ),
			RandomFloatRange( -1.0f, 1.0f ) );

		D3DXVec3Normalize( &randDir, &randDir );

		//�����Ÿ�
		float randDistance = RandomFloatRange( 0, SphereEmissionRange );

		//�߰���ġ
		position += randDir * randDistance;
	}

	else if( EmissionType == PATICLE_EMISSION_TYPE::SPHERE_OUTLINE )
	{
		//��������
		D3DXVECTOR3 randDir(
			RandomFloatRange( -1.0f, 1.0f ),
			RandomFloatRange( -1.0f, 1.0f ),
			RandomFloatRange( -1.0f, 1.0f ) );

		D3DXVec3Normalize( &randDir, &randDir );

		//�߰���ġ
		position += randDir * SphereEmissionRange;
	}

	else if( EmissionType == PATICLE_EMISSION_TYPE::BOX )
	{
		//��������
		D3DXVECTOR3 randDir(
			RandomFloatRange( MinEmissionRangeX, MaxEmissionRangeX ),
			RandomFloatRange( MinEmissionRangeY, MaxEmissionRangeY ),
			RandomFloatRange( MinEmissionRangeZ, MaxEmissionRangeZ ) );


		//�߰���ġ
		position += randDir;
	}









	//���� ����
	D3DXVECTOR3 velocity;
	velocity.x = RandomFloatRange( m_StartVelocityMin.x, m_StartVelocityMax.x );
	velocity.y = RandomFloatRange( m_StartVelocityMin.y, m_StartVelocityMax.y );
	velocity.z = RandomFloatRange( m_StartVelocityMin.z, m_StartVelocityMax.z );
	
	D3DXVECTOR3 accelation;
	accelation.x = RandomFloatRange( m_StartAccelateMin.x, m_StartAccelateMax.x );
	accelation.y = RandomFloatRange( m_StartAccelateMin.y, m_StartAccelateMax.y );
	accelation.z = RandomFloatRange( m_StartAccelateMin.z, m_StartAccelateMax.z );


	//�ڽ��� ���� ��Ʈ������ ������ �´�.
	if( m_bLocal == false )
	{
		D3DXMATRIXA16 matWorld = this->pTransform->GetFinalMatrix();
		D3DXVec3TransformNormal( &velocity, &velocity, &matWorld );
		D3DXVec3TransformNormal( &accelation, &accelation, &matWorld );
	}


	//�����ϵ� ����
	float scale = RandomFloatRange( m_fStartScaleMin, m_fStartScaleMax );


	//������� �߻���Ų��
	m_pPaticles[ m_dwParticleCount ].Start(
		liveTime,
		&position, &velocity, &accelation, scale );

	//���� ��ƼŬ�� ���� ���� ����
	m_dwParticleCount++;
	if( m_dwParticleCount == this->m_PaticleNum )
		m_dwParticleCount = 0;



}

//��ƼŬ �ϳ� ���� ( ���� �־ )
void cPartcleEmitter::StartOneParticle( D3DXVECTOR3 dir, float life )
{
	
	float liveTime = life;

	//��ƼŬ�� ������ ��ġ
	D3DXVECTOR3 position;
	if( this->m_bLocal == false )
		position = pTransform->GetWorldPosition();
	else
		position = D3DXVECTOR3( 0, 0, 0 );


	//���� ����
	D3DXVECTOR3 velocity;
	velocity.x = dir.x;
	velocity.y = dir.y;
	velocity.z = dir.z;

	D3DXVECTOR3 accelation;
	accelation.x = RandomFloatRange( m_StartAccelateMin.x, m_StartAccelateMax.x );
	accelation.y = RandomFloatRange( m_StartAccelateMin.y, m_StartAccelateMax.y );
	accelation.z = RandomFloatRange( m_StartAccelateMin.z, m_StartAccelateMax.z );



	//�ڽ��� ���� ��Ʈ������ ������ �´�.
	if( m_bLocal == false )
	{
		D3DXMATRIXA16 matWorld = this->pTransform->GetFinalMatrix();
		D3DXVec3TransformNormal( &velocity, &velocity, &matWorld );
		D3DXVec3TransformNormal( &accelation, &accelation, &matWorld );
	}

	//�����ϵ� ����
	float scale = RandomFloatRange( m_fStartScaleMin, m_fStartScaleMax );


	//�߻���Ų��
	m_pPaticles[ m_dwParticleCount ].Start(
		liveTime,
		&position, &velocity, &accelation, scale );


	m_dwParticleCount++;
	if( m_dwParticleCount == this->m_PaticleNum )
		m_dwParticleCount = 0;

}