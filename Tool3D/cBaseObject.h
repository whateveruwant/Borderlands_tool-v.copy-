#pragma once

class cXMesh;
class cTransform;
class cSkinnedAnimation;

class cBaseObject
{
public:
	cTransform*			pTransform;
	cXMesh*				pMesh;						//�ϰ� ����ϴ� �޽��� ����?
	cBoundBox			BoundBox;
	bool				IgnoreCreateShadow;			//������� ���鶧 ���õǴ�
	bool				ApplyShadow;				//������ �޴�?

	DWORD				CullMode;

protected:
	bool				bActive;	//Ȱ��ȭ ����
	cSkinnedAnimation*	pSkinned;	//��Ų�� Animtion


public:
	cBaseObject(void);
	~cBaseObject(void);

	void Update( float timeDelta );

	void Render(){
		if( this->bActive )
			this->BaseObjectRender();
	}

	void RenderShadow(){
		if( this->bActive )
			this->BaseObjectRenderShadow();
	}


	//������ �� �޽��� �����Ѵ�.
	void SetMesh( cXMesh*	pMesh );

	//Ȱ��ȭ ����
	void SetActive( bool bActive );

	cSkinnedAnimation* GetSkinned() {
		return pSkinned;
	}

	//Ȱ��ȭ ���θ� ��´�.
	bool IsActive() {
		return this->bActive;
	}


	//���õ� �޽��� ���� �ٿ��ڽ��� ���� �Ѵ�.
	void ComputeBoundBox();



protected:

	//override �ؼ� ���ÿ�....
	virtual void BaseObjectEnable() {}							//BaseObject �� Ȱ��ȭ �ɶ� ����
	virtual void BaseObjectDisable(){}							//BaseObject �� ��Ȱ��ȭ �ɶ� ����
	virtual void BaseObjectUpdate( float timeDelta ) {}			//BaseObject �� Update �� ����....
	virtual void BaseObjectNoActiveUpdate( float timeDelte){}	//BaseObject �� ��Ȱ��ȭ�� ������Ʈ ����....
	virtual void BaseObjectRender();							//BaseObject �� �׸��� ����
	virtual void BaseObjectRenderShadow();						//BaseObject �� �׸��� ����
};

