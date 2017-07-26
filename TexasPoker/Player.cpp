#include "Player.h"

CPlayer::CPlayer()
{
	DateInit();
}

CPlayer::~CPlayer()
{
	delete []m_pCards;
}
//==================================================================
//函数名： DateInit
//功能：   玩家内部数据初始化
//输入参数：    无
//返回值：    无
//修改记录：
//==================================================================
void CPlayer::DateInit()
{
	m_nCoins     = 0;
	m_nTopRecord = 0;
	memset(m_pCards, NULL, 2 * sizeof(Card *));
}

void CPlayer::Show()
{
	for (int i = 0; i < m_nTopRecord; i++)
	{
		Card *pCard = m_pCards[i];
		cout << pCard->sSuit<<"\t"<<pCard->cRank<<endl;
	}
}
//==================================================================
//函数名： DrawCard
//功能：   摸牌动作，把每次得到的牌存入指针数组里面
//输入参数：   Card *pCard:扑克牌的数据结构
//返回值：    无
//修改记录：
//==================================================================
void CPlayer::DrawCard(Card *pCard)
{
	if (2 <= m_nTopRecord)
	{
		return;
	}
	m_pCards[m_nTopRecord] = pCard;
	m_nTopRecord++;
}

//==================================================================
//函数名： AddCoin
//功能：   增加金币数量
//输入参数：    int nAmount: 加金币的数量
//返回值：    无
//修改记录：
//==================================================================
void CPlayer::AddCoin(int nAmount)
{
	m_nCoins += nAmount;
}

//==================================================================
//函数名： MinusCoin
//功能：   减少金币数量
//输入参数：    int nAmount: 减金币的数量
//返回值：    无
//修改记录：
//==================================================================
void CPlayer::MinusCoin(int nAmount)
{
	m_nCoins -= nAmount;
}


