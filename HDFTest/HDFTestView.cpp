// HDFTestView.cpp : implementation of the CHDFTestView class
//

#include "stdafx.h"
#include "HDFTest.h"

#include "HDFTestDoc.h"
#include "HDFTestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHDFTestView

IMPLEMENT_DYNCREATE(CHDFTestView, CView)

BEGIN_MESSAGE_MAP(CHDFTestView, CView)
	//{{AFX_MSG_MAP(CHDFTestView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHDFTestView construction/destruction

CHDFTestView::CHDFTestView()
{
	// TODO: add construction code here

}

CHDFTestView::~CHDFTestView()
{
}

BOOL CHDFTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CHDFTestView drawing

void CHDFTestView::OnDraw(CDC* pDC)
{
	CHDFTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CHDFTestView printing

BOOL CHDFTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CHDFTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CHDFTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CHDFTestView diagnostics

#ifdef _DEBUG
void CHDFTestView::AssertValid() const
{
	CView::AssertValid();
}

void CHDFTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHDFTestDoc* CHDFTestView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHDFTestDoc)));
	return (CHDFTestDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHDFTestView message handlers
