// ImageProcess.cpp: 구현 파일
//

#include "pch.h"
#include "gMFCProject.h"
#include "ImageProcess.h"
#include <iostream>
using namespace std;

// CImageProcess

CImageProcess::CImageProcess()
{
}

CImageProcess::~CImageProcess()
{
}

BOOL CImageProcess::FindPattern(CImage* pImage, const int nThreshHold)
{
	BOOL bFound = FALSE;
	if (pImage != nullptr) {
		int nWidth = pImage->GetWidth();
		int nHeight = pImage->GetHeight();
		int nPitch = pImage->GetPitch();

		int nSumX = 0;
		int nSumY = 0;
		int nCount = 0;
		CRect rect(0, 0, nWidth, nHeight);
		unsigned char* fm = (unsigned char*)pImage->GetBits();

		for (int nCurY = rect.top; nCurY < rect.bottom; nCurY++) {
			for (int nCurX = rect.left; nCurX < rect.right; nCurX++) {
				if (fm[nCurY * nPitch + nCurX] > nThreshHold) {
					nSumX += nCurX;
					nSumY += nCurY;
					nCount++;
				}
			}
		}

		if (nCount > 0) {
			bFound = TRUE;
			int nCenterX = (int)(nSumX / nCount);
			int nCenterY = (int)(nSumY / nCount);

			cout << "Center point : " << nCenterX << ", " << nCenterY << endl;
		}
		else {
			bFound = FALSE;
		}
	}
	return bFound;
}

BOOL CImageProcess::FindPattern(CImage* pImage, const int nThreshHold, int* nRetCenterX, int* nRetCenterY)
{
	BOOL bFound = FALSE;
	if (pImage != nullptr) {
		int nWidth = pImage->GetWidth();
		int nHeight = pImage->GetHeight();
		int nPitch = pImage->GetPitch();

		int nSumX = 0;
		int nSumY = 0;
		int nCount = 0;
		CRect rect(0, 0, nWidth, nHeight);
		unsigned char* fm = (unsigned char*)pImage->GetBits();

		for (int nCurY = rect.top; nCurY < rect.bottom; nCurY++) {
			for (int nCurX = rect.left; nCurX < rect.right; nCurX++) {
				if (fm[nCurY * nPitch + nCurX] > nThreshHold) {
					nSumX += nCurX;
					nSumY += nCurY;
					nCount++;
				}
			}
		}

		if (nCount > 0) {
			bFound = TRUE;
			int nCenterX = (int)(nSumX / nCount);
			int nCenterY = (int)(nSumY / nCount);

			// 중심좌표
			if (nRetCenterX != nullptr && nRetCenterY != nullptr) {
				*nRetCenterX = nCenterX;
				*nRetCenterY = nCenterY;
			}
			cout << "Center point : " << nCenterX << ", " << nCenterY << endl;
		}
		else {
			bFound = FALSE;
		}
	}
	return bFound;
}
