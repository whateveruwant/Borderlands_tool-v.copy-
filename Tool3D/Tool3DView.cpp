
// Tool3DView.cpp : CTool3DView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Tool3D.h"
#endif

#include "Tool3DDoc.h"
#include "Tool3DView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HWND g_hWnd;

// CTool3DView

IMPLEMENT_DYNCREATE(CTool3DView, CView)

BEGIN_MESSAGE_MAP(CTool3DView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CTool3DView 생성/소멸

CTool3DView::CTool3DView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CTool3DView::~CTool3DView()
{
	m_GameEdu01.Cleanup();
}

BOOL CTool3DView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CTool3DView 그리기

void CTool3DView::OnDraw(CDC* /*pDC*/)
{
	CTool3DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}

void CTool3DView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CTool3DView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CTool3DView 진단

#ifdef _DEBUG
void CTool3DView::AssertValid() const
{
	CView::AssertValid();
}

void CTool3DView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTool3DDoc* CTool3DView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTool3DDoc)));
	return (CTool3DDoc*)m_pDocument;
}
#endif //_DEBUG


// CTool3DView 메시지 처리기


void CTool3DView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	m_GameEdu01.InitD3D(this->m_hWnd);
}


BOOL CTool3DView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return FALSE;
}


LRESULT CTool3DView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_GameEdu01.WndProc(g_hWnd, message, wParam, lParam);
	return CView::WindowProc(message, wParam, lParam);
}
