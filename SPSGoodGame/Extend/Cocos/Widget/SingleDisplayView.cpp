#include "SingleDisplayView.h"
#if ( ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) )
__SPS_GG__NS__U_EXTEND_COCOS;



SingleDisplayView* SingleDisplayView::create( int nTouchPriority, SingleDisplayViewDataSource *pDataSource, const Size &contentSize )
{
	SingleDisplayView *pRet = new SingleDisplayView();
	if ( pRet == nullptr )
	{
		return nullptr;
	}


	if ( pRet->init( nTouchPriority, pDataSource, contentSize ) )
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}



SingleDisplayView::SingleDisplayView()
{
	m_pDataSource = nullptr;
	m_pListener = nullptr;

	m_eDirection = Direction::HORIZONTAL;
	m_isEnable = true;
	m_nSingleTouchPriority = 0;
	m_isSwallowTouch = true;
	m_isTouchScheduleRun = false;

	m_eSwitchPageAction = SwitchPageAction::WAITING;
	m_fSwitchPageTime = SingleDisplayViewSwitchPageTime;
	m_beginTouchPosition.setPoint( 0, 0 );
	m_nFastScrollTime = SingleDisplayViewFastScrollIntervalMilliSecond;
	m_nFastScrollMinOffset = SingleDisplayViewFastScrollMinOffset;
	m_isTouchIgnore = true;

	m_pTableView = nullptr;
	m_tvBeginContentOffset.setPoint( 0, 0 );

	m_nPageIndex = 0;
}



SingleDisplayView::~SingleDisplayView()
{
	
}



bool SingleDisplayView::init( int nTouchPriority, SingleDisplayViewDataSource *pDataSource, const Size &contentSize )
{
	if ( Layer::init() == false )
	{
		return false;
	}

	if ( pDataSource == nullptr )
	{
		return false;
	}

	SetDataSource( pDataSource );
	setContentSize( contentSize );

	m_nSingleTouchPriority = nTouchPriority;

	return true;
}



bool SingleDisplayView::BuildDisplayView( Direction eDirection )
{
	if ( m_pTableView )
	{
		m_pTableView->removeFromParentAndCleanup( true );
		m_pTableView = nullptr;
	}
	
	const Size contentSize = getContentSize();

	m_pTableView = TableView::create( this, contentSize );
	SetDirection( eDirection );
	m_pTableView->setVerticalFillOrder( TableView::VerticalFillOrder::TOP_DOWN );
	m_pTableView->setTouchEnabled( false );
	addChild( m_pTableView, kSingleDisplayView_UITag_TableView, kSingleDisplayView_UITag_TableView );
	m_pTableView->setPosition( Point( -contentSize.width / 2, -contentSize.height / 2 ) );

	return true;
}



void SingleDisplayView::onEnter()
{
	Layer::onEnter();

	if ( m_pTableView )
	{
		m_pTableView->reloadData();
	}
}



void SingleDisplayView::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
}



void SingleDisplayView::onExitTransitionDidStart()
{
	Layer::onExitTransitionDidStart();
}



void SingleDisplayView::onExit()
{
	Layer::onExit();
}



bool SingleDisplayView::onTouchBegan( Touch *pTouch, Event *pEvent )
{
	if ( m_isEnable == false || IsTouchMe( pTouch ) == false || isVisible() == false || m_pTableView == nullptr || m_pDataSource == nullptr )
	{
		return false;
	}

	if ( m_eSwitchPageAction != SwitchPageAction::WAITING )
	{
		return false;
	}	

	for ( Node *pParent = this->_parent; pParent != nullptr; pParent = pParent->getParent() )
	{
		if ( pParent->isVisible() == false )
		{
			return false;
		}
	}

	m_beginTouchPosition = pTouch->getLocation();
	gettimeofday( &m_beginTouchTime, nullptr );	
	m_tvBeginContentOffset = m_pTableView->getContentOffset();

	m_isTouchIgnore = false;

	if ( m_pListener )
	{
		m_pListener->SingleDisplayView_TouchBegin( this, pTouch );
	}

	return true;
}



void SingleDisplayView::onTouchMoved( Touch *pTouch, Event *pEvent )
{
	if ( IsTouchMe( pTouch ) == false )
	{
		return ;
	}


	const Point curPosition = pTouch->getLocation();
	const Point offsetPoint = Point( curPosition.x - m_beginTouchPosition.x, curPosition.y - m_beginTouchPosition.y );
	Point contentOffset = Point::ZERO;
	m_isTouchIgnore = true;


	if ( m_eDirection == Direction::HORIZONTAL )
	{
		contentOffset.x = m_tvBeginContentOffset.x + offsetPoint.x;

		m_isTouchIgnore = IsIgnoreOffset( offsetPoint.x );
	}
	else if ( m_eDirection == Direction::VERTICAL )
	{
		contentOffset.y = m_tvBeginContentOffset.y + offsetPoint.y;

		m_isTouchIgnore = IsIgnoreOffset( offsetPoint.y );
	}
	

	if ( m_isTouchIgnore == false )
	{
		//m_pTableView->setBounceable( false );
		m_pTableView->setContentOffset( contentOffset, false );
		//m_pTableView->setBounceable( true );
	}


	if ( m_pListener )
	{
		m_pListener->SingleDisplayView_TouchMoved( this, pTouch );
	}
}



void SingleDisplayView::onTouchEnded( Touch *pTouch, Event *pEvent )
{
	timeval currentTouchTime;
	gettimeofday( &currentTouchTime, nullptr );	
	const unsigned int nIntervalMilliSecond = ( currentTouchTime.tv_sec - m_beginTouchTime.tv_sec ) * 1e3 + ( currentTouchTime.tv_usec - m_beginTouchTime.tv_usec ) / 1e3;
	const bool isFastScroll = nIntervalMilliSecond < m_nFastScrollTime;


	unsigned int nTotalCount = m_pDataSource->SingleDisplayViewDataSource_DataCount( this );
	const Point endPosition = pTouch->getLocation();
	const Point offsetPoint = Point( endPosition.x - m_beginTouchPosition.x, endPosition.y - m_beginTouchPosition.y );
	const Size contentSize = getContentSize();


	int nResult = -1;
	m_isTouchIgnore = true;


	if ( m_eDirection == Direction::HORIZONTAL )
	{
		if ( isFastScroll )
		{
			if ( offsetPoint.x < -m_nFastScrollMinOffset ) // left
			{
				nResult = NextPage();
			}
			else if ( offsetPoint.x > m_nFastScrollMinOffset ) // right
			{
				nResult = PrePage();
			}
		}
		else
		{
			if ( offsetPoint.x < -contentSize.width / 3 ) // left
			{
				nResult = NextPage();
			}
			else if ( offsetPoint.x > contentSize.width / 3 ) // right
			{
				nResult = PrePage();
			}
		}


		if ( nResult == 0 )
		{
			m_isTouchIgnore = false;
		}
		else
		{
			m_isTouchIgnore = IsIgnoreOffset( offsetPoint.x );

			if ( m_isTouchIgnore == false )
			{
				m_eSwitchPageAction = SwitchPageAction::RESTORE_START;
			}
		}


		if ( m_isTouchIgnore == false )
		{
			if ( m_pListener )
			{
				m_pListener->SingleDisplayView_SwitchPage( this );
			}

			RunSwitchAction();
			m_pTableView->setContentOffsetInDuration( Point( -contentSize.width * m_nPageIndex, 0.0f ), m_fSwitchPageTime );
		}
	}
	else if ( m_eDirection == Direction::VERTICAL )
	{
		if ( isFastScroll )
		{
			if ( offsetPoint.y < -m_nFastScrollMinOffset ) // up
			{
				nResult = PrePage();
			}
			else if ( offsetPoint.y > m_nFastScrollMinOffset ) // down
			{
				nResult = NextPage();
			}
		}
		else
		{
			if ( offsetPoint.y < -contentSize.height / 3 ) // up
			{
				nResult = PrePage();
			}
			else if ( offsetPoint.y > contentSize.height / 3 ) // down
			{
				nResult = NextPage();
			}
		}

		
		if ( nResult == 0 )
		{
			m_isTouchIgnore = false;
		}
		else
		{
			m_isTouchIgnore = IsIgnoreOffset( offsetPoint.y );

			if ( m_isTouchIgnore == false )
			{
				m_eSwitchPageAction = SwitchPageAction::RESTORE_START;
			}
		}


		if ( m_isTouchIgnore == false )
		{
			if ( m_pListener )
			{
				m_pListener->SingleDisplayView_SwitchPage( this );
			}

			RunSwitchAction();
			m_pTableView->setContentOffsetInDuration( Point( 0.0f, -contentSize.height * ( nTotalCount - 1 - m_nPageIndex ) ), m_fSwitchPageTime );
		}
	}


	if ( m_pListener )
	{
		m_pListener->SingleDisplayView_TouchEnded( this, pTouch );
	}
}



void SingleDisplayView::onTouchCancelled( Touch *pTouch, Event *pEvent )
{
	m_eSwitchPageAction = SwitchPageAction::WAITING;


	if ( m_pListener )
	{
		m_pListener->SingleDisplayView_TouchCancelled( this, pTouch );
	}

}



Size SingleDisplayView::tableCellSizeForIndex( TableView *pTableView, ssize_t nIdx )
{
    return cellSizeForTable( pTableView );
}



Size SingleDisplayView::cellSizeForTable( TableView *pTableView )
{
    return getContentSize();
}



ssize_t SingleDisplayView::numberOfCellsInTableView( TableView *pTableView )
{
	if ( m_pDataSource )
	{
		return m_pDataSource->SingleDisplayViewDataSource_DataCount( this );
	}
	return 0;
}



TableViewCell *SingleDisplayView::tableCellAtIndex( TableView *pTableView, ssize_t nIdx )
{
	if ( m_pDataSource )
	{
		return m_pDataSource->SingleDisplayViewDataSource_CellAtPageIndex( this, nIdx );
	}
	return nullptr;
}



TableViewCell *SingleDisplayView::DequeueCell()
{
	if ( m_pTableView )
	{
		return m_pTableView->dequeueCell();
	}
	return nullptr;
}



int SingleDisplayView::PrePage()
{
	if ( m_nPageIndex > 0 )
	{
		m_nPageIndex--;

		m_eSwitchPageAction = SwitchPageAction::PRE_PAGE_START;

		return 0;
	}

	return -1;
}



int SingleDisplayView::NextPage()
{
	if ( m_pTableView == nullptr )
	{
		return -1;
	}
	if ( m_pDataSource == nullptr )
	{
		return -2;
	}

	unsigned int nTotalCount = m_pDataSource->SingleDisplayViewDataSource_DataCount( this );

	if ( m_nPageIndex < nTotalCount - 1 )
	{
		m_nPageIndex++;

		m_eSwitchPageAction = SwitchPageAction::NEXT_PAGE_START;

		return 0;
	}

	return -3;
}



void SingleDisplayView::RunSwitchAction()
{
	runAction( Sequence::createWithTwoActions(
			DelayTime::create( m_fSwitchPageTime ),
			CallFunc::create( CC_CALLBACK_0(SingleDisplayView::SwitchActionFinishCallBack, this) )
		));
}



void SingleDisplayView::SwitchActionFinishCallBack()
{
	if ( m_eSwitchPageAction == SwitchPageAction::RESTORE_START )
	{
		m_eSwitchPageAction = SwitchPageAction::RESTORE_END;
	}
	else if ( m_eSwitchPageAction == SwitchPageAction::PRE_PAGE_START )
	{
		m_eSwitchPageAction = SwitchPageAction::PRE_PAGE_END;
	}
	else if ( m_eSwitchPageAction == SwitchPageAction::NEXT_PAGE_START )
	{
		m_eSwitchPageAction = SwitchPageAction::NEXT_PAGE_END;
	}

	if ( m_pListener )
	{
		m_pListener->SingleDisplayView_SwitchPage( this );
	}

	m_eSwitchPageAction = SwitchPageAction::WAITING;
}



bool SingleDisplayView::IsIgnoreOffset( float fOffset )
{
	const float fIgnoreOffset = 5;

	if ( fOffset < -fIgnoreOffset || fOffset > fIgnoreOffset )
	{
		return false;
	}

	return true;
}



void SingleDisplayView::SetDataSource( SingleDisplayViewDataSource *pDataSource )
{
	m_pDataSource = pDataSource;
}



SingleDisplayViewDataSource *SingleDisplayView::GetDataSource()
{
	return m_pDataSource;
}



void SingleDisplayView::SetListener( SingleDisplayViewListener *pListener )
{
	m_pListener = pListener;
}



SingleDisplayViewListener *SingleDisplayView::GetListener()
{
	return m_pListener;
}



TableView *SingleDisplayView::GetDisplayView()
{
	return m_pTableView;
}



TableViewCell *SingleDisplayView::GetViewCell( unsigned int nIndex )
{
	if ( m_pTableView == nullptr )
	{
		return nullptr;
	}

	return m_pTableView->cellAtIndex( nIndex );
}



bool SingleDisplayView::IsEnable()
{
	return m_isEnable;
}



void SingleDisplayView::SetEnable( bool isEnable )
{
	m_isEnable = isEnable;
}



bool SingleDisplayView::IsTouchMe( Touch *pTouch )
{
	if ( pTouch == nullptr )
	{
		return false;
	}
	
	return IsCollidedWithMe( pTouch->getLocation() );
}



bool SingleDisplayView::IsCollidedWithMe( Node *pNode )
{
	if ( pNode == nullptr )
	{
		return false;
	}
	
	Node *pParentNode = pNode->getParent();
	const Point localPosition = pNode->getPosition();
	const Point worldPosition = pParentNode ? pParentNode->convertToWorldSpace( localPosition ) : localPosition;
	return IsCollidedWithMe( worldPosition );
}



bool SingleDisplayView::IsCollidedWithMe( const Point &worldPosition )
{
	const Point anchorPoint = Point::ANCHOR_MIDDLE;
	Node *pParentNode = getParent();
	const Point localPosition = getPosition();
	const Point _worldPosition = pParentNode ? pParentNode->convertToWorldSpace( localPosition ) : localPosition;
	const Size contentSize = getContentSize() * getScale();
	Rect rect( _worldPosition.x - contentSize.width * anchorPoint.x, _worldPosition.y - contentSize.height * anchorPoint.y, contentSize.width, contentSize.height );
	return rect.containsPoint( worldPosition );
}



unsigned int SingleDisplayView::GetPageIndex()
{
	return m_nPageIndex;
}



void SingleDisplayView::SetDirection( Direction eDirection )
{
	m_eDirection = eDirection;
	
	if ( m_eDirection == Direction::HORIZONTAL )
	{
		m_pTableView->setDirection( ScrollView::Direction::HORIZONTAL );
	}
	else
	{
		m_pTableView->setDirection( ScrollView::Direction::VERTICAL );
	}
}



SingleDisplayView::Direction SingleDisplayView::GetDirection()
{
	return m_eDirection;
}



SingleDisplayView::SwitchPageAction SingleDisplayView::GetSwitchPageAction()
{
	return m_eSwitchPageAction;
}



void SingleDisplayView::SetSwitchPageTime( float fTime )
{
	m_fSwitchPageTime = fTime;

	if ( m_fSwitchPageTime < 0.0f )
	{
		m_fSwitchPageTime = 0.0f;
	}
}



float SingleDisplayView::GetSwitchPageTime()
{
	return m_fSwitchPageTime;
}



void SingleDisplayView::SetFastScrollTime( unsigned int nMilliSecond )
{
	m_nFastScrollTime = nMilliSecond;
}



unsigned int SingleDisplayView::GetFastScrollTime()
{
	return m_nFastScrollTime;
}



void SingleDisplayView::SetFastScrollMinOffset( int nMinOffset )
{
	m_nFastScrollMinOffset = nMinOffset;
}



int SingleDisplayView::GetFastScrollMinOffset()
{
	return m_nFastScrollMinOffset;
}



bool SingleDisplayView::IsTouchIgnore()
{
	return m_isTouchIgnore;
}



void SingleDisplayView::ReloadData()
{
	if ( m_pTableView )
	{
		m_pTableView->reloadData();
	}
}



int SingleDisplayView::RemoveCellAtIndex( unsigned int nIndex )
{
	return 0;
}

#endif // #if ( ( defined( __SPS_GG__SUPPORT__COCOS ) ) && ( __SPS_GG__SUPPORT__COCOS ) )
