
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "MarkProtection.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_UPDATE_COMMAND_UI(ID_CONVERT_SAVE_AS, &CMainFrame::OnUpdateConvertSaveAs)
	ON_MESSAGE(WM_SET_DIRTY, &CMainFrame::OnSetDirty)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	m_DirtyFlag = 0;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers



void CMainFrame::OnUpdateConvertSaveAs(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
/*	CMenu* mmenu = GetMenu();
	CMenu* submenu = mmenu->GetSubMenu(0);
	submenu->EnableMenuItem(ID_CONVERT_SAVE_AS, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
*/

	pCmdUI->Enable(m_DirtyFlag);


}

afx_msg LRESULT CMainFrame::OnSetDirty(WPARAM wParam, LPARAM lParam)
{
	m_DirtyFlag = (int)lParam;
	return LRESULT();
}

