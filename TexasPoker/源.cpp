#include <iostream>
#include "Poker.h"
#include "Player.h"
#include "PublicPlace.h"
#include "TexasPokerRule.h"

using namespace std;
int main()
{
	int i;
	CPlayer *pPlayer = new CPlayer();  //创建玩家对象，但是扑克牌的初始化仍然需要从扑克牌类中得到
	CPoker  *pPoker = new CPoker();
	CPublicPlace *pPublicPlace = new CPublicPlace();
	CTexasPokerRule *pRule = new CTexasPokerRule();

	pPoker ->Shuffle();
	/*对玩家的手牌初始化*/
	for (int i = 0; i < 2; i++)
	{
		Card *pCard = pPoker->Deal();
		pPlayer->DrawCard(pCard);
		pRule->PushCard(pCard);
	}

	/*对公共区域的牌初始化*/
	for (int i = 0; i < 5; i++)   
	{
		Card *pCard = pPoker->Deal();
		pPublicPlace->DrawCard(pCard);
		pRule->PushCard(pCard);
	}
	pRule->Show();
	pRule->SortVector();
	cout << endl;
	pRule->Show();
	cout << endl << pRule->Judge();
	cin >> i;
	delete pPlayer;
	delete pPoker;
	delete pPublicPlace;
	delete pRule;
}