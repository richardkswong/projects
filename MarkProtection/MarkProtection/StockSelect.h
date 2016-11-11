#pragma once


// StockSelect dialog

class StockSelect : public CDialog
{
	DECLARE_DYNAMIC(StockSelect)

public:
	StockSelect(CWnd* pParent = NULL);   // standard constructor
	virtual ~StockSelect();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STOCKSELECT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_StockCode;
};
