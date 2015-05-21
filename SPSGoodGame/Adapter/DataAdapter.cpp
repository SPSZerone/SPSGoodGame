#include "DataAdapter.h"
__SPS_GG__NS__U_ADAPTER;



DataAdapter::DataAdapter()
{
	_gg_nDataType = -1;
	_gg_pData = nullptr;

	_gg_dwDataID = 0;

	_gg_nType = -1;
	_gg_dwIndex = 0;
}



DataAdapter::~DataAdapter()
{
	
}



bool DataAdapter::IsAnyDataAvailable() const
{
	return IsDataAvailable() || IsDataIDAvailable();
}



bool DataAdapter::IsDataAvailable() const
{
	return _gg_pData != nullptr;
}



bool DataAdapter::IsDataIDAvailable() const
{
	return _gg_dwDataID != 0;
}



int DataAdapter::SetDataType( int nDataType )
{
	_gg_nDataType = nDataType;
	return _gg_nDataType;
}



int DataAdapter::GetDataType() const
{
	return _gg_nDataType;
}



void *DataAdapter::SetData( void *pDataInfor )
{
	_gg_pData = pDataInfor;
	return _gg_pData;
}



void *DataAdapter::GetData() const
{
	return _gg_pData;
}



unsigned long DataAdapter::SetDataID( unsigned long dwDataID )
{
	_gg_dwDataID = dwDataID;
	return _gg_dwDataID;
}



unsigned long DataAdapter::GetDataID() const
{
	return _gg_dwDataID;
}



int DataAdapter::SetType( int nType )
{
	_gg_nType = nType;
	return _gg_nType;
}



int DataAdapter::GetType() const
{
	return _gg_nType;
}



unsigned long DataAdapter::SetIndex( unsigned long dwIndex )
{
	_gg_dwIndex = dwIndex;
	return _gg_dwIndex;
}



unsigned long DataAdapter::GetIndex() const
{
	return _gg_dwIndex;
}
