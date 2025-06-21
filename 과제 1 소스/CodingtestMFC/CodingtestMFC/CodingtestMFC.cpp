#include "pch.h"
#include "CodingtestMFC.h"
#include "CodingtestMFCDlg.h"

BEGIN_MESSAGE_MAP(CCodingtestMFCApp, CWinApp)
END_MESSAGE_MAP()

CCodingtestMFCApp theApp;

BOOL CCodingtestMFCApp::InitInstance()
{
    CWinApp::InitInstance();
    AfxEnableControlContainer();

    CCodingtestMFCDlg dlg;
    m_pMainWnd = &dlg;
    INT_PTR nResponse = dlg.DoModal();
    return FALSE;
}