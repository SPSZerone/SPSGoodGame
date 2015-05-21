#ifndef __SPS__GOOD_GAME__EXTEND_COCOS_WIDGET__SINGLE_DISPLAY_VIEW_H__
#define __SPS__GOOD_GAME__EXTEND_COCOS_WIDGET__SINGLE_DISPLAY_VIEW_H__

#include "SPSGoodGame/Base/Base.h"
#include "SPSGoodGame/Base/Config.h"
#if ( ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) )
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;



// 快速拖动时间间隔（毫秒）
#define SingleDisplayViewFastScrollIntervalMilliSecond			200
// 快速拖动最小移动距离
#define SingleDisplayViewFastScrollMinOffset			20
// 翻页时动画时间
#define SingleDisplayViewSwitchPageTime			0.2f



__SPS_GG__NS__B_EXTEND_COCOS

class SingleDisplayView;
class SingleDisplayViewDataSource
{
public:
	virtual unsigned int SingleDisplayViewDataSource_DataCount( SingleDisplayView *pSingleDisplayView ) = 0;
	virtual TableViewCell *SingleDisplayViewDataSource_CellAtPageIndex( SingleDisplayView *pSingleDisplayView, unsigned int nIdx ) = 0;
};

class SingleDisplayViewListener
{
public:

	// nCode：<0:上一页，0当前页，>0:下一页
	virtual int SingleDisplayView_SwitchPage( SingleDisplayView *pSingleDisplayView ) = 0;

	virtual int SingleDisplayView_TouchBegin( SingleDisplayView *pSingleDisplayView, Touch *pTouch ) = 0;
	virtual int SingleDisplayView_TouchMoved( SingleDisplayView *pSingleDisplayView, Touch *pTouch ) = 0;
	virtual int SingleDisplayView_TouchEnded( SingleDisplayView *pSingleDisplayView, Touch *pTouch ) = 0;
	virtual int SingleDisplayView_TouchCancelled( SingleDisplayView *pSingleDisplayView, Touch *pTouch ) = 0;
};

class SingleDisplayView : public Layer, public TableViewDataSource
{
public:	
	enum UITag
	{
		kSingleDisplayView_UITag_BG = 0,
		kSingleDisplayView_UITag_TableView,
	};
	
	enum class Direction
	{
		HORIZONTAL,
		VERTICAL
	};

	enum class SwitchPageAction
	{
		WAITING,
		RESTORE_START,
		RESTORE_END,
		PRE_PAGE_START,
		PRE_PAGE_END,
		NEXT_PAGE_START,
		NEXT_PAGE_END,
	}; 
protected:
	SingleDisplayViewDataSource *m_pDataSource;
	SingleDisplayViewListener *m_pListener;


	Direction m_eDirection;		// 水平或垂直方向
	bool m_isEnable;		// 是否禁用触摸
	int m_nSingleTouchPriority;
	bool m_isSwallowTouch;
	bool m_isTouchScheduleRun;	// 重新注册Touch Schedule


	SwitchPageAction m_eSwitchPageAction;
	float m_fSwitchPageTime;
	Point m_beginTouchPosition;
	timeval m_beginTouchTime;
	unsigned int m_nFastScrollTime; // 快速拖动时间间隔（毫秒）
	int m_nFastScrollMinOffset; // 快速拖动最小移动距离
	bool m_isTouchIgnore;


	TableView *m_pTableView;
	Point m_tvBeginContentOffset;

	unsigned int m_nPageIndex;		// 第几页索引,从0开始



public:
	static SingleDisplayView *create( int nTouchPriority, SingleDisplayViewDataSource *pDataSource, const Size &contentSize );
	SingleDisplayView();
	virtual ~SingleDisplayView();
	virtual bool init( int nTouchPriority, SingleDisplayViewDataSource *pDataSource, const Size &contentSize );

	virtual bool BuildDisplayView( Direction eDirection );


	virtual void onEnter() override;
	virtual void onEnterTransitionDidFinish() override;
	virtual void onExitTransitionDidStart() override;
	virtual void onExit() override;


	virtual bool onTouchBegan( Touch *pTouch, Event *pEvent );
	virtual void onTouchMoved( Touch *pTouch, Event *pEvent );
	virtual void onTouchEnded( Touch *pTouch, Event *pEvent );
	virtual void onTouchCancelled( Touch *pTouch, Event *pEvent );


	// >> TableViewDataSource [ begin ]
	virtual Size tableCellSizeForIndex( TableView *pTableView, ssize_t nIdx ) override;
    virtual Size cellSizeForTable( TableView *pTableView ) override;
    virtual ssize_t numberOfCellsInTableView( TableView *pTableView ) override;
    virtual TableViewCell* tableCellAtIndex( TableView *pTableView, ssize_t nIdx ) override;
	// >> TableViewDataSource [ end ]


	virtual TableViewCell *DequeueCell();


protected:
	virtual int PrePage();
	virtual int NextPage();
	virtual void RunSwitchAction();
	virtual void SwitchActionFinishCallBack();
	virtual bool IsIgnoreOffset( float fOffset );


public:
	virtual void SetDataSource( SingleDisplayViewDataSource *pDataSource );
	virtual SingleDisplayViewDataSource *GetDataSource();
	virtual void SetListener( SingleDisplayViewListener *pListener );
	virtual SingleDisplayViewListener *GetListener();
	virtual TableView *GetDisplayView();
	virtual TableViewCell *GetViewCell( unsigned int nIndex );


	virtual bool IsEnable();
	virtual void SetEnable( bool isEnable );
	virtual bool IsTouchMe( Touch *pTouch );
	virtual bool IsCollidedWithMe( Node *pNode );
	virtual bool IsCollidedWithMe( const Point &worldPosition );
	virtual unsigned int GetPageIndex();

	virtual void SetDirection( Direction eDirection );
	virtual Direction GetDirection();
	virtual SwitchPageAction GetSwitchPageAction();

	virtual void SetSwitchPageTime( float fTime );
	virtual float GetSwitchPageTime();
	virtual void SetFastScrollTime( unsigned int nMilliSecond );
	virtual unsigned int GetFastScrollTime();
	virtual void SetFastScrollMinOffset( int nMinOffset );
	virtual int GetFastScrollMinOffset();
	virtual bool IsTouchIgnore();

	virtual void ReloadData();

	virtual int RemoveCellAtIndex( unsigned int nIndex );
}; // end class SingleDisplayView

__SPS_GG__NS__END // end __SPS_GG__NS__B_EXTEND_COCOS


	
#endif // #if ( ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) )

#endif // #ifndef __SPS__GOOD_GAME__EXTEND_COCOS_WIDGET__SINGLE_DISPLAY_VIEW_H__
