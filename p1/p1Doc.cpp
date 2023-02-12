
// p1Doc.cpp: Cp1Doc 类的实现
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

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Cp1Doc

IMPLEMENT_DYNCREATE(Cp1Doc, CDocument)

BEGIN_MESSAGE_MAP(Cp1Doc, CDocument)
END_MESSAGE_MAP()


// Cp1Doc 构造/析构

Cp1Doc::Cp1Doc() noexcept
{
	// TODO: 在此添加一次性构造代码

}

Cp1Doc::~Cp1Doc()
{
}

BOOL Cp1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// Cp1Doc 序列化

void Cp1Doc::Serialize(CArchive& ar)
{
	POSITION pos = GetFirstViewPosition();
	Cp1View* pView = (Cp1View*)GetNextView(pos);

	// int cnt = pView->m_pGraphs.GetSize();
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
		// 存储长度
		//ar << cnt;
		//// 遍历数组，依次存储
		//for (int i = 0; i < cnt; ++i)
		//{
		//	ar << pView->m_pGraphs.GetAt(i);
		//}
	}
	else
	{
		//// TODO: 在此添加加载代码
		//ar >> cnt;
		//for (int i = 0; i < cnt; ++i)
		//{
		//	Graph* ph;
		//	ar >> ph;
		//	pView->m_pGraphs.Add(ph);
		//}
	}
	pView->m_pGraphs.Serialize(ar);
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void Cp1Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void Cp1Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void Cp1Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// Cp1Doc 诊断

#ifdef _DEBUG
void Cp1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void Cp1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Cp1Doc 命令
