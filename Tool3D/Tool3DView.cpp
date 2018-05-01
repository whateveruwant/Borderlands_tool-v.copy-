
// Tool3DView.cpp : CTool3DView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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

// CTool3DView ����/�Ҹ�

CTool3DView::CTool3DView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CTool3DView::~CTool3DView()
{
	m_GameEdu01.Cleanup();
}

BOOL CTool3DView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CTool3DView �׸���

void CTool3DView::OnDraw(CDC* /*pDC*/)
{
	CTool3DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
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


// CTool3DView ����

#ifdef _DEBUG
void CTool3DView::AssertValid() const
{
	CView::AssertValid();
}

void CTool3DView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTool3DDoc* CTool3DView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTool3DDoc)));
	return (CTool3DDoc*)m_pDocument;
}
#endif //_DEBUG


// CTool3DView �޽��� ó����


void CTool3DView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	m_GameEdu01.InitD3D(this->m_hWnd);
}


BOOL CTool3DView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	return FALSE;
}


LRESULT CTool3DView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	m_GameEdu01.WndProc(g_hWnd, message, wParam, lParam);
	return CView::WindowProc(message, wParam, lParam);
}
