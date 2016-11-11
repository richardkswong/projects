
// MarkProtectionDoc.h : interface of the CMarkProtectionDoc class
//


#pragma once
#include "OptionCSV.h"

class CMarkProtectionDoc : public CDocument
{
protected: // create from serialization only
	CMarkProtectionDoc();
	DECLARE_DYNCREATE(CMarkProtectionDoc)

// Attributes
public:
	CString     m_OutputFilePath;
	CString		m_HeaderString;
	OptionCSV   m_Row[1000];    // max size: 1000 rows
	int			m_NumRow;

// Operations
public:
	static CMarkProtectionDoc * GetDoc();
	void ReadIniFile();
	CString GetOutputFilename();
	
// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CMarkProtectionDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	virtual void SetPathName(LPCTSTR lpszPathName, BOOL bAddToMRU = TRUE);
	virtual void SetTitle(LPCTSTR lpszTitle);
	afx_msg void OnConvertSaveAs();
};
