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
//�������� DrawCard
//���ܣ�   ���ƶ�������ÿ�εõ����ƴ���ָ����������
//���������   Card *pCard:�˿��Ƶ����ݽṹ
//����ֵ��    ��
//�޸ļ�¼��
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