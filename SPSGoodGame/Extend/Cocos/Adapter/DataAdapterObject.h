#ifndef __SPS__GOOD_GAME__EXTEND_COCOS_ADAPTER__DATA_ADAPTER_OBJECT_H__
#define __SPS__GOOD_GAME__EXTEND_COCOS_ADAPTER__DATA_ADAPTER_OBJECT_H__

#include "SPSGoodGame/Base/Base.h"
#include "SPSGoodGame/Base/Common.h"
#include "SPSGoodGame/Adapter/DataAdapter.h"
#include "SPSGoodGame/Base/Config.h"
#if ( ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) )
#include "cocos2d.h"
USING_NS_CC;
__SPS_GG__NS__U_ADAPTER;



__SPS_GG__NS__B_EXTEND_COCOS

class DataAdapterObject : public DataAdapter, public Ref
{
protected:
	// ========== DATA [ begin ] ==========
	Ref *_gg_pDataObject;
	// ========== DATA [ end ] ==========


public:
	DataAdapterObject();
	virtual ~DataAdapterObject();


	virtual bool IsAnyDataAvailable() const override;
	virtual bool IsDataObjectAvailable() const;

	virtual Ref *SetDataObject( Ref *pDataObject );
	virtual Ref *GetDataObject() const;
}; // end class DataAdapterObject

__SPS_GG__NS__END // end __SPS_GG__NS__B_EXTEND_COCOS



#endif // #if ( ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) )

#endif // #ifndef __SPS__GOOD_GAME__EXTEND_COCOS_ADAPTER__DATA_ADAPTER_OBJECT_H__
