
// MarkProtectionView.cpp : implementation of the CMarkProtectionView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MarkProtection.h"
#endif

#include "MarkProtectionDoc.h"
#include "MarkProtectionView.h"
#include "StockSelect.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMarkProtectionView

IMPLEMENT_DYNCREATE(CMarkProtectionView, CView)

BEGIN_MESSAGE_MAP(CMarkProtectionView, CView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_MESSAGE(WM_SetProtection, &CMarkProtectionView::OnSetProtection)
	ON_MESSAGE(WM_SetSpecial, &CMarkProtectionView::OnSetSpecial)
	ON_COMMAND(ID_SELECT_STOCK, &CMarkProtectionView::OnSelectStock)
END_MESSAGE_MAP()

// CMarkProtectionView construction/destruction

CMarkProtectionView::CMarkProtectionView()
{
	// TODO: add construction code here
}

CMarkProtectionView::~CMarkProtectionView()
{
}

BOOL CMarkProtectionView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMarkProtectionView drawing

void CMarkProtectionView::OnDraw(CDC* /*pDC*/)
{
	CMarkProtectionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;


	// TODO: add draw code for native data here
}


// CMarkProtectionView diagnostics

#ifdef _DEBUG
void CMarkProtectionView::AssertValid() const
{
	CView::AssertValid();
}

void CMarkProtectionView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMarkProtectionDoc* CMarkProtectionView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMarkProtectionDoc)));
	return (CMarkProtectionDoc*)m_pDocument;
}
#endif //_DEBUG


// CMarkProtectionView message handlers
int CMarkProtectionView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO: Add your specialized creation code here
	CString strTitle = GetDocument()->GetTitle();

	CString docName;
	CWnd::GetWindowText(docName);

	m_grid.CreateGrid(WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, 100);

	DrawGrid();

	return 0;
}

void CMarkProtectionView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	CString docName;

	//	this->get  GetEditCtrl().GetWindowText(strText);

	CWnd::GetWindowText(docName);
	m_grid.MoveWindow(0, 0, cx, cy);
}

BOOL CMarkProtectionView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	return TRUE;
	// return CView::OnEraseBkgnd(pDC);
}

void CMarkProtectionView::DrawGrid()
{
	CUGCell cell;
	// Clear the sheet first
	for (int i = 0; i < m_grid.GetNumberRows(); i++) {
		for (int j = 0; j < m_grid.GetNumberCols(); j++) {
			m_grid.QuickSetText(j, i, L"");
			m_grid.SetRowHeight(i, 20);    // show the row
		}
	}
	m_StockCode = 0;

	CMarkProtectionDoc* pDoc = GetDocument();
	m_grid.m_NumRows = pDoc->m_NumRow;

	for (int row = 0; row < pDoc->m_NumRow; row++) {
		CString strRow;
		strRow.Format(L"%d", row + 1);
		m_grid.QuickSetText(-1, row, strRow);   // indicate the row no.

		m_grid.GetCell(0, row, &cell);
		cell.SetMask(L"A"); cell.SetBorder(UG_BDR_RECESSED); cell.SetAlignment(UG_ALIGNCENTER); cell.SetBackColor(COLOR_EDITABLE);
		cell.SetText(pDoc->m_Row[row].Protection);
		m_grid.SetCell(0, row, &cell);

		m_grid.GetCell(1, row, &cell);
		cell.SetMask(L"A"); cell.SetBorder(UG_BDR_RECESSED); cell.SetAlignment(UG_ALIGNCENTER); cell.SetBackColor(COLOR_EDITABLE);
		cell.SetText(pDoc->m_Row[row].Special);
		m_grid.SetCell(1, row, &cell);

		m_grid.QuickSetText(2, row, pDoc->m_Row[row].Trades);
		m_grid.QuickSetText(3, row, pDoc->m_Row[row].Name);
		m_grid.QuickSetText(4, row, pDoc->m_Row[row].BQty);
		m_grid.QuickSetText(5, row, pDoc->m_Row[row].SQty);
		m_grid.QuickSetText(6, row, pDoc->m_Row[row].Price);
		m_grid.QuickSetText(7, row, pDoc->m_Row[row].Time);
		m_grid.QuickSetText(8, row, pDoc->m_Row[row].OrderNo);
		m_grid.QuickSetText(9, row, pDoc->m_Row[row].Status);
		m_grid.QuickSetText(10, row, pDoc->m_Row[row].ExtOrderNo);
		m_grid.QuickSetText(11, row, pDoc->m_Row[row].Source);
	}
}

afx_msg LRESULT CMarkProtectionView::OnSetProtection(WPARAM wParam, LPARAM lParam) {
	CUGCell cell;
	int row = (int)lParam;

	CMarkProtectionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return 0;

	m_grid.GetCell(0, row, &cell); // Protection Flag
	pDoc->m_Row[row].Protection = cell.GetText();
	pDoc->m_Row[row].Protection.Trim();
	
	AfxGetMainWnd()->SendMessage(WM_SET_DIRTY, NULL, 1);

	return 0;
}

afx_msg LRESULT CMarkProtectionView::OnSetSpecial(WPARAM wParam, LPARAM lParam) {
	CUGCell cell;
	int row = (int)lParam;

	CMarkProtectionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return 0;

	m_grid.GetCell(1, row, &cell);  // Special Flag
	pDoc->m_Row[row].Special = cell.GetText();
	pDoc->m_Row[row].Special.Trim();

	AfxGetMainWnd()->SendMessage(WM_SET_DIRTY, NULL, 1);

	return 0;
}


CMarkProtectionView * CMarkProtectionView::GetView()
{
	CFrameWnd * pFrame = (CFrameWnd *)(AfxGetApp()->m_pMainWnd);

	CView * pView = pFrame->GetActiveView();

	if (!pView)
		return NULL;

	// Fail if view is of wrong kind
	// (this could occur with splitter windows, or additional
	// views on a single document

	if (!pView->IsKindOf(RUNTIME_CLASS(CMarkProtectionView)))
		return NULL;

	return (CMarkProtectionView *)pView;
}


void CMarkProtectionView::OnSelectStock()
{
	StockSelect   dlg;

	if (IDOK == dlg.DoModal())
	{
		m_StockCode = dlg.m_StockCode;

		CString strStockCode;
		strStockCode.Format(L"%s%d", L"00000", m_StockCode);
		strStockCode = strStockCode.Right(5);

		CMarkProtectionDoc* pDoc = GetDocument();
		for (int row = 0; row < pDoc->m_NumRow; row++) {
			CString strName = m_grid.QuickGetText(3, row);   // Name  at col 3

			if (strStockCode=="00000" || strStockCode == strName.Left(5)) {        // stockcode 0 to show all
				m_grid.SetRowHeight(row, 20);    // show the row
			}
			else {
				m_grid.SetRowHeight(row, 0);    // hide the row
			}
		}
		m_grid.RedrawAll();
	}
}
