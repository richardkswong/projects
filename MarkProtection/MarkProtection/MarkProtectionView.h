
// MarkProtectionView.h : interface of the CMarkProtectionView class
//

#pragma once
#include "Mycug.h"

class CMarkProtectionView : public CView
{
protected: // create from serialization only
	CMarkProtectionView();
	DECLARE_DYNCREATE(CMarkProtectionView)

// Attributes
public:
	CMarkProtectionDoc* GetDocument() const;
	MyCug   m_grid;
	int		m_StockCode;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	static CMarkProtectionView * GetView();
	void CMarkProtectionView::DrawGrid();

protected:

// Implementation
public:
	virtual ~CMarkProtectionView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg LRESULT OnSetProtection(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetSpecial(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSelectStock();
	DECLARE_MESSAGE_MAP()
public:
};

#ifndef _DEBUG  // debug version in MarkProtectionView.cpp
inline CMarkProtectionDoc* CMarkProtectionView::GetDocument() const
   { return reinterpret_cast<CMarkProtectionDoc*>(m_pDocument); }
#endif

