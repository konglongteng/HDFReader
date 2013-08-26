// SDSet.cpp: implementation of the CSDSet class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HDFTest.h"
#include "SDSet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSDSet::CSDSet()
{
	m_HDFfilename = NULL;
	m_SdsData = NULL;
	m_SdsIndex = -1;
    m_SdsName = NULL;
	m_SdsDimSize[0] = m_SdsDimSize[1] = 0;
	m_SdsDataType = 0;
	m_SdsAttrNum = 0;
	m_SdsRank = 0;
	m_SdsStart[0] = m_SdsStart[1] = m_SdsEnd[0] = m_SdsEnd[1] = 0;
}

CSDSet::CSDSet(char *HdfFilename,int32 sdsIndex,char *sdsName,int32 sdsRank,int32 *sdsDim,int32 sdsDatatype,int32 sdsAttrNum)
{
	m_HDFfilename = HdfFilename;
	m_SdsData = NULL;
	m_SdsIndex = sdsIndex;
    m_SdsName = sdsName;
//	m_rows = sdsDim[0];
//	m_cols = sdsDim[1];
	m_SdsDimSize[0] = sdsDim[0];
    m_SdsDimSize[1] = sdsDim[1];
	m_SdsDataType = sdsDatatype;
	m_SdsAttrNum = sdsAttrNum;
	m_SdsRank = sdsRank;
	m_SdsStart[0] = m_SdsStart[1] =  0;
	m_SdsEnd[0] = sdsDim[0];
	m_SdsEnd[1] = sdsDim[1];
}

CSDSet::~CSDSet()
{
	CAttr *pNext; 
	if (!m_SdsAttrList.IsEmpty())
	{
		pNext = m_SdsAttrList.GetHead();
		POSITION pos = m_SdsAttrList.GetHeadPosition();
		while(pos != NULL)
		{		
			pNext = m_SdsAttrList.GetNext(pos);
			free(pNext->m_Attr);
			delete pNext;		
		}
		m_SdsAttrList.RemoveAll();
	}

}

void CSDSet::ReadSDSet()
{
	if (m_SdsIndex < 0)
	{
		AfxMessageBox("SDS数据集索引指定有误！");
		return;
	}
	int32 file_id = SDstart(m_HDFfilename,DFACC_READ);   //获取文件索引地址 
	int32 sds_id  = SDselect(file_id,m_SdsIndex);        //获取SDS索引地址 	
	int status = 0;
	
	int32 m_rows = m_SdsDimSize[0];
	int32 m_cols = m_SdsDimSize[1];
	m_SdsEnd[0] = m_rows;
	m_SdsEnd[1] = m_cols;
	
	//读取数据集
	switch(m_SdsDataType) {
	case 3: 
		m_SdsData = (uchar8*)allow_memory(sizeof(uchar8)*m_rows*m_cols,m_SdsDataType);
		status = SDreaddata(sds_id,m_SdsStart,NULL,m_SdsEnd,m_SdsData);
		break;
	case 4: 
		m_SdsData = (char8*)allow_memory(sizeof(char8)*m_rows*m_cols,m_SdsDataType);
		status = SDreaddata(sds_id,m_SdsStart,NULL,m_SdsEnd,m_SdsData);
		break;		
	case 5: 
		m_SdsData = (float32*)allow_memory(sizeof(float32)*m_rows*m_cols,m_SdsDataType);
		status = SDreaddata(sds_id,m_SdsStart,NULL,m_SdsEnd,m_SdsData);
		break;		
	case 6: 
		m_SdsData = (float64*)allow_memory(sizeof(float64)*m_rows*m_cols,m_SdsDataType);
		status = SDreaddata(sds_id,m_SdsStart,NULL,m_SdsEnd,m_SdsData);
		break;		
	case 20: 
		m_SdsData = (int8*)allow_memory(sizeof(int8)*m_rows*m_cols,m_SdsDataType);
		status = SDreaddata(sds_id,m_SdsStart,NULL,m_SdsEnd,m_SdsData);			
		break;
	case 21: 
		m_SdsData = (uint8*)allow_memory(sizeof(uint8)*m_rows*m_cols,m_SdsDataType);
		status = SDreaddata(sds_id,m_SdsStart,NULL,m_SdsEnd,m_SdsData);			
		break;		
	case 22: 	
		m_SdsData = (int16*)allow_memory(sizeof(int16)*m_rows*m_cols,m_SdsDataType);
		status = SDreaddata(sds_id,m_SdsStart,NULL,m_SdsEnd,m_SdsData);				
		break;		
	case 23: 
		//m_SdsData = (uint16*)allow_memory(sizeof(uint16)*m_rows*m_cols,m_SdsDataType);
		m_SdsData = (uint16*)allow_memory(sizeof(uint16)*15*2030*1354,m_SdsDataType);
		status = SDreaddata(sds_id,m_SdsStart,NULL,m_SdsEnd,m_SdsData);			//kong 这里分配的是  15* 2030 出错。这里没有意义啊。应该是个三维的数组才对。
		break;		
	case 24: 
		m_SdsData = (int32*)allow_memory(sizeof(int32)*m_rows*m_cols,m_SdsDataType);
		status = SDreaddata(sds_id,m_SdsStart,NULL,m_SdsEnd,m_SdsData);			
		break;		
	case 25: 
		m_SdsData = (uint32*)allow_memory(sizeof(uint32)*m_rows*m_cols,m_SdsDataType);
		status = SDreaddata(sds_id,m_SdsStart,NULL,m_SdsEnd,m_SdsData);
		break;		
	default:         
		AfxMessageBox("不存在的数据类型 !");
		break;			
	}
	status = SDendaccess(sds_id);
	status = SDend(file_id);
}

void CSDSet::ReadSdsAttr(char *HdfFileName,int32 sdsIndex)
{
	m_HDFfilename = HdfFileName;
	m_SdsIndex = sdsIndex;
	if (m_SdsIndex < 0)
	{
		AfxMessageBox("SDS数据集索引指定有误！");
		return;
	}	
	int32 file_id = SDstart(m_HDFfilename,DFACC_READ);   //获取文件索引地址 
	int32 sds_id  = SDselect(file_id,m_SdsIndex);        //获取SDS索引地址
	char  sds_name[128];
	int32 status = SDgetinfo(sds_id,sds_name,&m_SdsRank,m_SdsDimSize,&m_SdsDataType,&m_SdsAttrNum);
	m_SdsName = sds_name;
	char AttrName[128];
	int32 AttrType = 0;
	int32 AttrLen  = 0;
	for(int i =0; i < m_SdsAttrNum;i++)                  //获取数据集的属性信息
	{
		status = SDattrinfo(sds_id,i,AttrName,&AttrType,&AttrLen);
		CAttr *pAttr = new CAttr();                         //new出文件属性
        pAttr->m_AttrLen = AttrLen;
        pAttr->m_AttrName = AttrName;
		pAttr->m_AttrType = AttrType;
		switch(pAttr->m_AttrType) 
		{
		case 3: 
			pAttr->m_Attr = (uchar8*)allow_memory(pAttr->m_AttrLen,pAttr->m_AttrType);
			status = SDreadattr(sds_id, i,pAttr->m_Attr );
			break;
		case 4: 
			pAttr->m_Attr = (char8*)allow_memory(pAttr->m_AttrLen,pAttr->m_AttrType);
			status = SDreadattr(sds_id, i,pAttr->m_Attr );
			break;
		case 5: 
			pAttr->m_Attr = (float32*)allow_memory(pAttr->m_AttrLen,pAttr->m_AttrType);
			status = SDreadattr(sds_id, i,pAttr->m_Attr );
			break;
		case 6: 
			pAttr->m_Attr = (float64*)allow_memory(pAttr->m_AttrLen,pAttr->m_AttrType);
			status = SDreadattr(sds_id, i,pAttr->m_Attr );
			break;
		case 20: 
			pAttr->m_Attr = (int8*)allow_memory(pAttr->m_AttrLen,pAttr->m_AttrType);
			status = SDreadattr(sds_id, i,pAttr->m_Attr );
			break;
		case 21: 
			pAttr->m_Attr = (uint8*)allow_memory(pAttr->m_AttrLen,pAttr->m_AttrType);
			status = SDreadattr(sds_id, i,pAttr->m_Attr );
			break;
		case 22: 
			pAttr->m_Attr = (int16*)allow_memory(pAttr->m_AttrLen,pAttr->m_AttrType);
			status = SDreadattr(sds_id, i,pAttr->m_Attr );
			break;
		case 23: 
			pAttr->m_Attr = (uint16*)allow_memory(pAttr->m_AttrLen,pAttr->m_AttrType);
			status = SDreadattr(sds_id, i,pAttr->m_Attr );
			break;
		case 24: 
			pAttr->m_Attr = (int32*)allow_memory(pAttr->m_AttrLen,pAttr->m_AttrType);
			status = SDreadattr(sds_id, i,pAttr->m_Attr );
			break;
		case 25: 
			pAttr->m_Attr = (uint32*)allow_memory(pAttr->m_AttrLen,pAttr->m_AttrType);
			status = SDreadattr(sds_id, i,pAttr->m_Attr );
			break;
		default:         
			AfxMessageBox("不存在的数据类型 !");
			break;
		}
		 m_SdsAttrList.InsertAfter(m_SdsAttrList.GetTailPosition(),pAttr);
	}
    status = SDendaccess(sds_id);
	status = SDend(file_id);	
}

void CSDSet::WriteSDSet(int32 newSdsIndex)
{

}

void* CSDSet::allow_memory(long datasize,int datatype)
{
	
	switch(datatype) 
	{
	case 3: 
		return( (uchar8 *)calloc(datasize, sizeof(char8)));
		break;
	case 4: 
		return( (char8 *)calloc(datasize, sizeof(uchar8)));
		break;
	case 5: 
		return( (float32 *)calloc(datasize, sizeof(float32)));
		break;
	case 6: 
		return( (float64 *)calloc(datasize, sizeof(float64)));
		break;
	case 20: 
		return( (int8 *)calloc(datasize, sizeof(int8)));
		break;
	case 21: 
		return( (uint8 *)calloc(datasize, sizeof(uint8)) );
		break;
	case 22: 
		return( (int16 *)calloc(datasize, sizeof(int16)) );
		break;
	case 23: 
		return( (uint16 *)calloc(datasize, sizeof(uint16)) );
		break;
	case 24: 
		return( (int32 *)calloc(datasize, sizeof(int32)) );
		break;
	case 25: 
		return( (uint32 *)calloc(datasize, sizeof(uint32)) );
		break;
	default:         
		AfxMessageBox("不存在的数据类型 !");
		return NULL;
		break;
    }	
}