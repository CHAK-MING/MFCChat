
// p1View.h: Cp1View 类的接口
//

#pragma once
#define TIMER_TEXT 9526

#include "Graph.h"



class Cp1View : public CView
{
protected: // 仅从序列化创建
	Cp1View() noexcept;
	DECLARE_DYNCREATE(Cp1View)

// 特性
public:
	Cp1Doc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~Cp1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
protected:
	CPoint m_pOrigin;
	bool m_bDraw; // 是否点击了左键
	int m_nWidth;
	DRAW_TYPE m_DrawType;
	CMenu m_Menu;
	int m_nLineWidth;
public:
	CObArray m_pGraphs; // 存储所有的绘制信息
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnDrawLine();
	afx_msg void OnDrawRect();
	afx_msg void OnDrawEllipse();
	afx_msg void OnDrawPen();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnUpdateDrawEllipse(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDrawLine(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDrawPen(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDrawRect(CCmdUI* pCmdUI);

	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnFileSetup();
protected:
	int m_nLineStyle;
	COLORREF m_nColor;
	// CMetaFileDC m_dcMetaFile;
	CDC m_dcCompatible;
	Graph* m_tmpGraph;
public:
	afx_msg void OnFileRead();
	afx_msg void OnFileWrite();
};

#ifndef _DEBUG  // p1View.cpp 中的调试版本
inline Cp1Doc* Cp1View::GetDocument() const
   { return reinterpret_cast<Cp1Doc*>(m_pDocument); }
#endif

