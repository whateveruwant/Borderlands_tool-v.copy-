
// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������ 
// ��� �ִ� ���� �����Դϴ�.

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
#endif

#include "targetver.h"

#define _CRT_SECURE_NO_WARNINGS      // �Ϻ� CString �����ڴ� ��������� ����˴ϴ�.
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // �Ϻ� CString �����ڴ� ��������� ����˴ϴ�.

// MFC�� ���� �κа� ���� ������ ��� �޽����� ���� ����⸦ �����մϴ�.
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC �ٽ� �� ǥ�� ���� ����Դϴ�.
#include <afxext.h>         // MFC Ȯ���Դϴ�.

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Internet Explorer 4 ���� ��Ʈ�ѿ� ���� MFC �����Դϴ�.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // Windows ���� ��Ʈ�ѿ� ���� MFC �����Դϴ�.
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC�� ���� �� ��Ʈ�� ���� ����


#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

#include <d3dx9.h>
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
//
// ��ũ�� ���
//
#define WINSIZE_X	1240				//�ʱ� ������ ���� ũ��
#define WINSIZE_Y	787					//�ʱ� ������ ���� ũ��
#define WINPOS_X	100					//�ʱ� ������ ���� ��ġ X
#define WINPOS_Y	10					//�ʱ� ������ ���� ��ġ Y
#define WIN_CLASS	"Windows Exam"		//������ Ŭ���� �̸�
#define WIN_TITLE	"Windows Exam"		//������ Ÿ��Ʋ �̸�
#define WIN_STYLE	WS_OVERLAPPEDWINDOW	//������ ����


#define ONE_RAD 0.017453f		//����1 ��

extern HWND g_hWnd;
extern HINSTANCE	g_hInst;	//���α׷� �ν��Ͻ� �ڵ� ( OS �� �ο��� ���α׷� ��ȣ )

//
// ��ũ�� �Լ�
//
#define SAFE_DELETE(p)		{ if(p){ delete (p); (p) = NULL; } }
#define SAFE_DELETE_ARR(p)	{ if(p){ delete[] (p); (p) = NULL; } }
#define SAFE_RELEASE(p)		{ if(p){ (p)->Release(); (p) = NULL; } }

#include <string>
#include <vector>
#include <map>

//
// �Ŵ���
//
#include "UserSetting.h"
#include "MyUtil.h"
using namespace MyUtil;
using namespace std;

//
// ��Ÿ ���
//
#include "cTimeMgr.h"
#include "cKeyMgr.h"
#include "cDXFontManager.h"
#include "cGizmoManager.h"
#include "cPhysicManager.h"
#include "cSpriteManager.h"
#include "cResourceMgr_Texture.h"
#include "cResourceMgr_ShaderFX.h"
#include "cResourceMgr_XStaticMesh.h"
#include "cResourceMgr_XSkinnedMesh.h"