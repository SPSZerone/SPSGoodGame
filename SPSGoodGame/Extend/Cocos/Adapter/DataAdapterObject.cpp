#include "DataAdapterObject.h"
#if ( ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) )
__SPS_GG__NS__U_EXTEND_COCOS;



DataAdapterObject::DataAdapterObject()
{
	_gg_pDataObject = nullptr;
}



DataAdapterObject::~DataAdapterObject()
{
	CC_SAFE_RELEASE_NULL( _gg_pDataObject );
}



bool DataAdapterObject::IsAnyDataAvailable() const
{
	return IsDataAvailable() || IsDataObjectAvailable() || IsDataIDAvailable();
}



bool DataAdapterObject::IsDataObjectAvailable() const
{
	return _gg_pDataObject != nullptr;
}



Ref *DataAdapterObject::SetDataObject( Ref *pDataObject )
{
	if ( _gg_pDataObject == pDataObject )
	{
		return _gg_pDataObject;
	}

	CC_SAFE_RELEASE_NULL( _gg_pDataObject );
	_gg_pDataObject = pDataObject;
	CC_SAFE_RETAIN( _gg_pDataObject );

	return _gg_pDataObject;
}



Ref *DataAdapterObject::GetDataObject() const
{
	return _gg_pDataObject;
}

#endif // #if ( ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) )
