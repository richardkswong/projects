
// MarkProtectionDoc.cpp : implementation of the CMarkProtectionDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MarkProtection.h"
#endif

#include "MarkProtectionDoc.h"
#include "MarkProtectionView.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMarkProtectionDoc

IMPLEMENT_DYNCREATE(CMarkProtectionDoc, CDocument)

BEGIN_MESSAGE_MAP(CMarkProtectionDoc, CDocument)
	ON_COMMAND(ID_CONVERT_SAVE_AS, &CMarkProtectionDoc::OnConvertSaveAs)
END_MESSAGE_MAP()


// CMarkProtectionDoc construction/destruction

CMarkProtectionDoc::CMarkProtectionDoc()
{
	// TODO: add one-time construction code here

}

CMarkProtectionDoc::~CMarkProtectionDoc()
{
}

BOOL CMarkProtectionDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CMarkProtectionDoc serialization

void CMarkProtectionDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CMarkProtectionDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CMarkProtectionDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMarkProtectionDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMarkProtectionDoc diagnostics

#ifdef _DEBUG
void CMarkProtectionDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMarkProtectionDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMarkProtectionDoc commands


BOOL CMarkProtectionDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	ReadIniFile();

	if (!CDocument::OnOpenDocument(lpszPathName)) {
		AfxGetMainWnd()->SendMessage(WM_SET_DIRTY, NULL, 0);
		return FALSE;
	}
		
	CString strLine;
	CStdioFile f;
	if (f.Open(lpszPathName, CFile::modeRead | CFile::shareDenyNone | CFile::typeText))
	{
		CString addedHeader, addedFlags;

		f.ReadString(m_HeaderString);
		if (m_HeaderString == HEADER_ORIGINAL) {
			addedHeader = "Protection,Special,";
			addedFlags = "N,,";
		}
		else if (m_HeaderString == HEADER_REVISED) {
			addedHeader = "";
			addedFlags = "";
		}
		else {
			AfxMessageBox(L"Invalid file format!", MB_ICONEXCLAMATION);
			return FALSE;
		}
		m_HeaderString = addedHeader + m_HeaderString;

		m_NumRow = 0;
		while (f.ReadString(strLine))
		{
			strLine = addedFlags + strLine;
			m_Row[m_NumRow].Set(strLine);
			m_NumRow++;
		}

		CMarkProtectionView *pView = CMarkProtectionView::GetView();
		pView->DrawGrid();

		AfxGetMainWnd()->SendMessage(WM_SET_DIRTY, NULL, 1);
	}

	return TRUE;
}




void CMarkProtectionDoc::OnCloseDocument()
{
	// TODO: Add your specialized code here and/or call the base class
	CDocument::OnCloseDocument();
}


void CMarkProtectionDoc::SetPathName(LPCTSTR lpszPathName, BOOL bAddToMRU)
{
	// TODO: Add your specialized code here and/or call the base class

	CDocument::SetPathName(lpszPathName, bAddToMRU);
}


void CMarkProtectionDoc::SetTitle(LPCTSTR lpszTitle)
{
	// TODO: Add your specialized code here and/or call the base class

	CDocument::SetTitle(lpszTitle);
}


CMarkProtectionDoc * CMarkProtectionDoc::GetDoc()
{
	CFrameWnd * pFrame = (CFrameWnd *)(AfxGetApp()->m_pMainWnd);
	return (CMarkProtectionDoc *)pFrame->GetActiveDocument();
}


void CMarkProtectionDoc::OnConvertSaveAs()
{
	CMarkProtectionView *pView = CMarkProtectionView::GetView();
	pView->m_grid.GotoCell(3, 0);

	int answer = AfxMessageBox(L"Save now ?", MB_YESNO | MB_DEFBUTTON2);
	if (answer != IDYES)
	{
		return;
	}

	// store the flags from the grid
	CUGCell cell;
	for (int i = 0; i < m_NumRow; i++) {
		m_Row[i].Protection = pView->m_grid.QuickGetText(0, i);
		m_Row[i].Special = pView->m_grid.QuickGetText(1, i);
	}

	// work out the Output file name
	CString strInputFile = GetPathName();

	CString strPath(L"");
	CString strOutputFile(L"");
	int nPos = strInputFile.ReverseFind('\\');
	if (nPos != -1)
	{
		strPath = strInputFile.Left(nPos+1);

		strOutputFile = GetOutputFilename();
		if (strOutputFile == L"") {
			AfxMessageBox(L"source is empty!", MB_ICONEXCLAMATION);
			return;
		}
		strOutputFile = L"Option" + strOutputFile;
		strOutputFile = strOutputFile + L".csv";

		if (m_OutputFilePath == L"") {    // if OutputFilePath not defined, set to original path
			strOutputFile = strPath + strOutputFile;
		}
		else {
			strOutputFile = m_OutputFilePath + strOutputFile;
		}
		
	}

	// Write the header and then line by line
	CString str;
	CStdioFile file;
	if (file.Open(strOutputFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite | CFile::shareDenyWrite))
	{
		str.Format(L"%s\n", HEADER_REVISED);
		file.WriteString(str);

		for (int i = 0; i < m_NumRow; i++) {
			str.Format(L"%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",
				m_Row[i].Protection.Trim(),
				m_Row[i].Special.Trim(),
				m_Row[i].Trades.Trim(),
				m_Row[i].Name.Trim(),
				m_Row[i].BQty.Trim(),
				m_Row[i].SQty.Trim(),
				m_Row[i].Price.Trim(),
				m_Row[i].Time.Trim(),
				m_Row[i].OrderNo.Trim(),
				m_Row[i].Status.Trim(),
				m_Row[i].ExtOrderNo.Trim(),
				m_Row[i].Source.Trim()
				);

			file.WriteString(str);
		}

		file.Flush();
		file.Close();
	}
	CString strText;
	strText.Format(L"File saved.\n%s", strOutputFile);
	AfxMessageBox(strText, MB_ICONINFORMATION);

	AfxGetMainWnd()->SendMessage(WM_SET_DIRTY, NULL, 0);

	return;
	//	return CDocument::OnSaveDocument(lpszPathName);   // DO NOT serialize
}


void CMarkProtectionDoc::ReadIniFile()
{
	char buf[100];
	// Read setting from INI file  

	GetPrivateProfileString(L"MarkProtectionOutputFile", L"Path", L"", (LPWSTR)buf, 100, L".\\ServerSetting.ini");
	m_OutputFilePath = (LPWSTR)buf;
}


CString CMarkProtectionDoc::GetOutputFilename() {
	CString strDateTime = m_Row[0].Time;
	if (strDateTime == L"") {
		return L"";
	}

	int pos = strDateTime.Find(L" ");
	CString strDate = strDateTime.Left(pos);

	pos = strDate.Find(L"/");
	CString strDay = strDate.Left(pos);
	strDate = strDate.Mid(pos+1, 10);
	pos = strDate.Find(L"/");
	CString strMonth = strDate.Left(pos);
	CString strYear = strDate.Right(4);

	strDay = L"00" + strDay;
	strMonth = L"00" + strMonth;

	CString str;
	str.Format(L"%s%s%s", strYear, strMonth.Right(2), strDay.Right(2));   // return yyyymmdd
	return str;
}