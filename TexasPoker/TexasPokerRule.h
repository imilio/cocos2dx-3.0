#ifndef _TexasPokerRule_H_
#define _TexasPokerRule_H_

#include "Poker.h"
#include <vector>
#include <algorithm>

using namespace std;

enum Patterns { NO_PAIR, ONE_PAIR, TWO_PAIR, TRIPS, STRAIGHT, FLUSH, FULL_HOUSE, QUADS, STRAIGHT_FLUSH, ROYAL_FLUSH };

class CTexasPokerRule
{
public:
	/*CTexasPokerRule();
	virtual ~CTexasPokerRule();*/

	void PushCard(Card *pCard);
	void SortVector();
	Patterns  Judge();
	void Show();

private:
	Patterns Judgement();
	Patterns Permutation(vector<Card *> &vecCards);   //���в��ж�
	bool Pair(vector<Card *> &vecCards);   //һ��
	bool Trips(vector<Card *> &vecCards);   //����
	bool Quads(vector<Card *> vecCards);  //����
	bool Straight(vector<Card *> vecCards);  //˳��
	bool Flush(vector<Card *> vecCards);   //ͬ��
	bool TtoA(vector<Card *> vecCards);  //���ж��Ƿ�Ϊ10,J,Q,K,A

private:
	CPoker *m_pPoker;
	vector<Card *> m_vecCards;
	vector<Card *> m_vecTempForJudgement;
};


#endif