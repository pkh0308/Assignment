#pragma once
#include "afxdialogex.h"


// CImageDlg 대화 상자

class CImageDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CImageDlg)

public:
	CImageDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CImageDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CImageDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();

private:
	CWnd* m_pParent; // 부모 윈도우
	CImage m_image;

	void InitDlg(); // 초기화

// 원 그리기
private:
	// 이전에 그린 원을 기억하기 위한 변수
	int m_nBefX = 0;
	int m_nBefY = 0;
	int m_nBefRadius = 0;

	bool ValidPoint(int x, int y) const; // 유효한 좌표인지 검사
	int GetValidRadius(int x, int y) const; // 원을 그릴 수 있는 반지름인지 검사
	bool IsInCircle(int centerX, int centerY, int x, int y, int nRadius) const; // 원 안에 들어가는지 검사
	void DrawCircleWithRadius(int x, int y, int nRadius, int nColor);

	int Clamp(int nValue, int nMin, int nMax);
	void UpdateDisplay();
	void ResetImage();

	void MemoryData(int x, int y);
	void MemoryData(int x, int y, int nRadius);

	void SaveImage(int count);
	void DrawCenterMark(int x, int y, COLORREF crColor);
	void DrawCenterText(int x, int y, COLORREF crColor);

public:
	void DrawCircle(int x, int y, int nColor);
	void MoveCircle(int nBeginX, int nBeginY, int nDestX, int nDestY);

	void DrawFile(CString strFilePath);
};
