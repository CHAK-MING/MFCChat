
// MFCChatClientDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCChatClient.h"
#include "MFCChatClientDlg.h"
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


// CMFCChatClientDlg 对话框



CMFCChatClientDlg::CMFCChatClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCHATCLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCChatClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HISTORYMSG_LIST, m_list);
	DDX_Control(pDX, IDC_SENDMSG_EDIT, m_input);
	DDX_Control(pDX, IDC_COLOR_COMBO, m_wordColorCombo);
}

BEGIN_MESSAGE_MAP(CMFCChatClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT_BUTTON, &CMFCChatClientDlg::OnBnClickedConnectButton)
	ON_BN_CLICKED(IDC_DISCONNECT_BUTTON, &CMFCChatClientDlg::OnBnClickedDisconnectButton)
	ON_BN_CLICKED(IDC_SENDMSG_BUTTON, &CMFCChatClientDlg::OnBnClickedSendmsgButton)
	ON_BN_CLICKED(IDC_SAVENAME_BUTTON, &CMFCChatClientDlg::OnBnClickedSavenameButton)
	ON_BN_CLICKED(IDC_CLEAR_BUTTON, &CMFCChatClientDlg::OnBnClickedClearButton)
	ON_BN_CLICKED(IDC_AUTOSENDMSG_CHECK, &CMFCChatClientDlg::OnBnClickedAutosendmsgCheck)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()
// mark


// CMFCChatClientDlg 消息处理程序

BOOL CMFCChatClientDlg::OnInitDialog()
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
	GetDlgItem(IDC_IPADDRESS)->SetWindowText(_T("127.0.0.1"));

	// 从配置文件获取昵称
	WCHAR wszName[MAX_PATH] = { 0 };
	WCHAR strPath[MAX_PATH] = { 0 };
	GetCurrentDirectoryW(MAX_PATH, strPath);
	CString strFilePath;
	strFilePath.Format(L"%ls//Test.ini", strPath);
	
	DWORD dwNum = GetPrivateProfileStringW(_T("CLIENT"), _T("NAME"), NULL,
		wszName, MAX_PATH, strFilePath); // ctrl+ end/home 可以到顶端或低端
	if (dwNum > 0)
	{
		SetDlgItemText(IDC_NAME_EDIT, wszName);
		UpdateData(FALSE);
	}
	else
	{
		WritePrivateProfileStringW(_T("CLIENT"), _T("NAME"), L"客户端", strFilePath);
		SetDlgItemText(IDC_NAME_EDIT, L"客户端");
		UpdateData(FALSE);
	}

	// 初始化控件
	GetDlgItem(IDC_SENDMSG_BUTTON)->EnableWindow(FALSE);
	GetDlgItem(IDC_DISCONNECT_BUTTON)->EnableWindow(FALSE);
	GetDlgItem(IDC_CONNECT_BUTTON)->EnableWindow(TRUE);
	GetDlgItem(IDC_AUTOSENDMSG_CHECK)->EnableWindow(FALSE);

	m_wordColorCombo.AddString(_T("黑色"));
	m_wordColorCombo.AddString(_T("红色"));
	m_wordColorCombo.AddString(_T("蓝色"));
	m_wordColorCombo.AddString(_T("绿色"));

	m_wordColorCombo.SetCurSel(0);
	SetDlgItemText(IDC_COLOR_COMBO, _T("黑色"));
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCChatClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCChatClientDlg::OnPaint()
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
HCURSOR CMFCChatClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCChatClientDlg::OnBnClickedConnectButton()
{
	// TODO: 在此添加控件通知处理程序代码
	TRACE("##OnBnClickedConnectButton");
	// 获取IP和端口
	CString strPort, strIP;
	// 从控件里面获取内容
	GetDlgItem(IDC_PORT_EDIT)->GetWindowText(strPort);
	GetDlgItem(IDC_IPADDRESS)->GetWindowText(strIP);

	// CString 转 char*
	USES_CONVERSION;
	LPCSTR szPort = (LPCSTR)T2A(strPort);
	LPCSTR szIP = (LPCSTR)T2A(strIP);
	TRACE("##szPort = %s szIP = %s", szPort, szIP);

	// 把字符串转换为int类型
	int iPort = _ttoi(strPort);

	// 创建SOCKET
	m_client = new CMySocket;
	if (!m_client->Create())
	{
		TRACE("##m_client Create errorCode %d", GetLastError());
		return;
	}

	// 连接
	m_client->Connect(strIP, iPort);
	
	GetDlgItem(IDC_SENDMSG_BUTTON)->EnableWindow(TRUE);
	GetDlgItem(IDC_DISCONNECT_BUTTON)->EnableWindow(TRUE);
	GetDlgItem(IDC_CONNECT_BUTTON)->EnableWindow(FALSE);
	GetDlgItem(IDC_AUTOSENDMSG_CHECK)->EnableWindow(TRUE);
}
// mark


void CMFCChatClientDlg::OnBnClickedDisconnectButton()
{
	// 控制控件
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_SENDMSG_BUTTON)->EnableWindow(FALSE);
	GetDlgItem(IDC_DISCONNECT_BUTTON)->EnableWindow(FALSE);
	GetDlgItem(IDC_CONNECT_BUTTON)->EnableWindow(TRUE);
	GetDlgItem(IDC_AUTOSENDMSG_CHECK)->EnableWindow(FALSE);

	// 回收资源
	m_client->Close();
	if (m_client)
	{
		delete m_client;
		m_client = nullptr;
	}

	// 显示到列表框
	m_list.AddString(CatShowString(_T(""), _T("与服务器断开连接")));
	UpdateData(FALSE);
}


CString CMFCChatClientDlg::CatShowString(CString strInfo, CString strMsg) // 连接显示字符串
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

void CMFCChatClientDlg::OnBnClickedSendmsgButton()
{
	// TODO: 在此添加控件通知处理程序代码
	// 第一步获取编辑框内容
	CString strTmpMsg;
	CString strInfo;
	GetDlgItemText(IDC_NAME_EDIT, strInfo);
	strInfo += ": ";
	GetDlgItem(IDC_SENDMSG_EDIT)->GetWindowText(strTmpMsg);
	strTmpMsg = strInfo + strTmpMsg;
	USES_CONVERSION;
	char* szSendBuf = T2A(strTmpMsg);

	// 发送给服务端
	m_client->Send(szSendBuf, SEND_MAX_BUF, 0);

	// 显示到列表框
	CString strShow;
	strShow = CatShowString(_T(""), strTmpMsg);
	m_list.AddString(strShow);
	UpdateData(false);
	GetDlgItem(IDC_SENDMSG_EDIT)->SetWindowText(_T(""));
}


void CMFCChatClientDlg::OnBnClickedSavenameButton()
{
	// TODO: 在此添加控件通知处理程序代码
	// 保存昵称
// 	WritePrivateProfileStringW(
// 		_In_opt_ LPCWSTR lpAppName, // 项
// 		_In_opt_ LPCWSTR lpKeyName, // 键
// 		_In_opt_ LPCWSTR lpString,
// 		_In_opt_ LPCWSTR lpFileName
// 	);
	CString strName;
	GetDlgItemText(IDC_NAME_EDIT, strName); // 获取文本框的内容
	if (strName.GetLength() <= 0)
	{
		AfxMessageBox(_T("昵称不能为空"),NULL,NULL); // 弹出警告框
		return;
	}
	if (IDOK == AfxMessageBox(_T("真的要修改昵称吗?"), MB_OKCANCEL))
	{
		WCHAR strPath[MAX_PATH] = { 0 };
		// 获取当前路径
		GetCurrentDirectoryW(MAX_PATH, strPath);
		TRACE("##strPath = %ls", strPath);
		CString strFilePath;
		strFilePath.Format(L"%ls//Test.ini", strPath);

		WritePrivateProfileStringW(_T("CLIENT"), _T("NAME"), strName, strFilePath);
		TRACE("##strName = %ls", strName);
		MessageBox(_T("修改成功!"));
	}
}





void CMFCChatClientDlg::OnBnClickedClearButton()
{
	// TODO: 在此添加控件通知处理程序代码
	m_list.ResetContent();
}


void CMFCChatClientDlg::OnBnClickedAutosendmsgCheck()
{
	// TODO: 在此添加控件通知处理程序代码
		// TODO: 在此添加控件通知处理程序代码
	if (((CButton*)GetDlgItem(IDC_AUTOSENDMSG_CHECK))->GetCheck())
	{
		((CButton*)GetDlgItem(IDC_AUTOSENDMSG_CHECK))->SetCheck(FALSE);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_AUTOSENDMSG_CHECK))->SetCheck(TRUE);
	}
}


HBRUSH CMFCChatClientDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
		else if(strColor == L"红色")
			pDC->SetTextColor(RGB(255, 0, 0));
		else if(strColor == L"绿色")
			pDC->SetTextColor(RGB(0, 255, 0));
		else if(strColor == L"蓝色")
			pDC->SetTextColor(RGB(0, 0, 255));
	}

	// 设置文本底色透明
	if (id == IDC_STATIC)
	{
		pDC->SetTextColor(RGB(255, 255, 255));//设置文本框字体颜色
		pDC->SetBkMode(TRANSPARENT);//设透明
		return HBRUSH(GetStockObject(HOLLOW_BRUSH));//这句话不能掉
	}

	// 设置复选框和按钮背景为透明
	if (id == IDC_AUTOSENDMSG_CHECK || id == IDC_CLEAR_BUTTON || id == IDC_CONNECT_BUTTON || id == IDC_DISCONNECT_BUTTON || id == IDC_SENDMSG_BUTTON || id == IDC_SAVENAME_BUTTON)
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


BOOL CMFCChatClientDlg::PreTranslateMessage(MSG* pMsg)
{
	// 规避回车键
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
