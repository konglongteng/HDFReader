// HDFTestDoc.cpp : implementation of the CHDFTestDoc class
//

#include "stdafx.h"
#include "HDFTest.h"

#include "HDFTestDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHDFTestDoc

IMPLEMENT_DYNCREATE(CHDFTestDoc, CDocument)

BEGIN_MESSAGE_MAP(CHDFTestDoc, CDocument)
	//{{AFX_MSG_MAP(CHDFTestDoc)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHDFTestDoc construction/destruction

CHDFTestDoc::CHDFTestDoc()
{
	// TODO: add one-time construction code here

}

CHDFTestDoc::~CHDFTestDoc()
{
	if (phdfDataSet != NULL)
		delete phdfDataSet;	
}

BOOL CHDFTestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CHDFTestDoc serialization

void CHDFTestDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CHDFTestDoc diagnostics

#ifdef _DEBUG
void CHDFTestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHDFTestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHDFTestDoc commands

void CHDFTestDoc::OnFileOpen() 
{
	// TODO: Add your command handler code here
	char szFileFilter[]={"*.hdf|*.hdf|*.l3m_8D_chlo|*.l3m_8D_chlo|*.l3m_8D_SST_4|*.l3m_8D_SST_4||"};
	
	CFileDialog Dlg(true,NULL,NULL,OFN_HIDEREADONLY,szFileFilter,NULL);
	if (Dlg.DoModal()!=IDOK) { return ;}
	CString filename = Dlg.GetPathName() ;
	
	if(filename.IsEmpty())
		return;
	
	//CReadHdfData *readHdf = new CReadHdfData();
	phdfDataSet = new CHDFDataset();
	phdfDataSet->open((LPSTR)(LPCTSTR)filename);



	//phdfDataSet->ReadHDFVSData((LPSTR)(LPCTSTR)filename);孔注释

	//phdfDataSet->ReadHDFVData((LPSTR)(LPCTSTR)filename);孔注释
	phdfDataSet->ReadHDFHead();
	phdfDataSet->ReadAllSdsAttr();
	
	
//	readHdf->SetFilename(filename);
//	readHdf->ReadHDFHead();
//	readHdf->ReadSdsAttr(0);
//	readHdf->ReadSdsData(0);
	AfxMessageBox("读取HDF文件成功！");
	
	return;
}

void CHDFTestDoc::OnFileSaveAs() 
{
	// TODO: Add your command handler code here
	char szFileFilter[]={"*.hdf|*.hdf|*.l3m_8D_chlo|*.l3m_8D_chlo|*.l3m_8D_SST_4|*.l3m_8D_SST_4||"};
	
	CFileDialog Dlg(false,NULL,NULL,OFN_HIDEREADONLY,szFileFilter,NULL);
	if (Dlg.DoModal()!=IDOK) { return ;}
	CString filename = Dlg.GetPathName() ;	
	if(filename.IsEmpty())
		return;

    phdfDataSet->WriteSDSet((LPSTR)(LPCTSTR)filename);
}
