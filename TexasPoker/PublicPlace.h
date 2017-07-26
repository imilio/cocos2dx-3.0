#ifndef _PublicPlace_H_
#define _PublicPlace_H_

#include "Poker.h"

class CPublicPlace
{
public:
	CPublicPlace();
	virtual ~CPublicPlace();

	void DrawCard(Card *pCard);
	void Show();
private:
	void DataInit();

private:
	int m_nTopRecord;
	int m_nCoins;

	Card *m_pCards[5];
};




#endif 