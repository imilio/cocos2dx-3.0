#include <iostream>
#include "Poker.h"
#include "Player.h"
#include "PublicPlace.h"
#include "TexasPokerRule.h"

using namespace std;
int main()
{
	int i;
	CPlayer *pPlayer = new CPlayer();  //������Ҷ��󣬵����˿��Ƶĳ�ʼ����Ȼ��Ҫ���˿������еõ�
	CPoker  *pPoker = new CPoker();
	CPublicPlace *pPublicPlace = new CPublicPlace();
	CTexasPokerRule *pRule = new CTexasPokerRule();

	pPoker ->Shuffle();
	/*����ҵ����Ƴ�ʼ��*/
	for (int i = 0; i < 2; i++)
	{
		Card *pCard = pPoker->Deal();
		pPlayer->DrawCard(pCard);
		pRule->PushCard(pCard);
	}

	/*�Թ���������Ƴ�ʼ��*/
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