// StockSelect.cpp : implementation file
//

#include "stdafx.h"
#include "MarkProtection.h"
#include "StockSelect.h"
#include "afxdialogex.h"


// StockSelect dialog

IMPLEMENT_DYNAMIC(StockSelect, CDialog)

StockSelect::StockSelect(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_STOCKSELECT, pParent)
	, m_StockCode(0)
{

}

StockSelect::~StockSelect()
{
}

void StockSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_StockCode);
	DDV_MinMaxInt(pDX, m_StockCode, 0, 99999);
}


BEGIN_MESSAGE_MAP(StockSelect, CDialog)
END_MESSAGE_MAP()


// StockSelect message handlers
