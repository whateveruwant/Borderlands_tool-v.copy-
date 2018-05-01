#pragma once
#include <d3d9.h>

class CD3DApp
{

protected:
	virtual void OnInit()=0;
	virtual void OnRender()=0;
	virtual void OnUpdate()=0;
	virtual void OnRelease()=0;

public:
	HRESULT InitD3D( HWND hWnd );
	void Render();
	void Update();
	void Cleanup();

public:
	CD3DApp(void);
	~CD3DApp(void);
};