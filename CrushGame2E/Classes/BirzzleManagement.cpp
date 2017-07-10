#include "BirzzleManagement.h"

CBirzzleManagement::CBirzzleManagement()
{
	for (int nRow = 0; nRow < ROWS; nRow++)
	{
		for (int nCol = 0; nCol < COLS; nCol++)
		{
			m_pBirzzleMap[nRow][nCol] = NULL;
		}
	}
}

CBirzzleManagement::~CBirzzleManagement()
{
}

bool CBirzzleManagement::init()
{
	InitData();
	return true;
}


void CBirzzleManagement::InitData()
{
	for (int nRow = 0; nRow < ROWS; nRow++)
	{
		for (int nCol = 0; nCol < COLS; nCol++)
		{
			CreateBirzzle(nRow, nCol);
		}
	}
}

void CBirzzleManagement::CreateBirzzle(int nRow, int nCol)
{
	m_pBirzzle =  CBirzzle::create();

	int nBirzzleType = rand() % TOTAL_SP;
	m_pBirzzle->setBirzzleType(nBirzzleType);

	m_pBirzzle->setIsNeedRemove(false);
	m_pBirzzle->setRow(nRow);
	m_pBirzzle->setCol(nCol);

	m_pBirzzleMap[nRow][nCol] = m_pBirzzle;
}

CBirzzle* CBirzzleManagement::GetBirzzle(int nRow, int nCol)
{
	if (nRow < 0 || nRow > ROWS)
	{
		return NULL;
	}

	if (nCol < 0 || nCol > COLS)
	{
		return NULL;
	}

	return m_pBirzzleMap[nRow][nCol];
}

void CBirzzleManagement::GetColChain(CBirzzle *pBirzzle, std::list<CBirzzle *> &listChain)
{
	listChain.push_back(pBirzzle);

	int nNeighborCol = pBirzzle->getCol() - 1;

	while (nNeighborCol >= 0)
	{
		CBirzzle *pBirzzleNeighbor = m_pBirzzleMap[pBirzzle->getRow()][nNeighborCol];
		if (pBirzzleNeighbor
			&& (pBirzzleNeighbor->getBirzzleType() == pBirzzle->getBirzzleType())
			&& (!pBirzzleNeighbor->getIsNeedRemove()))
		{
			listChain.push_back(pBirzzleNeighbor);
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
		CBirzzle *pBirzzleNeighbor = m_pBirzzleMap[pBirzzle->getRow()][nNeighborCol];
		if (pBirzzleNeighbor
			&& (pBirzzleNeighbor->getBirzzleType() == pBirzzle->getBirzzleType())
			&& (!pBirzzleNeighbor->getIsNeedRemove()))
		{
			listChain.push_back(pBirzzleNeighbor);
			nNeighborCol++;
		}
		else
		{
			break;
		}

	}
}

void CBirzzleManagement::GetRowChain(CBirzzle *pBirzzle, std::list<CBirzzle *> &listChain)
{
	listChain.push_back(pBirzzle);

	//在当前列上向下循环遍历
	int nNeighborRow = pBirzzle->getRow() - 1;
	while (nNeighborRow >= 0)
	{
		CBirzzle *pBirzzleNeighbor = m_pBirzzleMap[nNeighborRow][pBirzzle->getCol()];
		if (pBirzzleNeighbor
			&& (pBirzzleNeighbor->getBirzzleType() == pBirzzle->getBirzzleType())
			&& (!pBirzzleNeighbor->getIsNeedRemove()))
		{
			listChain.push_back(pBirzzleNeighbor);
			nNeighborRow --;
		}
		else
		{
			break;
		}
	}
	
	//在当前列上向上循环遍历
	nNeighborRow = pBirzzle->getRow() + 1;
	while (nNeighborRow < ROWS)
	{
		CBirzzle *pBirzzleNeighbor = m_pBirzzleMap[nNeighborRow][pBirzzle->getCol()];

		if (pBirzzleNeighbor
			&& (pBirzzleNeighbor->getBirzzleType() == pBirzzle->getBirzzleType())
			&& (!pBirzzleNeighbor->getIsNeedRemove()))
		{
			listChain.push_back(pBirzzleNeighbor);
			nNeighborRow++;
		}
		else
		{
			break;
		}
	}
}

void CBirzzleManagement::BindMap(int nRow, int nCol, CBirzzle *pBirzzle)
{
	m_pBirzzleMap[nRow][nCol] = pBirzzle;
}

bool CBirzzleManagement::CheckIsAnimating()
{
	for (int nRow = 0; nRow < ROWS; nRow++)
	{
		for (int nCol = 0; nCol < COLS; nCol++)
		{
			if (m_pBirzzleMap[nRow][nCol] && m_pBirzzleMap[nRow][nCol]->getNumberOfRunningActions() > 0)
			{
				return true;
			}
		}
	}
	return false;
}

void CBirzzleManagement::CheckAndRemoveChain()
{
	CBirzzle *pBirzzle = NULL;
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

			if (NULL == pBirzzle)
			{
				continue;
			}

			if (pBirzzle->getIsNeedRemove())
			{
				continue;
			}

			std::list<CBirzzle *> listChainOfCol;
			GetColChain(pBirzzle, listChainOfCol);

			std::list<CBirzzle *> listChainOfRow;
			GetRowChain(pBirzzle, listChainOfRow);

			std::list<CBirzzle *> &listLonger = (listChainOfCol.size() > listChainOfRow.size()) ? listChainOfCol : listChainOfRow;
			if (listLonger.size() < 3)
			{
				continue;
			}

			std::list<CBirzzle *>::iterator itList;
			for (itList = listLonger.begin(); itList != listLonger.end(); itList++)
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

void CBirzzleManagement::RemoveBirzzle(int nRow, int nCol)
{
	m_pBirzzleMap[nRow][nCol] = NULL;
}