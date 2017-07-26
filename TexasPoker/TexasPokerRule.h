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
	Patterns Permutation(vector<Card *> &vecCards);   //排列并判断
	bool Pair(vector<Card *> &vecCards);   //一对
	bool Trips(vector<Card *> &vecCards);   //三条
	bool Quads(vector<Card *> vecCards);  //四条
	bool Straight(vector<Card *> vecCards);  //顺子
	bool Flush(vector<Card *> vecCards);   //同花
	bool TtoA(vector<Card *> vecCards);  //仅判断是否为10,J,Q,K,A

private:
	CPoker *m_pPoker;
	vector<Card *> m_vecCards;
	vector<Card *> m_vecTempForJudgement;
};


#endif