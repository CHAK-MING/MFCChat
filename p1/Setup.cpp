// Setup.cpp: 实现文件
//

#include "pch.h"
#include "p1.h"
#include "afxdialogex.h"
#include "Setup.h"


// Setup 对话框

IMPLEMENT_DYNAMIC(Setup, CDialogEx)

Setup::Setup(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_SETUP, pParent)
	, m_nLineWidth(0)
	, m_nLineStyle(0)
{

}

Setup::~Setup()
{
}

void Setup::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Slider(pDX, IDC_SLIDER1, m_nLineWidth);
	DDX_Radio(pDX, IDC_RADIO1, m_nLineStyle);
}


BEGIN_MESSAGE_MAP(Setup, CDialogEx)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &Setup::OnNMCustomdrawSlider1)
	ON_BN_CLICKED(IDC_BUTTON1, &Setup::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_RADIO1, &Setup::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &Setup::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &Setup::OnBnClickedRadio3)
	ON_WM_PAINT()
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// Setup 消息处理程序


// 初始化对话框
BOOL Setup::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	// 获得滑块控件
	CSliderCtrl* slide = (CSliderCtrl*)GetDlgItem(IDC_SLIDER1);
	// 修改属性
	slide->SetRange(1, 30);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void Setup::OnNMCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}




void Setup::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	// 打开颜色对话框
	CColorDialog colDig;
	// colDig.m_cc.Flags = CC_RGBINIT; // bug
	colDig.m_cc.rgbResult = m_nColor;
	if (IDOK == colDig.DoModal())
	{
		m_nColor = colDig.m_cc.rgbResult;
		Invalidate();
	}
}


void Setup::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	// 使窗口无效
	Invalidate();
}


void Setup::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	Invalidate();
}


void Setup::OnBnClickedRadio3()
{
	// TODO: 在此添加控件通知处理程序代码
	Invalidate();
}


void Setup::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	// 
	// 同步控件和绑定的成员变量
	UpdateData();

	// 在示例区域绘线
	CPen pen(m_nLineStyle, m_nLineWidth, m_nColor);
	CPen* pOldPen = dc.SelectObject(&pen);
	
	// 获得对应ID控件的坐标
	CRect rect;
	GetDlgItem(IDC_SAMPLE)->GetWindowRect(&rect);
	ScreenToClient(rect);
	dc.MoveTo(rect.left + 25, rect.top + rect.Height() / 2);
	dc.LineTo(rect.right - 25, rect.top + rect.Height() / 2);
	dc.SelectObject(&pOldPen);
}


void Setup::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	// 响应滑块控件的水平移动消息
	Invalidate();
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}
