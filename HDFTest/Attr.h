// Attr.h: interface for the CAttr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ATTR_H__E1C6574A_B34A_43DA_BB47_D71C3FC809FD__INCLUDED_)
#define AFX_ATTR_H__E1C6574A_B34A_43DA_BB47_D71C3FC809FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <afxtempl.h>
#include "include425/hdf.h"
#include "include425/dfsd.h"
#include "include425/mfhdf.h"

class CAttr  
{
public:
	void* m_Attr;
	int32 m_AttrType;
	int32 m_AttrLen;
	char *m_AttrName;
	CAttr();
	virtual ~CAttr();
};
typedef CList<CAttr*,CAttr*> CAttrList;
#endif // !defined(AFX_ATTR_H__E1C6574A_B34A_43DA_BB47_D71C3FC809FD__INCLUDED_)
