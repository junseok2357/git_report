#pragma once
#include <afxwin.h>
#include "resource.h"
#include <vector>

class CCodingtestMFCDlg : public CDialogEx
{
public:
    CCodingtestMFCDlg(CWnd* pParent = nullptr);
    enum { IDD = IDD_CODINGTESTMFC_DIALOG};

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnBnClickedReset();
    afx_msg void OnBnClickedRandomMove();
    DECLARE_MESSAGE_MAP()

private:
    HICON m_hIcon;
    std::vector<CPoint> m_points;
    int m_dragIndex = -1;
    bool m_dragging = false;
    int m_radius = 10;
    int m_outline = 2;
    static UINT RandomMoveThread(LPVOID pParam);
};