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
	void *m_SdsData;             //存储当前的SDS数据集	
	int32 m_SdsStart[2];         //SDS读取起始位置
	int32 m_SdsEnd[2];           //SDS读取结束位置
	int32 m_SdsDimSize[2];
	int32 m_SdsRank;             //SDS数据集的维度（2维、3维、or...）
protected:
	char *m_HDFfilename;
	char *m_SdsName;             //当前SDS数据集名称
	CAttrList m_SdsAttrList;     //当前SDS中的属性列表
	int32 m_SdsIndex;            //当前SDS数据集在HDF文件中的索引          
	int32 m_SdsDataType;         //当前SDS数据集中数据类型
	int32 m_SdsAttrNum;          //SDS数据集的属性个数
//    int   m_rows,m_cols;       //SDS的行列数
	
	

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
