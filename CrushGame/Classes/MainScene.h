#ifndef _MAINSCENE_H_
#define _MAINSCENE_H_

#include "cocos2d.h"
using namespace cocos2d;
USING_NS_CC;

#define TOTAL_SP 7

// 获取精灵 普通
static const char *sprNormal[TOTAL_SP] = {
	"blue.png",
	"pink.png",
	"red.png",
	"white.png",
	"yellow.png",
	"purple.png",
	"green.png"
};

//界面相关
#define SPRITE_WIDTH 84
#define SPRITE_HEIGHT 88

#define SIDE 23
#define SPACE 2
#define BUTTOM 115

#define ROWS 8
#define COLS 7

class CBirzzle;
class CMainScene : public Layer
{
public:
	CMainScene();
	static Scene * createScene();
	virtual bool init();
	CREATE_FUNC(CMainScene);
	void update(float dt);
	bool onTouchBegan(Touch *touch, Event *unused);
	void onTouchMoved(Touch *touch, Event *unused);

	void GameInit();
	void ActionEndCallback(Node *node);
	void DescendActionEndCallback(Node *node);
private:
	Sprite *m_pBgSprite;

	CBirzzle *m_pBirzzle;
	CBirzzle *m_pBirzzleMap[ROWS][COLS];

	CBirzzle *m_pSrcBirzzle;
	CBirzzle *m_pDstBirzzle;

	Point m_SrcLocation;
	Point m_DstLocation;

	bool m_bTouchEnable;
	bool m_isAnimationing;

	Action* DescendAction(int nDstRow, int nDstCol);
	Action* DescendActionAfterRemove(int nBlanks, CBirzzle *pBirzzle);
	CBirzzle* GetBirzzleFromLocation(Point *pLocation);

	void CheckAndRemoveChain();
	void GetColChain(CBirzzle *pBirzzle, std::list<CBirzzle *> &chainList);
	void GetRowChain(CBirzzle *pBirzzle, std::list<CBirzzle *> &chainList);
	void SwapSprite();
	void RemoveBirzzle();
	void FillEmptyMap();
	void CreateSprite(int nDstRow, int nDstCol, int nZOrder);
};


#endif