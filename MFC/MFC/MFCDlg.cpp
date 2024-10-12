
// MFCDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFC.h"
#include "MFCDlg.h"

#include <iostream>

#include "afxdialogex.h"

#include "CImageDlg.h"
#include "CustomDefine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCDlg 대화 상자



CMFCDlg::CMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_DIALOG, pParent)
	, m_nX1(0)
	, m_nY1(0)
	, m_nX2(0)
	, m_nY2(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_X1, m_nX1);
	DDX_Text(pDX, IDC_EDIT_Y1, m_nY1);
	DDX_Text(pDX, IDC_EDIT_X2, m_nX2);
	DDX_Text(pDX, IDC_EDIT_Y2, m_nY2);
}

BEGIN_MESSAGE_MAP(CMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_DRAW, &CMFCDlg::OnBnClickedBtnDraw)
	ON_BN_CLICKED(IDC_BTN_ACTION, &CMFCDlg::OnBnClickedBtnAction)
	ON_BN_CLICKED(IDC_BTN_OPEN, &CMFCDlg::OnBnClickedBtnOpen)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMFCDlg 메시지 처리기

BOOL CMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	InitDlg();

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (m_pImgDlg) delete m_pImgDlg;
}

#pragma region 초기화
void CMFCDlg::InitDlg()
{
	m_pImgDlg = new CImageDlg;
	m_pImgDlg->Create(IDD_IMGDLG, this);
	m_pImgDlg->ShowWindow(SW_SHOW);
}
#pragma endregion


#pragma region 버튼 이벤트
void CMFCDlg::OnBnClickedBtnDraw()
{
	// 데이터 갱신
	UpdateData(true);

	// 좌표가 유효하지 않다면 경고 
	if(false == ValidatePoint(m_nX1, m_nY1))
	{
		CString message;
		message.Format(_T("시작 좌표를 다시 입력해주세요.\n(0 <= x < %d, 0 <= y < %d)"), IMG_WIDTH, IMG_HEIGHT);
		AfxMessageBox(message);
		return;
	}

	m_pImgDlg->DrawCircle(m_nX1, m_nY1, COLOR_GRAY);
	UpdateData(false);
}


void CMFCDlg::OnBnClickedBtnAction()
{
	// 데이터 갱신
	UpdateData(true);

	// 좌표가 유효하지 않다면 경고 
	if (false == ValidatePoint(m_nX1, m_nY1))
	{
		CString message;
		message.Format(_T("시작 좌표를 다시 입력해주세요.\n(0 <= x < %d, 0 <= y < %d)"), IMG_WIDTH, IMG_HEIGHT);
		AfxMessageBox(message);
		return;
	}
	if(false == ValidatePoint(m_nX2, m_nY2))
	{
		CString message;
		message.Format(_T("종료 좌표를 다시 입력해주세요.\n(0 <= x < %d, 0 <= y < %d)"), IMG_WIDTH, IMG_HEIGHT);
		AfxMessageBox(message);
		return;
	}
	if(m_nX1 == m_nX2 && m_nY1 == m_nY2)
	{
		AfxMessageBox(_T("시작 좌표와 종료 좌표를 다르게 설정해주세요."));
		return;
	}

	m_pImgDlg->MoveCircle(m_nX1, m_nY1, m_nX2, m_nY2);
	UpdateData(false);
}


void CMFCDlg::OnBnClickedBtnOpen()
{
	CString str = _T("All files(*.*)|*.*|"); // 모든 파일 표시
	// _T("Excel 파일 (*.xls, *.xlsx) |*.xls; *.xlsx|"); 와 같이 확장자를 제한하여 표시할 수 있음
	CFileDialog dlg(TRUE, _T("*.dat"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, str, this);

	if (dlg.DoModal() == IDOK)
	{
		CString strFilePath = dlg.GetPathName(); 
		m_pImgDlg->DrawFile(strFilePath);
	}
}
#pragma endregion

bool CMFCDlg::ValidatePoint(int x, int y)
{
	if (x < 0 || x >= IMG_WIDTH)
		return false;
	if (y < 0 || y >= IMG_HEIGHT)
		return false;

	return true;
}
