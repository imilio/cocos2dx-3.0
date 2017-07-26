#ifndef _Poker_H_
#define _Poker_H_

#include <ctime>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

#define Randmod(x) (rand() % x)

#define CARDS 52

const string Suits[4] = { "Spade", "Heart", "Club", "Diamond" };

const char Ranks[13] = { 'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K' };

struct Card
{
	int    nCard;
	int    nRank;
	int    nSuit;
	char   cRank;
	string sSuit;
};

class CPoker
{
public:
	virtual ~CPoker();
	void  Shuffle();  //Ï´ÅÆ
	Card*  Deal();   //·¢ÅÆ

private:
	int m_nTopRecord;   //¼ÇÂ¼ÅÆ¶Ñ¶¥²¿Î»ÖÃ
	Card *m_pCards[CARDS];
};



#endif