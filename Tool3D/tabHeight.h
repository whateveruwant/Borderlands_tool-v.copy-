#pragma once
#include "afxwin.h"
#include "GameEdu01.h"
#include "afxcmn.h"


// tabHeight ��ȭ �����Դϴ�.

class tabHeight : public CDialogEx
{
	DECLARE_DYNAMIC(tabHeight)

public:
	tabHeight(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~tabHeight();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
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
	CEdit mHeightScale;
	afx_msg void OnEnKillfocusEdit2();
	CSliderCtrl mHeightSlide;
	afx_msg void OnNMReleasedcaptureSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	CEdit mOpacityEdit;
	CSliderCtrl mOpacitySlide;
	afx_msg void OnNMReleasedcaptureSlider2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnKillfocusEdit1();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	bool mPlus;
	bool mMinus;
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio5();
	afx_msg void OnBnClickedRadio6();
//	afx_msg void OnEnChangeEdit3();
	CEdit mSmooth;
	afx_msg void OnEnKillfocusEdit3();
	afx_msg void OnBnClickedButton2();
	CButton mSmoothExcute;
	afx_msg void OnBnClickedButton3();
};
