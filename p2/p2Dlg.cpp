
// p2Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "p2.h"
#include "p2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cp2Dlg 对话框



Cp2Dlg::Cp2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_P2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cp2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC, m_pic);
	DDX_Control(pDX, IDC_LIST2, m_list);
}

BEGIN_MESSAGE_MAP(Cp2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_CHECK, &Cp2Dlg::OnBnClickedBtnCheck)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// Cp2Dlg 消息处理程序

BOOL Cp2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	// 添加到列表框
	CComboBox* list = (CComboBox*)GetDlgItem(IDC_COMBO1);
	list->AddString(_T("上海"));
	list->AddString(_T("北京"));
	list->AddString(_T("广州"));
	list->AddString(_T("深圳"));
	list->SetCurSel(0); // 默认选项为第一个

	CProgressCtrl* prog = (CProgressCtrl*)GetDlgItem(IDC_PROGRESS1);
	prog->SetRange(0, 100);

	// 定时器
	SetTimer(TIMER_PROG, 100, NULL);
	
	// 加载PNG图片
	m_image.Load(_T("D:\\百度云\\wallhaven-85gxdy_1920x1080 (1).png"));

	// 绘制表头
	m_list.InsertColumn(0, _T("ID"), LVCFMT_LEFT, 50);
	m_list.InsertColumn(1, _T("Name"), LVCFMT_LEFT, 100);
	m_list.InsertColumn(2, _T("Age"), LVCFMT_LEFT, 50);
	m_list.InsertColumn(3, _T("Address"), LVCFMT_LEFT, 400);

	// 插入第一行数据
	int nidx = m_list.InsertItem(0, _T("0001"));
	m_list.SetItemText(nidx, 1, _T("John"));
	m_list.SetItemText(nidx, 2, _T("25"));
	m_list.SetItemText(nidx, 3, _T("上海"));

	nidx = m_list.InsertItem(0, _T("0002"));
	m_list.SetItemText(nidx, 1, _T("Saly"));
	m_list.SetItemText(nidx, 2, _T("18"));
	m_list.SetItemText(nidx, 3, _T("广州"));


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Cp2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Cp2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this); // 用于绘制的设备上下文
		// 绘制区域
		CRect rect;
		m_pic.GetWindowRect(&rect);
		ScreenToClient(&rect);
		// 绘制图像
		m_image.Draw(dc, rect);
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Cp2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cp2Dlg::OnBnClickedBtnCheck()
{
	// TODO: 在此添加控件通知处理程序代码
	// MessageBox(_T("测试"));
	// 获取文本框的内容
	CString text;
	/*CEdit* edit = (CEdit*)GetDlgItem(IDC_EDIT1);
	edit->GetWindowText(text);
	edit->SetWindowText(_T(""));
	CListBox* list = (CListBox*)GetDlgItem(IDC_LIST1);
	if (text != _T(""))
		list->AddString(text);*/
	CComboBox* list = (CComboBox*)GetDlgItem(IDC_COMBO1);
	int n = list->GetCurSel();
	list->GetLBText(n,text);
	MessageBox(text);
}



void Cp2Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int num = 0 , low , high;
	CProgressCtrl* prog;
	switch (nIDEvent)
	{
	case TIMER_PROG:
		prog = (CProgressCtrl*)GetDlgItem(IDC_PROGRESS1);
		num = prog->GetPos();
		prog->SetPos(++num);
		prog->GetRange(low, high);
		if (num >= high)
		{
			// 进度条归零
			prog->SetPos(low);
		}
		break;
	default:
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}
