﻿#pragma once
#include "afxdialogex.h"


// CImageWindow 대화 상자

class CImageWindow : public CDialogEx
{
	DECLARE_DYNAMIC(CImageWindow)

public:
	CImage m_Image;

	CImageWindow(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CImageWindow();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IMAGE_WINDOW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	void InitImage(void);
};
