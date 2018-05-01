// tabSplat.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool3D.h"
#include "tabSplat.h"
#include "afxdialogex.h"
#include "cTerrain.h"

// tabSplat 대화 상자입니다.

IMPLEMENT_DYNAMIC(tabSplat, CDialogEx)

tabSplat::tabSplat(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{
}

tabSplat::~tabSplat()
{
}

void tabSplat::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCEDITBROWSE1, mTexture1);
	DDX_Control(pDX, IDC_MFCEDITBROWSE2, mTexture2);
	DDX_Control(pDX, IDC_MFCEDITBROWSE3, mTexture3);
	DDX_Control(pDX, IDC_MFCEDITBROWSE4, mTexture4);
	DDX_Control(pDX, IDC_BUTTON1, mTexture1Excute);
	DDX_Control(pDX, IDC_BUTTON2, mTexture2Excute);
	DDX_Control(pDX, IDC_BUTTON3, mTexture3Excute);
	DDX_Control(pDX, IDC_BUTTON4, mTexture4Excute);
}

BOOL tabSplat::OnInitDialog()
{
	CDialog::OnInitDialog();
	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RADIO3))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RADIO4))->SetCheck(0);

	mTexture1.SetWindowTextA("../Resources/Testures/terrain1.jpg");
	mTexture2.SetWindowTextA("../Resources/Testures/terrain2.png");
	mTexture3.SetWindowTextA("../Resources/Testures/terrain3.png");
	mTexture4.SetWindowTextA("../Resources/Testures/terrain4.png");

	return TRUE;
}


BEGIN_MESSAGE_MAP(tabSplat, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO4, &tabSplat::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO3, &tabSplat::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO2, &tabSplat::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO1, &tabSplat::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_BUTTON1, &tabSplat::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &tabSplat::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &tabSplat::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &tabSplat::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &tabSplat::OnBnClickedButton5)
END_MESSAGE_MAP()


// tabSplat 메시지 처리기입니다.


void tabSplat::OnBnClickedRadio4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RADIO3))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RADIO4))->SetCheck(1);
	cGame->GetList()->eBrushTexture = eBrushTexture_4th;
}


void tabSplat::OnBnClickedRadio3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RADIO3))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_RADIO4))->SetCheck(0);
	cGame->GetList()->eBrushTexture = eBrushTexture_3rd;
}


void tabSplat::OnBnClickedRadio2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_RADIO3))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RADIO4))->SetCheck(0);
	cGame->GetList()->eBrushTexture = eBrushTexture_2nd;
}


void tabSplat::OnBnClickedRadio1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RADIO3))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RADIO4))->SetCheck(0);
	cGame->GetList()->eBrushTexture = eBrushTexture_1st;
}


void tabSplat::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	mTexture1Excute.EnableWindow(FALSE);
	CString buf;
	mTexture1.GetWindowTextA(buf);
	cGame->GetList()->sTerrain1 = buf;
	cGame->m_pNowScene->ChangeTexture1();
	mTexture1Excute.EnableWindow(TRUE);
}


void tabSplat::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	mTexture2Excute.EnableWindow(FALSE);
	CString buf;
	mTexture2.GetWindowTextA(buf);
	cGame->GetList()->sTerrain2 = buf;
	cGame->m_pNowScene->ChangeTexture2();
	mTexture2Excute.EnableWindow(TRUE);
}


void tabSplat::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	mTexture3Excute.EnableWindow(FALSE);
	CString buf;
	mTexture3.GetWindowTextA(buf);
	cGame->GetList()->sTerrain3 = buf;
	cGame->m_pNowScene->ChangeTexture3();
	mTexture3Excute.EnableWindow(TRUE);
}


void tabSplat::OnBnClickedButton4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	mTexture4Excute.EnableWindow(FALSE);
	CString buf;
	mTexture4.GetWindowTextA(buf);
	cGame->GetList()->sTerrain4 = buf;
	cGame->m_pNowScene->ChangeTexture4();
	mTexture4Excute.EnableWindow(TRUE);
}


void tabSplat::OnBnClickedButton5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	cGame->m_pNowScene->m_pTerrain->SaveSplatMap();
}
