
// Tool3DView.h : CTool3DView Ŭ������ �������̽�
//

#pragma once
#include "Tool3DDoc.h"
#include "GameEdu01.h"
class cScene_01;
class CTool3DView : public CView
{
protected: // serialization������ ��������ϴ�.
	CTool3DView();
	DECLARE_DYNCREATE(CTool3DView)

// Ư���Դϴ�.
public:
	CTool3DDoc* GetDocument() const;
	CGameEdu01 m_GameEdu01;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// �����Դϴ�.
public:
	virtual ~CTool3DView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

	CGameEdu01* GetGame() {
		return &m_GameEdu01;
	}
};

#ifndef _DEBUG  // Tool3DView.cpp�� ����� ����
inline CTool3DDoc* CTool3DView::GetDocument() const
   { return reinterpret_cast<CTool3DDoc*>(m_pDocument); }
#endif

