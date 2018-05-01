#pragma once
#include "afxwin.h"
#include "GameEdu01.h"
#include "afxcmn.h"

// tabObject 대화 상자입니다.

class tabObject : public CDialogEx
{
	DECLARE_DYNAMIC(tabObject)

public:
	tabObject(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~tabObject();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
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
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnEnKillfocusEdit1();
	CComboBox mEnemyList;
	CComboBox mObjectList;
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	CEdit mEnemyScaleEdit;
	CSliderCtrl mEnemyScaleSlider;
	CSliderCtrl mObjectScaleSlider;
	CEdit mObjectScaleEdit;
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	float mScaleEdit;
	float mScaleSlider;
	afx_msg void OnCbnCloseupCombo2();
	afx_msg void OnNMReleasedcaptureSlider1(NMHDR *pNMHDR, LRESULT *pResult);
};
