#include "Poker.h"

CPoker::~CPoker()
{
	delete[]m_pCards;
}
//==================================================================
//�������� Shuffle
//���ܣ�   ��ʼ���ƶѹ��������洢��m_vecPackOfCards
//���������    ��
//����ֵ��    ��
//�޸ļ�¼��
//==================================================================
void CPoker::Shuffle()
{
	int nCard = 0;

	int nCardRecorder[52] = { 0 };
	

	srand((unsigned)time(NULL));

	for (int i = 0; i < CARDS; i++)
	{
		
		nCard = Randmod(CARDS);    //��0��51�������
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
//�������� Deal
//���ܣ�   ȡ���ƶ��ϵĵ�һ����
//���������    ��
//����ֵ��    �˿��ƵĽṹ���ָ��
//�޸ļ�¼��
//==================================================================
Card* CPoker::Deal()
{
	Card *pCard = m_pCards[m_nTopRecord];

	m_pCards[m_nTopRecord] = NULL;
	m_nTopRecord--;

	return pCard;
}
