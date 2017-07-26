#include "TexasPokerRule.h"

//==================================================================
//�������� CompareOfVector
//���ܣ�   ָ�����ڽṹ���nRank��������
//���������    ��
//����ֵ��    ��
//�޸ļ�¼��
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
//�������� SortVector
//���ܣ�   ��m_vecCards��������ĵ�������
//���������    ��
//����ֵ��    ��
//�޸ļ�¼��
//==================================================================
void CTexasPokerRule::SortVector()
{
	sort(m_vecCards.begin(), m_vecCards.end(), CompareOfVector);
}

//==================================================================
//�������� Judgement
//���ܣ�   �԰���5���Ƶ�����vector���ж��Ƿ��������
//���������    ��
//����ֵ��    int nCount:����������ȵĶ���
//�޸ļ�¼��
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
	else if (5 < m_vecCards.size())    //����5�Ϳ�ʼ��������ж�
	{
		return this->Permutation(m_vecTempForJudgement);
	}
	
	

}

Patterns CTexasPokerRule::Judgement()
{
	if (this->TtoA(m_vecTempForJudgement) && this->Flush(m_vecTempForJudgement))  //�ʼ�ͬ��˳
	{
		return ROYAL_FLUSH;
	}
	else if (this->Straight(m_vecTempForJudgement) && this->Flush(m_vecTempForJudgement))  //ͬ��˳
	{
		return STRAIGHT_FLUSH;
	}
	else if (this->Quads(m_vecTempForJudgement))   //4��
	{
		return QUADS;
	}
	else if (this->Flush(m_vecTempForJudgement))  //ͬ��
	{
		return FLUSH;
	}
	else if (this->Straight(m_vecTempForJudgement))  //˳��
	{
		return STRAIGHT;
	}
	else if (this->Trips(m_vecTempForJudgement))    
	{
		if (this->Pair(m_vecTempForJudgement))    //�ж�ʣ�µ��������ǲ���һ��
		{
			return FULL_HOUSE;       //��«
		}
		else
		{
			return TRIPS;    //����
		}
	}
	else if (this->Pair(m_vecTempForJudgement))
	{
		if (this->Pair(m_vecTempForJudgement))
		{
			return TWO_PAIR;  //����
		}
		else
		{
			return ONE_PAIR;  //һ��
		}
	}
	return NO_PAIR;   //����
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
//�������� Pair
//���ܣ�   �ж���ʱ�洢vector����������Ƶĵ����Ƿ����
//���������    ��
//����ֵ��    bool:�����Ƶĵ�������򷵻�true
//�޸ļ�¼��
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
//�������� Trips
//���ܣ�   �ж��Ƿ�Ϊ����
//���������    ��
//����ֵ��    bool:���������򷵻�true
//�޸ļ�¼��
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
//�������� Quads
//���ܣ�   �ж��Ƿ�Ϊ����
//���������    ��
//����ֵ��    bool:���������򷵻�true
//�޸ļ�¼��
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
//�������� Straight
//���ܣ�   �ж��Ƿ�Ϊ˳��
//���������    vector<Card *> vecCards:ֻ��5��Ԫ�ص�����
//����ֵ��    bool:��˳���򷵻�true
//�޸ļ�¼��
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
		if ((pFirCard->nRank + 1) == pSecCard->nRank) //���������continue, ���ڲ����򷵻�
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
//�������� Flush
//���ܣ�   �ж��Ƿ�Ϊͬ��
//���������    vector<Card *> vecCards:ֻ��5��Ԫ�ص�����
//����ֵ��    bool:��ͬ���򷵻�true
//�޸ļ�¼��
//==================================================================
bool CTexasPokerRule::Flush(vector<Card *> vecCards)
{
	vector<Card *>::iterator itVect;
	Card *pFirCard = (Card *)*vecCards.begin();
	Card *pSecCard = NULL;
	for (itVect = vecCards.begin() + 1; itVect != vecCards.end(); itVect++)
	{
		pSecCard = (Card *)*itVect;
		if (pFirCard->nSuit == pSecCard->nSuit) //���������continue, ���ڲ����򷵻�
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
//�������� RoyalFlush
//���ܣ�   �ж��Ƿ�Ϊ10,J,Q,K,A
//���������    vector<Card *> vecCards:ֻ��5��Ԫ�ص�����
//����ֵ��    bool:���򷵻�true
//�޸ļ�¼��
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