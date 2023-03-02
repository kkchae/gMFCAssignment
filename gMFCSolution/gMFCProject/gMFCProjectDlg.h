﻿
// gMFCProjectDlg.h: 헤더 파일
//

#pragma once

#include "ImageWindow.h"
#include "ImageProcess.h"

// CgMFCProjectDlg 대화 상자
class CgMFCProjectDlg : public CDialogEx
{
private:
	CImageWindow* m_pImageWindow;
	CImageProcess* m_pImageProcess;

// 생성입니다.
public:
	CgMFCProjectDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	enum EDLG_STATUS {
		EDLG_STATUS_INIT = 0,
		EDLG_STATUS_PROCESS_USABLE,
		EDLG_STATUS_PROCESS_UNUSABLE,
	};

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GMFCPROJECT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	int m_nInputSize;
	afx_msg void OnBnClickedBtnMakePattern();
	afx_msg void OnBnClickedBtnProcess();
	afx_msg void OnUpdateEditInputSize();
	void UpdateDlgItems(EDLG_STATUS eStatus = EDLG_STATUS_INIT);
};
