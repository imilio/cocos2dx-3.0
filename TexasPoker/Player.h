#ifndef _Player_H_
#define _Player_H_

#include "Poker.h"
#include <iostream>
using namespace std;

class CPlayer
{
public:
	CPlayer();
	virtual ~CPlayer();
	
	void Show();

	void DrawCard(Card *pCard);

	void AddCoin(int nAmount);
	void MinusCoin(int nAmount);
	int  GetCoinAmount();

private:
	void DateInit();

private:
	int m_nCoins;
	int m_nTopRecord;
	Card *m_pCards[2];

};

#endif 