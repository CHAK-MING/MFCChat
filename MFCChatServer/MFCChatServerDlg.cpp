
// MFCChatServerDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCChatServer.h"
#include "MFCChatServerDlg.h"
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


// CMFCChatServerDlg 对话框



CMFCChatServerDlg::CMFCChatServerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCHATSERVER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCChatServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HISTORYMSG_LIST, m_list);
	DDX_Control(pDX, IDC_COLOR_COMBO, m_wordColorCombo);
}

BEGIN_MESSAGE_MAP(CMFCChatServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START_BUTTON, &CMFCChatServerDlg::OnBnClickedStartButton)
	ON_BN_CLICKED(IDC_SENDMSG_BUTTON, &CMFCChatServerDlg::OnBnClickedSendmsgButton)
	ON_BN_CLICKED(IDC_CLEAR_BUTTON, &CMFCChatServerDlg::OnBnClickedClearButton)
	ON_BN_CLICKED(IDC_STOP_BUTTON, &CMFCChatServerDlg::OnBnClickedStopButton)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_CALCULATOR_BUTTON, &CMFCChatServerDlg::OnBnClickedCalculatorButton)
	ON_BN_CLICKED(IDC_EMAIL_BUTTON, &CMFCChatServerDlg::OnBnClickedEmailButton)
	ON_BN_CLICKED(IDC_QQ_BUTTON, &CMFCChatServerDlg::OnBnClickedQqButton)
END_MESSAGE_MAP()


// CMFCChatServerDlg 消息处理程序

BOOL CMFCChatServerDlg::OnInitDialog()
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
	GetDlgItem(IDC_PORT_EDIT)->SetWindowText(_T("5000"));

	GetDlgItem(IDC_SENDMSG_BUTTON)->EnableWindow(FALSE);
	GetDlgItem(IDC_STOP_BUTTON)->EnableWindow(FALSE);
	GetDlgItem(IDC_START_BUTTON)->EnableWindow(TRUE);

	m_wordColorCombo.AddString(_T("黑色"));
	m_wordColorCombo.AddString(_T("红色"));
	m_wordColorCombo.AddString(_T("蓝色"));
	m_wordColorCombo.AddString(_T("绿色"));

	m_wordColorCombo.SetCurSel(0);
	SetDlgItemText(IDC_COLOR_COMBO, _T("黑色"));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCChatServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCChatServerDlg::OnPaint()
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
 		// 确定绘制的目的区域
 		CRect rect;
 		GetClientRect(&rect);
 		TRACE("##width = %d height = %d", rect.Width(), rect.Height());
 
 		// 定义并创建一个内存设备环境
 		CDC dcBmp;
 		dcBmp.CreateCompatibleDC(&dc);
 
 		// 载入资源图片
		CImage img;
		CString strPath = _T("D:\\C++3.0\\MFC\\MFCChatClient\\background.png");
		img.Load(strPath);

		HBITMAP hbmp = img.Detach();
		CBitmap bmpBackGround;
		bmpBackGround.Attach(hbmp);
 
 		// 将图片载入到位图
 		BITMAP bBitmap;
 		bmpBackGround.GetBitmap(&bBitmap);
 
 		// 将位图选入临时的内存设备环境
 		CBitmap* pbmpOld = dcBmp.SelectObject(&bmpBackGround);
 
 		// 开始绘制
 		// 将位图从源矩形复制到目标矩形，必要时可拉伸或压缩位图已符合目标矩形的尺寸。
 		dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcBmp, 
 			0, 0, bBitmap.bmWidth, bBitmap.bmHeight, SRCCOPY);
 
		dcBmp.SelectObject(pbmpOld);

 		CDialogEx::OnPaint();

	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCChatServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CString CMFCChatServerDlg::CatShowString(CString strInfo, CString strMsg) // 连接显示字符串
{
	// 时间 + 昵称:  + 消息
	CString strTime;
	CTime tmNow;
	tmNow = CTime::GetCurrentTime();
	strTime = tmNow.Format("%X ");
	CString strShow;
	strShow = strTime + strInfo;
	strShow += strMsg;
	return strShow;
}

void CMFCChatServerDlg::OnBnClickedStartButton()
{
	// TODO: 在此添加控件通知处理程序代码
	TRACE("##OnBnClickedStartButton");
	CString strPort;
	// 从控件里面获取内容
	GetDlgItem(IDC_PORT_EDIT)->GetWindowText(strPort);

	// CString 转 char*
	USES_CONVERSION; 
	LPCSTR szPort = (LPCSTR)T2A(strPort);
	TRACE("##szPort = %s", szPort);

	int iPort = _ttoi(strPort);

	// 创建服务器Socket
	m_server = new CServerSocket;
	// 创建套接字
	if (!m_server->Create(iPort))
	{
		TRACE("##m_server Create errorCode %d", GetLastError());
		return;
	}

	if (!m_server->Listen())
	{
		TRACE("##m_server Listen errorCode %d", GetLastError());
		return;
	}

	GetDlgItem(IDC_SENDMSG_BUTTON)->EnableWindow(TRUE);
	GetDlgItem(IDC_STOP_BUTTON)->EnableWindow(TRUE);
	GetDlgItem(IDC_START_BUTTON)->EnableWindow(FALSE);

	CString strShow;
	strShow = CatShowString(_T(""), _T("服务器启动成功"));
	m_list.AddString(strShow);
	m_list.UpdateData(false);
}



void CMFCChatServerDlg::OnBnClickedSendmsgButton()
{
	// TODO: 在此添加控件通知处理程序代码
	// 第一步获取编辑框内容
	CString strTmpMsg;
	GetDlgItem(IDC_SENDMSG_EDIT)->GetWindowText(strTmpMsg);
	if (strTmpMsg.GetLength() == 0)
	{
		AfxMessageBox(_T("编辑框不能为空"), NULL, NULL);
		return;
	}
	USES_CONVERSION;
	char* szSendBuf = T2A(strTmpMsg);

	// 发送给客户端
	m_chat->Send(szSendBuf, MAX_SERVER_BUF, 0);

	// 显示到列表框
	CString strShow;
	CString strInfo = _T("服务端: ");
	strShow = CatShowString(strInfo, strTmpMsg);
	m_list.AddString(strShow);
	UpdateData(false);
	GetDlgItem(IDC_SENDMSG_EDIT)->SetWindowText(_T(""));
}



void CMFCChatServerDlg::OnBnClickedClearButton()
{
	// TODO: 在此添加控件通知处理程序代码
	m_list.ResetContent();
}


void CMFCChatServerDlg::OnBnClickedStopButton()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_SENDMSG_BUTTON)->EnableWindow(FALSE);
	GetDlgItem(IDC_STOP_BUTTON)->EnableWindow(FALSE);
	GetDlgItem(IDC_START_BUTTON)->EnableWindow(TRUE);

	// 回收资源
	m_server->Close();
	if (m_server)
	{
		delete m_server;
		m_server = NULL;
	}
	if (m_chat)
	{
		delete m_server;
		m_server = NULL;
	}

	// 显示到列表框
	m_list.AddString(CatShowString(_T(""), _T("服务器停止")));
	UpdateData(FALSE);
}


HBRUSH CMFCChatServerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	UINT id = pWnd->GetDlgCtrlID();
	CString strColor;
	m_wordColorCombo.GetWindowText(strColor);

	if (IDC_HISTORYMSG_LIST == id)
	{
		if (strColor == L"黑色")
			pDC->SetTextColor(RGB(0, 0, 0));
		else if (strColor == L"红色")
			pDC->SetTextColor(RGB(255, 0, 0));
		else if (strColor == L"绿色")
			pDC->SetTextColor(RGB(0, 255, 0));
		else if (strColor == L"蓝色")
			pDC->SetTextColor(RGB(0, 0, 255));
	}

	// 设置文本背景为透明
	if (id == IDC_STATIC)
	{
		pDC->SetTextColor(RGB(255, 255, 255));//设置文本框字体颜色
		pDC->SetBkMode(TRANSPARENT);//设透明
		return HBRUSH(GetStockObject(HOLLOW_BRUSH));//这句话不能掉
	}

	// 设置复选框和按钮背景为透明
	if (id == IDC_CLEAR_BUTTON || id == IDC_START_BUTTON || id == IDC_STOP_BUTTON || id == IDC_SENDMSG_BUTTON)
	{
		pDC->SetBkMode(TRANSPARENT);
		CRect rc;
		pWnd->GetWindowRect(&rc);
		ScreenToClient(&rc);
		CDC* dc = GetDC();
		pDC->BitBlt(0, 0, rc.Width(), rc.Height(), dc, rc.left, rc.top, SRCCOPY);  //<把父窗口背景图片先画到按钮上
		ReleaseDC(dc);
		hbr = (HBRUSH) ::GetStockObject(NULL_BRUSH);
	}


	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CMFCChatServerDlg::OnBnClickedCalculatorButton()
{
	// TODO: 在此添加控件通知处理程序代码
	// 执行Shell命令
	ShellExecute(NULL, L"open", L"calc.exe", NULL, NULL, SW_SHOWNORMAL);
}


void CMFCChatServerDlg::OnBnClickedEmailButton()
{
	// TODO: 在此添加控件通知处理程序代码
	ShellExecute(NULL, L"open", L"https://mail.qq.com", NULL, NULL, SW_SHOWNORMAL);
}


void CMFCChatServerDlg::OnBnClickedQqButton()
{
	// TODO: 在此添加控件通知处理程序代码
	ShellExecute(NULL, L"open", L"D:\\Program Files (x86)\\Tencent\\QQ\\Bin\\QQScLauncher.exe", NULL, NULL, SW_SHOWNORMAL);
	
}


BOOL CMFCChatServerDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		TRACE("##回车");
		return TRUE;
	}

	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_SPACE)
	{
		TRACE("##空格");
		return TRUE;
	}

	// 添加快捷键 ctrl + X 退出整个对话框
	if (pMsg->message == WM_KEYDOWN)
	{
		if (GetKeyState(VK_CONTROL) < 0) // ctrl是否按下
		{
			if (pMsg->wParam == 'X')
				CDialogEx::OnOK();
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
