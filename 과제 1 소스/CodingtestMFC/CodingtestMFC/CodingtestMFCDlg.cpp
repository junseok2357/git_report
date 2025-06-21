#include "pch.h"
#include "CodingtestMFCDlg.h"
#include "resource.h"
#include <cmath>
#include <random>

BEGIN_MESSAGE_MAP(CCodingtestMFCDlg, CDialogEx)
    ON_WM_PAINT()
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_MOUSEMOVE()
    ON_BN_CLICKED(IDC_BTN_RESET, &CCodingtestMFCDlg::OnBnClickedReset)
    ON_BN_CLICKED(IDC_BTN_RANDOM, &CCodingtestMFCDlg::OnBnClickedRandomMove)
END_MESSAGE_MAP()

CCodingtestMFCDlg::CCodingtestMFCDlg(CWnd* pParent)
    : CDialogEx(IDD_CODINGTESTMFC_DIALOG, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCodingtestMFCDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BOOL CCodingtestMFCDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    SetIcon(m_hIcon, TRUE);
    SetIcon(m_hIcon, FALSE);
    return TRUE;
}

void CCodingtestMFCDlg::OnPaint()
{
    CPaintDC dc(this);
    dc.FillSolidRect(0, 0, 1000, 1000, RGB(255, 255, 255));

    CPen pen(PS_SOLID, 1, RGB(0, 0, 255));
    CPen* pOldPen = dc.SelectObject(&pen);

    for (const auto& pt : m_points)
        dc.Ellipse(pt.x - m_radius, pt.y - m_radius, pt.x + m_radius, pt.y + m_radius);

    if (m_points.size() == 3)
    {
        CPoint A = m_points[0], B = m_points[1], C = m_points[2];
        double a1 = B.x - A.x, b1 = B.y - A.y;
        double a2 = C.x - A.x, b2 = C.y - A.y;
        double d = 2 * (a1 * b2 - a2 * b1);
        if (d == 0) return;

        double cx = ((b2 * (a1 * (A.x + B.x) + b1 * (A.y + B.y)) - b1 * (a2 * (A.x + C.x) + b2 * (A.y + C.y))) / d);
        double cy = ((a1 * (a2 * (A.x + C.x) + b2 * (A.y + C.y)) - a2 * (a1 * (A.x + B.x) + b1 * (A.y + B.y))) / d);
        CPoint center((int)(cx + 0.5), (int)(cy + 0.5));
        double r = hypot(center.x - A.x, center.y - A.y);

        CPen thickPen(PS_SOLID, m_outline, RGB(255, 0, 0));
        dc.SelectObject(&thickPen);
        for (int i = 0; i < 360; ++i)
        {
            double rad1 = i * 3.14159 / 180.0;
            double rad2 = (i + 1) * 3.14159 / 180.0;
            dc.MoveTo((int)(center.x + r * cos(rad1)), (int)(center.y + r * sin(rad1)));
            dc.LineTo((int)(center.x + r * cos(rad2)), (int)(center.y + r * sin(rad2)));
        }
    }

    dc.SelectObject(pOldPen);
}

void CCodingtestMFCDlg::OnLButtonDown(UINT, CPoint point)
{
    if (m_points.size() < 3) m_points.push_back(point);
    else {
        for (int i = 0; i < 3; ++i)
            if (abs(point.x - m_points[i].x) <= m_radius && abs(point.y - m_points[i].y) <= m_radius)
                m_dragIndex = i, m_dragging = true;
    }
    Invalidate();
}

void CCodingtestMFCDlg::OnMouseMove(UINT, CPoint point)
{
    if (m_dragging && m_dragIndex >= 0 && m_dragIndex < 3) {
        m_points[m_dragIndex] = point;
        Invalidate(FALSE);
    }
}

void CCodingtestMFCDlg::OnLButtonUp(UINT, CPoint) { m_dragging = false; m_dragIndex = -1; }

void CCodingtestMFCDlg::OnBnClickedReset() { m_points.clear(); Invalidate(); }

UINT CCodingtestMFCDlg::RandomMoveThread(LPVOID pParam)
{
    CCodingtestMFCDlg* pDlg = reinterpret_cast<CCodingtestMFCDlg*>(pParam);
    std::default_random_engine rng((unsigned)time(NULL));
    std::uniform_int_distribution<int> dx(50, 270), dy(50, 200);
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 3; ++j)
            pDlg->m_points[j] = CPoint(dx(rng), dy(rng));
        pDlg->Invalidate(FALSE);
        Sleep(500);
    }
    return 0;
}

void CCodingtestMFCDlg::OnBnClickedRandomMove()
{
    if (m_points.size() < 3) return;
    AfxBeginThread(RandomMoveThread, this);
}
