#include "TexasPokerRule.h"

//==================================================================
//函数名： CompareOfVector
//功能：   指定基于结构体的nRank进行排序
//输入参数：    无
//返回值：    无
//修改记录：
//==================================================================
bool CompareOfVector(const Card *a, const Card *b)
{
	return (a->nRank < b->nRank);
}

void CTexasPokerRule::PushCard(Card *pCard)
{
	m_vecCards.push_back(pCard);
}

void CTexasPokerRule::Show()
{
	vector<Card *>::iterator itVect;
	for (itVect = m_vecCards.begin(); itVect != m_vecCards.end(); itVect++)
	{
		Card *pCard = (Card *)*itVect;
		cout << pCard->nCard << "\t" << pCard->sSuit << "\t" << pCard->cRank << endl;
	}
}

//==================================================================
//函数名： SortVector
//功能：   对m_vecCards根据牌面的点数排序
//输入参数：    无
//返回值：    无
//修改记录：
//==================================================================
void CTexasPokerRule::SortVector()
{
	sort(m_vecCards.begin(), m_vecCards.end(), CompareOfVector);
}

//==================================================================
//函数名： Judgement
//功能：   对包含5张牌的容器vector，判断是否两两相等
//输入参数：    无
//返回值：    int nCount:计算两两相等的对数
//修改记录：
//==================================================================
//int CTexasPokerRule::Judgement()
//{
//	int nCount = 0;
//	vector<Card *>::iterator itVect;
//	for (itVect = m_vecCards.begin(); itVect != m_vecCards.end(); itVect++)
//	{
//		
//		Card *pCard = (Card *)*itVect;
//		m_vecTempForJudgement.push_back(pCard);
//		itVect++;
//
//		if (itVect != m_vecCards.end())
//		{
//			Card *pCard = (Card *)*itVect;
//			m_vecTempForJudgement.push_back(pCard);
//			if (this->Pair())
//			{
//				nCount++;
//			}
//		}
//		m_vecTempForJudgement.clear();
//		itVect--;
//	}
//	return nCount;
//}

Patterns CTexasPokerRule::Judge()
{
	if (5 == m_vecCards.size())
	{
		m_vecTempForJudgement = m_vecCards;

		return this->Judgement();
	}
	else if (5 < m_vecCards.size())    //大于5就开始排列组合判断
	{
		return this->Permutation(m_vecTempForJudgement);
	}
	
	

}

Patterns CTexasPokerRule::Judgement()
{
	if (this->TtoA(m_vecTempForJudgement) && this->Flush(m_vecTempForJudgement))  //皇家同花顺
	{
		return ROYAL_FLUSH;
	}
	else if (this->Straight(m_vecTempForJudgement) && this->Flush(m_vecTempForJudgement))  //同花顺
	{
		return STRAIGHT_FLUSH;
	}
	else if (this->Quads(m_vecTempForJudgement))   //4条
	{
		return QUADS;
	}
	else if (this->Flush(m_vecTempForJudgement))  //同花
	{
		return FLUSH;
	}
	else if (this->Straight(m_vecTempForJudgement))  //顺子
	{
		return STRAIGHT;
	}
	else if (this->Trips(m_vecTempForJudgement))    
	{
		if (this->Pair(m_vecTempForJudgement))    //判断剩下的两张牌是不是一对
		{
			return FULL_HOUSE;       //葫芦
		}
		else
		{
			return TRIPS;    //三条
		}
	}
	else if (this->Pair(m_vecTempForJudgement))
	{
		if (this->Pair(m_vecTempForJudgement))
		{
			return TWO_PAIR;  //两对
		}
		else
		{
			return ONE_PAIR;  //一对
		}
	}
	return NO_PAIR;   //高牌
}

Patterns CTexasPokerRule::Permutation(vector<Card *> &vecCards)
{
	vector<Patterns> vecJudgement;
	int nVecSize = m_vecCards.size();

	for (int i = nVecSize - 1; i >= 0; i--)
	{
		for (int j = i - 1; j >= 0; j--)
		{
			for (int k = j - 1; k >= 0; k--)
			{
				for (int m = k - 1; m >= 0; m--)
				{
					for (int n = m - 1; n >= 0; n--)
					{
						if (!vecCards.empty())
						{
							vecCards.clear();
						}
						vecCards.push_back(m_vecCards.at(i));
						vecCards.push_back(m_vecCards.at(j));
						vecCards.push_back(m_vecCards.at(k));
						vecCards.push_back(m_vecCards.at(m));
						vecCards.push_back(m_vecCards.at(n));
						vecJudgement.push_back(this->Judgement());
					}
				}
			}
		}
	}
	sort(vecJudgement.begin(), vecJudgement.end());
	return vecJudgement.at(vecJudgement.size() - 1);
}
//==================================================================
//函数名： Pair
//功能：   判断临时存储vector里面的两张牌的点数是否相等
//输入参数：    无
//返回值：    bool:两张牌的点数相等则返回true
//修改记录：
//==================================================================
bool CTexasPokerRule::Pair(vector<Card *> &vecCards)
{
	int i = 0;
	int j = 0;

	Card *pFirCard = NULL;
	Card *pSecCard = NULL;

	int nVecSize = vecCards.size();

	for (i = nVecSize - 1; i >= 0; i--)
	{
		for (j = i - 1; j >= 0; j--)
		{
			pFirCard = vecCards.at(i);
			pSecCard = vecCards.at(j);

			if (pFirCard->cRank == pSecCard->cRank)
			{
				vector<Card *>::iterator itVecFir = vecCards.begin() + i;
				vector<Card *>::iterator itVecSec = vecCards.begin() + j;
				
				vecCards.erase(itVecFir);
				vecCards.erase(itVecSec);

				return true;
			}
		}
	}
	return false;
}

//==================================================================
//函数名： Trips
//功能：   判断是否为三条
//输入参数：    无
//返回值：    bool:存在三条则返回true
//修改记录：
//==================================================================
bool CTexasPokerRule::Trips(vector<Card *> &vecCards)
{
	int i = 0;
	int j = 0;
	int k = 0;

	Card *pFirCard = NULL;
	Card *pSecCard = NULL;
	Card *pThiCard = NULL;

	int nVecSize = vecCards.size();

	for (i = nVecSize - 1; i >= 0; i--)
	{
		for (j = i - 1; j >= 0; j--)
		{
			for (k = j - 1; k >= 0; k--)
			{

				pFirCard = vecCards.at(i);
				pSecCard = vecCards.at(j);
				pThiCard = vecCards.at(k);

				if ((pFirCard->cRank == pSecCard->cRank)
					&& (pSecCard->cRank == pThiCard->cRank))
				{
					vector<Card *>::iterator itVecFir = vecCards.begin() + i;
					vector<Card *>::iterator itVecSec = vecCards.begin() + j;
					vector<Card *>::iterator itVecThi = vecCards.begin() + k;

					vecCards.erase(itVecFir);
					vecCards.erase(itVecSec);
					vecCards.erase(itVecThi);
					return true;
				}
			}
		}
	}

	return false;
}

//==================================================================
//函数名： Quads
//功能：   判断是否为四条
//输入参数：    无
//返回值：    bool:存在四条则返回true
//修改记录：
//==================================================================
bool CTexasPokerRule::Quads(vector<Card *> vecCards)
{
	int i = 0;
	int j = 0;
	int m = 0;
	int n = 0;

	Card *pFirCard = NULL;
	Card *pSecCard = NULL;
	Card *pThiCard = NULL;
	Card *pFouCard = NULL;

	int nVecSize = vecCards.size();

	for (i = nVecSize - 1; i >= 0; i--)
	{
		for (j = i - 1; j >= 0; j--)
		{
			for (m = j - 1; m >= 0; m--)
			{
				for (n = m - 1; n >= 0; n--)
				{
					pFirCard = m_vecCards.at(i);
					pSecCard = m_vecCards.at(j);
					pThiCard = m_vecCards.at(m);
					pFouCard = m_vecCards.at(n);
					
					if ((pFirCard->cRank == pSecCard->cRank)
						&& (pSecCard->cRank == pThiCard->cRank)
						&& (pThiCard->cRank == pFouCard->cRank))
					{
						return true;
					}
				}
			}
		}
	}

	return false;
}

//==================================================================
//函数名： Straight
//功能：   判断是否为顺子
//输入参数：    vector<Card *> vecCards:只有5个元素的容器
//返回值：    bool:是顺子则返回true
//修改记录：
//==================================================================
bool CTexasPokerRule::Straight(vector<Card *> vecCards)
{
	if (this->TtoA(vecCards))
	{
		return true;
	}

	vector<Card *>::iterator itVect;
	Card *pFirCard = (Card *)*vecCards.begin();
	Card *pSecCard = NULL;
	for (itVect = vecCards.begin() + 1; itVect != vecCards.end(); itVect++)
	{
		pSecCard = (Card *)*itVect;
		if ((pFirCard->nRank + 1) == pSecCard->nRank) //连续相等则continue, 存在不等则返回
		{
			pFirCard = pSecCard;
			continue;
		}
		else
		{
			return false;
		}
	}
	return true;
}

//==================================================================
//函数名： Flush
//功能：   判断是否为同花
//输入参数：    vector<Card *> vecCards:只有5个元素的容器
//返回值：    bool:是同花则返回true
//修改记录：
//==================================================================
bool CTexasPokerRule::Flush(vector<Card *> vecCards)
{
	vector<Card *>::iterator itVect;
	Card *pFirCard = (Card *)*vecCards.begin();
	Card *pSecCard = NULL;
	for (itVect = vecCards.begin() + 1; itVect != vecCards.end(); itVect++)
	{
		pSecCard = (Card *)*itVect;
		if (pFirCard->nSuit == pSecCard->nSuit) //连续相等则continue, 存在不等则返回
		{
			pFirCard = pSecCard;
			continue;
		}
		else
		{
			return false;
		}
	}
	return true;
}

//==================================================================
//函数名： RoyalFlush
//功能：   判断是否为10,J,Q,K,A
//输入参数：    vector<Card *> vecCards:只有5个元素的容器
//返回值：    bool:是则返回true
//修改记录：
//==================================================================
bool CTexasPokerRule::TtoA(vector<Card *> vecCards)
{
	if ((vecCards.at(0)->nRank == 0)
		&& (vecCards.at(1)->nRank == 9)
		&& (vecCards.at(2)->nRank == 10)
		&& (vecCards.at(3)->nRank == 11)
		&& (vecCards.at(4)->nRank == 12))
	{
		return true;
	}
	else
	{
		return false;
	}
}