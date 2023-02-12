#pragma once
#include "afxdialogex.h"


// Setup 对话框

class Setup : public CDialogEx
{
	DECLARE_DYNAMIC(Setup)

public:
	Setup(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Setup();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_SETUP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
//	UINT m_nLineWidth;
	virtual BOOL OnInitDialog();
	afx_msg void OnNMCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult);
	int m_nLineWidth;
	int m_nLineStyle;
	COLORREF m_nColor;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnPaint();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
