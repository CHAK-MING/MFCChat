#pragma once
#include <afx.h>

enum DRAW_TYPE
{
    DT_LINE,
    DT_RECT,
    DT_ELLIPSE,
    DT_PEN
};

class Graph :
    public CObject
{
public:
    DECLARE_SERIAL(Graph);
    Graph() = default;
    Graph(UINT drawtype, UINT linestyle, UINT linewidth, COLORREF color);

    void AddPoint(CPoint point);
    void AddPoint(CPoint start, CPoint end);

    void Draw(CDC* pDC);
public:
    UINT m_nDrawType;           // 绘制类型
    UINT m_nLineStyle;          // 线型
    UINT m_nLineWidth;          // 线宽
    COLORREF m_nColor;          // 颜色
    CArray<CPoint> m_Points;    // 点的数组
    virtual void Serialize(CArchive& ar);
};

