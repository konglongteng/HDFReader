// HDFDataset.cpp: implementation of the CHDFDataset class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HDFTest.h"
#include "HDFDataset.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHDFDataset::CHDFDataset()
{
	m_pCurSDS = NULL;

}

CHDFDataset::~CHDFDataset()
{
	CAttr *pNextAttr; 
	if (!m_FileAttrlist.IsEmpty())
	{
		pNextAttr = m_FileAttrlist.GetHead();
		POSITION pos = m_FileAttrlist.GetHeadPosition();
		while(pos != NULL)
		{		
			pNextAttr = m_FileAttrlist.GetNext(pos);
			free( pNextAttr->m_Attr);
			delete pNextAttr;		
		}
		m_FileAttrlist.RemoveAll();
	}

	CSDSet *pNextSDS; 
	if (!m_SDSetlist.IsEmpty())
	{
		pNextSDS = m_SDSetlist.GetHead();
		POSITION pos = m_SDSetlist.GetHeadPosition();
		while(pos != NULL)
		{		
			pNextSDS = m_SDSetlist.GetNext(pos);
			free(pNextSDS->m_SdsData);
			delete pNextSDS;		
		}
		m_SDSetlist.RemoveAll();
	}

}

void CHDFDataset::open(char *hdffilename)
{
	m_HDFfilename = hdffilename;
}

void CHDFDataset::ReadHDFHead()
{

	//kong
	intn sd_id;
	int32 num_datasets,num_global_attrs;
	intn sd_status;

	int hdf4ID=Hopen(m_HDFfilename, DFACC_READ , 0) ; //retrieve the file id hou.hdf 536870912
	int status_vd = Vstart (hdf4ID); //Vstart must be called before any vdata or vgroup operation is attempted on an HDF file.
	//sd_id=SDstart(m_HDFfilename,DFACC_READ);
	//sd_status=SDfileinfo(sd_id,&num_datasets,&num_global_attrs);

	//end kong



	//读取基本信息 
    int32 fileid = SDstart(m_HDFfilename,DFACC_READ);      //获取文件的id 
	//fileid = fileid - 122;kong
	int32 status = SDfileinfo(fileid,&m_numSDS,&m_numAttr);//获取文件中数据集的个数和属性的个数
	
	char AttrName[128];
	int32 AttrType = 0;
	int32 AttrLen  = 0;
	//获取文件属性并进行链表存储
	for(int i =0; i<m_numAttr; i++)
	{		 
		status = SDattrinfo(fileid,i,AttrName,&AttrType,&AttrLen);
		CAttr *pAttr = new CAttr();                         //new出文件属性
        pAttr->m_AttrLen = AttrLen;
        pAttr->m_AttrName = AttrName;
		pAttr->m_AttrType = AttrType;

		 switch(pAttr->m_AttrType) 
		 {
			case 3: 
				pAttr->m_Attr = (uchar8*)allow_memory(pAttr->m_AttrLen,pAttr->m_AttrType);
				status = SDreadattr(fileid, i,pAttr->m_Attr );
				break;
			case 4: 
				pAttr->m_Attr = (char8*)allow_memory(pAttr->m_AttrLen,pAttr->m_AttrType);
				status = SDreadattr(fileid, i,pAttr->m_Attr );
				break;
			case 5: 
				pAttr->m_Attr = (float32*)allow_memory(pAttr->m_AttrLen,pAttr->m_AttrType);
				status = SDreadattr(fileid, i,pAttr->m_Attr );
				break;
			case 6: 
				pAttr->m_Attr = (float64*)allow_memory(pAttr->m_AttrLen,pAttr->m_AttrType);
				status = SDreadattr(fileid, i,pAttr->m_Attr );
				break;
			case 20: 
				pAttr->m_Attr = (int8*)allow_memory(pAttr->m_AttrLen,pAttr->m_AttrType);
				status = SDreadattr(fileid, i,pAttr->m_Attr );
				break;
			case 21: 
				pAttr->m_Attr = (uint8*)allow_memory(pAttr->m_AttrLen,pAttr->m_AttrType);
				status = SDreadattr(fileid, i,pAttr->m_Attr );
				break;
			case 22: 
				pAttr->m_Attr = (int16*)allow_memory(pAttr->m_AttrLen,pAttr->m_AttrType);
				status = SDreadattr(fileid, i,pAttr->m_Attr );
				break;
			case 23: 
				pAttr->m_Attr = (uint16*)allow_memory(pAttr->m_AttrLen,pAttr->m_AttrType);
				status = SDreadattr(fileid, i,pAttr->m_Attr );
				break;
			case 24: 
				pAttr->m_Attr = (int32*)allow_memory(pAttr->m_AttrLen,pAttr->m_AttrType);
				status = SDreadattr(fileid, i,pAttr->m_Attr );
				break;
			case 25: 
				pAttr->m_Attr = (uint32*)allow_memory(pAttr->m_AttrLen,pAttr->m_AttrType);
				status = SDreadattr(fileid, i,pAttr->m_Attr );
				break;
			default:         
				AfxMessageBox("不存在的数据类型 !");
				break;
		   }
		 m_FileAttrlist.InsertAfter(m_FileAttrlist.GetTailPosition(),pAttr);
	}
	
	status = SDend(fileid);
}

void CHDFDataset::ReadAllSdsAttr()
{
	if( m_numSDS < 0)                      //文件中没有数据集 
		return;
	
	for(int j = 0; j < m_numSDS; j++ )    //循环获取数据集的基本信息
	{   	
		CSDSet *pSDSet = new CSDSet();    //new出SDS属性
		pSDSet->ReadSdsAttr(m_HDFfilename,j);


		//kong 这里是应该添加代码的地方，读出数据集，怎么存储的？



		pSDSet->ReadSDSet();



		//end kong



		m_SDSetlist.InsertAfter(m_SDSetlist.GetTailPosition(),pSDSet);
		
	}
}

void CHDFDataset::WriteSDSet(char *newFilename)
{
	CSDSet *pSDSet;	   
	POSITION pos = m_SDSetlist.GetHeadPosition();
	if (pos != NULL)
	{
		pSDSet = m_SDSetlist.GetNext(pos);
		pSDSet->ReadSDSet();
		WriteSDSet(newFilename,pSDSet);
		AfxMessageBox("HDF文件写入成功！");
	}	   
	
}

void CHDFDataset::WriteSDSet(char *newFilename,CSDSet *pWriteSDS)
{
	int32 file_id = SDstart (newFilename, DFACC_CREATE);
	int32 sds_id = SDcreate(file_id,"MODIS VI QA",DFNT_UINT16,pWriteSDS->m_SdsRank,pWriteSDS->m_SdsDimSize);//创建数据集1
//    int32 sds_id = SDselect (file_id, sds_Index);

	int32 status = SDwritedata (sds_id, pWriteSDS->m_SdsStart, NULL, pWriteSDS->m_SdsEnd, pWriteSDS->m_SdsData);
	status = SDendaccess (sds_id);	   
    status = SDend (file_id);

}
void* CHDFDataset::allow_memory(long datasize,int datatype)
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

void CHDFDataset::ReadHDFVData(char *hdffilename)
{
	/************************* Variable declaration **************************/
	intn status_n; /* returned status for functions returning an intn */
	int32 status_32, /* returned status for functions returning an int32 */
		file_id, vgroup_id;
	int32 lone_vg_number, /* current lone vgroup number */
		num_of_lones = 0; /* number of lone vgroups */
	int32 *ref_array; /* buffer to hold the ref numbers of lone vgroups */
	char vgroup_name[VGNAMELENMAX], vgroup_class[VGNAMELENMAX];
	/********************** End of variable declaration **********************/
	/*
	* Open the HDF file for reading.
	*/
	file_id = Hopen (hdffilename, DFACC_READ, 0);
	/*
	* Initialize the V interface.
	*/
	status_n = Vstart (file_id);
	/*
	* Get and print the names and class names of all the lone vgroups.
	* First, call Vlone with num_of_lones set to 0 to get the number of
	* lone vgroups in the file, but not to get their reference numbers.
	*/
	num_of_lones = Vlone (file_id, NULL, num_of_lones );
	/*
	* Then, if there are any lone vgroups,
	*/
	if (num_of_lones > 0)
	{
	/*
	* use the num_of_lones returned to allocate sufficient space for the
	* buffer ref_array to hold the reference numbers of all lone vgroups,
		*/
		ref_array = (int32 *) malloc(sizeof(int32) * num_of_lones);
		/*
		* and call Vlone again to retrieve the reference numbers into
		* the buffer ref_array.
		*/
		num_of_lones = Vlone (file_id, ref_array, num_of_lones);
		/*
		* Display the name and class of each lone vgroup.
		*/
		printf ("Lone vgroups in this file are:\n");
		for (lone_vg_number = 0; lone_vg_number < num_of_lones;
		lone_vg_number++)
		{
		/*
		* Attach to the current vgroup then get and display its
		* name and class. Note: the current vgroup must be detached before
		* moving to the next.
			*/
			vgroup_id = Vattach (file_id, ref_array[lone_vg_number], "r");
			status_32 = Vgetname (vgroup_id, vgroup_name);
			status_32 = Vgetclass (vgroup_id, vgroup_class);
			printf (" Vgroup name %s and class %s\n", vgroup_name,vgroup_class);
			status_32 = Vdetach (vgroup_id);
		} /* for */
	} /* if */
	  /*
	  * Terminate access to the V interface and close the file.
	*/
	status_n = Vend (file_id);
	status_n = Hclose (file_id);
	/*
	* Free the space allocated by this program.
	*/
     free (ref_array);

}


void CHDFDataset::ReadHDFVSData(char *hdffilename)
{
	/************************* Variable declaration **************************/
	intn status_n; /* returned status for functions returning an intn */
	int32 status_32, /* returned status for functions returning an int32 */
		file_id, vdata_id,
		vdata_ref, /* vdata’s reference number */
		num_of_records, /* number of records actually written to the vdata */
		record_pos; /* position of the current record */
	int16 i, rec_num; /* current record number in the vdata */
	float32 databuf[N_RECORDS][N_VALS_PER_REC]; /* buffer for vdata values */
	/********************** End of variable declaration **********************/
	/*
	* Open the HDF file for reading.
	*/
	file_id = Hopen (hdffilename, DFACC_READ, 0);
	/*
	* Initialize the VS interface.
	*/
	status_n = Vstart (file_id);
	/*
	* Get the reference number of the vdata, whose name is specified in
	* VDATA_NAME, using VSfind, which will be discussed in Section 4.7.3.
	*/


	//以下孔注释

	//vdata_ref = VSfind (file_id, VDATA_NAME);
	///*
	//* Attach to the vdata for reading if it is found, otherwise
	//* exit the program.
 //   */

	//if (vdata_ref == 0) exit;
	//vdata_id = VSattach (file_id, vdata_ref, "r");
	///*
	//* Specify the fields that will be read.
	//*/
	//status_n = VSsetfields (vdata_id, FIELDNAME_LIST);
	///*
	//* Place the current point to the position specified in RECORD_INDEX.
	//*/
	//record_pos = VSseek (vdata_id, RECORD_INDEX);
	///*
	//* Read the next N_RECORDS records from the vdata and store the data
	//* in the buffer databuf with fully interlaced mode.
	//*/
	//num_of_records = VSread (vdata_id, (uint8 *)databuf, N_RECORDS,
	//	FULL_INTERLACE);
	//	/*
	//	* Display the read data as many records as the number of records
	//	* returned by VSread.
	//*/
	//printf ("\n Particle Position Temperature Range\n\n");
	//for (rec_num = 0; rec_num < num_of_records; rec_num++)
	//{
	//	printf (" %6.2f, %6.2f, %6.2f %6.2f, %6.2f\n",
	//		databuf[rec_num][0], databuf[rec_num][1], databuf[rec_num][2],
	//		databuf[rec_num][3], databuf[rec_num][4]);
	//}
	///*
	//* Terminate access to the vdata and to the VS interface, then close
	//* the HDF file.
	//*/
	//status_32 = VSdetach (vdata_id);
	//status_n = Vend (file_id);
 //   status_32 = Hclose (file_id);

}
