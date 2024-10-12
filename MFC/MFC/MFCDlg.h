
// MFCDlg.h: 헤더 파일
//

#pragma once


// CMFCDlg 대화 상자
class CMFCDlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_DIALOG };
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
	afx_msg void OnBnClickedBtnDraw();
	afx_msg void OnBnClickedBtnAction();
	afx_msg void OnBnClickedBtnOpen();

// 초기화
private:
	void InitDlg();

// 이미지 출력용 다이얼로그
private:
	class CImageDlg* m_pImgDlg;

public:
	afx_msg void OnDestroy();

// 시작 좌표(x1, y1)
// 종료 좌표(x2, y2)
private:
	int m_nX1 = 0;
	int m_nY1 = 0;
	int m_nX2 = 0;
	int m_nY2 = 0;

	bool ValidatePoint(int x, int y);
};
