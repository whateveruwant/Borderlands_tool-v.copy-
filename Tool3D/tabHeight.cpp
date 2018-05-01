// tabHeight.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool3D.h"
#include "tabHeight.h"
#include "afxdialogex.h"
#include "cTerrain.h"


// tabHeight 대화 상자입니다.

IMPLEMENT_DYNAMIC(tabHeight, CDialogEx)

tabHeight::tabHeight(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
	, mPlus(false)
	, mMinus(false)
{
}

tabHeight::~tabHeight()
{
}

void tabHeight::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, mHeightScale);
	DDX_Control(pDX, IDC_SLIDER1, mHeightSlide);
	DDX_Control(pDX, IDC_EDIT1, mOpacityEdit);
	DDX_Control(pDX, IDC_SLIDER2, mOpacitySlide);
	DDX_Control(pDX, IDC_EDIT3, mSmooth);
	DDX_Control(pDX, IDC_BUTTON2, mSmoothExcute);
}

BOOL tabHeight::OnInitDialog()
{
	CDialog::OnInitDialog();

	mHeightSlide.SetRange(0, 255);
	mHeightSlide.SetPos(100);
	mHeightSlide.SetTicFreq(10);
	mHeightSlide.SetSelection(0, 255);
	char tmp[200];
	sprintf(tmp, "%d", 100);
	mHeightScale.SetWindowTextA(tmp);


	mOpacitySlide.SetRange(1, 100);
	mOpacitySlide.SetPos(1);
	mOpacitySlide.SetTicFreq(10);
	mOpacitySlide.SetRange(1, 100);
	tmp[200];
	sprintf(tmp, "%d", 1);
	mOpacityEdit.SetWindowTextA(tmp);

	mPlus = true;
	mMinus = false;
	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RADIO3))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RADIO4))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RADIO5))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_RADIO6))->SetCheck(0);


	tmp[200];
	sprintf(tmp, "%d", 2);
	mSmooth.SetWindowTextA(tmp);
	return TRUE;
}

BEGIN_MESSAGE_MAP(tabHeight, CDialogEx)
	ON_EN_KILLFOCUS(IDC_EDIT2, &tabHeight::OnEnKillfocusEdit2)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER1, &tabHeight::OnNMReleasedcaptureSlider1)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER2, &tabHeight::OnNMReleasedcaptureSlider2)
	ON_EN_KILLFOCUS(IDC_EDIT1, &tabHeight::OnEnKillfocusEdit1)
	ON_BN_CLICKED(IDC_BUTTON1, &tabHeight::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_RADIO1, &tabHeight::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &tabHeight::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &tabHeight::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &tabHeight::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO5, &tabHeight::OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_RADIO6, &tabHeight::OnBnClickedRadio6)
	ON_EN_KILLFOCUS(IDC_EDIT3, &tabHeight::OnEnKillfocusEdit3)
	ON_BN_CLICKED(IDC_BUTTON2, &tabHeight::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &tabHeight::OnBnClickedButton3)
END_MESSAGE_MAP()


// tabHeight 메시지 처리기입니다.

void tabHeight::OnEnKillfocusEdit2()
{
	CString buf;
	mHeightScale.GetWindowTextA(buf);
	cGame->GetList()->iHeightMax = _ttoi(buf);
	mHeightSlide.SetPos(_ttoi(buf));
}


void tabHeight::OnNMReleasedcaptureSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	char tmp[200];
	sprintf(tmp, "%d", mHeightSlide.GetPos());
	mHeightScale.SetWindowTextA(tmp);
	cGame->GetList()->iHeightMax = mHeightSlide.GetPos();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void tabHeight::OnNMReleasedcaptureSlider2(NMHDR *pNMHDR, LRESULT *pResult)
{
	char tmp[200];
	sprintf(tmp, "%d", mOpacitySlide.GetPos());
	mOpacityEdit.SetWindowTextA(tmp);
	cGame->GetList()->fOpacity= mOpacitySlide.GetPos();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}


void tabHeight::OnEnKillfocusEdit1()
{
	CString buf;
	mOpacityEdit.GetWindowTextA(buf);
	cGame->GetList()->fOpacity = _ttoi(buf);
	mOpacitySlide.SetPos(_ttoi(buf));
}


void tabHeight::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	cGame->Flatten();
}


void tabHeight::OnBnClickedRadio1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (mMinus) {
		mMinus = false;
		mPlus = true;
		((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(0);
		((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(1);
		cGame->GetList()->bPlus = true;
	}
	switch (cGame->GetList()->eBrushType)
	{
	case eBrushType_1st:
		((CButton*)GetDlgItem(IDC_RADIO3))->SetCheck(1);
		break;
	case eBrushType_2nd:
		((CButton*)GetDlgItem(IDC_RADIO4))->SetCheck(1);
		break;
	case eBrushType_3rd:
		((CButton*)GetDlgItem(IDC_RADIO5))->SetCheck(1);
		break;
	case eBrushType_Eraser:
		((CButton*)GetDlgItem(IDC_RADIO6))->SetCheck(1);
		break;
	}
}


void tabHeight::OnBnClickedRadio2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (mPlus) {
		mPlus = false;
		mMinus = true;
		((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(1);
		((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(0);
		cGame->GetList()->bPlus = false;
	}
	switch (cGame->GetList()->eBrushType)
	{
	case eBrushType_1st:
		((CButton*)GetDlgItem(IDC_RADIO3))->SetCheck(1);
		break;
	case eBrushType_2nd:
		((CButton*)GetDlgItem(IDC_RADIO4))->SetCheck(1);
		break;
	case eBrushType_3rd:
		((CButton*)GetDlgItem(IDC_RADIO5))->SetCheck(1);
		break;
	case eBrushType_Eraser:
		((CButton*)GetDlgItem(IDC_RADIO6))->SetCheck(1);
		break;
	}
}


void tabHeight::OnBnClickedRadio3()
{
	if (cGame->GetList()->bPlus) {
		((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(0);
		((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(1);
	}
	else {
		((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(1);
		((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(0);
	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	((CButton*)GetDlgItem(IDC_RADIO3))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_RADIO4))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RADIO5))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RADIO6))->SetCheck(0);
	cGame->GetList()->eBrushType = eBrushType::eBrushType_1st;
}


void tabHeight::OnBnClickedRadio4()
{
	if (cGame->GetList()->bPlus) {
		((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(0);
		((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(1);
	}
	else {
		((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(1);
		((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(0);
	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	((CButton*)GetDlgItem(IDC_RADIO3))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RADIO4))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_RADIO5))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RADIO6))->SetCheck(0);
	cGame->GetList()->eBrushType = eBrushType::eBrushType_2nd;
}


void tabHeight::OnBnClickedRadio5()
{
	if (cGame->GetList()->bPlus) {
		((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(0);
		((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(1);
	}
	else {
		((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(1);
		((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(0);
	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	((CButton*)GetDlgItem(IDC_RADIO3))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RADIO4))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RADIO5))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_RADIO6))->SetCheck(0);
	cGame->GetList()->eBrushType = eBrushType::eBrushType_3rd;
}


void tabHeight::OnBnClickedRadio6()
{
	if (cGame->GetList()->bPlus) {
		((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(0);
		((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(1);
	}
	else {
		((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(1);
		((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(0);
	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	((CButton*)GetDlgItem(IDC_RADIO3))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RADIO4))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RADIO5))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RADIO6))->SetCheck(1);
	cGame->GetList()->eBrushType = eBrushType::eBrushType_Eraser;
}

void tabHeight::OnEnKillfocusEdit3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString buf;
	mSmooth.GetWindowTextA(buf);
	cGame->GetList()->iSmoothLevel = _ttoi(buf);
}


void tabHeight::OnBnClickedButton2()
{
	mSmoothExcute.EnableWindow(FALSE);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	cGame->Smoothing();
	mSmoothExcute.EnableWindow(TRUE);
}


void tabHeight::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	cGame->m_pNowScene->m_pTerrain->SaveHeightMap();
}
