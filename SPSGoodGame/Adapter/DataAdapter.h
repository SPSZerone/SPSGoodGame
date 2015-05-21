#ifndef __SPS__GOOD_GAME__ADAPTER__DATA_ADAPTER_H__
#define __SPS__GOOD_GAME__ADAPTER__DATA_ADAPTER_H__

#include "SPSGoodGame/Base/Base.h"
#include "SPSGoodGame/Base/Const.h"



__SPS_GG__NS__B_ADAPTER

class DataAdapter
{
protected:
	// ========== DATA [ begin ] ==========
	int _gg_nDataType; // 数据类型
	void *_gg_pData; // 弱引用

	unsigned long _gg_dwDataID;
	// ========== DATA [ end ] ==========


	int _gg_nType;
	unsigned long _gg_dwIndex;


public:
	DataAdapter();
	virtual ~DataAdapter();


	virtual bool IsAnyDataAvailable() const;
	virtual bool IsDataAvailable() const;
	virtual bool IsDataIDAvailable() const;


	virtual int SetDataType( int nDataType );
	virtual int GetDataType() const;
	virtual void *SetData( void *pData );
	virtual void *GetData() const;

	virtual unsigned long SetDataID( unsigned long dwDataID );
	virtual unsigned long GetDataID() const;


	virtual int SetType( int nType );
	virtual int GetType() const;

	virtual unsigned long SetIndex( unsigned long dwIndex );
	virtual unsigned long GetIndex() const;
}; // end class DataAdapter

__SPS_GG__NS__END // end __SPS_GG__NS__B_ADAPTER



#endif // end #ifndef __SPS__GOOD_GAME__ADAPTER__DATA_ADAPTER_H__
