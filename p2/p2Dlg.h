
// p2Dlg.h: 头文件
//

#pragma once

#define TIMER_PROG 9517


// Cp2Dlg 对话框
class Cp2Dlg : public CDialogEx
{
// 构造
public:
	Cp2Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_P2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnCheck();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CStatic m_pic;
	CImage m_image;
	CListCtrl m_list;
};
