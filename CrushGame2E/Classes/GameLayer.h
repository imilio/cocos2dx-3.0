#ifndef _GAME_LAYER_H_
#define _GAME_LAYER_H_

#include "cocos2d.h"
#include "BirzzleManagement.h"
#include "Birzzle.h"

USING_NS_CC;

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


class CGameLayer : public Layer
{
public:
	CGameLayer();
	virtual ~CGameLayer();
	virtual bool init();
	CREATE_FUNC(CGameLayer);

	void update(float dt);
	bool onTouchBegan(Touch *touch, Event *unused);
	void onTouchMoved(Touch *touch, Event *unused);

private:
	void InitData();
	void BindSprite(int nRow, int nCol);
	void SwapBirzzle();
	void RemoveBirzzle();

	void ActionEndCallback(Node *node);
	void FillEmptyMap();

	Action* DescendActionAfterRemove(int nBlanks, CBirzzle *pBirzzle);
	Action* DropAnimation(int nRow, int nCol);
	CBirzzle* GetBirzzleFromLocation(Point *pLocation);
private:
	CBirzzleManagement *m_pBirMgmt;
	CBirzzle *m_pBirzzle;
	CBirzzle *m_pBirzzleSrc;
	CBirzzle *m_pBirzzleDst;

	Point m_LocationSrc;
	Point m_LocationDst;

	bool m_bTouchEnable;
	bool m_isAnimating;
};

#endif 