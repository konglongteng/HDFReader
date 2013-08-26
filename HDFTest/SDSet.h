// SDSet.h: interface for the CSDSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SDSET_H__2A71FF39_54D2_4B71_B548_AC6FB753BF92__INCLUDED_)
#define AFX_SDSET_H__2A71FF39_54D2_4B71_B548_AC6FB753BF92__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <Afxtempl.h>
#include "include425/hdf.h"
#include "include425/dfsd.h"
#include "include425/mfhdf.h"
#include "Attr.h"

class CSDSet  
{
public:
	void *m_SdsData;             //�洢��ǰ��SDS���ݼ�	
	int32 m_SdsStart[2];         //SDS��ȡ��ʼλ��
	int32 m_SdsEnd[2];           //SDS��ȡ����λ��
	int32 m_SdsDimSize[2];
	int32 m_SdsRank;             //SDS���ݼ���ά�ȣ�2ά��3ά��or...��
protected:
	char *m_HDFfilename;
	char *m_SdsName;             //��ǰSDS���ݼ�����
	CAttrList m_SdsAttrList;     //��ǰSDS�е������б�
	int32 m_SdsIndex;            //��ǰSDS���ݼ���HDF�ļ��е�����          
	int32 m_SdsDataType;         //��ǰSDS���ݼ�����������
	int32 m_SdsAttrNum;          //SDS���ݼ������Ը���
//    int   m_rows,m_cols;       //SDS��������
	
	

public:
	void ReadSdsAttr(char *HdfFileName,int32 sdsIndex);
    void ReadSDSet();
	void WriteSDSet(int32 newSdsIndex);
	void* allow_memory(long datasize,int datatype);
public:
	CSDSet();

	CSDSet(char *HdfFilename,int32 sdsIndex,char *sdsName,int32 sdsRank,
		   int32 *sdsDim,int32 sdsDatatype,int32 sdsAttrNum);
	virtual ~CSDSet();

};
typedef CList <CSDSet*,CSDSet*> CSDSetList;
#endif // !defined(AFX_SDSET_H__2A71FF39_54D2_4B71_B548_AC6FB753BF92__INCLUDED_)
