#include "Poker.h"

CPoker::~CPoker()
{
	delete[]m_pCards;
}
//==================================================================
//函数名： Shuffle
//功能：   初始化牌堆工作，并存储于m_vecPackOfCards
//输入参数：    无
//返回值：    无
//修改记录：
//==================================================================
void CPoker::Shuffle()
{
	int nCard = 0;

	int nCardRecorder[52] = { 0 };
	

	srand((unsigned)time(NULL));

	for (int i = 0; i < CARDS; i++)
	{
		
		nCard = Randmod(CARDS);    //从0到51的随机数
		if (1 == nCardRecorder[nCard])
		{
			i--;
			continue;
		}
		else
		{
			Card *structCard = new Card();

			nCardRecorder[nCard] = 1;

			structCard->nCard = nCard;
			structCard->nSuit = nCard / 13;
			structCard->nRank = nCard % 13;
			structCard->sSuit = Suits[nCard / 13];
			structCard->cRank = Ranks[nCard % 13];

			cout << i << "\t"<< nCard << "\t" << Suits[nCard / 13] <<"\t" << Ranks[nCard % 13] <<endl;

			m_nTopRecord = i;
			m_pCards[i] = structCard; 
		}
	}
}

//==================================================================
//函数名： Deal
//功能：   取出牌堆上的第一张牌
//输入参数：    无
//返回值：    扑克牌的结构体的指针
//修改记录：
//==================================================================
Card* CPoker::Deal()
{
	Card *pCard = m_pCards[m_nTopRecord];

	m_pCards[m_nTopRecord] = NULL;
	m_nTopRecord--;

	return pCard;
}
