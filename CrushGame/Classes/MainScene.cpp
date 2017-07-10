#include "MainScene.h"
#include "birzzle.h"
CMainScene::CMainScene()
{
	GameInit();
}

void CMainScene::GameInit()
{
	m_bTouchEnable		= true;
	m_isAnimationing    = true;
	m_pDstBirzzle       = NULL;
	m_pSrcBirzzle       = NULL;
	m_pBgSprite         = NULL;
	m_SrcLocation       = Point(0,0);
	m_DstLocation       = Point(0,0);
	memset(m_pBirzzleMap[ROWS * COLS], NULL, sizeof(m_pBirzzle));
}

Scene *CMainScene::createScene()
{
	auto scene = Scene::create();

	auto layer = CMainScene::create();

	scene->addChild(layer);

	return scene;
}

bool CMainScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();

	m_pBgSprite = Sprite::create("Background.png");
	m_pBgSprite->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(m_pBgSprite, 0);

	m_pBgSprite = Sprite::create("stage_bg_landscape_RGB_RETINA.png");
	m_pBgSprite->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	m_pBgSprite->setScaleX(0.95f);
	m_pBgSprite->setScaleY(0.98f);
	this->addChild(m_pBgSprite, 0);

	// 触摸事件处理
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(CMainScene::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(CMainScene::onTouchMoved, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	int nZOrder = 10;

	for (int nRow = 0; nRow < ROWS; nRow++)
	{
		for (int nCol = 0; nCol < COLS; nCol++)
		{
			CreateSprite(nRow, nCol, nZOrder);
		}
	nZOrder--;
	}
	
	scheduleUpdate();
	return true;
}

void CMainScene::CreateSprite(int nDstRow, int nDstCol, int nZOrder)
{
	log("initMap : %x", m_pBirzzleMap[nDstRow][nDstCol]);


	int nBirzzleType = rand() % TOTAL_SP;
	m_pBirzzle = CBirzzle::create();
	m_pBirzzle->BindSprite(Sprite::create(sprNormal[nBirzzleType]));
	m_pBirzzle->setBirzzleType(nBirzzleType);
	m_pBirzzle->runAction(DescendAction(nDstRow, nDstCol));
	m_pBirzzle->setIsNeedRemove(false);
	m_pBirzzle->setRow(nDstRow);
	m_pBirzzle->setCol(nDstCol);
	m_pBirzzleMap[nDstRow][nDstCol] = m_pBirzzle;
	log("After Assignment BirzzleMap : %x", m_pBirzzleMap[nDstRow][nDstCol]);
	log("m_pBirzzle: %x", m_pBirzzle);
	
	this->addChild(m_pBirzzle, nZOrder);
}

Action* CMainScene::DescendAction(int nDstRow, int nDstCol)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	Point startPosition = Point(SIDE + SPRITE_WIDTH * nDstCol + 42 + SPACE * nDstCol, SPRITE_HEIGHT * nDstRow + 48.5 + BUTTOM + visibleSize.height / 2);
	Point endPosition = Point(SIDE + SPRITE_WIDTH * nDstCol + 42 + SPACE * nDstCol, SPRITE_HEIGHT * nDstRow + 48.5 + BUTTOM);
	m_pBirzzle->setPosition(startPosition);

	float speed = startPosition.y / (1.5 * visibleSize.height);

	return MoveTo::create(speed, endPosition);
}

bool CMainScene::onTouchBegan(Touch *touch, Event *unused)
{
	if (m_bTouchEnable)
	{
		m_SrcLocation = touch->getLocation();
		//根据location去获取在某行某列的精灵
		m_pSrcBirzzle = GetBirzzleFromLocation(&m_SrcLocation);

		if (NULL == m_pSrcBirzzle)
		{
			return false;
		}

		int nRow = m_pSrcBirzzle->getRow();
		int nCol = m_pSrcBirzzle->getCol();

		log("nRow: %d,nCol:%d", nRow, nCol);
		return true;


	}
	return m_bTouchEnable;

}

void CMainScene::onTouchMoved(Touch *touch, Event *unused)
{
	if (NULL == m_pSrcBirzzle)
	{
		return;
	}

	m_DstLocation = touch->getLocation();
	
	int nRow = m_pSrcBirzzle->getRow();
	int nCol = m_pSrcBirzzle->getCol();


	//设置一定范围的长方形，如果落入该方向的方形内，就确定相应的移动方向
	auto halfSpriteWidth = SPRITE_WIDTH / 2;
	auto halfSpriteHeight = SPRITE_HEIGHT / 2;
	auto  UpRect  = Rect(m_pSrcBirzzle->getPositionX() - halfSpriteWidth,           //上方框位置定义
						 m_pSrcBirzzle->getPositionY() + halfSpriteHeight,
						 SPRITE_WIDTH,
						 SPRITE_HEIGHT);
	
	if (UpRect.containsPoint(m_DstLocation))
	{
		nRow++;
		if (nRow < ROWS)
		{
			m_pDstBirzzle = m_pBirzzleMap[nRow][nCol];
			SwapSprite();
		}
		log("upRow:%d",nRow);
		return;
	}

	auto DownRect = Rect(m_pSrcBirzzle->getPositionX() - halfSpriteWidth,           //下方框位置定义
						 m_pSrcBirzzle ->getPositionY() - (halfSpriteHeight * 3),
						 SPRITE_WIDTH,
						 SPRITE_HEIGHT);

	if (DownRect.containsPoint(m_DstLocation))
	{
		nRow--;
		if (nRow >= 0)
		{
			m_pDstBirzzle = m_pBirzzleMap[nRow][nCol];
			SwapSprite();
		}
		log("downRow:%d",nRow);
		return;
	}

	auto LeftRect = Rect(m_pSrcBirzzle->getPositionX() - (halfSpriteWidth * 3),            //左方框位置定义
						 m_pSrcBirzzle->getPositionY() - halfSpriteHeight,
						 SPRITE_WIDTH,
		                 SPRITE_HEIGHT);

	if (LeftRect.containsPoint(m_DstLocation))
	{

		nCol--;
		if (nCol >= 0)
		{
			m_pDstBirzzle = m_pBirzzleMap[nRow][nCol];
			SwapSprite();
		}
		log("leftCol:%d",nCol);
		return;
	}

	auto RightRect = Rect(m_pSrcBirzzle->getPositionX() + halfSpriteWidth,             //右方框位置定义
						  m_pSrcBirzzle->getPositionY() - halfSpriteHeight,
						 SPRITE_WIDTH,
						 SPRITE_HEIGHT);
	
	if (RightRect.containsPoint(m_DstLocation))
	{

		nCol++;
		if (nCol < COLS)
		{
			m_pDstBirzzle = m_pBirzzleMap[nRow][nCol];
			SwapSprite();
		}
		log("rightCol:%d",nCol);
		return;
	}

	return;

}

CBirzzle *CMainScene::GetBirzzleFromLocation(Point *pLocation)
{
	Rect rect = Rect(0,0,0,0);

	auto HalfSpriteWidth = SPRITE_WIDTH / 2;
	auto HalfSpriteHeight = SPRITE_HEIGHT / 2;

	for (int nRow = 0; nRow < ROWS; nRow++)
	{
		for (int nCol = 0; nCol < COLS; nCol++)
		{
			if (NULL == m_pBirzzleMap[nRow][nCol])
			{
				continue;
			}
			Point BirzzlePosition = Point(m_pBirzzleMap[nRow][nCol]->getPositionX(), m_pBirzzleMap[nRow][nCol]->getPositionY());
			
			rect.setRect(BirzzlePosition.x - HalfSpriteWidth, BirzzlePosition.y - HalfSpriteHeight, SPRITE_WIDTH, SPRITE_HEIGHT);

			if (rect.containsPoint(*pLocation))
			{
				return m_pBirzzleMap[nRow][nCol];
			}

		}
	}
	return NULL;
}

void  CMainScene::SwapSprite()
{
	if (!m_bTouchEnable)
	{
		return ;
	}

	m_bTouchEnable = false;
	
	MoveTo *pMoveToDst = MoveTo::create(0.5f, Point(m_pDstBirzzle->getPositionX(), m_pDstBirzzle->getPositionY()));
	MoveTo *pMoveToSrc = MoveTo::create(0.5f, Point(m_pSrcBirzzle->getPositionX(), m_pSrcBirzzle->getPositionY()));

	auto callFunc = CallFunc::create([&]()   //动作结束后改标记
	{
		m_bTouchEnable = true;
		m_isAnimationing = false;
	});

	int nSrcRow = m_pSrcBirzzle->getRow();
	int nSrcCol = m_pSrcBirzzle->getCol();

	int nDstRow = m_pDstBirzzle->getRow();
	int nDstCol = m_pDstBirzzle->getCol();

	int nTempZOrder = m_pDstBirzzle->getZOrder();
	m_pDstBirzzle->setZOrder(m_pSrcBirzzle->getZOrder());
	m_pSrcBirzzle->setZOrder(nTempZOrder);

	m_pSrcBirzzle->setRow(nDstRow);
	m_pSrcBirzzle->setCol(nDstCol);

	m_pDstBirzzle->setRow(nSrcRow);
	m_pDstBirzzle->setCol(nSrcCol);

	m_pBirzzleMap[nSrcRow][nSrcCol] = m_pDstBirzzle;
	m_pBirzzleMap[nDstRow][nDstCol] = m_pSrcBirzzle;

	std::list<CBirzzle *> SrcColChainList;
	GetColChain(m_pSrcBirzzle, SrcColChainList);

	std::list<CBirzzle *> SrcRowChainList;
	GetRowChain(m_pSrcBirzzle, SrcRowChainList);

	std::list<CBirzzle *> DstColChainList;
	GetColChain(m_pDstBirzzle, DstColChainList);

	std::list<CBirzzle *> DstRowChainList;
	GetRowChain(m_pDstBirzzle, DstRowChainList);

	if (SrcColChainList.size() >= 3 || SrcRowChainList.size() >= 3 || DstColChainList.size() >= 3 || DstRowChainList.size() >= 3)
	{
		auto MoveToDstActions = Sequence::create(pMoveToDst, callFunc, NULL);
		auto MoveToSrcActions = Sequence::create(pMoveToSrc, NULL);

		m_pSrcBirzzle->runAction(MoveToDstActions);
		m_pDstBirzzle->runAction(MoveToSrcActions);

		return;
	}
	else
	{   
		//回到原来的位置
		m_bTouchEnable = false;

		m_pSrcBirzzle->runAction(Sequence::create(pMoveToDst, pMoveToSrc, callFunc, NULL));
		m_pDstBirzzle->runAction(Sequence::create(pMoveToSrc, pMoveToDst, NULL));

		int nTempZOrder = m_pSrcBirzzle->getZOrder();
		m_pSrcBirzzle->setZOrder(m_pDstBirzzle->getZOrder());
		m_pDstBirzzle->setZOrder(nTempZOrder);

		m_pSrcBirzzle->setRow(nSrcRow);
		m_pSrcBirzzle->setCol(nSrcCol);

		m_pDstBirzzle->setRow(nDstRow);
		m_pDstBirzzle->setCol(nDstCol);

		m_pBirzzleMap[nSrcRow][nSrcCol] = m_pSrcBirzzle;
		m_pBirzzleMap[nDstRow][nDstCol] = m_pDstBirzzle;
	}
}
void CMainScene::update(float dt)
{
	//检测游戏场景中是否有Actions
	if (m_isAnimationing)
	{
		//初始化m_isAnimationing
		m_isAnimationing = false;
		//依次检测每个寿司，看他们是否正在执行某个Action
		for (int nRow = 0; nRow < ROWS; nRow++)
		{
			for (int nCol = 0; nCol < COLS; nCol++)
			{
				if (m_pBirzzleMap[nRow][nCol] && m_pBirzzleMap[nRow][nCol]->getNumberOfRunningActions() > 0)
				{
					m_isAnimationing = true;
					break;
				}
			}
		}
	}

	//如果寿司正在移动，忽略触摸事件
	m_bTouchEnable = !m_isAnimationing;

	//当没有任何寿司执行Action时，检测和删除满足消除条件的精灵
	if (!m_isAnimationing)
	{
		CheckAndRemoveChain();
		RemoveBirzzle();
		FillEmptyMap();
	}

}

void CMainScene::CheckAndRemoveChain()
{
	CBirzzle *pBirzzle;

	for (int nRow = 0; nRow < ROWS; nRow++)
	{
		for (int nCol = 0; nCol < COLS; nCol++)
		{
			pBirzzle = m_pBirzzleMap[nRow][nCol];
			if (!pBirzzle)
			{
				continue;
			}
		}
	}

	for (int nRow = 0; nRow < ROWS; nRow++)
	{
		for (int nCol = 0; nCol < COLS; nCol++)
		{
			pBirzzle = m_pBirzzleMap[nRow][nCol];
			if (!pBirzzle)
			{
				continue;
			}

			if (pBirzzle->getIsNeedRemove())
			{
				continue;	//已标记过的跳过检查
			}

			std::list<CBirzzle *> colChainList;
			GetColChain(pBirzzle, colChainList);

			std::list<CBirzzle *> rowChainList;
			GetRowChain(pBirzzle, rowChainList);

			std::list<CBirzzle *> &longerList = colChainList.size() > rowChainList.size() ? colChainList : rowChainList;
			if (longerList.size() < 3)
			{
				continue;   //小于3个不消除
			}

			std::list<CBirzzle *>::iterator itList;
			bool isSetedIgnoreCheck = false;
			for (itList = longerList.begin(); itList != longerList.end(); itList++)
			{
				pBirzzle = (CBirzzle *)*itList;

				if (!pBirzzle)
				{
					continue;
				}
				
				pBirzzle->setIsNeedRemove(true);
			}
		}
	}

}

void CMainScene::GetColChain(CBirzzle *pBirzzle, std::list<CBirzzle *> &chainList)
{
	chainList.push_back(pBirzzle);

	int nNeighborCol = pBirzzle->getCol() - 1;

	while (nNeighborCol >= 0)
	{
		CBirzzle *neighborBirzzle = m_pBirzzleMap[pBirzzle->getRow()][nNeighborCol];
		if (neighborBirzzle
			&& (neighborBirzzle->getBirzzleType() == pBirzzle->getBirzzleType())
			&& (!neighborBirzzle->getIsNeedRemove()))
		{
			chainList.push_back(neighborBirzzle);
			nNeighborCol--;
		}
		else
		{
			break;
		}
	}
	nNeighborCol = pBirzzle->getCol() + 1;

	while (nNeighborCol < COLS)
	{
		CBirzzle *neighborBirzzle = m_pBirzzleMap[pBirzzle->getRow()][nNeighborCol];
		if (neighborBirzzle
			&& (neighborBirzzle->getBirzzleType() == pBirzzle->getBirzzleType())
			&& (!neighborBirzzle->getIsNeedRemove()))
		{
			chainList.push_back(neighborBirzzle);
			nNeighborCol++;
		}
		else
		{
			break;
		}
	}
}

void CMainScene::GetRowChain(CBirzzle *pBirzzle, std::list<CBirzzle *> &chainlist)
{
	chainlist.push_back(pBirzzle);

	int nNeighborRow = pBirzzle->getRow() - 1;
	while (nNeighborRow >= 0)
	{
		CBirzzle *pNeighborBirzzle = m_pBirzzleMap[nNeighborRow][pBirzzle->getCol()];
		if (pNeighborBirzzle
			&& (pNeighborBirzzle->getBirzzleType() == pBirzzle->getBirzzleType())
			&& (!pNeighborBirzzle->getIsNeedRemove()))
		{
			chainlist.push_back(pNeighborBirzzle);
			nNeighborRow--;
		}
		else
		{
			break;
		}
	}

	nNeighborRow = pBirzzle->getRow() + 1;
	while (nNeighborRow < ROWS)
	{
		CBirzzle *nNeighborBirzzle = m_pBirzzleMap[nNeighborRow][pBirzzle->getCol()];
		if (nNeighborBirzzle
			&& (nNeighborBirzzle->getBirzzleType() == pBirzzle->getBirzzleType())
			&& (!nNeighborBirzzle->getIsNeedRemove()))
		{
			chainlist.push_back(nNeighborBirzzle);
			nNeighborRow++;
		}
		else
		{
			break;
		}
	}
 }

void CMainScene::RemoveBirzzle()
{
	m_isAnimationing = true;

	for (int nRow = 0; nRow < ROWS; nRow++)
	{
		for (int nCol = 0; nCol < COLS; nCol++)
		{
			CBirzzle *pBirzzle = m_pBirzzleMap[nRow][nCol];
			if (!pBirzzle)
			{
				continue;
			}

			if (pBirzzle->getIsNeedRemove())
			{
				float time = 0.3;

				pBirzzle->runAction(Sequence::create(
					                                 ScaleTo::create(time, 0.0),
													 CallFuncN::create(CC_CALLBACK_1(CMainScene::ActionEndCallback, this)),
													 NULL));
			}
		}
	}
}

void CMainScene::ActionEndCallback(Node *node)
{
	CBirzzle *pBirzzle = (CBirzzle *)node;
	m_pBirzzleMap[pBirzzle->getRow()][pBirzzle->getCol()] = NULL;
	pBirzzle->removeFromParent();
	
}

void CMainScene::FillEmptyMap()
{
	m_isAnimationing = true;

	int nCountEmptyBlank[7] = {0};
	for (int nCol = 0; nCol < COLS; nCol++)
	{
		for (int nRow = 0; nRow < ROWS; nRow++)
		{
			CBirzzle *pBirzzle = m_pBirzzleMap[nRow][nCol];
			if (NULL == pBirzzle)
			{
				nCountEmptyBlank[nCol]++;
			}
			else
			{
				if (nCountEmptyBlank[nCol] > 0)
				{
					int nNewRow                         = nRow - nCountEmptyBlank[nCol];
					m_pBirzzleMap[nNewRow][nCol]        = pBirzzle;
					m_pBirzzleMap[nRow][nCol]           = NULL;
					pBirzzle->stopAllActions();// must stop pre drop action
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
			CreateSprite(nRow, nCol, 10 - nRow);
		}
	}
}
void CMainScene::DescendActionEndCallback(Node *node)
{
	CBirzzle *pBirzzle = (CBirzzle *)node;
	m_pBirzzleMap[pBirzzle->getRow()][pBirzzle->getCol()] = NULL;
}

Action* CMainScene::DescendActionAfterRemove(int nBlanks, CBirzzle *pBirzzle)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Point startPosition = pBirzzle->getPosition();
	Point endPosition = Point(pBirzzle->getPositionX(), pBirzzle->getPositionY() - nBlanks * SPRITE_HEIGHT);

	float speed = startPosition.y / (1.5 * visibleSize.height);

	return MoveTo::create(speed, endPosition);
}