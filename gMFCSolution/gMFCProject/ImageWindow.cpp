// ImageWindow.cpp: 구현 파일
//

#include "pch.h"
#include "gMFCProject.h"
#include "afxdialogex.h"
#include "ImageWindow.h"
#include <iostream>
using namespace std;


// CImageWindow 대화 상자

IMPLEMENT_DYNAMIC(CImageWindow, CDialogEx)

CImageWindow::CImageWindow(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_IMAGE_WINDOW, pParent)
{

}

CImageWindow::~CImageWindow()
{
}

void CImageWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CImageWindow, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CImageWindow 메시지 처리기


BOOL CImageWindow::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	//InitImage();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CImageWindow::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.

	if (m_Image) {
		m_Image.Draw(dc, 0, 0);
	}
}

void CImageWindow::InitImage(void)
{
	CRect rect;
	this->GetClientRect(&rect);
	cout << "Image window size - width : " << rect.right << ", height : " << rect.bottom << endl;

	int nWidth = rect.right;
	int nHeight = rect.bottom;
	int nBPP = BIT_PER_PIXEL_8;

	m_Image.Create(nWidth, -nHeight, nBPP);

	int nColorNumber = 1 << nBPP;
	cout << "nColorNumber : " << nColorNumber << endl;

	if (BIT_PER_PIXEL_8 == nBPP) {
		RGBQUAD* rgb = new RGBQUAD[nColorNumber];
		for (int i = 0; i < nColorNumber; i++) {
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		}
		m_Image.SetColorTable(0, nColorNumber, rgb);

		unsigned char* fm = (unsigned char*)m_Image.GetBits();
		memset(fm, COLOR_BLACK, sizeof(unsigned char) * nWidth * nHeight);

		delete[] rgb;
	}
	//else if (BIT_PER_PIXEL_16 == nBPP) {
	//	unsigned short* fm = (unsigned short*)m_Image.GetBits();
	//	memset(fm, COLOR_WHITE, sizeof(unsigned short) * nWidth * nHeight);
	//}
	//else {}
}
