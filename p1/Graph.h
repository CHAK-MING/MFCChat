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
    UINT m_nDrawType;           // ��������
    UINT m_nLineStyle;          // ����
    UINT m_nLineWidth;          // �߿�
    COLORREF m_nColor;          // ��ɫ
    CArray<CPoint> m_Points;    // �������
    virtual void Serialize(CArchive& ar);
};

