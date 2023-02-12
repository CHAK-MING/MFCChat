#include "pch.h"
#include "Graph.h"

IMPLEMENT_SERIAL(Graph, CObject, 1);

Graph::Graph(UINT drawtype, UINT linestyle, UINT linewidth, COLORREF color)
	: m_nDrawType(drawtype),
	m_nLineStyle(linestyle),
	m_nLineWidth(linewidth),
	m_nColor(color)
{
}

void Graph::AddPoint(CPoint point)
{
	m_Points.Add(point);
}

void Graph::AddPoint(CPoint start, CPoint end)
{
	m_Points.Add(start);
	m_Points.Add(end);
}

void Graph::Draw(CDC* pDC)
{
	CPen pen(m_nLineStyle, m_nLineWidth, m_nColor);
	CPen* pOldPen = pDC->SelectObject(&pen);
	int num;
	switch (m_nDrawType)
	{
	case DT_LINE:
		pDC->MoveTo(m_Points.GetAt(0));
		pDC->LineTo(m_Points.GetAt(1));
		break;
	case DT_RECT:
		pDC->Rectangle(CRect(m_Points.GetAt(0), m_Points.GetAt(1)));
		break;
	case DT_ELLIPSE:
		pDC->Ellipse(CRect(m_Points.GetAt(0), m_Points.GetAt(1)));
		break;
	case DT_PEN:
		num = m_Points.GetSize();
		for (int i = 0; i < num; )
		{
			// 取出两个点
			pDC->MoveTo(m_Points.GetAt(i));
			if (++i < num)
				pDC->LineTo(m_Points.GetAt(i));
		}
		break;
	default:
		break;
	}
	pDC->SelectObject(pOldPen);
}


// 序列化方法
void Graph::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
		ar << m_nDrawType << m_nLineStyle << m_nLineWidth << m_nColor;

	}
	else
	{	// loading code
		ar >> m_nDrawType >> m_nLineStyle >> m_nLineWidth >> m_nColor;
	}
	m_Points.Serialize(ar);
}
