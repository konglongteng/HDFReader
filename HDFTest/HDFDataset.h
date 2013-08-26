// HDFDataset.h: interface for the CHDFDataset class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HDFDATASET_H__FB40C0CA_4967_4344_A02F_E23B1B5FF01D__INCLUDED_)
#define AFX_HDFDATASET_H__FB40C0CA_4967_4344_A02F_E23B1B5FF01D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "include425/hdf.h"
#include "include425/dfsd.h"
#include "include425/mfhdf.h"
#include "SDSet.h"
#include "Attr.h"

#define FILE_NAME "General_Vdatas.hdf"
#define VDATA_NAME "Solid Particle"
#define N_RECORDS 5 /* number of records the vdata contains */
#define RECORD_INDEX 3 /* position where reading starts - 4th record */
#define ORDER_1 3 /* order of first field to be read */
#define ORDER_2 2 /* order of second field to be read */
#define FIELDNAME_LIST "Position,Temperature" /* only two fields are read */
#define N_VALS_PER_REC (ORDER_1 + ORDER_2)
/* number of values per record */

class CHDFDataset  
{

protected:
	char* m_HDFfilename;        //HDF文件名
	CSDSetList m_SDSetlist;     //SDS数据集链表
	CAttrList  m_FileAttrlist;  //HDF文件属性链表
	CSDSet *m_pCurSDS;          //当前SDS指针
	int32 m_numSDS;             //HDF文件SDS数据集个数
	int32 m_numAttr;            //HDF文件属性个数    
public:
	void open(char *hdffilename);
	void ReadHDFHead();
	void ReadAllSdsAttr();
	void WriteSDSet(char *newFilename);
	void WriteSDSet(char *newFilename,CSDSet *pWriteSDS);
    void* allow_memory(long datasize,int datatype);
public:
	void ReadHDFVSData(char *hdffilename);
	void ReadHDFVData(char *hdffilename);
	CHDFDataset();
	virtual ~CHDFDataset();
};

#endif // !defined(AFX_HDFDATASET_H__FB40C0CA_4967_4344_A02F_E23B1B5FF01D__INCLUDED_)
