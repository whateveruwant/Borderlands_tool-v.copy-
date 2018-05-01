// tabBase.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool3D.h"
#include "tabBase.h"
#include "afxdialogex.h"


// tabBase ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(tabBase, CDialog)

tabBase::tabBase(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG1, pParent)
{

}

tabBase::~tabBase()
{
}

void tabBase::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCEDITBROWSE1, mHeightTEX);
	DDX_Control(pDX, IDC_MFCEDITBROWSE2, mSplatTEX);
	DDX_Control(pDX, IDC_MFCEDITBROWSE3, mEnvironSphere);
	DDX_Control(pDX, IDC_BUTTON1, mHeightExcute);
	DDX_Control(pDX, IDC_BUTTON2, mSplatExcute);
	DDX_Control(pDX, IDC_BUTTON3, mEnvironExcute);
}

BOOL tabBase::OnInitDialog()
{
	CDialog::OnInitDialog();
	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RADIO3))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_RADIO4))->SetCheck(0);

	mHeightTEX.SetWindowTextA("../Resources/Testures/Default512.png");
	mSplatTEX.SetWindowTextA("../Resources/Testures/Default512_Splat.png");
	mEnvironSphere.SetWindowTextA("../Resources/TextureCUBE/grassenvmap1024.dds");
	return TRUE;
}


BEGIN_MESSAGE_MAP(tabBase, CDialog)
	ON_BN_CLICKED(IDC_RADIO1, &tabBase::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &tabBase::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &tabBase::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &tabBase::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_BUTTON1, &tabBase::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &tabBase::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &tabBase::OnBnClickedButton3)
END_MESSAGE_MAP()


// tabBase �޽��� ó�����Դϴ�.


void tabBase::OnBnClickedRadio1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RADIO3))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RADIO4))->SetCheck(0);
	cGame->GetList()->sHeightMap = "../Resources/Testures/Default128.png";
	cGame->GetList()->sSplatMap = "../Resources/Testures/Default128_Splat.png";
	cGame->ResetMap();
}


void tabBase::OnBnClickedRadio2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_RADIO3))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RADIO4))->SetCheck(0);
	cGame->GetList()->sHeightMap = "../Resources/Testures/Default256.png";
	cGame->GetList()->sSplatMap = "../Resources/Testures/Default256_Splat.png";
	cGame->ResetMap();
}


void tabBase::OnBnClickedRadio3()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RADIO3))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_RADIO4))->SetCheck(0);
	cGame->GetList()->sHeightMap = "../Resources/Testures/Default512.png";
	cGame->GetList()->sSplatMap = "../Resources/Testures/Default512_Splat.png";
	cGame->ResetMap();
}


void tabBase::OnBnClickedRadio4()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RADIO3))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RADIO4))->SetCheck(1);
	cGame->GetList()->sHeightMap = "../Resources/Testures/Default1024.png";
	cGame->GetList()->sSplatMap = "../Resources/Testures/Default1024_Splat.png";
	cGame->ResetMap();
}

void tabBase::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	mHeightExcute.EnableWindow(FALSE);
	CString buf;
	mHeightTEX.GetWindowTextA(buf);
	cGame->GetList()->sHeightMap = buf;
	cGame->ResetMap();
	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RADIO3))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RADIO4))->SetCheck(0);
	mHeightExcute.EnableWindow(TRUE);
}


void tabBase::OnBnClickedButton2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	mSplatExcute.EnableWindow(FALSE);
	CString buf;
	mSplatTEX.GetWindowTextA(buf);
	cGame->GetList()->sSplatMap = buf;
	cGame->ResetMap();
	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RADIO3))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RADIO4))->SetCheck(0);
	mSplatExcute.EnableWindow(TRUE);
}


void tabBase::OnBnClickedButton3()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	mEnvironExcute.EnableWindow(FALSE);
	CString buf;
	mEnvironSphere.GetWindowTextA(buf);
	cGame->GetList()->sEnvironment = buf;
	cGame->m_pNowScene->SetEnvironment(cGame->GetList()->sEnvironment);
	mEnvironExcute.EnableWindow(TRUE);
}
