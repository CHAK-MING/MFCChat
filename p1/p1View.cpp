
// p1View.cpp: Cp1View 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "p1.h"
#endif

#include "p1Doc.h"
#include "p1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "Setup.h"


// Cp1View

IMPLEMENT_DYNCREATE(Cp1View, CView)

BEGIN_MESSAGE_MAP(Cp1View, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_COMMAND(ID_DRAW_LINE, &Cp1View::OnDrawLine)
	ON_COMMAND(ID_DRAW_RECT, &Cp1View::OnDrawRect)
	ON_COMMAND(ID_DRAW_ELLIPSE, &Cp1View::OnDrawEllipse)
	ON_COMMAND(ID_DRAW_PEN, &Cp1View::OnDrawPen)
	ON_WM_CREATE()
	ON_UPDATE_COMMAND_UI(ID_DRAW_ELLIPSE, &Cp1View::OnUpdateDrawEllipse)
	ON_UPDATE_COMMAND_UI(ID_DRAW_LINE, &Cp1View::OnUpdateDrawLine)
	ON_UPDATE_COMMAND_UI(ID_DRAW_PEN, &Cp1View::OnUpdateDrawPen)
	ON_UPDATE_COMMAND_UI(ID_DRAW_RECT, &Cp1View::OnUpdateDrawRect)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_FILE_SETUP, &Cp1View::OnFileSetup)
	ON_COMMAND(ID_FILE_READ, &Cp1View::OnFileRead)
	ON_COMMAND(ID_FILE_WRITE, &Cp1View::OnFileWrite)
END_MESSAGE_MAP()

// Cp1View 构造/析构

Cp1View::Cp1View() noexcept
{
	// TODO: 在此处添加构造代码
	m_pOrigin = 0;
	m_bDraw = false;
	m_nWidth = 0;
	m_DrawType = DT_LINE;
	m_nLineWidth = 0;
	m_nLineStyle = 0;
	m_tmpGraph = nullptr;
	m_nColor = RGB(0, 0, 0);
	// 基于内存的元文件
	// m_dcMetaFile.Create();
}

Cp1View::~Cp1View()
{
	int cnt = m_pGraphs.GetSize();
	while (cnt--)
	{
		delete m_pGraphs.GetAt(cnt);
	}
	m_pGraphs.RemoveAll();
}

BOOL Cp1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	m_Menu.LoadMenu(IDR_MENU1);
	return CView::PreCreateWindow(cs);
}

// Cp1View 绘图

void Cp1View::OnDraw(CDC* pDC)
{
	Cp1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	
	//HMETAFILE metaFile;
	//// 结束录制，保存文件
	//metaFile = m_dcMetaFile.Close();
	//// 重放元文件
	//pDC->PlayMetaFile(metaFile);
	//// 开始新的录制
	//m_dcMetaFile.Create();
	//// 在新的录制中重放旧的元文件
	//m_dcMetaFile.PlayMetaFile(metaFile);
	//// 删除元文件
	//DeleteMetaFile(metaFile);

	// 把兼容设备的数据拷贝到真实设备，完成显示工作
	/*CRect rect;
	GetClientRect(&rect);
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &m_dcCompatible, 0, 0, SRCCOPY);*/

	// 根据m_pGraphs数组的绘制信息，完成重绘操作
	int cnt = m_pGraphs.GetSize();
	for (int i = 0; i < cnt; ++i)
	{
		Graph* gh = (Graph*)m_pGraphs.GetAt(i);
		if (gh->m_nDrawType == DT_PEN)
			m_bDraw = false;
		gh->Draw(pDC);
	}

}

void Cp1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void Cp1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{

}


// Cp1View 诊断

#ifdef _DEBUG
void Cp1View::AssertValid() const
{
	CView::AssertValid();
}

void Cp1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cp1Doc* Cp1View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cp1Doc)));
	return (Cp1Doc*)m_pDocument;
}
#endif //_DEBUG


// Cp1View 消息处理程序

// 左键鼠标松开
void Cp1View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	// 画线
	// 获得设备上下文
	//CDC* pDC = GetDC();
	//// 定制画笔
	//CPen pen(PS_SOLID, 5, RGB(0, 255, 0));
	//CPen* pOldPen = pDC->SelectObject(&pen);
	//// 画笔移动到起点
	//pDC->MoveTo(m_pOrigin);
	//// 从起点到终点花一条线
	//pDC->LineTo(point);
	//// 设备上下文恢复原画笔
	//pDC->SelectObject(pOldPen);
	//// 释放设备上下文
	//ReleaseDC(pDC);

	//CClientDC dc(this); // 不需要释放
	//// dc.Rectangle(CRect(m_pOrigin, point)); // 左上角和右下角的坐标
	//CBrush* brush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH)); // 透明画笔
	//CBrush* oldBrush = dc.SelectObject(brush);
	//dc.Rectangle(CRect(m_pOrigin, point));
	//dc.SelectObject(oldBrush);
	//CClientDC dc(this); // 不需要释放
	//// CBrush brush(RGB(255, 0, 0));
	//// Bitmap对象，是一种图片格式
	//CBitmap bitmap;
	//bitmap.LoadBitmap(IDB_BITMAP1); // 图片ID
	//CBrush brush(&bitmap); // 以bitmap作为参数当作画刷
	//dc.FillRect(CRect(m_pOrigin, point), &brush);

	// CPen pen(PS_DASH, 1, RGB(0, 0, 255));
	//CPen* oldPen = dc.SelectObject(&pen);

	//// 画椭圆
	//// dc.Ellipse(CRect(m_pOrigin, point));
	//
	//// 画圆
	//long len = point.x - m_pOrigin.x;
	//dc.Ellipse(m_pOrigin.x, m_pOrigin.y, m_pOrigin.x + len, m_pOrigin.y + len);

	//CClientDC dc(this);
	//
	//CString str(_T("你好我好大家好！"));
	//CFont font;
	//font.CreatePointFont(200, _T("华文行楷"));
	//CFont* oldFont = dc.SelectObject(&font);

	//dc.SetTextColor(RGB(125, 0, 127));
	//

	//// 输出字符串
	//// dc.TextOut(point.x, point.y, str, str.GetLength());
	//
	//// 获取文字在屏幕上的空间大小，长度和宽度
	//CSize cz = dc.GetTextExtent(str);
	//
	//// 在指定的区域内画文字
	//dc.DrawText(str, CRect(point.x, point.y, point.x + cz.cx, point.y + cz.cy), DT_LEFT);

	//dc.SelectObject(&oldFont);

	CClientDC dc(this);
	CPen pen(m_nLineStyle, m_nLineWidth, m_nColor);
	CPen* pOldPen = dc.SelectObject(&pen);
	
	switch (m_DrawType)
	{
	case DT_LINE:
		dc.MoveTo(m_pOrigin);
		dc.LineTo(point);
		break;
	case DT_RECT:
		dc.Rectangle(CRect(m_pOrigin, point));
		break;
	case DT_ELLIPSE:
		dc.Ellipse(CRect(m_pOrigin, point));
		break;
	case DT_PEN:
		m_bDraw = false;
		break;
	default:
		break;
	}

	if (m_DrawType != DT_PEN)
	{
		// TODO: 释放内存
		Graph* gh = new Graph(m_DrawType, m_nLineStyle, m_nLineWidth, m_nColor);
		gh->AddPoint(m_pOrigin, point);
		m_pGraphs.Add(gh);
	}
	else
	{
		// 添加画笔的最后一点
		m_tmpGraph->AddPoint(point);
		m_pGraphs.Add(m_tmpGraph);
	}
	
	dc.SelectObject(pOldPen);

	// Invalidate();

	CView::OnLButtonUp(nFlags, point);
}

// 左键鼠标按下
void Cp1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	// MessageBox(_T("鼠标左键按下"));
	m_pOrigin = point;
	if (m_DrawType == DT_PEN)
	{
		m_bDraw = true;
		m_tmpGraph = new Graph(m_DrawType, m_nLineStyle, m_nLineWidth, m_nColor);
		m_tmpGraph->AddPoint(point);
	}
	CClientDC dc(this);
	// 初始化兼容设备上下文
	//if (!m_dcCompatible.m_hDC)
	//{
	//	// 创建兼容DC
	//	m_dcCompatible.CreateCompatibleDC(&dc);
	//	CRect rect;
	//	// 获取客户区大小
	//	GetClientRect(&rect);
	//	CBitmap bitmap;
	//	bitmap.CreateCompatibleBitmap(&dc,rect.Width(),rect.Height());
	//	m_dcCompatible.SelectObject(&bitmap);
	//	m_dcCompatible.FillSolidRect(rect, RGB(255, 255, 255)); // 给矩形填充颜色
	//}
	CView::OnLButtonDown(nFlags, point);
}


void Cp1View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	/*CClientDC dc(this);
	CPen pen(PS_SOLID, 3, RGB(0, 255, 255));
	CPen* oldPen = dc.SelectObject(&pen);
	if (m_bDraw)
	{
		dc.MoveTo(m_pOrigin);
		dc.LineTo(point);
	}
	dc.SelectObject(&oldPen);*/
	if (m_bDraw && m_DrawType == DT_PEN)
	{
		CClientDC dc(this);
		CPen pen(m_nLineStyle, m_nLineWidth, m_nColor);
		CPen* pOldPen = dc.SelectObject(&pen);
		dc.MoveTo(m_pOrigin);
		dc.LineTo(point);
		m_pOrigin = point;
		m_tmpGraph->AddPoint(point);
		dc.SelectObject(pOldPen);
		// Invalidate();
	}

	CView::OnMouseMove(nFlags, point);
}

//
//int Cp1View::OnCreate(LPCREATESTRUCT lpCreateStruct)
//{
//	if (CView::OnCreate(lpCreateStruct) == -1)
//		return -1;
//
//	// TODO:  在此添加您专用的创建代码
//	// 添加定时器
//	SetTimer(TIMER_TEXT, 200, NULL);
//
//	return 0;
//}

//
//void Cp1View::OnTimer(UINT_PTR nIDEvent)
//{
//	
//	CClientDC dc(this);
//	CString str(_T("你好我好大家好！"));
//	CFont font;
//	font.CreatePointFont(200, _T("华文行楷"));
//	CFont* oldFont = dc.SelectObject(&font);
//	dc.SetTextColor(RGB(125, 0, 127));
//	// 获取文字在屏幕上的空间大小，长度和宽度
//	CSize cz = dc.GetTextExtent(str);
//	CRect rect;
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//	switch (nIDEvent)
//	{
//	case TIMER_TEXT:
//		m_nWidth += 15;
//		rect.left = 200;
//		rect.top = 100;
//		rect.bottom = rect.top + cz.cy;
//		rect.right = rect.left + m_nWidth;
//		// 在指定的区域内画文字
//		dc.DrawText(str, rect, DT_LEFT);
//
//		if (m_nWidth > cz.cx)
//		{
//			m_nWidth = 0;
//			// 擦除屏幕的内容
//			Invalidate();
//		}
//
//		break;
//	default:
//		break;
//	}
//	dc.SelectObject(&oldFont);
//	CView::OnTimer(nIDEvent);
//}


void Cp1View::OnDrawLine()
{
	// TODO: 在此添加命令处理程序代码
	m_DrawType = DT_LINE;
}


void Cp1View::OnDrawRect()
{
	// TODO: 在此添加命令处理程序代码
	m_DrawType = DT_RECT;
}


void Cp1View::OnDrawEllipse()
{
	// TODO: 在此添加命令处理程序代码
	m_DrawType = DT_ELLIPSE;
}


void Cp1View::OnDrawPen()
{
	// TODO: 在此添加命令处理程序代码
	m_DrawType = DT_PEN;
}


int Cp1View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	CMFCToolBar::EnableQuickCustomization();

	return 0;
}


void Cp1View::OnUpdateDrawEllipse(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	// 决定画椭圆的菜单项chek状态
	pCmdUI->SetCheck(m_DrawType == DT_ELLIPSE);
}


void Cp1View::OnUpdateDrawLine(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_DrawType == DT_LINE);
}


void Cp1View::OnUpdateDrawPen(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_DrawType == DT_PEN);
}


void Cp1View::OnUpdateDrawRect(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_DrawType == DT_RECT);
}


void Cp1View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CMenu* mu = m_Menu.GetSubMenu(0);
	// 转换成屏幕坐标
	ClientToScreen(&point);
	mu->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
	CView::OnRButtonDown(nFlags, point);
}


void Cp1View::OnFileSetup()
{
	// TODO: 在此添加命令处理程序代码
	// 弹出选项对话框
	Setup config;
	config.m_nLineWidth = m_nLineWidth;
	config.m_nLineStyle = m_nLineStyle;
	config.m_nColor = m_nColor;
	if (IDOK == config.DoModal())// 调用模块对话框
	{
		// 如果用户按下了确定按钮
		this->m_nLineWidth = config.m_nLineWidth;
		this->m_nLineStyle = config.m_nLineStyle;
		this->m_nColor = config.m_nColor;
	}
}

void Cp1View::OnFileWrite()
{
	// TODO: 在此添加命令处理程序代码
	CString hello = _T("hello,world\n");
	// 打开文件对话框
	CFileDialog fileDlg(FALSE);
	if (IDOK == fileDlg.DoModal())
	{
		// 获取对话框返回的文件名
		CString path = fileDlg.GetPathName();
		// 打开文件
		CFile file(path, CFile::modeWrite | CFile::modeCreate);
		// 写入
		file.Write(hello, hello.GetLength() * sizeof(TCHAR));
		// 关闭
		file.Close();
	}
}

void Cp1View::OnFileRead()
{
	// TODO: 在此添加命令处理程序代码
	// 打开读取文件对话框
	CFileDialog fileDlg(TRUE);
	if (IDOK == fileDlg.DoModal())
	{
		// 获取文件名
		CString path = fileDlg.GetPathName();
		CFile file(path, CFile::modeRead);
		TCHAR* pBuf;
		int cnt = file.GetLength();
		int chars = cnt / sizeof(TCHAR);
		pBuf = new TCHAR[chars + 1];
		file.Read(pBuf, cnt);
		pBuf[chars] = 0;
		MessageBox(pBuf);
		file.Close();
		delete[] pBuf;
	}
}
