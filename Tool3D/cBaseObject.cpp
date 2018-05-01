#include "StdAfx.h"
#include "cBaseObject.h"
#include "cTransform.h"
#include "cSkinnedAnimation.h"


cBaseObject::cBaseObject(void)
	: bActive( false ), pMesh( NULL ), pSkinned( NULL )
{
	this->pTransform = new cTransform();
	IgnoreCreateShadow = false;
	ApplyShadow = true;

	this->CullMode = D3DCULL_NONE;
}

cBaseObject::~cBaseObject(void)
{
	SAFE_DELETE( this->pTransform );
	if( this->pSkinned != NULL )
	{
		this->pSkinned->Release();
		SAFE_DELETE( this->pSkinned );
	}
}


void cBaseObject::Update( float timeDelta ){
		if( this->bActive ){
			this->BaseObjectUpdate( timeDelta );
			if( this->pSkinned != NULL )
				this->pSkinned->Update( timeDelta );
		}
		else
			this->BaseObjectNoActiveUpdate( timeDelta );
}



//Ȱ��ȭ ����
void cBaseObject::SetActive( bool bActive ){
	
	//Ȱ��ȭ �Ǿ��ִ� ���¿��� ��Ȱ��ȭ ���ý� 
	if( bActive == false && this->bActive )
	{
		this->bActive = false;
		this->BaseObjectDisable();
	}

	//��Ȱ��ȭ �Ǿ��ִ� ���¿��� Ȱ��ȭ ���ý�
	else if( bActive && this->bActive == false )
	{
		this->bActive = true;
		this->BaseObjectEnable();
	}
}


//BaseObject �� �׸��� ����
void cBaseObject::BaseObjectRender() {
	

	if( this->pMesh != NULL ){
		DWORD tmp;
		Device->GetRenderState(D3DRS_CULLMODE, &tmp);
		Device->SetRenderState( D3DRS_CULLMODE, this->CullMode );

		if( this->pSkinned ){

			if( this->ApplyShadow )
				cXMesh_Skinned::SetTechniqueName( "ReciveShadow" );
			else
				cXMesh_Skinned::SetTechniqueName( "Base" );

			this->pSkinned->Render( this->pTransform );

		}
		
		else{

			if( this->ApplyShadow )
				cXMesh_Static::SetTechniqueName( "ReciveShadow" );
			else
				cXMesh_Static::SetTechniqueName( "Base" );

			this->pMesh->Render( this->pTransform );
	
		}

		Device->SetRenderState(D3DRS_CULLMODE, tmp);

	}
	//this->BoundBox.RenderGizmo( this->pTransform );
}

void cBaseObject::BaseObjectRenderShadow()
{
	if( this->pMesh != NULL && this->IgnoreCreateShadow == false ){
		
		Device->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );

		if( this->pSkinned ){
			cXMesh_Skinned::SetTechniqueName( "CreateShadow" );
			this->pSkinned->Render( this->pTransform );
		}
		
		else{
			cXMesh_Static::SetTechniqueName( "CreateShadow" );
			this->pMesh->Render( this->pTransform );
	
		}
	}
}



//���õ� �޽��� ���� �ٿ��ڽ��� ���� �Ѵ�.
void cBaseObject::ComputeBoundBox()
{
	if( this->pMesh != NULL )
	{
		//���õ� �޽��� cXMesh_Static ���...
		cXMesh_Static* pStaticMesh = dynamic_cast< cXMesh_Static* >( this->pMesh );
		if( pStaticMesh != NULL )
		{
			this->BoundBox.localCenter = pStaticMesh->Bound_Center;
			this->BoundBox.halfSize = pStaticMesh->Bound_HalfSize;
			this->BoundBox.localMinPos = pStaticMesh->Bound_Min;
			this->BoundBox.localMaxPos = pStaticMesh->Bound_Max;
			this->BoundBox.radius = pStaticMesh->Bound_Radius;
		}


		//���õ� �޽��� cXMesh_Skinned ���... ( �ӽ÷� �ٿ�� �ڽ� )
		else
		{
			this->BoundBox.SetBound( &D3DXVECTOR3( 0, 0, 0), &D3DXVECTOR3( 10.0f, 10.0f, 10.0f ) );


		}
	}

}


//������ �� �޽��� �����Ѵ�.
void  cBaseObject::SetMesh( cXMesh*	pMesh ){
	
	this->pMesh = pMesh;
	cXMesh_Skinned* pSkin  = dynamic_cast<cXMesh_Skinned*>( pMesh );
	this->ComputeBoundBox();

	//StaticMesh ���...
	if( pSkin == NULL )
	{
		if( this->pSkinned != NULL )
		{
			this->pSkinned->Release();
			SAFE_DELETE( this->pSkinned );
		}

		pSkinned = NULL;
	}
	

	//SkinnedMesh ���...
	else
	{
		this->pSkinned = new cSkinnedAnimation();
		this->pSkinned->Init( pSkin );
	}

}
