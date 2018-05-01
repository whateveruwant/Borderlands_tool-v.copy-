// tabObject.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool3D.h"
#include "tabObject.h"
#include "afxdialogex.h"


// tabObject 대화 상자입니다.

IMPLEMENT_DYNAMIC(tabObject, CDialogEx)

tabObject::tabObject(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG4, pParent)
	, mScaleEdit(0)
	, mScaleSlider(0)
{

}

tabObject::~tabObject()
{
}

void tabObject::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, mEnemyList);
	DDX_Control(pDX, IDC_COMBO2, mObjectList);
	DDX_Control(pDX, IDC_SLIDER1, mObjectScaleSlider);
	DDX_Control(pDX, IDC_EDIT1, mObjectScaleEdit);
}

BOOL tabObject::OnInitDialog()
{
	CDialog::OnInitDialog();
	mObjectList.AddString("Toilet");
	mObjectList.AddString("vendingMachine");
	mObjectList.AddString("DahlEpicCrate");
	mObjectList.AddString("TreasureChest");
	mObjectList.AddString("saveVendingMachine");
	mObjectList.AddString("equipVendingMachine");
	mObjectList.AddString("itemVendingMachine");
	mObjectList.AddString("PanelHouse"); 
	mObjectList.AddString("WreckedCar02");
	mObjectList.AddString("Potal");
	mObjectList.AddString("Rock");
	mObjectList.AddString("Rock2");
	
	mEnemyList.AddString("Skag");
	mEnemyList.AddString("BattleDroid");
	mEnemyList.AddString("Bandit");

	mObjectScaleSlider.SetRange(0, 100);
	mObjectScaleSlider.SetPos(10);
	mObjectScaleSlider.SetTicFreq(10);
	mObjectScaleSlider.SetSelection(0, 100);
	SetDlgItemText(IDC_EDIT1, "0.1");


	return TRUE;
}


BEGIN_MESSAGE_MAP(tabObject, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &tabObject::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &tabObject::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &tabObject::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &tabObject::OnBnClickedButton4)
	ON_EN_KILLFOCUS(IDC_EDIT1, &tabObject::OnEnKillfocusEdit1)
	ON_BN_CLICKED(IDC_BUTTON5, &tabObject::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &tabObject::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &tabObject::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &tabObject::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &tabObject::OnBnClickedButton9)
	ON_CBN_CLOSEUP(IDC_COMBO2, &tabObject::OnCbnCloseupCombo2)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER1, &tabObject::OnNMReleasedcaptureSlider1)
END_MESSAGE_MAP()


// tabObject 메시지 처리기입니다.


void tabObject::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	cGame->m_pNowScene->SaveObjectsToFile("Object.save");
}


void tabObject::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	cGame->m_pNowScene->LoadObjectToFile("Object.save");
}


void tabObject::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString selectName;
	mObjectList.GetLBText(mObjectList.GetCurSel(), selectName);
	cGame->m_pNowScene->sourceList->sTmpObject = "../Resources/Meshes/Objects/";
	cGame->m_pNowScene->sourceList->sTmpObject += selectName;
	cGame->m_pNowScene->sourceList->sTmpObject += ".X";
	if (selectName == "DahlEpicCrate" || selectName == "TreasureChest")
		cGame->m_pNowScene->ChoiceObject(cGame->m_pNowScene->sourceList->sTmpObject, true);
	else
		cGame->m_pNowScene->ChoiceObject(cGame->m_pNowScene->sourceList->sTmpObject, false);

}


void tabObject::OnBnClickedButton4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	/*cXMesh_Static* pStaticMesh = dynamic_cast< cXMesh_Static* >(cGame->m_pNowScene->m_tmpObject->mObject->pMesh);
	cGame->m_pNowScene->m_tmpObject->mObject->BoundBox.localCenter = pStaticMesh->Bound_Center;
	cGame->m_pNowScene->m_tmpObject->mObject->BoundBox.halfSize = pStaticMesh->Bound_HalfSize;
	cGame->m_pNowScene->m_tmpObject->mObject->BoundBox.localMinPos = pStaticMesh->Bound_Min;
	cGame->m_pNowScene->m_tmpObject->mObject->BoundBox.localMaxPos = pStaticMesh->Bound_Max;
	cGame->m_pNowScene->m_tmpObject->mObject->BoundBox.radius = pStaticMesh->Bound_Radius;*/
}


void tabObject::OnEnKillfocusEdit1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//스케일
	CString buf;
	mObjectScaleEdit.GetWindowTextA(buf);
	mObjectScaleSlider.SetPos(_ttof(buf)*100);
	cGame->m_pNowScene->SetScaling(_ttof(buf));
}


void tabObject::OnBnClickedButton5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString selectName;
	mEnemyList.GetLBText(mEnemyList.GetCurSel(), selectName);
	cGame->m_pNowScene->sourceList->sTmpObject = "../Resources/Meshes/enemy/";
	cGame->m_pNowScene->sourceList->sTmpObject += selectName;
	cGame->m_pNowScene->sourceList->sTmpObject += "/";
	cGame->m_pNowScene->sourceList->sTmpObject += selectName;
	cGame->m_pNowScene->sourceList->sTmpObject += ".X";
	cGame->m_pNowScene->ChoiceEnemy(cGame->m_pNowScene->sourceList->sTmpObject);
}


void tabObject::OnBnClickedButton6()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void tabObject::OnBnClickedButton7()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	cGame->m_pNowScene->ObjectClear();
	cGame->m_pNowScene->EnemyClear();
}


void tabObject::OnBnClickedButton8()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 에너미 세이브
	cGame->m_pNowScene->SaveEnemysToFile("Enemy.save");
}


void tabObject::OnBnClickedButton9()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 에너미 로드
	cGame->m_pNowScene->LoadEnemysToFile("Enemy.save");
}

void tabObject::OnCbnCloseupCombo2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	char tmp[200];
	sprintf(tmp, "%0.2f\n", cGame->m_pNowScene->sourceList->fObjectScale);
	mObjectScaleEdit.SetWindowTextA(tmp);
	CString buf;
	mObjectScaleEdit.GetWindowTextA(buf);
	mObjectScaleSlider.SetPos(_ttof(buf)*100);
	cGame->m_pNowScene->SetScaling(_ttof(tmp));
}


void tabObject::OnNMReleasedcaptureSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	char tmp[200];
	sprintf(tmp, "%0.2f\n", (float)mObjectScaleSlider.GetPos()/100);
	mObjectScaleEdit.SetWindowTextA(tmp);
	cGame->m_pNowScene->SetScaling(_ttof(tmp));
	*pResult = 0;
}
