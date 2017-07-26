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
//�������� DateInit
//���ܣ�   ����ڲ����ݳ�ʼ��
//���������    ��
//����ֵ��    ��
//�޸ļ�¼��
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
//�������� DrawCard
//���ܣ�   ���ƶ�������ÿ�εõ����ƴ���ָ����������
//���������   Card *pCard:�˿��Ƶ����ݽṹ
//����ֵ��    ��
//�޸ļ�¼��
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
//�������� AddCoin
//���ܣ�   ���ӽ������
//���������    int nAmount: �ӽ�ҵ�����
//����ֵ��    ��
//�޸ļ�¼��
//==================================================================
void CPlayer::AddCoin(int nAmount)
{
	m_nCoins += nAmount;
}

//==================================================================
//�������� MinusCoin
//���ܣ�   ���ٽ������
//���������    int nAmount: ����ҵ�����
//����ֵ��    ��
//�޸ļ�¼��
//==================================================================
void CPlayer::MinusCoin(int nAmount)
{
	m_nCoins -= nAmount;
}


