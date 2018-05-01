
// Tool3DView.h : CTool3DView 클래스의 인터페이스
//

#pragma once
#include "Tool3DDoc.h"
#include "GameEdu01.h"
class cScene_01;
class CTool3DView : public CView
{
protected: // serialization에서만 만들어집니다.
	CTool3DView();
	DECLARE_DYNCREATE(CTool3DView)

// 특성입니다.
public:
	CTool3DDoc* GetDocument() const;
	CGameEdu01 m_GameEdu01;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 구현입니다.
public:
	virtual ~CTool3DView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
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

#ifndef _DEBUG  // Tool3DView.cpp의 디버그 버전
inline CTool3DDoc* CTool3DView::GetDocument() const
   { return reinterpret_cast<CTool3DDoc*>(m_pDocument); }
#endif

