#include "PublicPlace.h"

CPublicPlace::CPublicPlace()
{
	DataInit();
}

CPublicPlace::~CPublicPlace()
{
	delete[]m_pCards;
}

void CPublicPlace::DataInit()
{
	m_nCoins     = 0;
	m_nTopRecord = 0;
	memset(m_pCards, NULL, 5 * sizeof(Card *));
}

//==================================================================
//函数名： DrawCard
//功能：   摸牌动作，把每次得到的牌存入指针数组里面
//输入参数：   Card *pCard:扑克牌的数据结构
//返回值：    无
//修改记录：
//==================================================================
void CPublicPlace::DrawCard(Card *pCard)
{
	if (5 <= m_nTopRecord)
	{
		return;
	}
	m_pCards[m_nTopRecord] = pCard;
	m_nTopRecord++;
}

void CPublicPlace::Show()
{
	for (int i = 0; i < m_nTopRecord; i++)
	{
		Card *pCard = m_pCards[i];
		cout << pCard->sSuit << "\t" << pCard->cRank << endl;
	}
}