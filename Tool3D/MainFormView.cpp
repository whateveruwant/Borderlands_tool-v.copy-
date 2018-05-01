// MainFormView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool3D.h"
#include "MainFormView.h"


// CMainFormView

IMPLEMENT_DYNCREATE(CMainFormView, CFormView)

CMainFormView::CMainFormView()
	: CFormView(IDD_FORMVIEW)
{
	//CString buf;
	//buf = "10";
	//cellSizeEdit.SetWindowTextA(buf);
	m_pTabBase = NULL;
	m_pTabHeight = NULL;
}

CMainFormView::~CMainFormView()
{
	SAFE_DELETE(m_pTabBase);
	SAFE_DELETE(m_pTabHeight);
	SAFE_DELETE(m_pTabSplat);
	SAFE_DELETE(m_pTabObject);
}

void CMainFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, cellSizeEdit);
	DDX_Control(pDX, IDC_TAB2, m_ctlTab);
}

BEGIN_MESSAGE_MAP(CMainFormView, CFormView)
	ON_EN_KILLFOCUS(IDC_EDIT1, &CMainFormView::OnEnKillfocusEdit1)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB2, &CMainFormView::OnTcnSelchangeTab2)
END_MESSAGE_MAP()


// CMainFormView 진단입니다.

#ifdef _DEBUG
void CMainFormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMainFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMainFormView 메시지 처리기입니다.


void CMainFormView::OnEnKillfocusEdit1()
{
	UpdateData(TRUE);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString buf;
	cellSizeEdit.GetWindowTextA(buf);
	cGame->GetList()->fRangeSize = _ttof(buf);
}

void CMainFormView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();


	char tmp[200];
	sprintf(tmp, "%d", 10);
	cellSizeEdit.SetWindowTextA(tmp);
	
	m_ctlTab.DeleteAllItems();
	m_ctlTab.InsertItem(0, "Base");
	m_ctlTab.InsertItem(1, "Height");
	m_ctlTab.InsertItem(2, "Splatting");
	m_ctlTab.InsertItem(3, "Object");
	
	CRect rect;

	m_pTabBase = new tabBase;
	m_pTabBase->Create(IDD_DIALOG1, &m_ctlTab);
	m_pTabBase->GetWindowRect(&rect);
	m_pTabBase->MoveWindow(5, 25, rect.Width(), rect.Height());
	m_pTabBase->ShowWindow(SW_SHOW);
	m_pTabBase->SetGame(this->cGame);

	m_pTabHeight = new tabHeight;
	m_pTabHeight->Create(IDD_DIALOG2, &m_ctlTab);
	m_pTabHeight->GetWindowRect(&rect);
	m_pTabHeight->MoveWindow(5, 25, rect.Width(), rect.Height());
	m_pTabHeight->ShowWindow(SW_HIDE);
	m_pTabHeight->SetGame(this->cGame);

	m_pTabSplat = new tabSplat;
	m_pTabSplat->Create(IDD_DIALOG3, &m_ctlTab);
	m_pTabSplat->GetWindowRect(&rect);
	m_pTabSplat->MoveWindow(5, 25, rect.Width(), rect.Height());
	m_pTabSplat->ShowWindow(SW_HIDE);
	m_pTabSplat->SetGame(this->cGame);

	m_pTabObject = new tabObject;
	m_pTabObject->Create(IDD_DIALOG4, &m_ctlTab);
	m_pTabObject->GetWindowRect(&rect);
	m_pTabObject->MoveWindow(5, 25, rect.Width(), rect.Height());
	m_pTabObject->ShowWindow(SW_HIDE);
	m_pTabObject->SetGame(this->cGame);

	UpdateData(FALSE);
}


void CMainFormView::OnTcnSelchangeTab2(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int select = m_ctlTab.GetCurSel();

	switch (select)
	{
	case 0:
		m_pTabBase->ShowWindow(SW_SHOW);
		m_pTabHeight->ShowWindow(SW_HIDE);
		m_pTabSplat->ShowWindow(SW_HIDE);
		m_pTabObject->ShowWindow(SW_HIDE);
		cGame->m_pNowScene->sourceList->eTab = BASE;
		break;
	case 1:
		m_pTabBase->ShowWindow(SW_HIDE);
		m_pTabHeight->ShowWindow(SW_SHOW);
		m_pTabSplat->ShowWindow(SW_HIDE);
		m_pTabObject->ShowWindow(SW_HIDE);
		cGame->m_pNowScene->sourceList->eTab = HEIGHT;
		break;
	case 2:
		m_pTabBase->ShowWindow(SW_HIDE);
		m_pTabHeight->ShowWindow(SW_HIDE);
		m_pTabSplat->ShowWindow(SW_SHOW);
		m_pTabObject->ShowWindow(SW_HIDE);
		cGame->m_pNowScene->sourceList->eTab = SPLAT;
		break;
	case 3:
		m_pTabBase->ShowWindow(SW_HIDE);
		m_pTabHeight->ShowWindow(SW_HIDE);
		m_pTabSplat->ShowWindow(SW_HIDE);
		m_pTabObject->ShowWindow(SW_SHOW);
		cGame->m_pNowScene->sourceList->eTab = OBJECT;
		break;
	}

	*pResult = 0;
}
