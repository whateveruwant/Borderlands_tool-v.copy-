#pragma once
#include "afxwin.h"
#include "GameEdu01.h"
#include "afxcmn.h"
// CMainFormView 폼 뷰입니다.
#include "tabBase.h"
#include "tabHeight.h"
#include "tabSplat.h"
#include "tabObject.h"

class CMainFormView : public CFormView
{
	DECLARE_DYNCREATE(CMainFormView)

protected:
	CMainFormView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CMainFormView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORMVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CEdit cellSizeEdit;
	afx_msg void OnEnKillfocusEdit1();

	CGameEdu01* cGame;
	void SetGame(CGameEdu01* cGame) {
		this->cGame = cGame;
	}

public:
	CTabCtrl m_ctlTab;
	tabBase* m_pTabBase;
	tabHeight* m_pTabHeight;
	tabSplat* m_pTabSplat;
	tabObject* m_pTabObject;

	virtual void OnInitialUpdate();
	afx_msg void OnTcnSelchangeTab2(NMHDR *pNMHDR, LRESULT *pResult);
};


