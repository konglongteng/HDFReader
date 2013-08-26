// HDFTestDoc.h : interface of the CHDFTestDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HDFTESTDOC_H__A5240C65_E880_46EA_BC75_693596EA672D__INCLUDED_)
#define AFX_HDFTESTDOC_H__A5240C65_E880_46EA_BC75_693596EA672D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "HDFDataset.h"


class CHDFTestDoc : public CDocument
{
protected: // create from serialization only
	CHDFTestDoc();
	DECLARE_DYNCREATE(CHDFTestDoc)

// Attributes
public:
    CHDFDataset *phdfDataSet;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHDFTestDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHDFTestDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CHDFTestDoc)
	afx_msg void OnFileOpen();
	afx_msg void OnFileSaveAs();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HDFTESTDOC_H__A5240C65_E880_46EA_BC75_693596EA672D__INCLUDED_)
