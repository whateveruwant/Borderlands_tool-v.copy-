#pragma once
#include "GameEdu01.h"
#include "afxeditbrowsectrl.h"
#include "afxwin.h"


// tabSplat 대화 상자입니다.

class tabSplat : public CDialogEx
{
	DECLARE_DYNAMIC(tabSplat)

public:
	tabSplat(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~tabSplat();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

	CGameEdu01* cGame;
	void SetGame(CGameEdu01* cGame) {
		this->cGame = cGame;
	}
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedButton1();
	CMFCEditBrowseCtrl mTexture1;
	CMFCEditBrowseCtrl mTexture2;
	CMFCEditBrowseCtrl mTexture3;
	CMFCEditBrowseCtrl mTexture4;
	CButton mTexture1Excute;
	CButton mTexture2Excute;
	CButton mTexture3Excute;
	CButton mTexture4Excute;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
};
