
// gMFCProjectDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "gMFCProject.h"
#include "gMFCProjectDlg.h"
#include "afxdialogex.h"
#include <iostream>
using namespace std;

#ifdef _DEBUG
	#define new DEBUG_NEW
	#ifdef UNICODE
		#pragma comment(linker, "/ENTRY:wWinMainCRTStartup /subsystem:console")
	#else
		#pragma comment(linker, "/ENTRY:WinMainCRTStartup /subsystem:console")
	#endif
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


// CgMFCProjectDlg 대화 상자



CgMFCProjectDlg::CgMFCProjectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GMFCPROJECT_DIALOG, pParent)
	, m_nInputSize(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CgMFCProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_INPUT_SIZE, m_nInputSize);
}

BEGIN_MESSAGE_MAP(CgMFCProjectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_MAKE_PATTERN, &CgMFCProjectDlg::OnBnClickedBtnMakePattern)
	ON_BN_CLICKED(IDC_BTN_PROCESS, &CgMFCProjectDlg::OnBnClickedBtnProcess)
END_MESSAGE_MAP()


// CgMFCProjectDlg 메시지 처리기

BOOL CgMFCProjectDlg::OnInitDialog()
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
	// 메인 윈도우 크기 조정
	this->MoveWindow(0, 0, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);

	// 이미지 윈도우 생성, 크기 조정, 초기화
	m_pImageWindow = new CImageWindow(this);
	m_pImageWindow->Create(IDD_IMAGE_WINDOW, NULL);
	m_pImageWindow->MoveWindow(IMAGE_WINDOW_MARGIN_WIDTH, IMAGE_WINDOW_MARGIN_HEIGHT, IMAGE_WINDOW_WIDTH, IMAGE_WINDOW_HEIGHT);
	m_pImageWindow->InitImage();
	m_pImageWindow->ShowWindow(SW_SHOW);

	// 이미지 처리 클래스 생성
	m_pImageProcess = new CImageProcess();

	// 입력 안내 텍스트
	CString strMsg;
	strMsg.Format(IDS_INFO_INPUT_VALUE, IMAGE_WINDOW_WIDTH < IMAGE_WINDOW_HEIGHT ? IMAGE_WINDOW_WIDTH : IMAGE_WINDOW_HEIGHT);
	GetDlgItem(IDC_STATIC_INFO)->SetWindowText(strMsg);
	
	UpdateData(FALSE);
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CgMFCProjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CgMFCProjectDlg::OnPaint()
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
HCURSOR CgMFCProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CgMFCProjectDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	if (m_pImageWindow)
		delete m_pImageWindow;

	if (m_pImageProcess)
		delete m_pImageProcess;
}


void CgMFCProjectDlg::OnBnClickedBtnMakePattern()
{
	// 입력값 검사
	int nInputSize = GetDlgItemInt(IDC_EDIT_INPUT_SIZE);
	cout << "InputSize : " << nInputSize << endl;

	int nMinVal = IMAGE_WINDOW_WIDTH < IMAGE_WINDOW_HEIGHT ? IMAGE_WINDOW_WIDTH : IMAGE_WINDOW_HEIGHT;

	if (nInputSize > nMinVal || nInputSize < 1) {
		CString strMsg;
		strMsg.Format(IDS_WARN_INPUT_VALUE, nMinVal);
		AfxMessageBox(strMsg);
	}
	else {
		int nPosX = rand() % (IMAGE_WINDOW_WIDTH - nInputSize + 1);
		int nPosY = rand() % (IMAGE_WINDOW_HEIGHT - nInputSize + 1);
		cout << "nPosX, nPosY : " << nPosX << ", " << nPosY  << endl;
		m_pImageWindow->DrawPattern(nPosX, nPosY, nInputSize);
	}
}


void CgMFCProjectDlg::OnBnClickedBtnProcess()
{
	int nCenterX = 0;
	int nCenterY = 0;

	// threshold 값 초과하는 픽셀의 무게중심 찾기
	if( m_pImageProcess->FindPattern(&m_pImageWindow->m_Image, COLOR_BLACK, &nCenterX, &nCenterY) )
		m_pImageWindow->DrawCrossLine(nCenterX, nCenterY); // 무게중심에 십자모양 라인 그리기
}
