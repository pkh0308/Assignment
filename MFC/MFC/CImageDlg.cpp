// CImageDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MFC.h"
#include "afxdialogex.h"
#include "CImageDlg.h"
#include <iostream>
#include "CustomDefine.h"
#include <algorithm>

#include "CProcess.h"

// CImageDlg 대화 상자

IMPLEMENT_DYNAMIC(CImageDlg, CDialogEx)

CImageDlg::CImageDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_IMGDLG, pParent)
{
	m_pParent = pParent;
}

CImageDlg::~CImageDlg()
{
}

void CImageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CImageDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CImageDlg 메시지 처리기


BOOL CImageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitDlg();
	MoveWindow(0, 0, 640, 480);

	return TRUE; 
}


void CImageDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	if(m_image)
	{
		m_image.Draw(dc, 0, 0);
	}
}

#pragma region 초기화
void CImageDlg::InitDlg()
{
	int nWidth = IMG_WIDTH;
	int nHeight = IMG_HEIGHT;
	int nBPP = 8;

	m_image.Create(nWidth, -nHeight, nBPP);
	if (nBPP == 8)
	{
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; ++i)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		m_image.SetColorTable(0, 256, rgb);
	}

	unsigned char* fm = static_cast<unsigned char*>(m_image.GetBits());
	memset(fm, COLOR_WHITE, nWidth * nHeight * sizeof(unsigned char));
}
#pragma endregion

#pragma region 유효성 검사
bool CImageDlg::ValidPoint(int x, int y) const
{
	CRect rect(0, 0, m_image.GetWidth(), m_image.GetHeight());
	return rect.PtInRect(CPoint(x, y));
}

int CImageDlg::GetValidRadius(int x, int y) const
{
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();

	int nMinX = min(MAX_RADIUS, min(x, nWidth - x));
	int nMinY = min(MAX_RADIUS, min(y, nHeight - y));
	// 최소값 1로 보정
	int nLimit = min(nMinX, nMinY) - 1;
	return rand() % nLimit + 1; 
}

bool CImageDlg::IsInCircle(int centerX, int centerY, int x, int y, int nRadius) const
{
	double dX = centerX - x;
	double dY = centerY - y;
	double dDist = dX * dX + dY * dY;
	double dRad = nRadius * nRadius;

	return dDist <= dRad;
}
#pragma endregion

#pragma region 원 그리기 & 이동
void CImageDlg::DrawCircle(int x, int y, int nColor)
{
	int nRadius = GetValidRadius(x, y);
	std::cout << "반지름 길이: " << nRadius << "\n";

	ResetImage(); // 이전에 그린 내용  초기화
	DrawCircleWithRadius(x, y, nRadius, nColor);
	UpdateDisplay();

	// 다음번 초기화를 위해 현재 값 저장
	MemoryData(x, y, nRadius);
}

void CImageDlg::DrawCircleWithRadius(int x, int y, int nRadius, int nColor)
{
	if (nullptr == m_image)
	{
		std::cout << "[CImageDlg::DrawCircleWithRadius] m_image가 널포인터입니다. \n";
		return;
	}

	int nPitch = m_image.GetPitch();
	unsigned char* fm = static_cast<unsigned char*>(m_image.GetBits());
	CRect rect(x - nRadius, y - nRadius, x + nRadius, y + nRadius);
	for (int j = rect.top; j < rect.bottom; ++j)
	{
		for (int i = rect.left; i < rect.right; ++i)
		{
			if (ValidPoint(i, j) && IsInCircle(x, y, i, j, nRadius))
				fm[j * nPitch + i] = nColor;
		}
	}
}

void CImageDlg::MoveCircle(int nBeginX, int nBeginY, int nDestX, int nDestY)
{
	std::cout << "[시작 좌표] \t x:" << nBeginX << "\t y: " << nBeginY << "\n";
	std::cout << "[타겟 좌표] \t x:" << nDestX << "\t y: " << nDestY << "\n";
	int nDiffX = nDestX - nBeginX;
	int nDiffY = nDestY - nBeginY;
	int nDeltaX = nDiffX > 0 ? Clamp(nDiffX / CIRCLE_MOVE_COUNT, 1, nDiffX) : Clamp(nDiffX / CIRCLE_MOVE_COUNT, nDiffX, -1);
	int nDeltaY = nDiffY > 0 ? Clamp(nDiffY / CIRCLE_MOVE_COUNT, 1, nDiffY) : Clamp(nDiffY / CIRCLE_MOVE_COUNT, nDiffY, -1);

	std::cout << "[Delta 값] \t x:" << nDeltaX << "\t y: " << nDeltaY << "\n";

	// 시작 좌표로 그리기
	if (m_nBefRadius == 0)
		m_nBefRadius = GetValidRadius(nBeginX, nBeginY);
	ResetImage();
	DrawCircleWithRadius(nBeginX, nBeginY, m_nBefRadius, COLOR_GRAY);
	MemoryData(nBeginX, nBeginY);
	UpdateDisplay();

	// 목표 지점에 도착할 때까지 반복
	int nCount = 0;
	CPoint ptMin(min(nBeginX, nDestX), min(nBeginY, nDestY));
	CPoint ptMax(max(nBeginX, nDestX), max(nBeginY, nDestY));
	while(m_nBefX != nDestX || m_nBefY != nDestY)
	{
		// 이전에 그린 원 지우기
		DrawCircleWithRadius(m_nBefX, m_nBefY, m_nBefRadius, COLOR_WHITE);
		// 다음 위치에 원 그리기
		int nNextX = Clamp(m_nBefX + nDeltaX, ptMin.x, ptMax.x);
		int nNextY = Clamp(m_nBefY + nDeltaY, ptMin.y, ptMax.y);
		MemoryData(nNextX, nNextY);
		DrawCircleWithRadius(nNextX, nNextY, m_nBefRadius, COLOR_GRAY);

		std::cout << "x: " << m_nBefX << ", y: " << m_nBefY << "\n";
		UpdateDisplay();
		SaveImage(nCount++);
		Sleep(CIRCLE_MOVE_DELTASLEEP);
	}
}

void CImageDlg::DrawFile(CString strFilePath)
{
	// 파일 그리기
	m_image.Destroy();
	m_image.Load(strFilePath);
	UpdateDisplay();

	// 중심 좌표 구하기
	CProcess process;
	CPoint ptCenter = process.GetCenter(&m_image);
	std::cout << "[중심 좌표] x:" << ptCenter.x << ", \ty:" << ptCenter.y << "\n";
	DrawCenterMark(ptCenter.x, ptCenter.y, RGB(0, 0xff, 0));
	DrawCenterText(ptCenter.x, ptCenter.y, RGB(0xff, 0, 0));
}

void CImageDlg::DrawCenterMark(int x, int y, COLORREF crColor)
{
	CClientDC dc(this);
	CPen pen;
	pen.CreatePen(PS_SOLID, 2, RGB(0, 0xff, 0));
	CPen* pOldPen = dc.SelectObject(&pen);

	// 좌상 -> 우하
	dc.MoveTo(x - SIZE_CENTER_MARK, y - SIZE_CENTER_MARK);
	dc.LineTo(x + SIZE_CENTER_MARK, y + SIZE_CENTER_MARK);
	// 우상 -> 좌하
	dc.MoveTo(x + SIZE_CENTER_MARK, y - SIZE_CENTER_MARK);
	dc.LineTo(x - SIZE_CENTER_MARK, y + SIZE_CENTER_MARK);

	// 펜 복원
	dc.SelectObject(pOldPen);
}

void CImageDlg::DrawCenterText(int x, int y, COLORREF crColor)
{
	// 좌표 표시
	CClientDC dc(this);
	dc.SetTextColor(crColor);

	CRect rect(x + 50, y, x + 200, y + 30);
	UINT nFormat = DT_CENTER | DT_WORDBREAK;

	CString strCenter;
	strCenter.Format(_T("[center] x: %d, y: %d"), x, y);

	dc.DrawText(strCenter, rect, nFormat);
}
#pragma endregion

#pragma region 기타 유틸 함수들
int CImageDlg::Clamp(int nValue, int nMin, int nMax)
{
	if (nValue < nMin) return nMin;
	if (nValue > nMax) return nMax;
	return nValue;
}

void CImageDlg::UpdateDisplay()
{
	CClientDC dc(this);
	m_image.Draw(dc, 0, 0);
}

void CImageDlg::ResetImage()
{
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();

	int nBPP = m_image.GetBPP();
	int nRealBPP = nBPP / 8;

	unsigned char* fm = static_cast<unsigned char*>(m_image.GetBits());
	// 각 행을 순회하며 초기화
	for (int j = 0; j < nHeight; ++j) {
		unsigned char* row = fm + (j * nPitch);
		memset(row, COLOR_WHITE, nWidth * nRealBPP);
	}
}

void CImageDlg::MemoryData(int x, int y)
{
	m_nBefX = x;
	m_nBefY = y;
}

void CImageDlg::MemoryData(int x, int y, int nRadius)
{
	m_nBefX = x;
	m_nBefY = y;
	m_nBefRadius = nRadius;
}

void CImageDlg::SaveImage(int count)
{
	// 실행 파일 경로 가져오기
	TCHAR path[_MAX_PATH];
	GetModuleFileName(NULL, path, _MAX_PATH);
	// 실행 파일의 폴더 경로 자르기
	CString strFolderPath(path);
	strFolderPath = strFolderPath.Left(strFolderPath.ReverseFind('\\'));
	// 저장할 상대 경로
	CString strFilePath;
	strFilePath.Format(_T("\\image\\image_%d.bmp"), count);
	// 조합하여 최종 경로로 사용
	m_image.Save(strFolderPath + strFilePath);
}
#pragma endregion
