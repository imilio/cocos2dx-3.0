#include "GameLayer.h"
CGameLayer::CGameLayer()
{
	InitData();
}

CGameLayer::~CGameLayer()
{
	m_pBirMgmt->release();
}

void CGameLayer::InitData()
{
	m_pBirMgmt     = NULL;
	m_pBirzzle     = NULL;
	m_pBirzzleSrc  = NULL;
	m_pBirzzleDst  = NULL;
	m_LocationSrc  = Point(0, 0);
	m_LocationDst  = Point(0, 0);
	m_bTouchEnable = true;
	m_isAnimating  = true;
}

bool CGameLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	m_pBirMgmt = CBirzzleManagement::create();
	m_pBirMgmt->retain();

	for (int nRow = 0; nRow < ROWS; nRow++)
	{
		for (int nCol = 0; nCol < COLS; nCol++)
		{
			BindSprite(nRow, nCol);
		}
	}
	
	scheduleUpdate();

	// 触摸事件处理
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(CGameLayer::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(CGameLayer::onTouchMoved, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	return true;
}

void CGameLayer::BindSprite(int nRow, int nCol)
{
	int nZOrder = 10 - nRow;
	m_pBirzzle = m_pBirMgmt->GetBirzzle(nRow, nCol);

	if (NULL == m_pBirzzle)
	{
		return;
	}

	int nBirzzleType = m_pBirzzle->getBirzzleType();

	m_pBirzzle->BindSprite(Sprite::create(sprNormal[nBirzzleType]));
	m_pBirzzle->runAction(DropAnimation(nRow, nCol));
	this->addChild(m_pBirzzle, nZOrder);

}

Action* CGameLayer::DropAnimation(int nRow, int nCol)
{
	Size sizeVisible = Director::getInstance()->getVisibleSize();

	Point PositionStart = Point(SIDE + SPRITE_WIDTH * nCol + 42 + SPACE * nCol, SPRITE_HEIGHT * nRow + 48.5 + BUTTOM + sizeVisible.height / 2);
	Point PositionEnd = Point(SIDE + SPRITE_WIDTH * nCol + 42 + SPACE * nCol, SPRITE_HEIGHT * nRow + 48.5 + BUTTOM);
	m_pBirzzle->setPosition(PositionStart);

	float fSpeed = PositionStart.y / (1.5 * sizeVisible.height);

	return MoveTo::create(fSpeed, PositionEnd);

}

bool CGameLayer::onTouchBegan(Touch *touch, Event *unused)
{
	if (m_bTouchEnable)
	{
		m_LocationSrc = touch->getLocation();
		//根据location去获取在某行某列的精灵
		m_pBirzzleSrc = GetBirzzleFromLocation(&m_LocationSrc);

		if (NULL == m_pBirzzleSrc)
		{
			return false;
		}

		return true;
	}

	return m_bTouchEnable;
}

void CGameLayer::onTouchMoved(Touch *touch, Event *unused)
{
	if (NULL == m_pBirzzleSrc)
	{
		return;
	}

	m_LocationDst = touch->getLocation();

	int nRow = m_pBirzzleSrc->getRow();
	int nCol = m_pBirzzleSrc->getCol();

	float fHalfSpriteWidth = SPRITE_WIDTH / 2;
	float fHalfSpriteHeight = SPRITE_HEIGHT / 2;

	Rect rectUp = Rect(m_pBirzzleSrc->getPositionX() - fHalfSpriteWidth,
		               m_pBirzzleSrc->getPositionY() + fHalfSpriteHeight,
		               SPRITE_WIDTH,
		               SPRITE_HEIGHT);
	
	if (rectUp.containsPoint(m_LocationDst))
	{
		nRow++;
		if (nRow < ROWS)
		{
			m_pBirzzleDst = m_pBirMgmt->GetBirzzle(nRow, nCol);
			SwapBirzzle();
		}
		return;
	}

	Point left = Point(rectUp.getMinX(), rectUp.getMinY());
	Point up = Point(rectUp.getMaxX(), rectUp.getMaxY());

	Rect rectDown = Rect(m_pBirzzleSrc->getPositionX() - fHalfSpriteWidth,
	                     m_pBirzzleSrc->getPositionY() - (fHalfSpriteHeight * 3),
		                 SPRITE_WIDTH,
		                 SPRITE_HEIGHT);
	
	if (rectDown.containsPoint(m_LocationDst))
	{
		nRow--;
		if (nRow >= 0)
		{
			m_pBirzzleDst = m_pBirMgmt->GetBirzzle(nRow, nCol);
			SwapBirzzle();
		}
		return;
	}

	Rect rectLeft = Rect(m_pBirzzleSrc->getPositionX() - (fHalfSpriteWidth * 3),
		                 m_pBirzzleSrc->getPositionY() - fHalfSpriteHeight ,
		                 SPRITE_WIDTH,
		                 SPRITE_HEIGHT);

	if (rectLeft.containsPoint(m_LocationDst))
	{
		nCol--;
		if (nCol >= 0)
		{
			m_pBirzzleDst = m_pBirMgmt->GetBirzzle(nRow, nCol);
			SwapBirzzle();
		}
		return;
	}

	Rect rectRight = Rect(m_pBirzzleSrc->getPositionX() + fHalfSpriteWidth,
		                  m_pBirzzleSrc->getPositionY() - fHalfSpriteHeight,
		                  SPRITE_WIDTH,
		                  SPRITE_HEIGHT);

	if (rectRight.containsPoint(m_LocationDst))
	{
		nCol++;
		if (nCol < COLS)
		{
			m_pBirzzleDst = m_pBirMgmt->GetBirzzle(nRow, nCol);
			SwapBirzzle();
		}
		return;
	}
	return;
}

CBirzzle* CGameLayer::GetBirzzleFromLocation(Point *pLocation)
{
	Rect rect = Rect(0, 0, 0, 0);

	float fHalfSpriteWidth = SPRITE_WIDTH / 2;
	float fHalfSpriteHeight = SPRITE_HEIGHT / 2;

	for (int nRow = 0; nRow < ROWS; nRow++)
	{
		for (int nCol = 0; nCol < COLS; nCol++)
		{
			CBirzzle *pBirzzle = m_pBirMgmt->GetBirzzle(nRow, nCol);

			if (NULL == pBirzzle)
			{
				continue;
			}

			Point BirzzlePosition = pBirzzle->getPosition();

			rect.setRect(BirzzlePosition.x - fHalfSpriteWidth, BirzzlePosition.y - fHalfSpriteHeight, SPRITE_WIDTH, SPRITE_HEIGHT);

			if (rect.containsPoint(*pLocation))
			{
				return pBirzzle;
			}
		}
	}
	return NULL;
}

void CGameLayer::SwapBirzzle()
{
	if (!m_bTouchEnable)
	{
		return;
	}

	m_bTouchEnable = false;

	MoveTo *pMoveToDst = MoveTo::create(0.5f, m_pBirzzleDst->getPosition());
	MoveTo *pMoveToSrc = MoveTo::create(0.5f, m_pBirzzleSrc->getPosition());

	auto callFunc = CallFunc::create([&]()
	{
		m_bTouchEnable = true;
		m_isAnimating  = false;
	});

	int nSrcRow = m_pBirzzleSrc->getRow();
	int nSrcCol = m_pBirzzleSrc->getCol();

	int nDstRow = m_pBirzzleDst->getRow();
	int nDstCol = m_pBirzzleDst->getCol();

	int nTempZOrder = m_pBirzzleDst->getZOrder();
	m_pBirzzleDst->setZOrder(m_pBirzzleSrc->getZOrder());
	m_pBirzzleSrc->setZOrder(nTempZOrder);

	m_pBirzzleSrc->setRow(nDstRow);
	m_pBirzzleSrc->setCol(nDstCol);

	m_pBirzzleDst->setRow(nSrcRow);
	m_pBirzzleDst->setCol(nSrcCol);

	m_pBirMgmt->BindMap(nSrcRow, nSrcCol, m_pBirzzleDst);
	m_pBirMgmt->BindMap(nDstRow, nDstCol, m_pBirzzleSrc);

	std::list<CBirzzle *> listChainSrcCol;
	m_pBirMgmt->GetColChain(m_pBirzzleSrc, listChainSrcCol);

	std::list<CBirzzle *> listChainSrcRow;
	m_pBirMgmt->GetRowChain(m_pBirzzleSrc, listChainSrcRow);

	std::list<CBirzzle *> listChainDstCol;
	m_pBirMgmt->GetColChain(m_pBirzzleDst, listChainDstCol);

	std::list<CBirzzle *> listChainDstRow;
	m_pBirMgmt->GetRowChain(m_pBirzzleDst, listChainDstRow);

	if (listChainSrcCol.size() >= 3 || listChainSrcRow.size() >= 3 || listChainDstCol.size() >= 3 || listChainDstRow.size() >= 3)
	{
		auto MoveToDstActions = Sequence::create(pMoveToDst, callFunc, NULL);
		auto MoveToSrcActions = Sequence::create(pMoveToSrc, NULL);

		m_pBirzzleSrc->runAction(MoveToDstActions);
		m_pBirzzleDst->runAction(MoveToSrcActions);

		m_pBirzzleDst = NULL;
		return;
	}
	else
	{
		//回到原来的位置
		m_bTouchEnable = false;

		m_pBirzzleSrc->runAction(Sequence::create(pMoveToDst, pMoveToSrc, callFunc, NULL));
		m_pBirzzleDst->runAction(Sequence::create(pMoveToSrc, pMoveToDst, NULL));

		int nTempZOrder = m_pBirzzleSrc->getZOrder();
		m_pBirzzleSrc->setZOrder(m_pBirzzleDst->getZOrder());
		m_pBirzzleDst->setZOrder(nTempZOrder);

		m_pBirzzleSrc->setRow(nSrcRow);
		m_pBirzzleSrc->setCol(nSrcCol);

		m_pBirzzleSrc->setRow(nDstRow);
		m_pBirzzleDst->setCol(nDstCol);

		m_pBirMgmt->BindMap(nSrcRow, nSrcCol, m_pBirzzleSrc);
		m_pBirMgmt->BindMap(nDstRow, nDstRow, m_pBirzzleDst);

		m_pBirzzleDst = NULL;

	}
}

void CGameLayer::update(float dt)
{

	if (m_isAnimating)
	{
		m_isAnimating = false;

		for (int nRow = 0; nRow < ROWS; nRow++)
		{
			for (int nCol = 0; nCol < COLS; nCol++)
			{
				CBirzzle *pBirzzle = m_pBirMgmt->GetBirzzle(nRow, nCol);
				if (pBirzzle && pBirzzle->getNumberOfRunningActions() > 0)
				{
					m_isAnimating = true;
					break;
				}
			}
		}
	}

	m_bTouchEnable = !m_isAnimating;

	if (!m_isAnimating)  
	{
		m_pBirMgmt->CheckAndRemoveChain();
		RemoveBirzzle();
		FillEmptyMap();
	}
}

void CGameLayer::RemoveBirzzle()
{
	m_isAnimating = true;

	CBirzzle *pBirzzle = NULL;

	for (int nRow = 0; nRow < ROWS; nRow++)
	{
		for (int nCol = 0; nCol < COLS; nCol++)
		{
			pBirzzle = m_pBirMgmt->GetBirzzle(nRow, nCol);

			if (!pBirzzle)
			{
				continue;
			}

			if (pBirzzle->getIsNeedRemove())
			{
				float time = 0.3;

				pBirzzle->runAction(Sequence::create(
					ScaleTo::create(time, 0.0),
					CallFuncN::create(CC_CALLBACK_1(CGameLayer::ActionEndCallback, this)),
					NULL));
			}
		}
	}
}

void CGameLayer::ActionEndCallback(Node *node)
{
	CBirzzle *pBirzzle = (CBirzzle *)node;
	m_pBirMgmt->RemoveBirzzle(pBirzzle->getRow(), pBirzzle->getCol());
	pBirzzle->removeFromParent();
}

void CGameLayer::FillEmptyMap()
{
	m_isAnimating = true;

	CBirzzle *pBirzzle = NULL;

	int nCountEmptyBlank[7] = { 0 };
	
	for (int nCol = 0; nCol < COLS; nCol++)
	{
		for (int nRow = 0; nRow < ROWS; nRow++)
		{
			pBirzzle = m_pBirMgmt->GetBirzzle(nRow, nCol);
			if (NULL == pBirzzle)
			{
				nCountEmptyBlank[nCol]++;
			}
			else
			{
				if (nCountEmptyBlank[nCol] > 0)
				{
					int nNewRow = nRow - nCountEmptyBlank[nCol];
					m_pBirMgmt->BindMap(nNewRow, nCol, pBirzzle);
					m_pBirMgmt->BindMap(nRow, nCol, NULL);
					pBirzzle->stopAllActions();
					pBirzzle->runAction(DescendActionAfterRemove(nCountEmptyBlank[nCol], pBirzzle));

					int nCurrentZOrder = pBirzzle->getZOrder();

					pBirzzle->setZOrder(nCurrentZOrder + nCountEmptyBlank[nCol]);
					pBirzzle->setRow(nNewRow);
				}
			}
		}
	}

	for (int nCol = 0; nCol < COLS; nCol++)
	{
		for (int nRow = ROWS - nCountEmptyBlank[nCol]; nRow < ROWS; nRow++)
		{
			m_pBirMgmt->CreateBirzzle(nRow, nCol);
			BindSprite(nRow, nCol);
		}
	}
}

Action* CGameLayer::DescendActionAfterRemove(int nBlanks, CBirzzle *pBirzzle)
{
	Size sizeVisible = Director::getInstance()->getVisibleSize();

	Point positionStart = pBirzzle->getPosition();
	Point positionEnd   = Point(pBirzzle->getPositionX(), pBirzzle->getPositionY() - nBlanks * SPRITE_HEIGHT);
	
	float fSpeed = positionStart.y / (1.5 * sizeVisible.height);

	return MoveTo::create(fSpeed, positionEnd);
}