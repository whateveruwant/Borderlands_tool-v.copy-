#include "StdAfx.h"
#include "cQuadParticleEmitter.h"

cQuadParticleEmitter::cQuadParticleEmitter(void)
	: m_pCameraTransform( NULL ), m_bCameraSort( false )
{
}


cQuadParticleEmitter::~cQuadParticleEmitter(void)
{
}

HRESULT cQuadParticleEmitter::Init( 
		DWORD partcleNum,					//�� ��ƼŬ ��
		float emission,						//�ʴ� �߻���
		float liveTimeMin,
		float liveTimeMax,
		const D3DXVECTOR3& velocityMin,
		const D3DXVECTOR3& velocityMax,
		const D3DXVECTOR3& accelMin,
		const D3DXVECTOR3& accelMax,
		const D3DXVECTOR3& startRotateMin,		//�����Ҷ� ȸ�� �ּҰ� 
		const D3DXVECTOR3& startRotateMax,		//�����Ҷ� ȸ�� �ִ밪
		const D3DXVECTOR3& rotateMin,			//�����ӿ����� ȸ�� �ּҷ�
		const D3DXVECTOR3& rotateMax,			//�����ӿ����� ȸ�� �ִ뷮
		const D3DXVECTOR3& rotateAccelMin,		//������ ���ӿ����� ȸ�� �ּҷ�
		const D3DXVECTOR3& rotateAccelMax,		//������ ���ӿ����� ȸ�� �ִ뷮
		const VEC_COLOR& colors,
		const VEC_SCALE& scales, 
		float scaleMin,
		float scaleMax,
		LPDIRECT3DTEXTURE9 pTex,
		bool bLocal
		)
{
	
	//�ش� ��ƼŬ ������ �� ��ƼŬ ��
	m_PaticleNum = partcleNum;

	//����ƼŬ �� * 4 ��ŭ ���ؽ��� �����
	m_ParticleVerticles = new PARTICLEQUAD_VERTEX[ m_PaticleNum * 4 ];

	//����ƼŬ �� * 6 ��ŭ �ε����� �����.
	m_ParticleIndex = new DWORD[ m_PaticleNum * 6 ];

	//��ƼŬ ��ü ����
	m_pPaticles = new cParticleQuad[ m_PaticleNum ];

	//��ƼŬ ��Ʈ�� Array
	m_pSortArray = new cParticleQuad*[ m_PaticleNum ];

	//�ʴ� ������
	m_fEmissionPerSec = emission;

	//�ʴ� ������ ���� �߻� ����
	m_fEmisionIntervalTime = 1.0f / m_fEmissionPerSec;

	//���� �ð��� 0
	m_fEmisionDeltaTime = 0.0f;

	//�߻� ���� false
	m_bEmission = false;

	//�÷� ����
	m_Colors.clear();
	for( int i = 0 ; i < colors.size() ;i++ )
		m_Colors.push_back( colors[i] );

	//������ ����
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

	//���۽� ȸ������ ���� �Լ�
	m_StartSetRotateMax = startRotateMax;
	m_StartSetRotateMin = startRotateMin;

	//����ȸ�� �� ����
	m_StartRotateMin = rotateMin;
	m_StartRotateMax = rotateMax;

	//ȸ�� ���� �� ����
	m_StartRotateAccelateMin = rotateAccelMin;
	m_StartRotateAccelateMax = rotateAccelMax;

	//���ۼ��� �ʱ�ȭ
	m_dwParticleCount = 0;

	//��ƼŬ �ؽ���
	m_pTex = pTex;

	m_bLocal = bLocal;

	return S_OK;
}
	
void cQuadParticleEmitter::Release()
{
	SAFE_DELETE_ARR( m_pSortArray );
	SAFE_DELETE_ARR( m_pPaticles );
	SAFE_DELETE_ARR( m_ParticleVerticles );
	SAFE_DELETE_ARR( m_ParticleIndex );
	SAFE_RELEASE( m_pTex );
}

void cQuadParticleEmitter::BaseObjectUpdate( float timeDelta )
{
	//�ʰ� ���� �߻� ���´�?
	if( m_bEmission ){
		//�ϳ� �߻��ϰ� �����ð�
		m_fEmisionDeltaTime += timeDelta;

		while( m_fEmisionDeltaTime > m_fEmisionIntervalTime){	
			m_fEmisionDeltaTime -= m_fEmisionIntervalTime;
			
			//��ƼŬ �ϳ� �߻�
			StartOneParticle();
		}
	}

	//��� ��ƼŬ ������Ʈ
	for( int i = 0 ; i < m_PaticleNum ; i++ ){
		m_pPaticles[i].Update( timeDelta );
	}
}
void cQuadParticleEmitter::BaseObjectRender()
{
	//�׸� ��ƼŬ ��
	DWORD drawParticleNum = 0;

	//ī�޶� ��Ʈ�� �ϴ�?
	if( this->m_bCameraSort && this->m_pCameraTransform != NULL )
	{
		//�׸� ��ƼŬ ��
		for( int i = 0 ; i < m_PaticleNum ; i++ ){

			//�ش���ƼŬ�� Ȱ��ȭ ���̴�?
			if( m_pPaticles[i].isLive() ){
				//��Ʈ�迭�� �ش� ��ƼŬ�� ���� ��Ų��.
				m_pSortArray[drawParticleNum] = &m_pPaticles[i];
				drawParticleNum++;
			}
		}

		//ī�޶� ���� ��ġ
		D3DXVECTOR3 cameraWorld = m_pCameraTransform->GetWorldPosition();

		//�׷����� ���� ��� ī�޶� �Ÿ��� ��Ʈ�� �����Ѵ�.
		for( int i = 0 ; i < ( drawParticleNum - 1 ) ; i++ ){
			

			for( int j = i + 1 ; j < drawParticleNum ; j++ ){

				//2���� ī�޶� �Ÿ��� ���

				//i �� ī�޶���� �Ÿ� ����
				D3DXVECTOR3 dirI = cameraWorld - m_pSortArray[i]->m_Transform.GetWorldPosition();
				float distI = D3DXVec3LengthSq( &dirI );

				//J �� ī�޶���� �Ÿ� ����
				D3DXVECTOR3 dirJ = cameraWorld - m_pSortArray[j]->m_Transform.GetWorldPosition();
				float distJ = D3DXVec3LengthSq( &dirJ );

				//�հŸ� ������
				if( distJ > distI ){

					cParticleQuad* pTemp = m_pSortArray[j];
					m_pSortArray[j] = m_pSortArray[i];
					m_pSortArray[i] = pTemp;

				}
			}
		}


		//��Ʈ�迭 ������ŭ���� �޽� ����
		for( int i = 0 ; i < drawParticleNum ; i++ ){

			
			//��Ʈ�迭�� �ش� ��ƼŬ�� ���� ��Ų��.
			m_pSortArray[i]->GetParticleVertex(
				&( m_ParticleVerticles[i * 4] ),
				&( m_ParticleIndex[i * 6] ),
				m_Colors, m_Scales, i );
				
			
		}



	}

	//��Ʈ ���ϴ�....
	else
	{
		
		for( int i = 0 ; i < m_PaticleNum ; i++ ){
			
			//�ش���ƼŬ�� Ȱ��ȭ ���̴�?
			if( m_pPaticles[i].isLive() ){
				//�ش� ��ƼŬ�� ������ ��´�.
				m_pPaticles[i].GetParticleVertex(
					&( m_ParticleVerticles[drawParticleNum * 4] ),		//���� ���� �ּ� 4 �� ����.
					&( m_ParticleIndex[drawParticleNum * 6] ),			//���� �ε��� �ּ� 6 �� ����.
					m_Colors, 
					m_Scales, 
					drawParticleNum										//�ε��� ���� �������� �׷��� ��ƼŬ���� ���� �Ѱܾ� �Ѵ�....
					);
				drawParticleNum++;
			}
		}

	}



	Device->SetRenderState( D3DRS_LIGHTING, false );		//�������� ����.
	Device->SetRenderState( D3DRS_ZWRITEENABLE, false );	//z ������ ���⸦ ���´�.

	Device->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

	//���� ���� ����
	Device->SetRenderState( D3DRS_ALPHABLENDENABLE, true );
	//Device->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	//Device->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE);


	Device->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	Device->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

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
	Device->SetFVF( PARTICLEQUAD_VERTEX::FVF );
	Device->DrawIndexedPrimitiveUP( 
		D3DPT_TRIANGLELIST, 
		0,
		drawParticleNum * 4,			//������
		drawParticleNum * 2,			//�ﰢ�� ��
		m_ParticleIndex,
		D3DFMT_INDEX32,
		m_ParticleVerticles,
		sizeof( PARTICLEQUAD_VERTEX ) );


	//��ƼŬ �׸��� ���� ��ó��
	Device->SetRenderState( D3DRS_LIGHTING, true );
	Device->SetRenderState( D3DRS_ALPHABLENDENABLE, false );
	Device->SetRenderState( D3DRS_ZWRITEENABLE, true );	

	Device->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );


	Device->SetTexture( 0, NULL );
}


void cQuadParticleEmitter::StartEmission()
{
	this->m_bEmission = true;
}

void cQuadParticleEmitter::StopEmission()
{
	this->m_bEmission = false;
}

//ī�޶� ������ �Ҳ���?
void cQuadParticleEmitter::SetCameraSort( cTransform* pCameraTrans, bool bSort )
{
	this->m_pCameraTransform = pCameraTrans;		//ī�޶� ��Ʈ ���
	this->m_bCameraSort = bSort;
}

////////////////////////////////

void cQuadParticleEmitter::StartOneParticle()
{
	//���̺� Ÿ�� ����
	float liveTime = RandomFloatRange(
		m_fStartLiveTimeMin, m_fStartLiveTimeMax );

	D3DXVECTOR3 position = pTransform->GetWorldPosition();

	//������ �ƴѰ�� �ڽ��� ���� ��ġ���� �����ϰ� 
	if( this->m_bLocal == false )
		position = this->pTransform->GetWorldPosition();
	
	//������ ��� 0 ���� �����Ѵ�.
	else
		position = D3DXVECTOR3( 0, 0, 0 );


	//���� ����
	D3DXVECTOR3 velocity;
	velocity.x = RandomFloatRange( m_StartVelocityMin.x, m_StartVelocityMax.x );
	velocity.y = RandomFloatRange( m_StartVelocityMin.y, m_StartVelocityMax.y );
	velocity.z = RandomFloatRange( m_StartVelocityMin.z, m_StartVelocityMax.z );
	
	D3DXVECTOR3 accelation;
	accelation.x = RandomFloatRange( m_StartAccelateMin.x, m_StartAccelateMax.x );
	accelation.y = RandomFloatRange( m_StartAccelateMin.y, m_StartAccelateMax.y );
	accelation.z = RandomFloatRange( m_StartAccelateMin.z, m_StartAccelateMax.z );


	D3DXVECTOR3 setRotate;
	setRotate.x = RandomFloatRange( m_StartSetRotateMin.x, m_StartSetRotateMax.x );
	setRotate.y = RandomFloatRange( m_StartSetRotateMin.y, m_StartSetRotateMax.y );
	setRotate.z = RandomFloatRange( m_StartSetRotateMin.z, m_StartSetRotateMax.z );


	//�������� ȸ���� ����
	D3DXVECTOR3 rotate;
	rotate.x = RandomFloatRange( m_StartRotateMin.x, m_StartRotateMax.x );
	rotate.y = RandomFloatRange( m_StartRotateMin.y, m_StartRotateMax.y );
	rotate.z = RandomFloatRange( m_StartRotateMin.z, m_StartRotateMax.z );


	//�������� ȸ�� ���ӷ� ����
	D3DXVECTOR3 rotateAccel;
	rotateAccel.x = RandomFloatRange( m_StartRotateAccelateMin.x, m_StartRotateAccelateMax.x );
	rotateAccel.y = RandomFloatRange( m_StartRotateAccelateMin.y, m_StartRotateAccelateMax.y );
	rotateAccel.z = RandomFloatRange( m_StartRotateAccelateMin.z, m_StartRotateAccelateMax.z );


	//�ڽ��� ���� ��Ʈ������ ������ �´�.
	if( m_bLocal == false )
	{
		D3DXMATRIXA16 matWorld = this->pTransform->GetFinalMatrix();
		D3DXVec3TransformNormal( &velocity, &velocity, &matWorld );
		D3DXVec3TransformNormal( &accelation, &accelation, &matWorld );
	}


	//�����ϵ� ����
	float scale = RandomFloatRange( m_fStartScaleMin, m_fStartScaleMax );


	m_pPaticles[ m_dwParticleCount ].m_Transform.SetRotateLocal( 
		setRotate.x, setRotate.y, setRotate.z );


	//������� �߻���Ų��
	m_pPaticles[ m_dwParticleCount ].Start(
		liveTime,			//���̺� Ÿ��
		&position,			//��ġ
		&velocity,			//���� ��Ƽ
		&accelation,		//����
		&rotate,			//ȸ����
		&rotateAccel,		//ȸ�� ����
		scale				//������
		);

	//���� ��ƼŬ�� ���� ���� ����
	m_dwParticleCount++;
	if( m_dwParticleCount == this->m_PaticleNum )
		m_dwParticleCount = 0;

}