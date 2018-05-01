#pragma once
#include "GameEdu01.h"
#include "afxeditbrowsectrl.h"
#include "afxwin.h"

// tabBase ��ȭ �����Դϴ�.

class tabBase : public CDialog
{
	DECLARE_DYNAMIC(tabBase)

public:
	tabBase(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~tabBase();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

	CGameEdu01* cGame;
	void SetGame(CGameEdu01* cGame) {
		this->cGame = cGame;
	}
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	CMFCEditBrowseCtrl mHeightTEX;
	CMFCEditBrowseCtrl mSplatTEX;
	CMFCEditBrowseCtrl mEnvironSphere;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	CButton mHeightExcute;
	CButton mSplatExcute;
	CButton mEnvironExcute;
};
