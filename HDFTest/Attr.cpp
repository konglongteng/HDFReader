// Attr.cpp: implementation of the CAttr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HDFTest.h"
#include "Attr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAttr::CAttr()
{
	m_Attr = NULL;
	m_AttrName= NULL;
	m_AttrLen = 0;
	m_AttrType = 0;

}

CAttr::~CAttr()
{

}
